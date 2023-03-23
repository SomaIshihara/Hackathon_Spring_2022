//========================================
// 
// UI:タイトルロゴ の処理
// Author:RIKU NISHIMURA
// 
//========================================
//  *** ui_title-logo.cpp ***
//========================================
#include "../_R.N.Lib/R.N.Lib.h"
#include "../main.h"

#include "ui_title-logo.h"	// UI :タイトルロゴ	

//****************************************
// マクロ定義
//****************************************
// UI:タイトルロゴ の位置
#define UI_TITLELOGO_POS	(D3DXVECTOR3((SCREEN_WIDTH*0.5f)+PIXEL*64,(SCREEN_HEIGHT*0.5f)+PIXEL*-64,0.0f))
// UI:タイトルロゴ のテキストの相対位置
#define UI_TITLELOGO_TEXT_RELATIVE_POS	(D3DXVECTOR3(0,PIXEL*-13,0.0f))

//****************************************
// 列挙型の定義
//****************************************
// UI:タイトルロゴ の部品番号
typedef enum
{
	UI_TITLELOGO_PARTS_TITLELOGO,	// タイトルロゴ
	UI_TITLELOGO_PARTS_MAX,
}UI_TITLELOGO_PARTS;

// UI:タイトルロゴ のテクスチャ番号
typedef enum 
{
	UI_TITLELOGO_TEXTURE_TITLELOGO,	// タイトルロゴ
	UI_TITLELOGO_TEXTURE_MAX,
}UI_TITLELOGO_TEXTURE;

//****************************************
// 構造体の定義
//****************************************
// UI:タイトルロゴ の部品毎の情報構造体
typedef struct
{
	UI_TITLELOGO_TEXTURE	tex;		// テクスチャ
	float					fWidth;		// 幅
	float					fHeight;	// 高さ
}Ui_titleLogoParts;

// UI:タイトルロゴ のテクスチャ毎の情報構造体
typedef struct
{
	char	aTexturePath[TXT_MAX];	// テクスチャファイルの相対パス
	int		nPtnWidth;				// パターン幅
	int		nPtnHeight;				// パターン高さ
}Ui_titleLogoTexture;

//****************************************
// グローバル宣言
//****************************************
static int g_nTex;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitUi_titleLogo関数 - UI:タイトルロゴ の初期化処理 -
//========================================
void InitUi_titleLogo(void)
{
	g_nTex = LoadTexture("data\\TEXTURE\\UserInterface\\title.png");
}

//========================================
// UninitUi_titleLogo関数 - UI:タイトルロゴ の終了処理 -
//========================================
void UninitUi_titleLogo(void)
{
	
}

//========================================
// UpdateUi_titleLogo関数 - UI:タイトルロゴ の更新処理 -
//========================================
void UpdateUi_titleLogo(void) 
{
	// ポリゴン(2D)の設定情報
	Polygon2DSet polySet;
	/* テクスチャ番号	*/polySet.nTex = g_nTex;
	/* パターン番号		*/polySet.nPtn = 0;
	/* パターン上限X	*/polySet.nPtnX = 1;
	/* パターン上限Y	*/polySet.nPtnY = 1;
	/* 幅				*/polySet.fWidth = PIXEL * 256;
	/* 高さ				*/polySet.fHeight = PIXEL * 128;
	/* 位置				*/polySet.pos = UI_TITLELOGO_POS;
	/* 向き				*/polySet.rot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI);
	/* 色				*/polySet.col = INITCOLOR;
	/* カメラ合わせ		*/polySet.bMatchCamera = false;
	// ポリゴン(2D)の設定処理
	SetPolygon2D(polySet);
}

//========================================
// DrawUi_titleLogo関数 - UI:タイトルロゴ の描画処理 -
//========================================
void DrawUi_titleLogo(void)
{
	
}