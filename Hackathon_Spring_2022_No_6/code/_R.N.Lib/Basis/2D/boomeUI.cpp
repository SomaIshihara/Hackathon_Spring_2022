//=======================================================================================================
//
//ブーメランの所持数UI処理[boomerangUI.h]
//Author:平澤詩苑
//
//=======================================================================================================
#include "../../RNmain.h"
#include "../../../main.h"
#include "../../../chr_player.h"
#include "text2D.h"
#include "boomeUI.h"

//****************************************
// マクロ定義
//****************************************
//UIサイズ
#define BOOME_UI_SIZE		(60.0f)
//UI位置
#define BOOME_UI_POS		(D3DXVECTOR3(100.0f, 30.0f, 0.0f))
//表示するUIの文字数
#define BOOME_UI_NUM_TXT	(5)

//========================================
// SetBoomeUI関数 - 所持ブーメラン数のUI設定処理 -
// Author:SHION HIRASAWA
//========================================
void SetBoomeUI(void)
{
	//所持ブーメラン数を文字列に
	char cBoomeUI[BOOME_UI_NUM_TXT];

	//所持ブーメラン数を文字列に置き換え
	snprintf(cBoomeUI, BOOME_UI_NUM_TXT, "! *%d", GetChr_player()->nBoomerang);

	// テキスト(2D)の設定処理
	Text2DSet text2DSet;
	/* 文字列のポインタ */text2DSet.pString = cBoomeUI;
	/* フォント番号		*/text2DSet.nFont = 1;
	/* 表示形式			*/text2DSet.disp = TEXT_DISP_CENTER;
	/* 位置				*/text2DSet.pos = BOOME_UI_POS;
	/* 向き				*/text2DSet.rot = INITD3DXVECTOR3;
	/* 色				*/text2DSet.col = INITCOLOR;
	/* 幅				*/text2DSet.fWidth = BOOME_UI_SIZE;
	/* 高さ				*/text2DSet.fHeight = BOOME_UI_SIZE;
	/* カメラ合わせ		*/text2DSet.bMatchCamera = false;
	// テキスト(2D)の設定処理
	SetText2D(text2DSet);
}