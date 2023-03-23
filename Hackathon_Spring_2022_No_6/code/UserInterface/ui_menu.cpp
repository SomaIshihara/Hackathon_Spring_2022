//========================================
// 
// UI:メニュー の処理
// Author:RIKU NISHIMURA
// 
//========================================
//  *** ui_menu.cpp ***
//========================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../_R.N.Lib/R.N.Lib.h"

#include "ui_menu.h"	// UI:メニュー

//****************************************
// マクロ定義
//****************************************
// UI:メニュー の最大数
#define UI_MENU_MAX (16)
// UI:メニュー の幅
#define UI_MENU_WIDTH (PIXEL * 256)
// UI:メニュー の高さ
#define UI_MENU_HEIGHT (PIXEL * 16)
// UI:メニュー の選択時の色
#define UI_MENU_SELECT_COLOR (Color{243, 189, 63, 255})

// UI:メニュー の配置間隔X
#define UI_MENU_SPACE_X (PIXEL * 0)
// UI:メニュー の配置間隔Y
#define UI_MENU_SPACE_Y (PIXEL * 16)
// UI:メニュー が消えるのにかかる時間
#define UI_MENU_CLEAR_TIME (4)

// UI:メニュー の出現にかかる時間
#define UI_MENU_APPEAR_TIME (10)
// UI:メニュー の出現している時の大きさにかかる倍率
#define UI_MENU_APPEAR_SCALE Scale{1.0f,1.0f,0.0f}
// UI:メニュー の消えている時の大きさにかかる倍率
#define UI_MENU_DISAPPEAR_SCALE Scale{1.0f,0.0f,0.0f}

//****************************************
// 構造体の定義
//****************************************
// UI:メニュー の予約情報
typedef struct 
{
	bool			bReservation;	// 予約フラグ
	Ui_menuSet	*pSet;			// 設定情報のポインタ
	int				nNum;			// メニュー数
}Ui_menuReservation;

//****************************************
// プロトタイプ宣言
//****************************************
// UI:メニュー のパラメーター初期化処理
// UI:メニュー の管理情報のパラメーター初期化処理
// UI:メニュー の予約情報のパラメーター初期化処理
void InitParameterUi_menu(Ui_menu *pUi);
void InitParameterUi_menuControl(void);
void InitParameterUi_menuReservation(void);

// UI:メニュー の状態処理
// UI:メニュー の作成処理
void StateProcessUi_menu(void);
void CreateUi_menu(void);

//****************************************
// グローバル宣言
//****************************************
static int g_aTex[UI_MENU_TYPE_MAX];		// テクスチャ
Ui_menu g_aUi_menu[UI_MENU_MAX];			// UI:メニュー の情報
Ui_menuControl g_ui_menuControl;			// UI:メニュー の管理情報
Ui_menuReservation g_ui_menuReservation;	// UI:メニュー の予約情報

// UI:メニュー のテクスチャファイルの相対パス
char g_aTexturePath[UI_MENU_TYPE_MAX][TXT_MAX] =
{
	"data\\TEXTURE\\UserInterface\\ui_menu\\normal.png",
	"data\\TEXTURE\\UserInterface\\ui_menu\\select.png",
};

//========== *** UI:メニュー の情報を取得 ***
Ui_menu *GetUi_menu(void) 
{
	return g_aUi_menu;
}

//========== *** UI:メニュー の全体管理の情報を取得 ***
Ui_menuControl *GetUi_menuControl(void) 
{
	return &g_ui_menuControl;
}

//========== *** UI:メニュー の現在の選択番号を取得 ***
int *GetSelect(void) 
{
	return &g_ui_menuControl.nSelect;
}


//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitParameterUi_menu関数 - UI:メニュー のパラメーター初期化処理 -
//========================================
void InitParameterUi_menu(Ui_menu *pUi)
{
	pUi->pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 位置
	pUi->type		= (UI_MENU_TYPE)0;				// 種類
	pUi->bUse		= false;							// 使用されているかフラグ
	pUi->bSelect	= false;							// 選択されているかフラグ
	sprintf(pUi->aString, "");							// 表示する文字列
	pUi->nSelectNum = 0;								// 現在の選択肢の番号
}

