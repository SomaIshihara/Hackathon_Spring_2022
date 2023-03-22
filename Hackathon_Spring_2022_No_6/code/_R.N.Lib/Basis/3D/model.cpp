//========================================
// 
// モデル関連の処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** model.cpp ***
//========================================
#include "assert.h"
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// グローバル変数宣言
//****************************************
// モデル関連のテクスチャ番号
static int g_aTextureIdxModel[MODELTYPE_MAX][MATERIAL_3D_MAX] = {};
// モデル関連のメッシュ(頂点情報)へのポインタ
static LPD3DXMESH g_aMeshModel[MODELTYPE_MAX] = {};
// モデル関連のマテリアルへのポインタ
static LPD3DXBUFFER g_pBuffMatModel[MODELTYPE_MAX] = {};
// モデル関連のマテリアルの数
static DWORD g_aNumMatModel[MODELTYPE_MAX] = {};
// モデルの管理情報
static ModelInfo g_modelSetUpInfo;

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
// InitModel関数 - モデルの初期化処理 -
// Author:RIKU NISHIMURA
//========================================
void InitModel(void)
{
	
}

//========================================
// UninitModel関数 - モデルの終了処理 -
// Author:RIKU NISHIMURA
//========================================
void UninitModel(void)
{
	for (int nCntType = 0; nCntType < MODELTYPE_MAX; nCntType++)
	{
		// メッシュの破棄
		if (g_aMeshModel[nCntType] != NULL)
		{
			g_aMeshModel[nCntType]->Release();
			g_aMeshModel[nCntType] = NULL;
		}

		// マテリアルの破棄
		if (g_pBuffMatModel[nCntType] != NULL)
		{
			g_pBuffMatModel[nCntType]->Release();
			g_pBuffMatModel[nCntType] = NULL;
		}
	}
}

//========================================
// DrawModel関数 - モデルの描画処理 -
// Author:RIKU NISHIMURA
//========================================
void DrawModel(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DMATERIAL9 matDef;	// 現在のマテリアルの保存用
	D3DXMATERIAL *pMat;		// マテリアルデータへのポインタ

	// モデルの設定数分描画
	for (int nCntModel = 0; nCntModel < g_modelSetUpInfo.nModelSetNum; nCntModel++)
	{
		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// 種類番号
		int nType = g_modelSetUpInfo.aModelSet[nCntModel].nModelIdx;

		// 本体のワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_modelSetUpInfo.aModelSet[nCntModel].mtx);

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatModel[nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aNumMatModel[nType]; nCntMat++)
		{
			// マテリアルの設定
			SetMaterial(pDevice, &pMat[nCntMat].MatD3D, g_modelSetUpInfo.aModelSet[nCntModel].col);

			// テクスチャの設定
			SetTexture(pDevice, g_aTextureIdxModel[nType][nCntMat]);

			// ポリゴン(パーツ)の描画
			g_aMeshModel[nType]->DrawSubset(nCntMat);
		}
	}
}

