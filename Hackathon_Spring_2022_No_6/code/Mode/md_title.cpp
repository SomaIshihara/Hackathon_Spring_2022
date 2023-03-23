//========================================
// 
// MD:タイトルの処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** md_title.cpp ***
//========================================
#include "../main.h"
#include "md_title.h"
#include "../_R.N.Lib/R.N.Lib.h"
#include "../UserInterface/ui_menu.h"
#include "../UserInterface/ui_title-logo.h"

//****************************************
// マクロ定義
//****************************************
// タイトル画面[00] のメインメニューの位置
// タイトル画面[00] のランキングメニューの位置
// タイトル画面[00] のランキングの位置
#define MD_TITLE_MAIN_MENU_POS		D3DXVECTOR3((PIXEL*80),SCREEN_HEIGHT-PIXEL*64,0.0f)
#define MD_TITLE_RANKING_MENU_POS	D3DXVECTOR3((PIXEL*80),SCREEN_HEIGHT-PIXEL*32,0.0f)
#define MD_TITLE_RANKING_POS			D3DXVECTOR3((PIXEL*80),SCREEN_HEIGHT*0.5f,0.0f)

//========== *** 状態関連 ***
// 初期の状態
#define INIT_STATE (MD_TITLE_STATE_NORMAL)

//****************************************
// 列挙型の定義
//****************************************
// タイトル画面[00] のユーザーガイドメニュー
typedef enum
{
	MD_TITLE_USERGUID_MENU_OK,	// OK
	MD_TITLE_USERGUID_MENU_MAX,
}MD_TITLE_USERGUID_MENU;

// タイトル画面[00] のランキングメニュー
typedef enum
{
	MD_TITLE_RANKING_MENU_OK,	// OK
	MD_TITLE_RANKING_MENU_MAX,
}MD_TITLE_RANKING_MENU;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 取得 ***
// MD:タイトルのパラメーター初期化
void InitParameterMd_title(Md_title *pMd);

//****************************************
// グローバル変数宣言
//****************************************
Md_title g_md_title;	// MD:タイトルの情報

// MD:タイトル画面[00] のメインメニュー設定情報
Ui_menuSet g_aMd_titleMainMenuSet[MD_TITLE_MAIN_MENU_MAX] =
{
	{ UI_MENU_TYPE_NORMAL,"START"    ,false },
	{ UI_MENU_TYPE_NORMAL,"RANKING"  ,true },
	{ UI_MENU_TYPE_NORMAL,"QUIT"     ,false },
};