//========================================
// InitParameterUi_menuControl関数 - UI:メニュー の管理情報のパラメーター初期化処理 -
//========================================
void InitParameterUi_menuControl(void)
{
	Ui_menuControl	*pUiCtl	// UI:メニュー の管理情報のポインタ
						= &g_ui_menuControl;

	pUiCtl->state			= UI_MENU_STATE_NONE;			// 状態 
	pUiCtl->nCounterState	= 0;								// 状態のカウンター 
	pUiCtl->scale			= { 0.0f,0.0f,0.0f };				// 拡大率 
	pUiCtl->nNum			= 0;								// 現在の使用数 
	pUiCtl->nSelect			= 0;								// 現在の選択番号 
	pUiCtl->centerPos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// 中心座標 
}

//========================================
// InitParameterUi_menuReservation関数 - UI:メニュー の予約情報のパラメーター初期化処理 -
//========================================
void InitParameterUi_menuReservation(void)
{
	Ui_menuReservation	*pUiRsv	// UI:メニュー の予約情報のポインタ
							= &g_ui_menuReservation;

	pUiRsv->bReservation	= false;	// 予約フラグ
	pUiRsv->pSet			= NULL;		// 設定情報のポインタ
	pUiRsv->nNum			= 0;		// メニュー数
}

//========================================
// StateProcessUi_menu関数 - UI:メニュー の状態処理 -
//========================================
void StateProcessUi_menu(void)
{
	Ui_menuControl	*pUiCtl	// UI:メニュー の管理情報のポインタ
						= &g_ui_menuControl;

	switch (pUiCtl->state)
	{
		//========== *** 出現中 ***
	case UI_MENU_STATE_IN_POP: {
		if (--pUiCtl->nCounterState <= 0)
		{// 状態のカウンターを減算した結果0以下の時、
			// 出現状態にする
			pUiCtl->state = UI_MENU_STATE_POP;
		}

		float	fRate	// 割合 
				= (float)pUiCtl->nCounterState / (float)UI_MENU_APPEAR_TIME;

		// 大きさにかかる倍率を更新
		pUiCtl->scale.fWidth =
			(UI_MENU_APPEAR_SCALE.fWidth * (1.0f - fRate)) +
			(UI_MENU_DISAPPEAR_SCALE.fWidth * fRate);
		pUiCtl->scale.fHeight =
			(UI_MENU_APPEAR_SCALE.fHeight * (1.0f - fRate)) +
			(UI_MENU_DISAPPEAR_SCALE.fHeight * fRate);
	}
		break;
		//========== *** 出現 ***
	case UI_MENU_STATE_POP: {
	}
		break;
		//========== *** 消え中 ***
	case UI_MENU_STATE_IN_CLEAR: {
		if (--pUiCtl->nCounterState <= 0)
		{// 状態のカウンターを減算した結果0以下の時、
			// 状態を無しにする
			pUiCtl->state = UI_MENU_STATE_NONE;

			// UI:メニュー を全て使用していない状態にする
			for (int nCntUi = 0; nCntUi < UI_MENU_MAX; nCntUi++) {
				g_aUi_menu[nCntUi].bUse = false;
			}
		}

		float	fRate	// 割合 
				= (float)pUiCtl->nCounterState / (float)UI_MENU_CLEAR_TIME;

		// 大きさにかかる倍率を更新
		pUiCtl->scale.fWidth =
			(UI_MENU_APPEAR_SCALE.fWidth * fRate) +
			(UI_MENU_DISAPPEAR_SCALE.fWidth * (1.0f - fRate));
		pUiCtl->scale.fHeight =
			(UI_MENU_APPEAR_SCALE.fHeight * fRate) +
			(UI_MENU_DISAPPEAR_SCALE.fHeight * (1.0f - fRate));
	}
		break;
	}
}