//========================================
// DrawSingleModel関数 - モデルの描画処理(単体) -
// Author:RIKU NISHIMURA
//========================================
void DrawSingleModel(LPDIRECT3DDEVICE9 pDevice,int nIdx)
{
	D3DMATERIAL9 matDef;	// 現在のマテリアルの保存用
	D3DXMATERIAL *pMat;		// マテリアルデータへのポインタ

	// 現在のマテリアルを取得
	pDevice->GetMaterial(&matDef);

	// 種類番号
	int nType = g_modelSetUpInfo.aModelSet[nIdx].nModelIdx;

	// 本体のワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &g_modelSetUpInfo.aModelSet[nIdx].mtx);

	// マテリアルデータへのポインタを取得
	pMat = (D3DXMATERIAL*)g_pBuffMatModel[nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_aNumMatModel[nType]; nCntMat++)
	{
		// マテリアルの設定
		SetMaterial(pDevice, &pMat[nCntMat].MatD3D, g_modelSetUpInfo.aModelSet[nIdx].col);

		// テクスチャの設定
		SetTexture(pDevice, g_aTextureIdxModel[nType][nCntMat]);

		// ポリゴン(パーツ)の描画
		g_aMeshModel[nType]->DrawSubset(nCntMat);
	}
}
#endif
//============================================================
//--------------------| *** 入出力 *** |----------------------
//============================================================
#if 1
//========================================
// LoadModel関数 - モデルの読み込み処理 -
// Author:RIKU NISHIMURA
//========================================
int LoadModel(ModelLoad modelLoad)
{
	// モデルのパス
	char *pModelPath = modelLoad.pModelPath;

	// 既に読み込まれているモデルか確認
	for (int nCntType = 0; nCntType < g_modelSetUpInfo.nModelTypeNum; nCntType++) 
	{
		if (!strcmp(pModelPath, g_modelSetUpInfo.aLoadModelPath[nCntType])) 
		{// 既に同じパスのモデルを読み込んでいた時、
			return nCntType;	// 種類番号を返す
		}
	}

	if (g_modelSetUpInfo.nModelTypeNum == MODELTYPE_MAX - 1) 
	{// 既にモデルの種類数が最大に達していた時、
		assert(false);
		return 0;
	}

	// モデルのパスを保存
	sprintf(g_modelSetUpInfo.aLoadModelPath[g_modelSetUpInfo.nModelTypeNum], "%s", pModelPath);

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	// マテリアルへのポインタ
	D3DXMATERIAL *pMat;

	// 種類番号
	int nType = g_modelSetUpInfo.nModelTypeNum;

	// Xファイルの読み込み
	D3DXLoadMeshFromX(
		pModelPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[nType],
		NULL,
		&g_aNumMatModel[nType],
		&g_aMeshModel[nType]);

	if (g_pBuffMatModel[nType] == NULL) 
	{// NULLだった時、
		char aMessage[TXT_MAX];
		sprintf(aMessage, "モデルの読み込みに失敗！ %s", pModelPath);
		MessageBox(*GetWindowHandle(), aMessage, "警告！", MB_ICONWARNING);

		nType = -1;	// 種類番号を-1指定
	}
	else
	{
		// マテリアル情報に対するポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatModel[nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aNumMatModel[nType]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// テクスチャのファイル名がNULLでない時、
				// テクスチャを読み込み
				g_aTextureIdxModel[nType][nCntMat] = LoadTexture(pMat[nCntMat].pTextureFilename);
			}
			else
			{// テクスチャのファイル名がNULLの時、
				// テクスチャ番号を-1で指定
				g_aTextureIdxModel[nType][nCntMat] = -1;
			}
		}

		// モデルの数を加算
		g_modelSetUpInfo.nModelTypeNum++;
	}

	// 種類番号を返す
	return nType;
}
#endif
//============================================================
//--------------------| *** 設定 *** |------------------------
//============================================================
#if 1
//========================================
// SetModel関数 - モデルの設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetModel(ModelSet modelSet)
{
	if (modelSet.nModelIdx < 0 || modelSet.nModelIdx >= g_modelSetUpInfo.nModelTypeNum) 
	{// モデルの種類番号が範囲外の時、
		return;	// 処理を終了
	}
	else if (g_modelSetUpInfo.nModelSetNum == MODEL_MAX)
	{// モデルの設定数が最大数に達している時、
		assert(false);
		return;	// 処理を終了
	}

	// モデルの設定情報を代入
	g_modelSetUpInfo.aModelSet[g_modelSetUpInfo.nModelSetNum] = modelSet;

	// モデルの設定数を加算
	g_modelSetUpInfo.nModelSetNum++;
}

//========================================
// GetModelInfo関数 - モデルの管理情報取得 -
// Author:RIKU NISHIMURA
//========================================
ModelInfo *GetModelInfo(void)
{
	return &g_modelSetUpInfo;
}
#endif
#endif