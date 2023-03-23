//==========================================
//
//ブーメランプログラム[player.cpp]
//Author:石原颯馬  （影関係：平澤詩苑）
//
//==========================================
#include "main.h"
#include "_R.N.Lib\R.N.Lib.h"
#include "boomerang.h"
#include "target.h"
#include "chr_player.h"
#include "_R.N.Lib\Basis\Other\sound.h"

//マクロ
#define BOOMERANG_SETUP_NUM			(2)					//ブーメランセットアップ番号
#define BOOMERANG_ONE_ROTATE		(15)				//ブーメラン自体が1周するのにかかるフレーム数（2PIで割る）
#define BOOMERANG_THROW_ROT			(0.10f * D3DX_PI)	//投げる角度
#define BOOMERANG_ROTTOTAL_MAX		(1.15f * D3DX_PI)	//回転した量の合計の最大値
#define BOOMERANG_MOVE_SPEED		(4.5f)				//ブーメランの移動速度
#define BOOMERANG_ADDROTFORCE		(0.001f)			//回転力増加・減少量
#define BOOMERANG_ROTFORCE_MAX		(0.1f)				//最大
#define BOOMERANG_STRAIGHT_END		(30)				//直線移動終了時間
#define BOOMERANG_DESTROY_LINE		(300.0f)			//ブーメランがどっか飛んでいく（消す）ライン

#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//角度を-PI~PIに修正

//プロト
void CollisionBoomerangEnemy(int nBoomerangNum);
void CollisionBoomerangPlayer(int nBoomerangNum);

//グローバル
Boomerang g_aBoomerang[MAX_USE_BOOMERANG] = {};

//========================
//初期化処理
//========================
void InitBoomerang(void)
{
	//変数初期化
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_BOOMERANG; nCntBoomerang++)
	{
		//変数初期化
		g_aBoomerang[nCntBoomerang].posOld = g_aBoomerang[nCntBoomerang].pos = INITD3DXVECTOR3;
		g_aBoomerang[nCntBoomerang].move = INITD3DXVECTOR3;
		g_aBoomerang[nCntBoomerang].rot = INITD3DXVECTOR3;
		g_aBoomerang[nCntBoomerang].fRotForce = 0.0f;
		g_aBoomerang[nCntBoomerang].bEndRotate = false;

		// 部品(3D)の初期化処理
		InitParts3DInfo(&g_aBoomerang[nCntBoomerang].partsInfo, BOOMERANG_SETUP_NUM);

		//使用有無初期化
		g_aBoomerang[nCntBoomerang].bUse = false;
	}
}

//========================
//終了処理
//========================
void UninitBoomerang(void)
{
	
}

//========================
//更新処理
//========================
void UpdateBoomerang(void)
{
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_BOOMERANG; nCntBoomerang++)
	{
		if (g_aBoomerang[nCntBoomerang].bUse == true)
		{
			//[内部]回転する
			g_aBoomerang[nCntBoomerang].nCounterStraight++;

			if (g_aBoomerang[nCntBoomerang].nCounterStraight > BOOMERANG_STRAIGHT_END)
			{
				if (g_aBoomerang[nCntBoomerang].throwType == THROWTYPE_LEFT)
				{
					g_aBoomerang[nCntBoomerang].fRotForce += BOOMERANG_ADDROTFORCE;

					//最大値を過ぎたら減らす
					if (g_aBoomerang[nCntBoomerang].fRotForce > BOOMERANG_ROTFORCE_MAX)
					{
						g_aBoomerang[nCntBoomerang].bReturn = true;
					}

					if (!g_aBoomerang[nCntBoomerang].bEndRotate)
					{
						g_aBoomerang[nCntBoomerang].rot.y += g_aBoomerang[nCntBoomerang].fRotForce;
						g_aBoomerang[nCntBoomerang].fRotTotal += g_aBoomerang[nCntBoomerang].fRotForce;
						if (g_aBoomerang[nCntBoomerang].fRotTotal >= BOOMERANG_ROTTOTAL_MAX)
						{
							g_aBoomerang[nCntBoomerang].bEndRotate = true;
						}
					}
				}
				else
				{
					g_aBoomerang[nCntBoomerang].fRotForce += BOOMERANG_ADDROTFORCE;

					//最大値を過ぎたら減らす
					if (g_aBoomerang[nCntBoomerang].fRotForce > BOOMERANG_ROTFORCE_MAX)
					{
						g_aBoomerang[nCntBoomerang].bReturn = true;
					}

					if (!g_aBoomerang[nCntBoomerang].bEndRotate)
					{
						g_aBoomerang[nCntBoomerang].rot.y -= g_aBoomerang[nCntBoomerang].fRotForce;
						g_aBoomerang[nCntBoomerang].fRotTotal += g_aBoomerang[nCntBoomerang].fRotForce;
						if (g_aBoomerang[nCntBoomerang].fRotTotal >= BOOMERANG_ROTTOTAL_MAX)
						{
							g_aBoomerang[nCntBoomerang].bEndRotate = true;
						}
					}
				}
				g_aBoomerang[nCntBoomerang].rot.y = FIX_ROT(g_aBoomerang[nCntBoomerang].rot.y);
			}

			//[内部]移動する
			g_aBoomerang[nCntBoomerang].move.x = -sinf(g_aBoomerang[nCntBoomerang].rot.y) * BOOMERANG_MOVE_SPEED;
			g_aBoomerang[nCntBoomerang].move.y = 0.0f;
			g_aBoomerang[nCntBoomerang].move.z = cosf(g_aBoomerang[nCntBoomerang].rot.y) * BOOMERANG_MOVE_SPEED;

			g_aBoomerang[nCntBoomerang].pos += g_aBoomerang[nCntBoomerang].move;

			//[内部]当たり判定
			CollisionBoomerangEnemy(nCntBoomerang);
			
			//帰ってきている時だけ回収処理を行う
			if (g_aBoomerang[nCntBoomerang].bReturn)
			{
				CollisionBoomerangPlayer(nCntBoomerang);
			}

			//[見た目]ブーメランの回転処理
			g_aBoomerang[nCntBoomerang].partsInfo.pos = g_aBoomerang[nCntBoomerang].pos;
			g_aBoomerang[nCntBoomerang].partsInfo.rot.y = FIX_ROT(g_aBoomerang[nCntBoomerang].partsInfo.rot.y + ((2 * D3DX_PI) / BOOMERANG_ONE_ROTATE));

			//画面外に出たら消す
			if (fabs(g_aBoomerang[nCntBoomerang].pos.x) > BOOMERANG_DESTROY_LINE || g_aBoomerang[nCntBoomerang].pos.z < -BOOMERANG_DESTROY_LINE)
			{
				g_aBoomerang[nCntBoomerang].bUse = false;
			}
			else
			{
				// 部品(3D)の更新処理
				UpdateParts3DInfo(&g_aBoomerang[nCntBoomerang].partsInfo);
			}
		}
	}
}

