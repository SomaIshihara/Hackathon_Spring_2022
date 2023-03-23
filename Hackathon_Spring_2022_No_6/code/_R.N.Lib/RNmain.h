//========================================
// 
// R.N.Libのメイン処理のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
//  *** RNmain.h ***
//========================================
#ifndef _RNMAIN_H_	// このマクロ定義がされていなかった時
#define _RNMAIN_H_	// 二重インクルード防止のマクロを定義する

#include <windows.h>
#include <stdio.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	// ビルド時の警告対処用マクロ
#include "dinput.h"						// 入力処理に必要
#include "Xinput.h"						// 入力処理に必要
#include "xaudio2.h"					// サウンド処理に必要

//****************************************
// ライブラリのリンク
//****************************************
#pragma comment(lib,"d3d9.lib")		// 描画処理に必要
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]の拡張ライブラリ
#pragma comment(lib,"dxguid.lib")	// DirectXコンポーネントを使用するのに必要
#pragma comment(lib,"dsound.lib")	// DirectSoundを使用するのに必要
#pragma comment(lib,"winmm.lib")	// システム時刻取得に必要
#pragma comment(lib,"dinput8.lib")	// 入力処理に必要
#pragma comment(lib,"xinput.lib")	// 入力処理に必要
#pragma warning(disable:4091)		// 警告:C4091を無視する
#pragma warning(disable:4244)		// 警告:C4244を無視する

//****************************************
// マクロ定義
//****************************************
// 頂点フォーマット(2D)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
// 頂点フォーマット(3D)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// D3DXVECTOR3の初期値
#define INITD3DXVECTOR3 D3DXVECTOR3(0.0f,0.0f,0.0f)
// Colorの初期値
#define INITCOLOR Color{255,255,255,255}

// 文字列の最大数(汎用)
#define TXT_MAX (1024)

// ピクセル単位の大きさ
#define PIXEL (2.0f)

//****************************************
// 構造体の定義
//****************************************
// R.N.Libのメイン処理の情報構造体
typedef struct 
{

}RNmain;

// 頂点情報(2D)の構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	float rhw;			// 座標変換用係数(1.0fで固定)
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_2D;

// 頂点情報(3D)の構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 頂点座標
	D3DXVECTOR3 nor;	// 法線ベクトル
	D3DCOLOR col;		// 頂点カラー
	D3DXVECTOR2 tex;	// テクスチャ座標
}VERTEX_3D;

// 拡大倍率構造体
typedef struct
{
	float fWidth;	// 幅
	float fHeight;	// 高さ
	float fDepth;	// 奥行き
}Scale;

// 色構造体
typedef struct
{
	int r;
	int g;
	int b;
	int a;
}Color;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 基本接続 ***
// 初期化処理
void RNInit(HINSTANCE hInstance);
// 終了処理
void RNUninit(void);
// 更新処理
void RNUpdate(void);
// 描画処理
void RNDraw(void);
// R.N.Libのウィンドウプロシージャの延長先
void RNWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//========== *** 入出力 ***
// 読み込み処理
void RNLoad(void);
// 書き込み処理
void RNSave(void);
//========== *** 取得 ***
// R.N.mainの情報を取得
RNmain *GetRNmain(void);

#endif