// MD:タイトル画面[00] のランキングメニュー設定情報
Ui_menuSet g_aMd_titleRankingMenuSet[MD_TITLE_RANKING_MENU_MAX] =
{
	{ UI_MENU_TYPE_NORMAL,"OK",true },
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
// StartMd_titleState関数 - MD:タイトル画面の状態に応じた開始処理 -
//========================================
void StartMd_titleState(void)
{
	Md_title	*pMd	// MD:タイトル画面[00] の情報
		= &g_md_title;

	// 状態カウンターを初期化
	pMd->nCounterState = 0;

	switch (pMd->state)
	{
	case /*/ 通常 /*/MD_TITLE_STATE_NORMAL: {
		// UI:メニュー[00] の中心座標を設定
		SetUi_menuPos(MD_TITLE_MAIN_MENU_POS);

		// UI:メニュー[00] の設定処理(メインメニュー)
		SetUi_menu(
			g_aMd_titleMainMenuSet,
			MD_TITLE_MAIN_MENU_MAX);

		break;
	}
	case /*/ ランキング /*/MD_TITLE_STATE_RANKING: {
		// UI:メニュー[00] の中心座標を設定
		SetUi_menuPos(MD_TITLE_RANKING_MENU_POS);

		// UI:メニュー[00] の設定処理(ランキングメニュー)
		SetUi_menu(
			g_aMd_titleRankingMenuSet,
			MD_TITLE_RANKING_MENU_MAX);

		break;
	}
	}
}

//========================================
// EndMd_titleState関数 - MD:タイトル画面の状態に応じた終了処理 -
//========================================
void EndMd_titleState(void)
{
	Md_title	*pMd	// MD:タイトル画面[00] の情報
		= &g_md_title;

	switch (pMd->state)
	{
	case /*/ 通常 /*/MD_TITLE_STATE_NORMAL: {
		break;
	}
	case /*/ ランキング /*/MD_TITLE_STATE_RANKING: {
		break;
	}
	}
}

//========================================
// UpdateMd_titleState関数 - MD:タイトル画面の状態に応じた更新処理 -
//========================================
void UpdateMd_titleState(void)
{
	Md_title	*pMd	// MD:タイトル画面[00] の情報
		= &g_md_title;

	switch (pMd->state)
	{
	case /*/ 通常 /*/MD_TITLE_STATE_NORMAL: {
		// メインメニューの選択処理
		switch (Ui_menuInput(UI_MENU_INPUT_MODE_UP_AND_DOWN))
		{
		case /*/ 開始 /*/MD_TITLE_MAIN_MENU_START: {
			// 画面をゲーム画面[00] に設定
			SetFade();

			// 決定SEを再生
			//PlaySound(MD_TITLE_DETERMINATION_SE);
			break;
		}
		case /*/ ランキング /*/MD_TITLE_MAIN_MENU_RANKING: {
			// UI:ランキングフレーム[00] の設定処理
			//SetUi_rankingFrame(MD_TITLE_RANKING_POS);

			break;
		}
		case /*/ 終了 /*/MD_TITLE_MAIN_MENU_EXIT: {
			// ウインドウを破棄する
			DestroyWindow(*GetWindowHandle());
			break;
		}
		}

		if (GetFadeSwap()) 
		{// フェードの切り替えを取得した時、
			SetMode(MODE_GAME);
		}

		//if (GetUi_rankingFrame()->state == UI_RANKINGFRAME_STATE_POP)
		//{// UI:ランキングフレーム[00] の状態が出現の時、
		//	SetMd_titleState(MD_TITLE_STATE_RANKING);	// 状態をランキングにする
		//}

		break;
	}
	case /*/ ランキング /*/MD_TITLE_STATE_RANKING: {
		// ランキングメニューの選択処理
		switch (Ui_menuInput(UI_MENU_INPUT_MODE_UP_AND_DOWN))
		{
		case /*/ OK /*/MD_TITLE_RANKING_MENU_OK: {
			//// UI:ランキングフレーム[00] の状態を消え中にする
			//SetStateUi_rankingFrame(UI_RANKINGFRAME_STATE_IN_CLEAR);

			break;
		}
		}

		//if (GetUi_rankingFrame()->state == UI_RANKINGFRAME_STATE_CLEAR)
		//{// UI:ランキングフレーム[00] の状態が消えている時、
		//	SetMd_titleState(MD_TITLE_STATE_NORMAL);	// 状態を通常にする
		//}

		break;
	}
	}
}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================

//========================================
// InitParameterMd_title関数 - MD:タイトルのパラメーター初期化 -
// Author:RIKU NISHIMURA
//========================================
void InitParameterMd_title(Md_title *pMd)
{
	pMd->state = MD_TITLE_STATE_NONE;	// 状態
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
// InitMd_title関数 - MD:タイトルの初期化処理 -
// Author:RIKU NISHIMURA
//========================================
void InitMd_title(void) 
{
	// MD:タイトル画面の情報のポインタ
	Md_title *pMd = &g_md_title;

	// パラメーター初期化
	InitParameterMd_title(pMd);

	InitUi_menu();
	InitUi_titleLogo();

	// 初期状態を設定
	SetStateMd_title(INIT_STATE);
}

//========================================
// UninitMd_title関数 - MD:タイトルの終了処理 -
// Author:RIKU NISHIMURA
//========================================
void UninitMd_title(void) 
{
	UninitUi_menu();
	UninitUi_titleLogo();
}

//========================================
// UpdateMd_title関数 - MD:タイトルの更新処理 -
// Author:RIKU NISHIMURA
//========================================
void UpdateMd_title(void) 
{
	// 状態に応じた更新処理
	UpdateMd_titleState();

	UpdateUi_menu();
	UpdateUi_titleLogo();
}

//========================================
// DrawMd_title関数 - MD:タイトルの描画処理 -
// Author:RIKU NISHIMURA
//========================================
void DrawMd_title(void)
{
	DrawUi_menu();
	DrawUi_titleLogo();
}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================
//========================================
// GetMd_title関数 - MD:タイトルの情報を取得 -
// Author:RIKU NISHIMURA
//========================================
Md_title *GetMd_title(void) 
{
	return &g_md_title;
}

//============================================================
//--------------------| *** 設定 *** |------------------------
//============================================================

//========================================
// SetStateMd_title関数 - MD:タイトルの状態設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetStateMd_title(MD_TITLE_STATE state)
{
	// MD:タイトル画面の情報のポインタ
	Md_title *pMd = &g_md_title;

	// 状態に応じた終了処理
	EndMd_titleState();
	
	// 状態を代入
	pMd->state = state;

	// 状態に応じた開始処理
	StartMd_titleState();
}