//========================
//描画処理
//========================
void DrawBoomerang(void)
{
	
}

//========================
//ブーメラン配置処理
//========================
void SetBoomerang(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_BOOMERANG; nCntBoomerang++)
	{
		//使用されていないか確認
		if (g_aBoomerang[nCntBoomerang].bUse == false)
		{
			//変数初期化
			g_aBoomerang[nCntBoomerang].posOld = g_aBoomerang[nCntBoomerang].pos = pos;
			g_aBoomerang[nCntBoomerang].rot = rot;
			g_aBoomerang[nCntBoomerang].rot.y *= -1;
			g_aBoomerang[nCntBoomerang].rot.y -= BOOMERANG_THROW_ROT;
			g_aBoomerang[nCntBoomerang].move = INITD3DXVECTOR3;
			g_aBoomerang[nCntBoomerang].nCounterStraight = 0;
			g_aBoomerang[nCntBoomerang].fRotForce = 0.0f;
			g_aBoomerang[nCntBoomerang].fRotTotal = 0.0f;
			g_aBoomerang[nCntBoomerang].bEndRotate = false;
			g_aBoomerang[nCntBoomerang].bReturn = false;
			
			//角度に応じて投げ方向設定
			if (rot.y >= 0.0f)
			{
				g_aBoomerang[nCntBoomerang].throwType = THROWTYPE_LEFT;
			}
			else
			{
				g_aBoomerang[nCntBoomerang].throwType = THROWTYPE_RIGHT;
			}

			// 部品(3D)の初期化処理
			InitParts3DInfo(&g_aBoomerang[nCntBoomerang].partsInfo, BOOMERANG_SETUP_NUM);

			//使用している状態にする
			g_aBoomerang[nCntBoomerang].bUse = true;

			//配置終了
			break;
		}
	}
}

//========================
//ブーメラン情報取得処理
//========================
Boomerang *GetBoomerang(void)
{
	return &g_aBoomerang[0];
}

//========================
//ブーメランと敵の当たり判定
//========================
void CollisionBoomerangEnemy(int nBoomerangNum)
{
	Target* pTarget = GetTarget();

	for (int nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++,pTarget++)
	{
		if (pTarget->bUse == true)
		{
			float fDistance = FindDistanceLookDown(pTarget->pos, g_aBoomerang[nBoomerangNum].pos);

			if (fDistance < BOOMERANG_HIT_RADIUS + GetTargetType()->fWidth * 0.5f)
			{//当たった
				if (pTarget->type == TARGET_D)
				{
					g_aBoomerang[nCntTarget].bUse = false;
				}
				else
				{
					//スコア足す
					GetChr_player()->nScore += GetTargetType()->nScore;

					//バルス
					pTarget->bUse = false;

					//ヒットサウンド再生
					PlaySound(5);
				}
			}
		}
	}
}

//========================
//ブーメランとプレイヤーの当たり判定
//========================
void CollisionBoomerangPlayer(int nBoomerangNum)
{
	Chr_player *pPlayer = GetChr_player();

	float fDistance = FindDistanceLookDown(pPlayer->partsInfo.pos, g_aBoomerang[nBoomerangNum].pos);

	if (fDistance < BOOMERANG_HIT_RADIUS + PLAYER_HIT_RADIUS)
	{//当たった
		//ブーメラン増やす
		GetChr_player()->nBoomerang++;

		//ブーメランキャッチ
		g_aBoomerang[nBoomerangNum].bUse = false;

		//キャッチサウンド再生
		PlaySound(6);
	}
}
