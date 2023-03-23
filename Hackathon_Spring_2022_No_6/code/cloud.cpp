//=======================================================================================================
//
//背景の雲処理[cloud.cpp]
//Author:平澤詩苑
//
//=======================================================================================================
#include "_R.N.Lib\RNmain.h"
#include "main.h"
#include "_R.N.Lib\Basis\3D\polygon3D.h"

//雲の構造体
typedef struct
{
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 move;		//移動量
	int			nTexType;	//テクスチャの種類
	bool		bUse;		//使用されているか
}Cloud;

//****************************************
// マクロ定義
//****************************************
#define CLOUD_WIDTH		(200.0f)//雲の横位置
#define CLOUD_HEIGHT	(50.0f)	//雲の高度
#define CLOUD_DEPTH		(270.0f)//雲の遠さ
#define MAX_CLOUD		(13)	//雲の最大数
#define CLOUD_SIZE		(50.0f)	//雲のサイズ
#define CLOUD_INTERVAL	(150.0f)//雲の間隔
#define CLOUD_ROT		(D3DXVECTOR3(D3DX_PI* 0.25f, D3DX_PI, 0.0f))
#define RETURN_WIDTH	(-325.0f)//折り返し地点
#define REVIVAL_WIDTH	(325.0f)//復帰地点
#define CLOUD_CLEAR		(150)	//雲の透明度

//グローバル変数宣言
Cloud		g_Cloud[MAX_CLOUD];
float fRot = 0.0f;

//========================================
// InitCloud関数 - 制限時間の初期化処理 -
// Author:SHION HIRASAWA
//========================================
void InitCloud(void)
{
	//雲のポインタ取得
	Cloud *pCloud = &g_Cloud[0];

	for (int nCntCloud = 0; nCntCloud < MAX_CLOUD; nCntCloud++, pCloud++)
	{
		pCloud->pos = D3DXVECTOR3(CLOUD_WIDTH + (nCntCloud * CLOUD_SIZE), CLOUD_HEIGHT, CLOUD_DEPTH);
		pCloud->move = INITD3DXVECTOR3;
		pCloud->bUse = false;
		pCloud->nTexType = LoadTexture("data/TEXTURE/BG/Sky_layer03.png");

		// ポリゴン(3D)の設定情報
		Polygon3DSet polygon3DSet;
		polygon3DSet.nTex = pCloud->nTexType;
		polygon3DSet.nPtn = 0;
		polygon3DSet.nPtnX = 1;
		polygon3DSet.nPtnY = 1;
		polygon3DSet.fWidth = CLOUD_SIZE;
		polygon3DSet.fHeight = CLOUD_SIZE;
		polygon3DSet.pos = pCloud->pos;
		polygon3DSet.rot = CLOUD_ROT;
		polygon3DSet.col = {255, 255, 255, CLOUD_CLEAR };
		// ポリゴン(3D)の設定処理
		SetPolygon3D(polygon3DSet);
	}
}

//========================================
// UninitCloud関数 - 制限時間の終了処理 -
// Author:SHION HIRASAWA
//========================================
void UninitCloud(void)
{

}

//========================================
// UpdateCloud関数 - 制限時間の更新処理 -
// Author:SHION HIRASAWA
//========================================
void UpdateCloud(void)
{
	//雲のポインタ取得
	Cloud *pCloud = &g_Cloud[0];

	for (int nCntCloud = 0; nCntCloud < MAX_CLOUD; nCntCloud++, pCloud++)
	{
		pCloud->pos.x -= 0.5f;

		if (pCloud->pos.x <= RETURN_WIDTH)
		{
			pCloud->pos.x = REVIVAL_WIDTH;
		}

		// ポリゴン(3D)の設定情報
		Polygon3DSet polygon3DSet;
		polygon3DSet.nTex = pCloud->nTexType;
		polygon3DSet.nPtn = 0;
		polygon3DSet.nPtnX = 1;
		polygon3DSet.nPtnY = 1;
		polygon3DSet.fWidth = CLOUD_SIZE;
		polygon3DSet.fHeight = CLOUD_SIZE;
		polygon3DSet.pos = pCloud->pos;
		polygon3DSet.rot = CLOUD_ROT;
		polygon3DSet.col = { 255, 255, 255, CLOUD_CLEAR };
		// ポリゴン(3D)の設定処理
		SetPolygon3D(polygon3DSet);
	}
}