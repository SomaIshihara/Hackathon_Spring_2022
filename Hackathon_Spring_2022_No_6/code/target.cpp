//========================================
// 
// 標的の処理
// Author:KEISUKE OOTONO
// 
//========================================
//  *** target.cpp ***
//========================================
#include "target.h"

//****************************************
// マクロ定義
//****************************************
#define MAXTEX_TARGET_TYPE	(TARGET_MAX)		// 標的の種類の最大数
#define MAX_TEXTURE			(16)				// テクスチャの最大数
//****************************************
// プロトタイプ宣言
//****************************************

//****************************************
// グローバル変数宣言
//****************************************
static LPD3DXMESH g_pMeshTarget[MAXTEX_TARGET_TYPE] = {};							// メッシュ(頂点情報)へのポインタ
static LPD3DXBUFFER g_pBuffMatTarget[MAXTEX_TARGET_TYPE] = {};						// マテリアルへのポインタ
static LPDIRECT3DTEXTURE9 g_pTextureTarget[MAXTEX_TARGET_TYPE][MAX_TEXTURE] = {};	// テクスチャへのポインタ
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTarget = NULL;								// 頂点バッファのポインタ
static DWORD					g_dwNumMatTarget[MAXTEX_TARGET_TYPE] = {};			// マテリアルの数

static Target g_aTarget[MAX_TARGET];		// アイテムの情報
static Summon g_aSummon[MAX_SUMMON];		// 召喚の情報

//****************************************
// グローバル定数宣言
//****************************************
// モデルパス
static char g_aModelPath[TARGET_MAX][TXT_MAX] = {
	"data//MODEL//Item//cheese.x",
	"data//MODEL//Item//cheese.x",
	"data//MODEL//Item//cheese.x",
};

// 移動速度
static const float g_aItemSize[TARGET_MAX] = {
	1.0f,
	0.75f,
	0.5f,
};

//========== *** 標的の情報を取得 ***
Target *GetTarget(void)
{
	return &g_aTarget[0];
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitTarget関数 - 標的の初期化処理 -
// Author:KEISUKE OOTONO
//========================================
void InitTarget(void)
{
		// デバイス取得
		LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

		D3DXMATERIAL *pMat;	// マテリアルへのポインタ

		for (int nCntType = 0; nCntType < MAXTEX_TARGET_TYPE; nCntType++)
		{
			// Xファイルの読み込み
			D3DXLoadMeshFromX(
				g_aModelPath[nCntType],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatTarget[nCntType],
				NULL,
				&g_dwNumMatTarget[nCntType],
				&g_pMeshTarget[nCntType]);

			// マテリアル情報に対するポインタを取得
			pMat = (D3DXMATERIAL*)g_pBuffMatTarget[nCntType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatTarget[nCntType]; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// テクスチャの読み込み
					D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_pTextureTarget[nCntType][nCntMat]);
				}
			}
		}

		// 標的の初期化処理
		for (int nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
		{
			g_aTarget[nCntTarget].pos = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].rot = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].move = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].type = TARGET_A;
			g_aTarget[nCntTarget].bUse = false;
		}
}
//========================================
// UninitTarget関数 - 標的の終了処理 -
// Author:KEISUKE OOTONO
//========================================
void UninitTarget(void)
{
	//メッシュの破棄
	for (int nCntType = 0; nCntType < MAXTEX_TARGET_TYPE; nCntType++)
	{
		if (g_pMeshTarget[nCntType] != NULL)
		{
			g_pMeshTarget[nCntType]->Release();
			g_pMeshTarget[nCntType] = NULL;

		}
	}

	//頂点バッファの破棄
	if (g_pVtxBuffTarget != NULL)
	{
		g_pVtxBuffTarget->Release();
		g_pVtxBuffTarget = NULL;

	}

	//テクスチャの破棄
	for (int nCntType = 0; nCntType < MAXTEX_TARGET_TYPE; nCntType++)
	{
		for (int nCntMat = 0; nCntMat < 16; nCntMat++)
		{
			if (g_pTextureTarget[nCntType][nCntMat] != NULL)
			{
				g_pTextureTarget[nCntType][nCntMat]->Release();
				g_pTextureTarget[nCntType][nCntMat] = NULL;
			}
		}
	}
}
//========================================
// UpdateTarget関数 - 標的の更新処理 -
// Author:KEISUKE OOTONO
//========================================
void UpdateTarget(void)
{

}
//========================================
// DrawTarget関数 - 標的の描画処理 -
// Author:KEISUKE OOTONO
//========================================
void DrawTarget(void)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DMATERIAL9 matDef;			// 現在のマテリアルの保存用
	D3DXMATERIAL *pMat;				// マテリアルデータへのポインタ
	D3DXMATRIX mtxSelf;				// 本体のマトリックス

	for (int nCntPlayer = 0; nCntPlayer < MAXTEX_TARGET_TYPE; nCntPlayer++)
	{
		// 現在のマテリアルを取得
		pDevice->GetMaterial(&matDef);

		// 本体のワールドマトリックスの初期化
		D3DXMatrixIdentity(&mtxSelf);

		// 本体の向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aTarget[nCntPlayer].rot.y, g_aTarget[nCntPlayer].rot.x, g_aTarget[nCntPlayer].rot.z);
		D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);

		// 本体の位置を反映
		D3DXMatrixTranslation(&mtxTrans, g_aTarget[nCntPlayer].pos.x, g_aTarget[nCntPlayer].pos.y, g_aTarget[nCntPlayer].pos.z);
		D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);

		// 本体のワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);
		D3DXMATRIX	mtxParent;	// 親マトリックス

		// マテリアルデータへのポインタを取得
		pMat = (D3DXMATERIAL*)g_pBuffMatTarget[g_aTarget[nCntPlayer].type]->GetBufferPointer();

		// ワールドマトリックスの設定
		pDevice->SetTransform(D3DTS_WORLD, &g_aTarget[nCntPlayer].mtxWorld);

		if (g_aTarget[nCntPlayer].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatTarget[g_aTarget[nCntPlayer].type]; nCntMat++)
			{
				// マテリアルの設定
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// テクスチャの設定
				pDevice->SetTexture(0, g_pTextureTarget[g_aTarget[nCntPlayer].type][nCntMat]);

				// ポリゴン(パーツ)の描画
				g_pMeshTarget[g_aTarget[nCntPlayer].type]->DrawSubset(nCntMat);

			}
		}
	}
}
//========================================
// SetTarget関数 - 標的の設定処理 -
// Author:KEISUKE OOTONO
//========================================
void SetTarget(int nPos, TARGET_ITEM type)
{
	for (int nCntItem = 0; nCntItem < MAX_TARGET; nCntItem++)
	{
		if (g_aTarget[nCntItem].bUse == false)
		{//使用されていないとき
			g_aTarget[nCntItem].pos = g_aSummon[nPos].pos;					// 位置
			g_aTarget[nCntItem].type = type;								// 種類の設定
			g_aTarget[nCntItem].bUse = true;								// 使用フラグ
			break;
		}
	}
}