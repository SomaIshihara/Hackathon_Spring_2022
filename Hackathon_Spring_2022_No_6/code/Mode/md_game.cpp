//========================================
// 
// MD:ゲームの処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** md_game.cpp ***
//========================================
#include "md_game.h"
#include "../_R.N.Lib/R.N.Lib.h"

//****************************************
// マクロ定義
//****************************************
//========== *** 状態関連 ***
// 初期の状態
#define INIT_STATE (MD_GAME_STATE_NORMAL)

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 取得 ***
// MD:ゲームのパラメーター初期化
void InitParameterMd_game(Md_game *pMd);

//****************************************
// グローバル変数宣言
//****************************************
Md_game g_md_game;	// MD:ゲームの情報

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 基本接続 *** |--------------------
//============================================================

//========================================
// StartMd_gameState関数 - MD:ゲーム画面の状態に応じた開始処理 -
//========================================
void StartMd_gameState(void)
{
	// MD:ゲーム画面の情報のポインタ
	Md_game *pMd = &g_md_game;

	switch (pMd->state)
	{
	case MD_GAME_STATE_NORMAL:

		break;
	}
}

//========================================
// EndMd_gameState関数 - MD:ゲーム画面の状態に応じた終了処理 -
//========================================
void EndMd_gameState(void)
{
	// MD:ゲーム画面の情報のポインタ
	Md_game *pMd = &g_md_game;

	switch (pMd->state)
	{
	case MD_GAME_STATE_NORMAL:

		break;
	}
}

//========================================
// UpdateMd_gameState関数 - MD:ゲーム画面の状態に応じた更新処理 -
//========================================
void UpdateMd_gameState(void)
{
	// MD:ゲーム画面の情報のポインタ
	Md_game *pMd = &g_md_game;

	switch (pMd->state)
	{
	case MD_GAME_STATE_NORMAL:

		break;
	}
}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================

//========================================
// InitParameterMd_game関数 - MD:ゲームのパラメーター初期化 -
// Author:RIKU NISHIMURA
//========================================
void InitParameterMd_game(Md_game *pMd)
{
	pMd->state = MD_GAME_STATE_NONE;	// 状態
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
// InitMd_game関数 - MD:ゲームの初期化処理 -
// Author:RIKU NISHIMURA
//========================================
void InitMd_game(void) 
{
	// MD:ゲーム画面の情報のポインタ
	Md_game *pMd = &g_md_game;

	// パラメーター初期化
	InitParameterMd_game(pMd);

	// 初期状態を設定
	SetStateMd_game(INIT_STATE);
}

//========================================
// UninitMd_game関数 - MD:ゲームの終了処理 -
// Author:RIKU NISHIMURA
//========================================
void UninitMd_game(void) 
{

}

//========================================
// UpdateMd_game関数 - MD:ゲームの更新処理 -
// Author:RIKU NISHIMURA
//========================================
void UpdateMd_game(void) 
{
	// 状態に応じた更新処理
	UpdateMd_gameState();
}

//========================================
// DrawMd_game関数 - MD:ゲームの描画処理 -
// Author:RIKU NISHIMURA
//========================================
void DrawMd_game(void)
{

}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================
//========================================
// GetMd_game関数 - MD:ゲームの情報を取得 -
// Author:RIKU NISHIMURA
//========================================
Md_game *GetMd_game(void) 
{
	return &g_md_game;
}

//============================================================
//--------------------| *** 設定 *** |------------------------
//============================================================

//========================================
// SetStateMd_game関数 - MD:ゲームの状態設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetStateMd_game(MD_GAME_STATE state)
{
	// MD:ゲーム画面の情報のポインタ
	Md_game *pMd = &g_md_game;

	// 状態に応じた終了処理
	EndMd_gameState();
	
	// 状態を代入
	pMd->state = state;

	// 状態に応じた開始処理
	StartMd_gameState();
}