//========================================
// 
// MD:タイトルの処理
// Author:RIKU NISHIMURA
// 
//========================================
//  *** md_title.h ***
//========================================
#ifndef _MD_TITLE_H_	// このマクロ定義がされていなかった時
#define _MD_TITLE_H_	// 二重インクルード防止のマクロを定義する

//****************************************
// 列挙型の定義
//****************************************
// MD:タイトルの状態
typedef enum
{
	MD_TITLE_STATE_NONE,	// 無し
	MD_TITLE_STATE_NORMAL,	// 通常
	MD_TITLE_STATE_MAX,
}MD_TITLE_STATE;

//****************************************
// 構造体の定義
//****************************************
// MD:タイトルの情報構造体
typedef struct
{
	// 状態関連
	MD_TITLE_STATE state;	// MD:タイトル画面[00] の状態
}Md_title;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 基本接続 ***
// MD:タイトルの初期化処理
void InitMd_title(void);
// MD:タイトルの終了処理
void UninitMd_title(void);
// MD:タイトルの更新処理
void UpdateMd_title(void);
// MD:タイトルの描画処理
void DrawMd_title(void);
//========== *** 取得 ***
// MD:タイトルの情報を取得
Md_title *GetMd_title(void);
//========== *** 設定 ***
// MD:タイトルの状態設定処理
void SetStateMd_title(MD_TITLE_STATE state);

#endif