//==========================================
//
//プレイヤープログラム[player.cpp]
//Author:石原颯馬  （影関係：平澤詩苑）
//
//==========================================
#include "main.h"
#include "_R.N.Lib\R.N.Lib.h"
#include "boomerang.h"

//マクロ
#define BOOMERANG_SETUP_NUM			(2)		//ブーメランセットアップ番号
#define BOOMERANG_ONE_ROTATE		(15)	//ブーメラン自体が1周するのにかかるフレーム数（2PIで割る）
#define BOOMERANG_MOVE_ROT			((1.0f / 60) * D3DX_PI)	//ブーメランの移動の回転速度
#define BOOMERANG_MOVE_SPEED		(8.0f)	//ブーメランの移動速度
#define BOOMERANG_ADDROTFORCE		(0.02f)	//回転力増加・減少量
#define BOOMERANG_ROTFORCE_MAX		(0.25f)		//最大
#define BOOMERANG_STRAIGHT_END		(40)	//直線移動終了時間

#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//角度を-PI~PIに修正

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
		g_aBoomerang[nCntBoomerang].bEndForce = false;

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
				if (!g_aBoomerang[nCntBoomerang].bReturn) 
				{
					g_aBoomerang[nCntBoomerang].fRotForce += BOOMERANG_ADDROTFORCE;
				}
				else 
				{
					g_aBoomerang[nCntBoomerang].fRotForce -= BOOMERANG_ADDROTFORCE;

					if (g_aBoomerang[nCntBoomerang].fRotForce < 0.0f) 
					{
						g_aBoomerang[nCntBoomerang].fRotForce = 0.0f;
					}
				}

				//最大値を過ぎたら減らす
				if (g_aBoomerang[nCntBoomerang].fRotForce > BOOMERANG_ROTFORCE_MAX)
				{
					g_aBoomerang[nCntBoomerang].bReturn = true;
				}

				g_aBoomerang[nCntBoomerang].rot.y += g_aBoomerang[nCntBoomerang].fRotForce;

				g_aBoomerang[nCntBoomerang].rot.y = FIX_ROT(g_aBoomerang[nCntBoomerang].rot.y);
			}

			//[内部]移動する
			g_aBoomerang[nCntBoomerang].move.x = -sinf(g_aBoomerang[nCntBoomerang].rot.y) * BOOMERANG_MOVE_SPEED;
			g_aBoomerang[nCntBoomerang].move.y = 0.0f;
			g_aBoomerang[nCntBoomerang].move.z = cosf(g_aBoomerang[nCntBoomerang].rot.y) * BOOMERANG_MOVE_SPEED;

			g_aBoomerang[nCntBoomerang].pos += g_aBoomerang[nCntBoomerang].move;

			//[内部]ブーメランとオブジェクトの当たり判定
			CollisionInfo collInfo;
			collInfo.pPos = &g_aBoomerang[nCntBoomerang].pos;
			collInfo.posOld;
			collInfo.pRot;
			collInfo.rotOld;
			collInfo.fScale = 1.0f;
			collInfo.mode = COLLCHK_MODE_NORMAL;
			collInfo.pMove = NULL;
			collInfo.pHitTest = &GetModelSetUp(BOOMERANG_SETUP_NUM).hitTestSet.aHitTest[0];



			//[見た目]ブーメランの回転処理
			g_aBoomerang[nCntBoomerang].partsInfo.pos = g_aBoomerang[nCntBoomerang].pos;
			g_aBoomerang[nCntBoomerang].partsInfo.rot.y = FIX_ROT(g_aBoomerang[nCntBoomerang].partsInfo.rot.y + ((2 * D3DX_PI) / BOOMERANG_ONE_ROTATE));

			//画面外に出たら消す
			if (fabs(g_aBoomerang[nCntBoomerang].pos.x) > 450.0f || fabs(g_aBoomerang[nCntBoomerang].pos.z) > 450.0f)
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
			g_aBoomerang[nCntBoomerang].move = INITD3DXVECTOR3;
			g_aBoomerang[nCntBoomerang].nCounterStraight = 0;
			g_aBoomerang[nCntBoomerang].fRotForce = 0.0f;
			g_aBoomerang[nCntBoomerang].bEndForce = false;
			g_aBoomerang[nCntBoomerang].bReturn = false;

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