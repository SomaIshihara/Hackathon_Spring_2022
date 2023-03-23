//========================================
// 
// MD:ゲームの処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** md_game.cpp ***
//========================================
#include "md_game.h"
#include "../_R.N.Lib/R.N.Lib.h"
#include "../boomerang.h"
#include "../_R.N.Lib/Basis/2D/boomeUI.h"
#include "../target.h"
#include "../chr_player.h"
#include "../_R.N.Lib/Basis/2D/timer.h"

#include "../UserInterface/ui_menu.h"
#include "../UserInterface/ui_ranking-frame.h"
#include "../System/sys_ranking.h"
#include "../_R.N.Lib/Basis/2D/score.h"
#include "../../code/_R.N.Lib/Basis/Other/sound.h"
#include "../cloud.h"

//****************************************
// マクロ定義
//****************************************
#define MD_GAME_RESULT_MENU_POS D3DXVECTOR3(SCREEN_WIDTH*0.5f,SCREEN_HEIGHT+(PIXEL*-32),0.0f)
#define MD_GAME_RANKING_POS D3DXVECTOR3(SCREEN_WIDTH*0.5f,(SCREEN_HEIGHT*0.5f)-PIXEL*8,0.0f)
#define MAX_TYPE	(1)
//========== *** 状態関連 ***
// 初期の状態
#define INIT_STATE (MD_GAME_STATE_NORMAL)

//****************************************
// 列挙型の定義
//****************************************
// ゲーム画面[00] のリザルトメニュー
typedef enum
{
	MD_GAME_RESULT_MENU_RETRY,			// リトライ
	MD_GAME_RESULT_MENU_BACK_TO_TITLE,	// タイトルに戻る
	MD_GAME_RESULT_MENU_MAX,
}MD_GAME_RESULT_MENU;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 取得 ***
// MD:ゲームのパラメーター初期化
void InitParameterMd_game(Md_game *pMd);

//****************************************
// グローバル変数宣言
//****************************************
Md_game g_md_game;	// MD:ゲームの情報

static int g_aTex2[MAX_TYPE];

// テクスチャパス
char g_aTexturePath2[MAX_TYPE][TXT_MAX] =
{
	"data//TEXTURE//UserInterface//guid.PNG",
};
// MD:ゲーム画面[00] のリザルトメニュー設定情報
Ui_menuSet g_aMd_gameResultMenuSet[MD_GAME_RESULT_MENU_MAX] =
{
	{ UI_MENU_TYPE_NORMAL,"RETRY"        ,true },
	{ UI_MENU_TYPE_NORMAL,"BACK TO TITLE",true },
};

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 基本接続 *** |--------------------
//============================================================

//========================================
// StartMd_gameState関数 - MD:ゲーム画面の状態に応じた開始処理 -
//========================================
void StartMd_gameState(void)
{
	// MD:ゲーム画面の情報のポインタ
	Md_game *pMd = &g_md_game;

	switch (pMd->state)
	{
	case MD_GAME_STATE_NORMAL:

		break;
	case /*/ ランキング /*/MD_GAME_STATE_RANKING: {
		// UI:ランキングフレーム[00] の名前入力設定処理
		SetNameEntryUi_rankingFrame(SetScore(GetChr_player()->nScore));

		// UI:ランキングフレーム[00] の設定処理
		SetUi_rankingFrame(MD_GAME_RANKING_POS);

		break;
	}
	case /*/ リザルト /*/MD_GAME_STATE_RESULT: {
		// UI:メニュー[00] の中心座標を設定
		SetUi_menuPos(MD_GAME_RESULT_MENU_POS);

		// UI:メニュー[00] の設定処理(リザルトメニュー)
		SetUi_menu(
			g_aMd_gameResultMenuSet,
			MD_GAME_RESULT_MENU_MAX);

		break;
	}
	}
}

//========================================
// EndMd_gameState関数 - MD:ゲーム画面の状態に応じた終了処理 -
//========================================
void EndMd_gameState(void)
{
	// MD:ゲーム画面の情報のポインタ
	Md_game *pMd = &g_md_game;

	switch (pMd->state)
	{
	case MD_GAME_STATE_NORMAL:

		break;
	}
}

//========================================
// UpdateMd_gameState関数 - MD:ゲーム画面の状態に応じた更新処理 -
//========================================
void UpdateMd_gameState(void)
{
	// MD:ゲーム画面の情報のポインタ
	Md_game *pMd = &g_md_game;

	switch (pMd->state)
	{
	case MD_GAME_STATE_NORMAL:

		break;
	case /*/ ランキング /*/MD_GAME_STATE_RANKING: {
		if (GetUi_rankingFrame()->state == UI_RANKINGFRAME_STATE_POP)
		{// UI:ランキングフレーム[00] の状態が出現の時、
			SetStateMd_game(MD_GAME_STATE_RESULT);	// 状態をリザルトにする
		}

		break;
	}
	case /*/ リザルト /*/MD_GAME_STATE_RESULT: {
		// リザルトメニューの選択処理
		switch (Ui_menuInput(UI_MENU_INPUT_MODE_UP_AND_DOWN))
		{
		case /*/ リトライ /*/MD_GAME_RESULT_MENU_RETRY: {
			// 画面をゲーム画面[00] に設定
			SetFade();
			pMd->mode = MODE_GAME;
			break;
		}
		case /*/ タイトルに戻る /*/MD_GAME_RESULT_MENU_BACK_TO_TITLE: {
			// 画面をタイトル画面[00] に設定
			SetFade();
			pMd->mode = MODE_TITLE;
			break;
		}
		}

		if (GetFadeSwap())
		{// フェード切り替え時、
			SetMode(pMd->mode);
		}

		break;
	}
	}
}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================

