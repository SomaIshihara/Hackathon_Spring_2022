//========================================
// 
// MD:リザルトの処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** md_result.cpp ***
//========================================
#include "md_result.h"
#include "../_R.N.Lib/R.N.Lib.h"

//****************************************
// マクロ定義
//****************************************
//========== *** 状態関連 ***
// 初期の状態
#define INIT_STATE (MD_RESULT_STATE_NORMAL)

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 取得 ***
// MD:リザルトのパラメーター初期化
void InitParameterMd_result(Md_result *pMd);

//****************************************
// グローバル変数宣言
//****************************************
Md_result g_md_result;	// MD:リザルトの情報

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 基本接続 *** |--------------------
//============================================================

//========================================
// StartMd_resultState関数 - MD:リザルト画面の状態に応じた開始処理 -
//========================================
void StartMd_resultState(void)
{
	// MD:リザルト画面の情報のポインタ
	Md_result *pMd = &g_md_result;

	switch (pMd->state)
	{
	case MD_RESULT_STATE_NORMAL:

		break;
	}
}

//========================================
// EndMd_resultState関数 - MD:リザルト画面の状態に応じた終了処理 -
//========================================
void EndMd_resultState(void)
{
	// MD:リザルト画面の情報のポインタ
	Md_result *pMd = &g_md_result;

	switch (pMd->state)
	{
	case MD_RESULT_STATE_NORMAL:

		break;
	}
}

//========================================
// UpdateMd_resultState関数 - MD:リザルト画面の状態に応じた更新処理 -
//========================================
void UpdateMd_resultState(void)
{
	// MD:リザルト画面の情報のポインタ
	Md_result *pMd = &g_md_result;

	switch (pMd->state)
	{
	case MD_RESULT_STATE_NORMAL:

		break;
	}
}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================

//========================================
// InitParameterMd_result関数 - MD:リザルトのパラメーター初期化 -
// Author:RIKU NISHIMURA
//========================================
void InitParameterMd_result(Md_result *pMd)
{
	pMd->state = MD_RESULT_STATE_NONE;	// 状態
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
// InitMd_result関数 - MD:リザルトの初期化処理 -
// Author:RIKU NISHIMURA
//========================================
void InitMd_result(void) 
{
	// MD:リザルト画面の情報のポインタ
	Md_result *pMd = &g_md_result;

	// パラメーター初期化
	InitParameterMd_result(pMd);

	// 初期状態を設定
	SetStateMd_result(INIT_STATE);
}

//========================================
// UninitMd_result関数 - MD:リザルトの終了処理 -
// Author:RIKU NISHIMURA
//========================================
void UninitMd_result(void) 
{

}

//========================================
// UpdateMd_result関数 - MD:リザルトの更新処理 -
// Author:RIKU NISHIMURA
//========================================
void UpdateMd_result(void) 
{
	// 状態に応じた更新処理
	UpdateMd_resultState();
}

//========================================
// DrawMd_result関数 - MD:リザルトの描画処理 -
// Author:RIKU NISHIMURA
//========================================
void DrawMd_result(void)
{

}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================
//========================================
// GetMd_result関数 - MD:リザルトの情報を取得 -
// Author:RIKU NISHIMURA
//========================================
Md_result *GetMd_result(void) 
{
	return &g_md_result;
}

//============================================================
//--------------------| *** 設定 *** |------------------------
//============================================================

//========================================
// SetStateMd_result関数 - MD:リザルトの状態設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetStateMd_result(MD_RESULT_STATE state)
{
	// MD:リザルト画面の情報のポインタ
	Md_result *pMd = &g_md_result;

	// 状態に応じた終了処理
	EndMd_resultState();
	
	// 状態を代入
	pMd->state = state;

	// 状態に応じた開始処理
	StartMd_resultState();
}