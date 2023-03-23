//=======================================================================================================
//
//制限時間処理[timer.cpp]
//Author:平澤詩苑
//
//=======================================================================================================
#include "../../RNmain.h"
#include "../../../main.h"
#include "text2D.h"
#include "timer.h"
#include "../../../Mode/md_game.h"

//****************************************
// マクロ定義
//****************************************
//最大桁数
#define MAX_DEJIT_TIMER		(256)
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
	//制限時間初期化
	g_nGameTime = GAME_TIME;

	//フレームカウンター初期化
	g_nCounterFrame = 0;

	//制限時間UI設定
	SetTimer();

	g_bEnd = false;
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
	if (!g_bEnd)
	{
		//1秒が経過した
		if (++g_nCounterFrame % 60 == 0)
		{
			//制限時間減少
			g_nGameTime--;

			if (g_nGameTime == 0) 
			{
				g_bEnd = true;
				SetStateMd_game(MD_GAME_STATE_RANKING);
			}
		}
	}

	//UI設定
	SetTimer();
}

//========================================
// SetTimer関数 - 制限時間のUI設定処理 -
// Author:SHION HIRASAWA
//========================================
void SetTimer(void)
{
	//表示桁数
	int nCntDejit = 1;

	//制限時間保存
	int nTempTimer = g_nGameTime;

	//表示する桁数を計算する（最低１桁
	do
	{
		//表示桁数を増やす
		nCntDejit++;

		//１桁減らす
		nTempTimer /= 10;

	} while (nTempTimer > 0);

	//制限時間を文字列に
	char cGameTimer[MAX_DEJIT_TIMER];

	//制限時間を文字列に置き換え
	sprintf(cGameTimer, "TIME %d", g_nGameTime);

	// テキスト(2D)の設定処理
	Text2DSet text2DSet;
	/* 文字列のポインタ */text2DSet.pString = cGameTimer;
	/* フォント番号		*/text2DSet.nFont = 1;
	/* 表示形式			*/text2DSet.disp = TEXT_DISP_CENTER;
	/* 位置				*/text2DSet.pos = TIMER_ORIGIN_POS;
	/* 向き				*/text2DSet.rot = INITD3DXVECTOR3;
	/* 色				*/text2DSet.col = INITCOLOR;
	/* 幅				*/text2DSet.fWidth = TIMER_UI_SIZE;
	/* 高さ				*/text2DSet.fHeight = TIMER_UI_SIZE;
	/* カメラ合わせ		*/text2DSet.bMatchCamera = false;
	// テキスト(2D)の設定処理
	SetText2D(text2DSet);
}