//========================================
// InitParameterMd_game関数 - MD:ゲームのパラメーター初期化 -
// Author:RIKU NISHIMURA
//========================================
void InitParameterMd_game(Md_game *pMd)
{
	pMd->state = MD_GAME_STATE_NONE;	// 状態
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
// InitMd_game関数 - MD:ゲームの初期化処理 -
// Author:RIKU NISHIMURA
//========================================
void InitMd_game(void)
{
	// MD:ゲーム画面の情報のポインタ
	Md_game *pMd = &g_md_game;

	g_aTex2[0] = LoadTexture(g_aTexturePath2[0]);


	// 敵の出現位置の読み込み処理
	LoadSummon();

	// 敵の出現情報の読み込み処理
	LoadTarget();

	// 敵の情報の読み込み処理
	LoadTargetType();

	// パラメーター初期化
	InitParameterMd_game(pMd);

	// 初期状態を設定
	SetStateMd_game(INIT_STATE);

	//カメラ初期化
	InitCamera3D();
	{
		GetCamera3D()->posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		GetCamera3D()->posV = D3DXVECTOR3(0.0f, 140.0f, -140.0f);
	}

	// ブーメラン初期化
	InitBoomerang();

	// 敵初期化
	InitTarget();

	// プレイヤー初期化
	InitChr_player();

	//制限時間設定
	InitTimer();

	//ブーメランの所持数UI初期化
	InitBoomeUI();

	//ブーメランの所持数UI設定
	SetBoomeUI();

	InitUi_menu();			// メニュー
	InitUi_rankingFrame();	// ランキング(UI)
	InitSys_ranking();		// ランキング

	//スコアUI設定
	SetScoreUI();

	//雲設定
	InitCloud();

	//ゲームBGM再生
	PlaySound(1);
}

//========================================
// UninitMd_game関数 - MD:ゲームの終了処理 -
// Author:RIKU NISHIMURA
//========================================
void UninitMd_game(void)
{
	UninitUi_menu();			// メニュー
	UninitUi_rankingFrame();	// ランキング(UI)
	UninitSys_ranking();		// ランキング
}

//========================================
// UpdateMd_game関数 - MD:ゲームの更新処理 -
// Author:RIKU NISHIMURA
//========================================
void UpdateMd_game(void)
{
	// 状態に応じた更新処理
	UpdateMd_gameState();

	//カメラ更新処理
	UpdateCamera3D();

	// プレイヤー更新
	UpdateChr_player();

	// ブーメラン更新処理
	UpdateBoomerang();

	// 敵 更新処理
	UpdateTarget();

	//雲の更新処理
	UpdateCloud();

	//ブーメランの所持数UI設定
	SetBoomeUI();

	UpdateUi_menu();			// メニュー
	UpdateUi_rankingFrame();	// ランキング(UI)
	UpdateSys_ranking();		// ランキング

	if (GetMd_game()->state == MD_GAME_STATE_NORMAL)
	{
		//制限時間更新処理
		UpdateTimer();

		SetScoreUI();	// スコアUI
	}

	// ポリゴン(3D)の設定情報
	Polygon3DSet polygon3DSet;
	polygon3DSet.nTex = g_aTex2[0];
	polygon3DSet.nPtn = 0;
	polygon3DSet.nPtnX = 1;
	polygon3DSet.nPtnY = 1;
	polygon3DSet.fWidth = 80;
	polygon3DSet.fHeight = 80;
	polygon3DSet.pos = D3DXVECTOR3(-110.0f, -10.0f, 30.0f);
	polygon3DSet.rot = D3DXVECTOR3(-D3DX_PI * 0.25f, 0.0f, 0.0f);
	polygon3DSet.col = Color{ 255,255,255,255 };
	// ポリゴン(3D)の設定処理
	SetPolygon3D(polygon3DSet);
}

//========================================
// DrawMd_game関数 - MD:ゲームの描画処理 -
// Author:RIKU NISHIMURA
//========================================
void DrawMd_game(void)
{
	//カメラ設定
	SetCamera3D();

	//ブーメラン（コンボ表示）
	DrawBoomerang();
}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================
//========================================
// GetMd_game関数 - MD:ゲームの情報を取得 -
// Author:RIKU NISHIMURA
//========================================
Md_game *GetMd_game(void)
{
	return &g_md_game;
}

//============================================================
//--------------------| *** 設定 *** |------------------------
//============================================================

//========================================
// SetStateMd_game関数 - MD:ゲームの状態設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetStateMd_game(MD_GAME_STATE state)
{
	// MD:ゲーム画面の情報のポインタ
	Md_game *pMd = &g_md_game;

	// 状態に応じた終了処理
	EndMd_gameState();

	// 状態を代入
	pMd->state = state;

	// 状態に応じた開始処理
	StartMd_gameState();
}