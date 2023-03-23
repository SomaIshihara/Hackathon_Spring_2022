//========================================
// 
// UI:メニュー のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// *** ui_menu.h ***
//========================================
#ifndef UI_MENU_H_	// このマクロ定義がされていなかった時
#define UI_MENU_H_	// 二重インクルード防止のマクロを定義する

//****************************************
// 列挙型の定義
//****************************************
// UI:メニュー の入力モード
typedef enum
{
	UI_MENU_INPUT_MODE_UP_AND_DOWN,		// 上下
	UI_MENU_INPUT_MODE_LEFT_AND_RIGHT,	// 左右
	UI_MENU_INPUT_MODE_MAX
}UI_MENU_INPUT_MODE;

// UI:メニュー の種類
typedef enum
{
	UI_MENU_TYPE_NORMAL,		// 通常
	UI_MENU_TYPE_SELECTION,	// 選択
	UI_MENU_TYPE_MAX
}UI_MENU_TYPE;

// UI:メニュー の状態
typedef enum
{
	UI_MENU_STATE_NONE,
	UI_MENU_STATE_IN_POP,	// 出現中
	UI_MENU_STATE_POP,		// 出現
	UI_MENU_STATE_IN_CLEAR,	// 消え中
	UI_MENU_STATE_MAX
}UI_MENU_STATE;

//****************************************
// 構造体の定義
//****************************************
// UI:メニュー の管理情報構造体
typedef struct
{
	UI_MENU_STATE	state;			// 状態
	int					nCounterState;	// 状態のカウンター
	Scale				scale;			// 拡大率
	int					nNum;			// 現在の使用数
	int					nSelect;		// 現在の選択番号
	D3DXVECTOR3			centerPos;		// 中心座標
}Ui_menuControl;

// UI:メニュー の情報構造体
typedef struct
{
	// 位置関連
	D3DXVECTOR3	pos;	// 位置

	// 分類情報
	UI_MENU_TYPE	type;	// 種類
	
	// 状態値
	bool	bUse;		// 使用されているかフラグ
	bool	bSelect;	// 選択されているかフラグ
	char	aString
			[TXT_MAX];	// 表示する文字列
	int	 nSelectNum;	// 現在の選択肢の番号
}Ui_menu;

// UI:メニュー の設定情報構造体
typedef struct 
{
	UI_MENU_TYPE type;	// 種類
	char *aString;		// 表示する文字列
	bool bDecisionSE;	// 決定SEフラグ
}Ui_menuSet;

//****************************************
// プロトタイプ宣言
//****************************************
// UI:メニュー の情報を取得
Ui_menu *GetUi_menu(void);
// UI:メニュー の全体管理の情報を取得
Ui_menuControl *GetUi_menuControl(void);
// UI:メニュー の現在の選択番号を取得
int *GetSelect(void);
// UI:メニュー の初期化処理
void InitUi_menu(void);
// UI:メニュー の終了処理
void UninitUi_menu(void);
// UI:メニュー の更新処理
void UpdateUi_menu(void);
// UI:メニュー の描画処理
void DrawUi_menu(void);
// UI:メニュー の入力処理
int Ui_menuInput(UI_MENU_INPUT_MODE mode);
// UI:メニュー の中心座標を設定
void SetUi_menuPos(D3DXVECTOR3 pos);
// UI:メニュー の設定処理
void SetUi_menu(Ui_menuSet *pSet, int nNum);

#endif