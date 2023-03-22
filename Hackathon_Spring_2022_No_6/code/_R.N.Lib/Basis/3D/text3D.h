//========================================
// 
// テキスト(3D)のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// *** text3D.h ***
//========================================
#ifndef _TEXT3D_H_	// このマクロ定義がされていなかった時
#define _TEXT3D_H_	// 二重インクルード防止のマクロを定義する

#include "../Graphic/text.h"

//****************************************
// 構造体の定義
//****************************************
// テキスト(3D)の設定情報
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
	bool bZtest = false;		// Zテストフラグ
	bool bLighting = false;		// ライティングフラグ
	bool bBillboard = false;	// ビルボードフラグ
}Text3DSet;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 設定 ***
// テキスト(3D)の設定処理
void SetText3D(Text3DSet text3DSet);

#endif