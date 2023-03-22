//========================================
// 
// メインのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// *** main.h ***
//========================================
#ifndef _MAIN_H_	// このマクロ定義がされていなかった時
#define _MAIN_H_	// 二重インクルード防止のマクロを定義する

#include "d3dx9.h"
#include "_R.N.Lib/R.N.Lib.h"

//****************************************
// マクロ定義
//****************************************
// ウインドウの幅
#define SCREEN_WIDTH (1280)	// NORMAL=1280 4:3=960
// ウインドウの高さ
#define SCREEN_HEIGHT (720)
// ウインドウの中心座標X
#define SCREEN_CENTER_X (SCREEN_WIDTH*0.5f)
// ウインドウの中心座標Y
#define SCREEN_CENTER_Y (SCREEN_HEIGHT*0.5f)
// 内側スクリーンの左端
#define INSIDE_SCREEN_LEFTMOST (960)
// 内側スクリーンの右端
#define INSIDE_SCREEN_RIGHTMOST (720)

//****************************************
// 列挙型の定義
//****************************************
// モード(画面)の種類
typedef enum
{
	MODENONE = -1,	// 無し
	MODE_TITLE,		// タイトル
	MODE_GAME,		// ゲーム
	MODE_RESULT,	// リザルト
	MODE_MAX,
}MODE;

//****************************************
// 構造体の定義
//****************************************
// メイン処理の情報構造体
typedef struct 
{
	int nCountFPS = 0;		// FPSのカウンター
	MODE mode = MODENONE;	// モード
}Main;

//****************************************
// プロトタイプ宣言
//****************************************
// メイン処理の情報の取得
Main *GetMain(void);
// モードの取得
MODE GetMode(void);
// モードの設定処理
void SetMode(MODE mode);

#endif