//========================================
// CreateUi_menu関数 - UI:メニュー の作成処理 -
//========================================
void CreateUi_menu(void)
{
	Ui_menuControl		*pUiCtl	// UI:メニュー の管理情報のポインタ
							= &g_ui_menuControl;
	Ui_menuReservation	*pUiRsv	// UI:メニュー の予約情報のポインタ
							= &g_ui_menuReservation;

	if ((!pUiRsv->bReservation)
		||
		(pUiCtl->state != UI_MENU_STATE_NONE))
	{// メニューの予約が無い、もしくは状態が無しでない時、
		// 処理を終了する
		return;
	}

	pUiRsv->bReservation	= false;					// 予約フラグを偽にする
	pUiCtl->state			= UI_MENU_STATE_IN_POP;	// 出現中にする
	pUiCtl->nCounterState	= UI_MENU_APPEAR_TIME;	// 状態カウンターを設定
	pUiCtl->nSelect			= 0;						// 現在の選択番号を初期化する
	pUiCtl->nNum			= pUiRsv->nNum;				// 現在の使用数を予約情報から代入

	Ui_menu	*pUi	// UI:メニュー の情報のポインタ 
				= g_aUi_menu;

	for (int nCntUi = 0; nCntUi < pUiRsv->nNum; nCntUi++, pUi++)
	{
		Ui_menuSet	*pSet	// UI:メニュー の設定情報のポインタ
						= &pUiRsv->pSet[nCntUi];

		pUi->type		= pSet->type;			// 種類を代入
		pUi->bUse		= true;					// 使用されている状態にする
		pUi->bSelect	= false;				// 選択されていない状態にする
		sprintf(pUi->aString, pSet->aString);	// 文字列を代入

		// 位置を設定
		pUi->pos =
			D3DXVECTOR3(
				pUiCtl->centerPos.x - (((pUiRsv->nNum - 1) * UI_MENU_SPACE_X) * 0.5f) + (nCntUi * UI_MENU_SPACE_X),
				pUiCtl->centerPos.y - (((pUiRsv->nNum - 1) * UI_MENU_SPACE_Y) * 0.5f) + (nCntUi * UI_MENU_SPACE_Y), 0.0f);

		// ポリゴン(2D)の設定情報
		Polygon2DSet polySet;
		/* テクスチャ番号	*/polySet.nTex = g_aTex[pUi->type];
		/* パターン番号		*/polySet.nPtn = 0;
		/* パターン上限X	*/polySet.nPtnX = 1;
		/* パターン上限Y	*/polySet.nPtnY = 1;
		/* 幅				*/polySet.fWidth = UI_MENU_WIDTH * pUiCtl->scale.fWidth;
		/* 高さ				*/polySet.fHeight = UI_MENU_HEIGHT * pUiCtl->scale.fHeight;
		/* 位置				*/polySet.pos = pUi->pos;
		/* 向き				*/polySet.rot = INITD3DXVECTOR3;
		/* 色				*/polySet.col = nCntUi == g_ui_menuControl.nSelect ? UI_MENU_SELECT_COLOR : Color{ 255,255,255,255 };
		/* カメラ合わせ		*/polySet.bMatchCamera = false;
		// ポリゴン(2D)の設定処理
		SetPolygon2D(polySet);
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitUi_menu関数 - UI:メニュー の初期化処理 -
//========================================
void InitUi_menu(void)
{
	InitParameterUi_menuControl();		// 管理情報のパラメーター初期化
	InitParameterUi_menuReservation();	// 予約情報のパラメーター初期化

	for (int nCntTex = 0; nCntTex < UI_MENU_TYPE_MAX; nCntTex++) 
	{
		g_aTex[nCntTex] = LoadTexture(g_aTexturePath[nCntTex]);
	}
}

//========================================
// UninitUi_menu関数 - UI:メニュー の終了処理 -
//========================================
void UninitUi_menu(void)
{
	
}

//========================================
// UpdateUi_menu関数 - UI:メニュー の更新処理 -
//========================================
void UpdateUi_menu(void)
{
	StateProcessUi_menu();	// 状態処理
	CreateUi_menu();		// 作成処理

	Ui_menu			*pUi	// UI:メニュー の情報のポインタ
						= g_aUi_menu;
	Ui_menuControl	*pUiCtl	// UI:メニュー の管理情報のポインタ
						= &g_ui_menuControl;

	for (int nCntUi = 0; nCntUi < UI_MENU_MAX; nCntUi++, pUi++)
	{
		if (!pUi->bUse)
		{// 使用されていない時、
			// 繰り返し処理をリセット
			continue;
		}

		// ポリゴン(2D)の設定情報
		Polygon2DSet polySet;
		/* テクスチャ番号	*/polySet.nTex = g_aTex[pUi->type];
		/* パターン番号		*/polySet.nPtn = 0;
		/* パターン上限X	*/polySet.nPtnX = 1;
		/* パターン上限Y	*/polySet.nPtnY = 1;
		/* 幅				*/polySet.fWidth = UI_MENU_WIDTH * pUiCtl->scale.fWidth;
		/* 高さ				*/polySet.fHeight = UI_MENU_HEIGHT * pUiCtl->scale.fHeight;
		/* 位置				*/polySet.pos = pUi->pos;
		/* 向き				*/polySet.rot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI);
		/* 色				*/polySet.col = nCntUi == g_ui_menuControl.nSelect ? UI_MENU_SELECT_COLOR : Color{ 255,255,255,255 };
		/* カメラ合わせ		*/polySet.bMatchCamera = false;
		// ポリゴン(2D)の設定処理
		SetPolygon2D(polySet);

		// テキスト(2D)の設定処理
		Text2DSet text2DSet;
		/* 文字列のポインタ */text2DSet.pString = pUi->aString;
		/* フォント番号		*/text2DSet.nFont = 0;
		/* 表示形式			*/text2DSet.disp = TEXT_DISP_CENTER;
		/* 位置				*/text2DSet.pos = pUi->pos;
		/* 向き				*/text2DSet.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		/* 色				*/text2DSet.col = INITCOLOR;
		/* 幅				*/text2DSet.fWidth = pUiCtl->scale.fWidth * 8 * PIXEL;
		/* 高さ				*/text2DSet.fHeight = pUiCtl->scale.fHeight * 8 * PIXEL;
		/* カメラ合わせ		*/text2DSet.bMatchCamera = false;
		// テキスト(2D)の設定処理
		SetText2D(text2DSet);
	}
}

//========================================
// Ui_menuInput関数 - UI:メニュー の入力処理 -
//========================================
int Ui_menuInput(UI_MENU_INPUT_MODE mode)
{
	int					nSelected	// 選択した番号(-1は選択無し)
						= -1;
	Ui_menuControl	*pUiCtl		// UI:メニュー の管理情報のポインタ
						= &g_ui_menuControl;

	if ((pUiCtl->state != UI_MENU_STATE_POP)
		||
		(GetFade() != FADE_NONE))
	{// 出現状態でない or フェード中の時、
		// 処理を終了する
		return nSelected;
	}

	{
		bool	bInput	// 入力フラグ
				= false;

		if (
			(((GetKeyboardRepeat(DIK_UP))
			|| (GetKeyboardRepeat(DIK_W))
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_UP])
			|| (GetButtonRepeat(BUTTON_UP)))
			&& (mode == UI_MENU_INPUT_MODE_UP_AND_DOWN))
			||
			(((GetKeyboardRepeat(DIK_LEFT))
			|| (GetKeyboardRepeat(DIK_A))
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_LEFT])
			|| (GetButtonRepeat(BUTTON_LEFT)))
			&& (mode == UI_MENU_INPUT_MODE_LEFT_AND_RIGHT)))
		{// 上入力時、
			g_ui_menuControl.nSelect--;	// 現在の選択番号を減算
			bInput = true;					// 入力フラグを真にする
		}
		else if (
			(((GetKeyboardRepeat(DIK_DOWN))
			|| (GetKeyboardRepeat(DIK_S))
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_DOWN])
			|| (GetButtonRepeat(BUTTON_DOWN)))
			&& (mode == UI_MENU_INPUT_MODE_UP_AND_DOWN))
			||
			(((GetKeyboardRepeat(DIK_RIGHT))
			|| (GetKeyboardRepeat(DIK_D))
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_RIGHT])
			|| (GetButtonRepeat(BUTTON_RIGHT)))
			&& (mode == UI_MENU_INPUT_MODE_LEFT_AND_RIGHT)))
		{// 下/右入力時、
			g_ui_menuControl.nSelect++;	// 現在の選択番号を加算
			bInput = true;					// 入力フラグを真にする
		}

		if ((g_ui_menuReservation.nNum != 1) && (bInput))
		{// メニューの数が1で無い & 入力フラグが真の時、
			//PlaySound(UI_MENU_SELECT_SE);	// 選択SEを再生
		}
	}

	// 選択番号をループ制御
	IntLoopControl(&pUiCtl->nSelect, pUiCtl->nNum, 0);

	if (g_aUi_menu[g_ui_menuControl.nSelect].type == UI_MENU_TYPE_SELECTION)
	{// 種類が選択の時、
		if (
			(GetKeyboardRepeat(DIK_LEFT))
			|| (GetKeyboardRepeat(DIK_RIGHT))
			|| (GetKeyboardRepeat(DIK_A))
			|| (GetKeyboardRepeat(DIK_D))
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_LEFT])
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_RIGHT])
			|| (GetButtonRepeat(BUTTON_LEFT))
			|| (GetButtonRepeat(BUTTON_RIGHT)))
		{// 左/右入力時、
			nSelected = g_ui_menuControl.nSelect;	// 選択した番号に現在の選択番号を代入
			//PlaySound(UI_MENU_SELECT_SE);			// 選択SEを再生
		}
	}
	else if ((GetKeyboardTrigger(DIK_RETURN)) || (GetButtonTrigger(BUTTON_A)))
	{// ENTERキー or Aボタン or マウス左ボタンが入力された時、
		nSelected = g_ui_menuControl.nSelect;					// 選択した番号に現在の選択番号を代入
		g_ui_menuControl.state = UI_MENU_STATE_IN_CLEAR;		// 消え中にする
		g_ui_menuControl.nCounterState = UI_MENU_CLEAR_TIME;	// 状態カウンターを設定する
		if (g_ui_menuReservation.pSet[nSelected].bDecisionSE)
		{// 決定SEフラグが真の時、決定SEを再生
			//PlaySound(UI_MENU_DETERMINATION_SE);
		}
	}
	
	// 選択した番号を返す
	return nSelected;
}

//========================================
// DrawUi_menu関数 - UI:メニュー の描画処理 -
//========================================
void DrawUi_menu(void)
{
	
}

//========================================
// SetUi_menuPos関数 - UI:メニュー の中心座標を設定 -
//========================================
void SetUi_menuPos(D3DXVECTOR3 pos)
{
	Ui_menuControl	*pUiCtl		// UI:メニュー の管理情報のポインタ
						= &g_ui_menuControl;

	// 中心座標を代入
	pUiCtl->centerPos = pos;
}

//========================================
// SetUi_menu関数 - UI:メニュー の設定処理 -
//========================================
void SetUi_menu(Ui_menuSet *pSet, int nNum)
{
	g_ui_menuReservation.bReservation	= true;	// 予約フラグを真にする
	g_ui_menuReservation.pSet			= pSet;	// 設定情報のポインタを代入
	g_ui_menuReservation.nNum			= nNum;	// メニュー数を代入
}