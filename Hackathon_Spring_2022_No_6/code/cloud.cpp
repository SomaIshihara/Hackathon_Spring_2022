//=======================================================================================================
//
//背景の雲処理[cloud.cpp]
//Author:平澤詩苑
//
//=======================================================================================================
#include "_R.N.Lib\RNmain.h"
#include "main.h"
#include "_R.N.Lib\Basis\3D\polygon3D.h"

//****************************************
// マクロ定義
//****************************************
//最大桁数
#define MAX_DEJIT_TIMER		(4)
//制限時間の原点位置
#define TIMER_ORIGIN_POS	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 30.0f, 0.0f))
//制限時間のUIサイズ
#define TIMER_UI_SIZE		(60.0f)

//グローバル変数宣言
int g_nGameTime = 0;	//制限時間
int g_nCounterFrame;	//フレームカウンター
bool g_bEnd = false;

//========================================
// InitTimer関数 - 制限時間の初期化処理 -
// Author:SHION HIRASAWA
//========================================
void InitTimer(void)
{

}

//========================================
// UninitTimer関数 - 制限時間の終了処理 -
// Author:SHION HIRASAWA
//========================================
void UninitTimer(void)
{

}

//========================================
// UpdateTimer関数 - 制限時間の更新処理 -
// Author:SHION HIRASAWA
//========================================
void UpdateTimer(void)
{

}