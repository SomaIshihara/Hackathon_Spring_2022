//========================================
// 
// UI:ランキングフレーム[00] のヘッダファイル
// Author:西村 吏功
// 
//========================================
// *** ui_ranking-frame.h ***
//========================================
#ifndef _UI_RANKINGFRAME_H_	// このマクロ定義がされていなかった時
#define _UI_RANKINGFRAME_H_	// 二重インクルード防止のマクロを定義する

#include "../main.h"

//****************************************
// 列挙型の定義
//****************************************
// UI:ランキングフレーム[00] の状態
typedef enum
{
	UI_RANKINGFRAME_STATE_POP,		// 出現
	UI_RANKINGFRAME_STATE_IN_POP,	// 出現中
	UI_RANKINGFRAME_STATE_CLEAR,		// 消えている
	UI_RANKINGFRAME_STATE_IN_CLEAR,	// 消え中
	UI_RANKINGFRAME_STATE_TEXT_SET,	// ランキングセット
	UI_RANKINGFRAME_STATE_MAX,
}UI_RANKINGFRAME_STATE;

//****************************************
// 構造体の定義
//****************************************
// UI:ランキングフレーム[00] の情報構造体
typedef struct
{
	UI_RANKINGFRAME_STATE	state;			// 状態
	int							nCounterState;	// 状態カウンター
	float						fAlpha;			// 全体の透明度
	D3DXVECTOR3					pos;			// 位置
	Scale						scale;			// 拡大倍率
	bool						bNameEntry;		// 名前入力
	int							nCountName;		// 名前カウント
	int							nCountChar;		// 文字カウント
	int							nUpdateRank;	// 更新順位
	int							nCounterBlink;	// 点滅カウンター
}Ui_rankingFrame;

//****************************************
// プロトタイプ宣言
//****************************************
// UI:ランキングフレーム[00] の情報を取得
Ui_rankingFrame *GetUi_rankingFrame(void);

// UI:ランキングフレーム[00] の初期化処理
// UI:ランキングフレーム[00] の終了処理
// UI:ランキングフレーム[00] の更新処理
// UI:ランキングフレーム[00] の描画処理
void InitUi_rankingFrame(void);
void UninitUi_rankingFrame(void);
void UpdateUi_rankingFrame(void);
void DrawUi_rankingFrame(void);

// UI:ランキングフレーム[00] の状態設定処理
// UI:ランキングフレーム[00] の設定処理
void SetStateUi_rankingFrame(UI_RANKINGFRAME_STATE state);
void SetUi_rankingFrame(D3DXVECTOR3 pos);

// UI:ランキングフレーム[00] の名前入力設定処理
void SetNameEntryUi_rankingFrame(int nUpdateRank);

#endif