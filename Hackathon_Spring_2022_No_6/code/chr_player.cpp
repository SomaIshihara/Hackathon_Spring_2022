//========================================
// 
// CHR:プレイヤーの処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** chr_player.cpp ***
//========================================
#include <stdio.h>
#include "main.h"

#include "Mode\md_game.h"
#include "chr_player.h"	// CHR:プレイヤー
#include "boomerang.h"
// R.N.Lib
#include "_R.N.Lib/R.N.Lib.h"

//****************************************
// マクロ定義
//****************************************
// CHR:プレイヤーの初期向き
#define CHR_PLAYER_INIT_ROT D3DXVECTOR3(0.0f,D3DX_PI,0.0f)
// CHR:プレイヤーの注視点の相対位置の移動倍率
#define CHR_PLAYER_RELATIVE_POS_R_MOVE_DIAMETER (0.25f)
// CHR:プレイヤーのモデルのセットアップ番号
#define CHR_PLAYER_MODEL_SETUP (3)
// CHR:プレイヤーの移動量
#define CHR_PLAYER_MOVE (1.0f)
// CHR;プレイヤーの移動幅
#define CHR_PLAYER_MOVEWIDTH (56.0f)
// CHR;プレイヤーの移動奥行き
#define CHR_PLAYER_MOVEDEPTH (8.0f)
// CHR:プレイヤーの回転量
#define CHR_PLAYER_SPIN (0.05f)
// CHR:プレイヤーの奥行き
#define CHR_PLAYER_DEPTH (80.0f)

//****************************************
// 列挙型の定義
//****************************************
// モーション番号
typedef enum 
{
	CHR_PLAYER_MOTION_WAIT,
	CHR_PLAYER_MOTION_MOVE,
	CHR_PLAYER_MOTION_SLOW,
	CHR_PLAYER_MOTION_MAX,
}CHR_PLAYER_MOTION;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 取得 ***
// CHR:プレイヤーのパラメーターの初期値を返す
void InitParameterChr_player(Chr_player *pChr);

//****************************************
// グローバル宣言
//****************************************
// CHR:プレイヤーの情報
Chr_player g_chr_player;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================
//========================================
// InitParameterChr_player関数 - CHR:プレイヤーのパラメーターの初期値を返す -
//========================================
void InitParameterChr_player(Chr_player *pChr)
{
	// 部品管理のパラメーター初期化
	InitParts3DInfo(&pChr->partsInfo, CHR_PLAYER_MODEL_SETUP);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 基本接続 *** |--------------------
//============================================================
//========================================
// InitChr_player関数 - CHR:プレイヤーの初期化処理 -
//========================================
void InitChr_player(void)
{
	// CHR:プレイヤーの情報のポインタ
	Chr_player *pChr = &g_chr_player;

	// パラメーターの初期化
	InitParameterChr_player(pChr);
}

//========================================
// UpdateChr_player関数 - CHR:プレイヤーの更新処理 -
//========================================
void UpdateChr_player(void)
{
	// CHR:プレイヤーの情報のポインタ
	Chr_player *pChr = &g_chr_player;
	// プレイヤーのセットアップ情報
	ModelSetUp setUp = GetModelSetUp(CHR_PLAYER_MODEL_SETUP);

	// 部品(3D)の更新処理
	UpdateParts3DInfo(&pChr->partsInfo);

	if (GetMd_game()->state == MD_GAME_STATE_RANKING || GetMd_game()->state == MD_GAME_STATE_RESULT)
	{
		return;
	}

	// 移動
	if (GetStick().aTplDiameter[STICK_TYPE_LEFT] > 0.01f)
	{
		// モーションを移動に設定
		pChr->partsInfo.nMotion = CHR_PLAYER_MOTION_MOVE;

		// 目標向きにスティックの角度を代入
		float fAngle = -GetStick().aAngle[STICK_TYPE_LEFT] + D3DX_PI;

		// 移動
		pChr->partsInfo.pos.x += sinf(fAngle) * CHR_PLAYER_MOVE;
		pChr->partsInfo.pos.z += cosf(fAngle) * CHR_PLAYER_MOVE;

		// 移動制御
		D3DXVECTOR3 *pPos = &pChr->partsInfo.pos;
		if (pPos->x <= -CHR_PLAYER_MOVEWIDTH) {
			pPos->x = -CHR_PLAYER_MOVEWIDTH;
		}
		else if (pPos->x >= CHR_PLAYER_MOVEWIDTH) {
			pPos->x = CHR_PLAYER_MOVEWIDTH;
		}

		if (pPos->z <= -CHR_PLAYER_MOVEDEPTH) {
			pPos->z = -CHR_PLAYER_MOVEDEPTH;
		}
		else if (pPos->z >= CHR_PLAYER_MOVEDEPTH) {
			pPos->z = CHR_PLAYER_MOVEDEPTH;
		}
	}
	else 
	{
		// モーションを待機に設定
		pChr->partsInfo.nMotion = CHR_PLAYER_MOTION_WAIT;
	}

	// 回転
	float fTplDiameter = GetStick().aTplDiameter[STICK_TYPE_RIGHT];
	if (fTplDiameter > 0.01f) 
	{
		if (GetStick().aAnglePress[STICK_TYPE_RIGHT][STICK_ANGLE_LEFT])
		{
			pChr->partsInfo.rot.y -= CHR_PLAYER_SPIN * fTplDiameter;
		}
		else if(GetStick().aAnglePress[STICK_TYPE_RIGHT][STICK_ANGLE_RIGHT])
		{
			pChr->partsInfo.rot.y += CHR_PLAYER_SPIN * fTplDiameter;
		}

		// 向きを制御
		ControlAngle(&pChr->partsInfo.rot.y);
	}

	if ((GetButtonTrigger(BUTTON_RIGHT_TRIGGER) || GetButtonTrigger(BUTTON_RIGHT_SHOULDER)))// && (pChr->nBoomerang > 0)
	{// ブーメラン投げ
		SetBoomerang(pChr->partsInfo.pos, pChr->partsInfo.rot);
		// ブーメラン数減算
		pChr->nBoomerang--;
	}

	// カメラ追従
	GetCamera3D()->posR = pChr->partsInfo.pos * 0.1f;
	GetCamera3D()->posR.z += CHR_PLAYER_DEPTH;

	// 衝突判定に必要な情報を作成
	CollisionInfo myCollInfo =
	{
		&pChr->partsInfo.pos,			// 現在の位置のポインタ
		pChr->partsInfo.pos,			// 過去の位置
		NULL,							// 移動量のポインタ
		&pChr->partsInfo.rot,			// 現在の向きのポインタ
		pChr->partsInfo.rot,			// 過去の向き
		&pChr->partsInfo,				// 部品管理情報
		&setUp.partsSet,				// 部品設定情報
		&setUp.hitTestSet.aHitTest[0],	// 当たり判定の情報
		(COLLCHK_MODE)0,				// 衝突チェックのモード
	};
}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================
//========================================
// GetChr_player関数 - CHR:プレイヤーの情報のポインタを取得 -
//========================================
Chr_player *GetChr_player(void)
{
	return &g_chr_player;
}