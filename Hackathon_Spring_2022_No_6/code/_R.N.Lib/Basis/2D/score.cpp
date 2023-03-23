//=======================================================================================================
//
//スコアUI処理[score.cpp]
//Author:平澤詩苑
//
//=======================================================================================================
#include "../../RNmain.h"
#include "../../../main.h"
#include "../../../chr_player.h"
#include "text2D.h"
#include "score.h"

//****************************************
// マクロ定義
//****************************************
//UIサイズ
#define SCORE_NAME_SIZE		(32.0f)
#define SCORE_DEJIT_SIZE	(64.0f)
//UI位置
#define SCORE_NAME_POS		(D3DXVECTOR3(1100.0f, 630.0f, 0.0f))
#define SCORE_DEJIT_POS		(D3DXVECTOR3(1100.0f, 680.0f, 0.0f))
//表示するUIの文字数
#define SCORE_DEJIT_NUM_TXT	(6)

//========================================
// SetScoreUI関数 - 所持ブーメラン数のUI設定処理 -
// Author:SHION HIRASAWA
//========================================
void SetScoreUI(void)
{
	// テキスト(2D)の設定処理
	Text2DSet text2DSet[2];

	//************************************
	//			"SCORE" を表示
	//************************************
	/* 文字列のポインタ */text2DSet[0].pString = "SCORE";
	/* フォント番号		*/text2DSet[0].nFont = 0;
	/* 表示形式			*/text2DSet[0].disp = TEXT_DISP_RIGHT;
	/* 位置				*/text2DSet[0].pos = SCORE_NAME_POS;
	/* 向き				*/text2DSet[0].rot = INITD3DXVECTOR3;
	/* 色				*/text2DSet[0].col = INITCOLOR;
	/* 幅				*/text2DSet[0].fWidth = SCORE_NAME_SIZE;
	/* 高さ				*/text2DSet[0].fHeight = SCORE_NAME_SIZE;
	/* カメラ合わせ		*/text2DSet[0].bMatchCamera = false;

	//************************************
	//		プレイヤーのスコア を表示
	//************************************
	//プレイヤーのスコアを文字列に
	char c_nScoreUI[SCORE_DEJIT_NUM_TXT];

	//プレイヤーのスコアを文字列に置き換え
	snprintf(c_nScoreUI, SCORE_DEJIT_NUM_TXT, "%d", GetChr_player()->nScore);

	/* 文字列のポインタ */text2DSet[1].pString = c_nScoreUI;
	/* フォント番号		*/text2DSet[1].nFont = 1;
	/* 表示形式			*/text2DSet[1].disp = TEXT_DISP_CENTER;
	/* 位置				*/text2DSet[1].pos = SCORE_DEJIT_POS;
	/* 向き				*/text2DSet[1].rot = INITD3DXVECTOR3;
	/* 色				*/text2DSet[1].col = INITCOLOR;
	/* 幅				*/text2DSet[1].fWidth = SCORE_DEJIT_SIZE;
	/* 高さ				*/text2DSet[1].fHeight = SCORE_DEJIT_SIZE;
	/* カメラ合わせ		*/text2DSet[1].bMatchCamera = false;

	for (int nCntScore = 0; nCntScore < 2; nCntScore++)
	{
		// テキスト(2D)の設定処理
		SetText2D(text2DSet[nCntScore]);
	}
}