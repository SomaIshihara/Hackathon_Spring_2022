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
	char *pString = NULL;	// 文字列のポインタ
	int nFont = 0;			// フォント番号
	TEXT_DISP disp = TEXT_DISP_CENTER;	// 表示形式
	D3DXVECTOR3 pos = INITD3DXVECTOR3;	// 位置
	D3DXVECTOR3 rot = INITD3DXVECTOR3;	// 向き
	Color col = INITCOLOR;	// 色
	float fWidth = 0.0f;	// 幅
	float fHeight = 0.0f;	// 高さ
	bool bMatchCamera = false;	// カメラ合わせフラグ
#if /* 設定フォーマット */0
	// テキスト(2D)の設定処理
	Text2DSet text2DSet;
	/* 文字列のポインタ */text2DSet.*pString = ;
	/* フォント番号		*/text2DSet.nFont = ;
	/* 表示形式			*/text2DSet.disp = ;
	/* 位置				*/text2DSet.pos = ;
	/* 向き				*/text2DSet.rot = ;
	/* 色				*/text2DSet.col = ;
	/* 幅				*/text2DSet.fWidth = ;
	/* 高さ				*/text2DSet.fHeight = ;
	/* カメラ合わせ		*/text2DSet.bMatchCamera = ;
	// テキスト(2D)の設定処理
	SetText2D(text2DSet);
#endif
}Text2DSet;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 設定 ***
// テキスト(2D)の設定処理
void SetText2D(Text2DSet text2DSet);

#endif