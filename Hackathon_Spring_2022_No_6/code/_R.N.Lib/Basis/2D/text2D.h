//========================================
// 
// テキスト(2D)のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// *** text2D.h ***
//========================================
#ifndef _TEXT2D_H_	// このマクロ定義がされていなかった時
#define _TEXT2D_H_	// 二重インクルード防止のマクロを定義する

#include "../Graphic/text.h"

//****************************************
// 構造体の定義
//****************************************
// テキスト(2D)の設定情報
typedef struct
{
	/* 文字列のポインタ */char *pString = NULL;
	/* フォント番号		*/int nFont = 0;
	/* 表示形式			*/TEXT_DISP disp = TEXT_DISP_CENTER;
	/* 位置				*/D3DXVECTOR3 pos = INITD3DXVECTOR3;
	/* 向き				*/D3DXVECTOR3 rot = INITD3DXVECTOR3;
	/* 色				*/Color col = INITCOLOR;
	/* 幅				*/float fWidth = 0.0f;
	/* 高さ				*/float fHeight = 0.0f;
	/* カメラ合わせ		*/bool bMatchCamera = false;
}Text2DSet;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 設定 ***
// テキスト(2D)の設定処理
void SetText2D(Text2DSet text2DSet);

#endif