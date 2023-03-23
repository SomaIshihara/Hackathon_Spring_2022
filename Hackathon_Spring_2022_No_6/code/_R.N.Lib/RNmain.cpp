//========================================
// 
// R.N.Libのメインの処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** RNmain.cpp ***
//========================================
#include <time.h>
#include "R.N.Lib.h"

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 取得 ***
// R.N.Libのメイン処理の情報のパラメーター初期値を取得
RNmain InitParameterRNmain(void);
//========== *** 設定 ***
// レンダーステートの設定処理
void SetRenderStateRN(void);

//****************************************
// グローバル変数宣言
//****************************************
RNmain g_RNmain;	// R.N.Libのメイン処理の情報
static int g_nGroundTex;	// 地面のテクスチャ番号

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================

//========================================
// InitParameterRNmain関数 - R.N.Libのメイン処理の情報のパラメーター初期値を取得 -
// Author:RIKU NISHIMURA
//========================================
RNmain InitParameterRNmain(void) 
{
	return{

	};
}

//============================================================
//--------------------| *** 設定 *** |------------------------
//============================================================

//========================================
// SetRenderStateRN関数 - レンダーステートの設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetRenderStateRN(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// レンダーステートの設定
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// サンプラーステート設定
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// テクスチャステージステートの設定
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// アルファブレンドの設定
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 基本接続 *** |--------------------
//============================================================

//========================================
// RNInit関数 - R.N.Libの初期化処理 -
// Author:RIKU NISHIMURA
//========================================
void RNInit(HINSTANCE hInstance)
{
	// パラメーター初期化
	g_RNmain = InitParameterRNmain();

	// レンダーステートの設定処理
	SetRenderStateRN();

	// 乱数の種を取得
	srand((unsigned int)time(0));

	// 3D
	InitCamera3D();	// カメラ(3D)
	InitLight();	// 光
	InitLine3D();	// 線(3D)
	InitModel();	// モデル
	InitMapChip3D();// マップチップ(3D)
	InitPolygon3D();// ポリゴン(3D)
	// 2D
	InitCamera2D();	// カメラ(2D)
	InitFade();		// フェード
	InitPolygon2D();// ポリゴン(2D)
	// Graphic
	InitText();		// テキスト
	// Other
	InitInput(		// 入力関連の初期化処理
		hInstance,
		*GetWindowHandle());
	InitPhysics();	// 物理関連
	InitSound(		// サウンド
		*GetWindowHandle());
	InitSetting();	// 設定

	// 地面テクスチャを読み込み
	g_nGroundTex = LoadTexture("data\\TEXTURE\\BG\\ground.png");
}

//========================================
// RNUninit関数 - R.N.Libの終了処理 -
// Author:RIKU NISHIMURA
//========================================
void RNUninit(void)
{
	// 3D
	UninitCamera3D();	// カメラ(3D)
	UninitLight();		// 光
	UninitLine3D();		// 線(3D)
	UninitModel();		// モデル
	UninitMapChip3D();	// マップチップ(3D)
	UninitPolygon3D();	// ポリゴン(3D)
	// 2D
	UninitCamera2D();	// カメラ(2D)
	UninitPolygon2D();	// ポリゴン(2D)
	// Other
	UninitInput();		// 入力関連
	UninitSetting();	// 設定
	UninitSound();		// サウンド
	UninitWindow();		// ウィンドウ
}

