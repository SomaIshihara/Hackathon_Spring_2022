//========================================
// 
// 描画(3D)の処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** draw3D.cpp ***
//========================================
#include "assert.h"
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// マクロ定義
//****************************************
// 描画3Dオブジェクトの最大数
#define DRAW3D_MAX (MODEL_MAX+POLYGON3D_MAX)
// 高低差によるスコア
#define VERTICAL_INTERVAL_SCORE (10)

//****************************************
// 列挙型の定義
//****************************************
// 描画3Dオブジェクトの種類
typedef enum 
{
	DRAW3D_TYPE_MODEL,
	DRAW3D_TYPE_POLYGON,
	DRAW3D_TYPE_MAX,
}DRAW3D_TYPE;

//****************************************
// 構造体の定義
//****************************************
// 描画3Dオブジェクトの情報構造体
typedef struct
{
	DRAW3D_TYPE type;	// 種類
	unsigned int nIdx;	// 番号
	float fDistance;	// 距離
}draw3D;

//****************************************
// グローバル変数宣言
//****************************************
// 描画3Dオブジェクトの情報
static draw3D g_aDraw3D[DRAW3D_MAX];
// 描画3Dオブジェクトの数
static unsigned int g_nDraw3DNum = 0;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================
#if 1
//============================================================
//--------------------| *** 基本接続 *** |--------------------
//============================================================
#if 1
//========================================
// SortDraw3D関数 - 描画する3Dオブジェクトのソート処理 -
// Author:RIKU NISHIMURA
//========================================
void SortDraw3D(void)
{
	// 視点位置
	D3DXVECTOR3 posV = GetCamera3D()->posV;

	// 描画3Dオブジェクトの数を初期化
	g_nDraw3DNum = 0;

	for (int nCntModel = 0; nCntModel < GetModelInfo()->nModelSetNum; nCntModel++)
	{
		D3DXVECTOR3 modelPos = ConvMatrixToPos(GetModelInfo()->aModelSet[nCntModel].mtx);
		// 視点位置からモデルの位置までの距離を測る
		g_aDraw3D[g_nDraw3DNum].fDistance = 
			FindDistanceLookDown(posV, modelPos)
			+ (fabsf(posV.y - modelPos.y) * VERTICAL_INTERVAL_SCORE);
		// 番号を指定
		g_aDraw3D[g_nDraw3DNum].nIdx = nCntModel;
		// 種類を指定
		g_aDraw3D[g_nDraw3DNum].type = DRAW3D_TYPE_MODEL;
		g_nDraw3DNum++;	// 描画数カウントを加算
	}

	for (int nCntPoly = 0; nCntPoly < GetPolygon3DControl()->nPolygonNum; nCntPoly++)
	{
		// 視点位置からモデルの位置までの距離を測る
		g_aDraw3D[g_nDraw3DNum].fDistance =
			FindDistanceLookDown(posV, GetPolygon3DControl()->aPolySet[nCntPoly].pos)
			+ (fabsf(posV.y - GetPolygon3DControl()->aPolySet[nCntPoly].pos.y) * VERTICAL_INTERVAL_SCORE);
		// 番号を指定
		g_aDraw3D[g_nDraw3DNum].nIdx = nCntPoly;
		// 種類を指定
		g_aDraw3D[g_nDraw3DNum].type = DRAW3D_TYPE_POLYGON;
		g_nDraw3DNum++;	// 描画数カウントを加算
	}

	if (g_nDraw3DNum == 0) 
	{// 描画数カウントが0の時、処理を終了
		return;
	}

	draw3D draw;		// 一時的に値を格納
	int nTempCnt = 0;	// カウントを格納

	for (int nCntCompare1 = 0; nCntCompare1 < g_nDraw3DNum - 1; nCntCompare1++)
	{
		// 先頭の要素を最大値として記憶
		draw = g_aDraw3D[nCntCompare1];

		for (int nCntCompare2 = nCntCompare1 + 1; nCntCompare2 < g_nDraw3DNum; nCntCompare2++)
		{
			if (g_aDraw3D[nCntCompare2].fDistance > draw.fDistance)
			{// 要素の値が最大値を上回っていた時、
				// 値を記憶
				draw = g_aDraw3D[nCntCompare2];
				// カウントを記憶
				nTempCnt = nCntCompare2;
			}
		}

		if (g_aDraw3D[nCntCompare1].fDistance < draw.fDistance)
		{// 最大値が先頭の要素の値を上回っていた時、
			// 値を入れ替える
			g_aDraw3D[nTempCnt] = g_aDraw3D[nCntCompare1];
			g_aDraw3D[nCntCompare1] = draw;
		}
	}
}

//========================================
// Draw3D関数 - 3Dオブジェクトの描画処理 -
// Author:RIKU NISHIMURA
//========================================
void Draw3D(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	for (int nCnt3D = 0; nCnt3D < g_nDraw3DNum; nCnt3D++) 
	{
		// 描画3Dオブジェクトの情報
		draw3D draw3D = g_aDraw3D[nCnt3D];

		switch (draw3D.type) 
		{
		case DRAW3D_TYPE_MODEL:
			DrawSingleModel(pDevice, draw3D.nIdx);
			break;
		case DRAW3D_TYPE_POLYGON:
			DrawSinglePolygon3D(pDevice, draw3D.nIdx);
			break;
		}
	}
}
#endif
#endif