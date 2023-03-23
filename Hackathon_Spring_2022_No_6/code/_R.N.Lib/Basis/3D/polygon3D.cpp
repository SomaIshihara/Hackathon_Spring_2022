//========================================
// 
// ポリゴン(3D)関連の処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** polygon3D.cpp ***
//========================================
#include "assert.h"
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// グローバル変数宣言
//****************************************
// ポリゴン(3D)の頂点バッファへのポインタ
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffpolygon3D = NULL;
// ポリゴン(3D)の管理情報
Polygon3DControl g_polygon3DControl;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 基本接続 *** |--------------------
//============================================================

//========================================
// InitPolygon3D関数 - ポリゴン(3D)の初期化処理 -
// Author:RIKU NISHIMURA
//========================================
void InitPolygon3D(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * POLYGON3D_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffpolygon3D,
		NULL);
}

//========================================
// UninitPolygon3D関数 - ポリゴン(3D)の終了処理 -
// Author:RIKU NISHIMURA
//========================================
void UninitPolygon3D(void)
{
	// 頂点バッファの破棄
	if (g_pVtxBuffpolygon3D != NULL)
	{
		g_pVtxBuffpolygon3D->Release();
		g_pVtxBuffpolygon3D = NULL;
	}
}

//========================================
// DrawPolygon3D関数 - ポリゴン(3D)の描画処理 -
// Author:RIKU NISHIMURA
//========================================
void DrawPolygon3D(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxSelf;	// 本体マトリックス

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffpolygon3D, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntPoly = 0; nCntPoly < g_polygon3DControl.nPolygonNum; nCntPoly++)
	{
		// ポリゴン(3D)の設定情報
		Polygon3DSet polygon3DSet = g_polygon3DControl.aPolySet[nCntPoly];

		// ワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxSelf);

		{
			// 位置と向きを設定
			D3DXVECTOR3 pos = polygon3DSet.pos;
			D3DXVECTOR3 rot = polygon3DSet.rot;
			
			// 向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
			D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);
			
			// 位置を反映
			D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
			D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);
		}

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);

		// テクスチャの設定
		SetTexture(pDevice, polygon3DSet.nTex);

		// ポリゴン(3D)の描画
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPoly, 2);
	}
}

//========================================
// DrawSinglePolygon3D関数 - ポリゴン(3D)の描画処理(単体) -
// Author:RIKU NISHIMURA
//========================================
void DrawSinglePolygon3D(LPDIRECT3DDEVICE9 pDevice,int nIdx)
{
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxSelf;	// 本体マトリックス

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffpolygon3D, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	// ポリゴン(3D)の設定情報
	Polygon3DSet polygon3DSet = g_polygon3DControl.aPolySet[nIdx];

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxSelf);

	{
		// 位置と向きを設定
		D3DXVECTOR3 pos = polygon3DSet.pos;
		D3DXVECTOR3 rot = polygon3DSet.rot;

		// 向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);

		// 位置を反映
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);
	}

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);

	// テクスチャの設定
	SetTexture(pDevice, polygon3DSet.nTex);

	// ポリゴン(3D)の描画
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nIdx, 2);
}

//============================================================
//--------------------| *** 設定 *** |------------------------
//============================================================

//========================================
// SetPolygon3D関数 - ポリゴン(3D)の設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetPolygon3D(Polygon3DSet polygon3DSet)
{
	if (g_polygon3DControl.nPolygonNum == POLYGON3D_MAX) 
	{// ポリゴン(3D)の数が最大数に達している時、
		assert(false);
		return;	// 処理を終了する
	}

	// ポリゴン数
	int nPolyNum = g_polygon3DControl.nPolygonNum;

	// 設定情報を代入
	g_polygon3DControl.aPolySet[nPolyNum] = polygon3DSet;

	VERTEX_3D *pVtx;	//頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffpolygon3D->Lock(0, 0, (void**)&pVtx, 0);
	{
		// 頂点情報へのポインタを進める
		pVtx += g_polygon3DControl.nPolygonNum * 4;

		// 頂点座標の設定
		SetVertexPos3D(pVtx, polygon3DSet.fWidth, polygon3DSet.fHeight);

		// 法線ベクトルの設定
		SetNormalLine3D(pVtx, FindNormalVector(polygon3DSet.rot));

		// 頂点カラーの設定
		SetVertexColor3D(pVtx, polygon3DSet.col);

		// テクスチャ座標の設定
		SetTexturePos3D(pVtx, polygon3DSet.nPtn, polygon3DSet.nPtnX, polygon3DSet.nPtnY, NULL);
	}
	// 頂点座標をアンロックする
	g_pVtxBuffpolygon3D->Unlock();

	// ポリゴン(3D)の数を加算
	g_polygon3DControl.nPolygonNum++;
}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================

