//========================================
// 
// ポリゴン(3D)関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
//  *** polygon3D.h ***
//========================================
#ifndef _POLYGON3D_H_	// このマクロ定義がされていなかった時
#define _POLYGON3D_H_	// 二重インクルード防止のマクロを定義する

#include <stdio.h>

//****************************************
// マクロ定義
//****************************************
// ポリゴン(3D)の最大数
#define POLYGON3D_MAX (1024)

//****************************************
// 構造体の定義
//****************************************
// ポリゴン(3D)の設定情報構造体
typedef struct 
{
	int nTex = -1;	// テクスチャ番号
	int nPtn = 0;	// パターン番号
	int nPtnX = 1;	// パターン上限X
	int nPtnY = 1;	// パターン上限Y
	float fWidth = 0.0f;	// 幅
	float fHeight = 0.0f;	// 高さ
	D3DXVECTOR3 pos = INITD3DXVECTOR3;	// 位置
	D3DXVECTOR3 rot = INITD3DXVECTOR3;	// 向き
	Color col = INITCOLOR;	// 色
#if /* 設定フォーマット */0
	// ポリゴン(3D)の設定情報
	Polygon3DSet polygon3DSet;
	polygon3DSet.nTex = ;
	polygon3DSet.nPtn = ;
	polygon3DSet.nPtnX = ;
	polygon3DSet.nPtnY = ;
	polygon3DSet.fWidth = ;
	polygon3DSet.fHeight = ;
	polygon3DSet.pos = ;
	polygon3DSet.rot = ;
	polygon3DSet.col = ;
	// ポリゴン(3D)の設定処理
	SetPolygon3D(Polygon3DSet);
#endif
}Polygon3DSet;

// ポリゴン(3D)の管理情報構造体
typedef struct
{
	// ポリゴン(3D)の設定情報
	Polygon3DSet aPolySet[POLYGON3D_MAX];
	int nPolygonNum = 0;	// ポリゴン(3D)の数
}Polygon3DControl;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 基本接続 ***
// ポリゴン(3D)の初期化処理
void InitPolygon3D(void);
// ポリゴン(3D)の終了処理
void UninitPolygon3D(void);
// ポリゴン(3D)の描画処理
void DrawPolygon3D(void);
// ポリゴン(3D)の描画処理(単体)
void DrawSinglePolygon3D(LPDIRECT3DDEVICE9 pDevice, int nIdx);
//========== *** 設定 ***
// ポリゴン(3D)の設定処理
void SetPolygon3D(Polygon3DSet polygon3DSet);
//========== *** 取得 ***
// ポリゴン(3D)の管理情報を取得
Polygon3DControl *GetPolygon3DControl(void);
//========== *** 頂点設定 ***
// 頂点座標の設定処理(3D)
void SetVertexPos3D(VERTEX_3D *pVtx, float fWidth, float fHeight);
// 法線ベクトルの設定処理(3D)
void SetNormalLine3D(VERTEX_3D *pVtx, D3DXVECTOR3 nor);
// 頂点色の設定処理(3D)
void SetVertexColor3D(VERTEX_3D *pVtx, Color col);
// テクスチャ座標の設定処理(3D)
void SetTexturePos3D(VERTEX_3D *pVtx, int nPtn, int nPtnMaxX, int nPtnMaxY, D3DXVECTOR3 *pPos);

#endif