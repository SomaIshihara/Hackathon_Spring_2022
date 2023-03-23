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
	"data//MODEL//Item//cheese.x"
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

}
//========================================
// UninitTarget関数 - 標的の終了処理 -
// Author:KEISUKE OOTONO
//========================================
void UninitTarget(void)
{

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

}
//========================================
// SetTarget関数 - 標的の設定処理 -
// Author:KEISUKE OOTONO
//========================================
void SetTarget(void)
{

}