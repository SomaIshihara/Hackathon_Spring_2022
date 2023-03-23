//========================================
// 
// MD:ゲームの処理
// Author:RIKU NISHIMURA
// 
//========================================
//  *** md_game.h ***
//========================================
#ifndef _MD_GAME_H_	// このマクロ定義がされていなかった時
#define _MD_GAME_H_	// 二重インクルード防止のマクロを定義する

#include "../main.h"

//****************************************
// 列挙型の定義
//****************************************
// MD:ゲームの状態
typedef enum
{
	MD_GAME_STATE_NONE,		// 無し
	MD_GAME_STATE_NORMAL,	// 通常
	MD_GAME_STATE_RANKING,	// ランキング
	MD_GAME_STATE_RESULT,	// リザルト
	MD_GAME_STATE_MAX,
}MD_GAME_STATE;

//****************************************
// 構造体の定義
//****************************************
// MD:ゲームの情報構造体
typedef struct
{
	// 状態関連
	MD_GAME_STATE state;	// MD:ゲーム画面[00] の状態
	MODE mode;	// 移動先のモード
}Md_game;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 基本接続 ***
// MD:ゲームの初期化処理
void InitMd_game(void);
// MD:ゲームの終了処理
void UninitMd_game(void);
// MD:ゲームの更新処理
void UpdateMd_game(void);
// MD:ゲームの描画処理
void DrawMd_game(void);
//========== *** 取得 ***
// MD:ゲームの情報を取得
Md_game *GetMd_game(void);
//========== *** 設定 ***
// MD:ゲームの状態設定処理
void SetStateMd_game(MD_GAME_STATE state);

#endif