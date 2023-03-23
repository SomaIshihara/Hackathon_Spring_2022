//========================================
// 
// UI:タイトルロゴ のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// *** ui_title-logo.h ***
//========================================
#ifndef _UI_TITLELOGO_H_	// このマクロ定義がされていなかった時
#define _UI_TITLELOGO_H_	// 二重インクルード防止のマクロを定義する

//****************************************
// プロトタイプ宣言
//****************************************
// UI:タイトルロゴ の初期化処理
void InitUi_titleLogo(void);
// UI:タイトルロゴ の終了処理
void UninitUi_titleLogo(void);
// UI:タイトルロゴ の更新処理
void UpdateUi_titleLogo(void);
// UI:タイトルロゴ の描画処理
void DrawUi_titleLogo(void);

#endif