//========================================
// RNUpdate関数 - R.N.Libの更新処理 -
// Author:RIKU NISHIMURA
//========================================
void RNUpdate(void)
{
	// 当たり判定の線の数を初期化
	InitHitTestLineNum();

	UpdateSetting();	// 設定
	UpdateInput();		// 入力関連
	UpdateMapChip3D();	// マップチップ(3D)
	UpdateCamera2D();	// カメラ(2D)
	UpdateCamera3D();	// カメラ(3D)
	UpdateLight();		// 光
	UpdateFade();		// フェード
	UpdateWindowRN();	// ウィンドウ
	DrawHitTestSetUp();	// 当たり判定の描画準備処理
	HitTestSignOut();	// 当たり判定の登録解除処理

	float fSize = 680.0f;
	// ポリゴン(3D)の設定情報
	Polygon3DSet polygon3DSet;
	polygon3DSet.nTex = g_nGroundTex;
	polygon3DSet.nPtn = 0;
	polygon3DSet.nPtnX = 1;
	polygon3DSet.nPtnY = 1;
	polygon3DSet.fWidth = fSize;
	polygon3DSet.fHeight = fSize;
	polygon3DSet.pos = D3DXVECTOR3(0.0f,-80.0f,320.0f);
	polygon3DSet.rot = D3DXVECTOR3(-0.25f,0.0f,0.0f);
	polygon3DSet.col = INITCOLOR;
	// ポリゴン(3D)の設定処理
	SetPolygon3D(polygon3DSet);
	polygon3DSet.pos = D3DXVECTOR3(-fSize, -80.0f, 320.0f);
	// ポリゴン(3D)の設定処理
	SetPolygon3D(polygon3DSet);
	polygon3DSet.pos = D3DXVECTOR3(fSize, -80.0f, 320.0f);
	// ポリゴン(3D)の設定処理
	SetPolygon3D(polygon3DSet);
}

//========================================
// RNDraw関数 - R.N.Libの描画処理 -
// Author:RIKU NISHIMURA
//========================================
void RNDraw(void)
{
	// デバイスの取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// 画面クリア
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), ColorToD3DXCOLOR(GetColorInfo()->bgCol), 1.0f, 0);

	// 描画する3Dオブジェクトをソート
	SortDraw3D();

	// 描画開始
	if (SUCCEEDED(pDevice->BeginScene()))
	{// 描画開始が成功した場合、
		// 3D
		SetCamera3D();		// カメラ(3D)の設定処理
		DrawMapChip3D();	// マップチップ(3D)
		Draw3D();			// 3Dオブジェクト全般

		// 2D
		DrawPolygon2D();	// ポリゴン(2D)
		DrawLine3D();		// 線(3D)
		DrawHitTest();		// 当たり判定

		// 描画終了
		pDevice->EndScene();
	}

	// ポリゴン(2D & 3D)の設定数を初期化
	GetPolygon2DControl()->nPolygonNum = 0;
	GetPolygon3DControl()->nPolygonNum = 0;
	// 線(3D)の数を初期化
	GetLine3DControl()->nLineNum = 0;
	// モデルの設定数を初期化
	GetModelInfo()->nModelSetNum = 0;

	// バックバッファをフロントバッファの入れ替え
	pDevice->Present(NULL, NULL, NULL, NULL);
}

//========================================
// RNWindowProc関数 - R.N.Libのウィンドウプロシージャの延長先 -
// Author:RIKU NISHIMURA
//========================================
void RNWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MOUSEWHEEL: // マウスホイールが回された時のメッセージ
		if (HIWORD(wParam) == WHEEL_DELTA)
		{// マウスホイールの回転状態を前回転に設定
			GetInputInfo()->wheelSpin = WHEELSPIN_FRONT;
		}
		else
		{// マウスホイールの回転状態を後回転に設定
			GetInputInfo()->wheelSpin = WHEELSPIN_BACK;
		}

		break;
	}
}

//============================================================
//--------------------| *** 入出力 *** |----------------------
//============================================================

//========================================
// RNLoad関数 - R.N.Libの読み込み処理 -
// Author:RIKU NISHIMURA
//========================================
void RNLoad(void)
{
	LoadFont();				// フォント
	LoadMapChip3DList();		// マップチップ(3D)リスト
	LoadModelSetUpList();	// モデルのセットアップリスト
}

//========================================
// RNSave関数 - R.N.Libの書き込み処理 -
// Author:RIKU NISHIMURA
//========================================
void RNSave(void)
{
	
}

//========================================
// GetRNmain関数 - R.N.mainの情報を取得 -
// Author:RIKU NISHIMURA
//========================================
RNmain *GetRNmain(void) 
{
	return &g_RNmain;
}