//========================================
// GetPolygon3DControl関数 - ポリゴン(3D)の管理情報を取得 -
// Author:RIKU NISHIMURA
//========================================
Polygon3DControl *GetPolygon3DControl(void) 
{
	return &g_polygon3DControl;
}

//============================================================
//--------------------| *** 頂点設定 *** |--------------------
//============================================================

//========================================
// SetVertexPos3D関数 - 頂点座標の設定処理(3D) -
// Author:RIKU NISHIMURA
//========================================
void SetVertexPos3D(VERTEX_3D *pVtx, float fWidth, float fHeight)
{
	// 頂点座標の設定
	pVtx[0].pos = D3DXVECTOR3(-(fWidth * 0.5f), 0.0f,  (fHeight * 0.5f));
	pVtx[1].pos = D3DXVECTOR3( (fWidth * 0.5f), 0.0f,  (fHeight * 0.5f));
	pVtx[2].pos = D3DXVECTOR3(-(fWidth * 0.5f), 0.0f, -(fHeight * 0.5f));
	pVtx[3].pos = D3DXVECTOR3( (fWidth * 0.5f), 0.0f, -(fHeight * 0.5f));
}

//========================================
// SetNormalLine3D関数 - 法線ベクトルの設定処理(3D) -
// Author:RIKU NISHIMURA
//========================================
void SetNormalLine3D(VERTEX_3D *pVtx, D3DXVECTOR3 nor) 
{
	// 法線ベクトルの設定
	pVtx[0].nor = nor;
	pVtx[1].nor = nor;
	pVtx[2].nor = nor;
	pVtx[3].nor = nor;
}

//========================================
// SetVertexColor3D関数 - 頂点色の設定処理(3D) -
// Author:RIKU NISHIMURA
//========================================
void SetVertexColor3D(VERTEX_3D *pVtx, Color col)
{
	// 頂点色の設定
	pVtx[0].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
}

//========================================
// SetTexturePos3D関数 - テクスチャ座標の設定処理(3D) -
// Author:RIKU NISHIMURA
//========================================
void SetTexturePos3D(VERTEX_3D *pVtx, int nPtn, int nPtnMaxX, int nPtnMaxY, D3DXVECTOR3 *pPos)
{
	if (nPtnMaxX * nPtnMaxY == 0)
	{// パターンの上限が0の時、
		// 処理を終了する
		return;
	}

	D3DXVECTOR3 pos;	// 位置

	if (pPos == NULL)
	{// 位置のポインタがNULLの時、
		// 位置を初期化
		pos = D3DXVECTOR3(0, 0, 0);
	}
	else
	{// 位置のポインタがNULLで無い時、
		// 位置を-補正して代入
		pos = -*pPos;
	}

	// テクスチャ座標の設定
	pVtx[0].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX) + pos.x						, ((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY) + pos.y);
	pVtx[1].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX) + (1.0f / nPtnMaxX) + pos.x	, ((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY) + pos.y);
	pVtx[2].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX) + pos.x						, (((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY)) + (1.0f / nPtnMaxY) + pos.y);
	pVtx[3].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX) + (1.0f / nPtnMaxX) + pos.x	, (((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY)) + (1.0f / nPtnMaxY) + pos.y);
}