//========================================
// 
// MD:リザルトの処理
// Author:RIKU NISHIMURA
// 
//========================================
//  *** md_result.h ***
//========================================
#ifndef _MD_RESULT_H_	// このマクロ定義がされていなかった時
#define _MD_RESULT_H_	// 二重インクルード防止のマクロを定義する

//****************************************
// 列挙型の定義
//****************************************
// MD:リザルトの状態
typedef enum
{
	MD_RESULT_STATE_NONE,	// 無し
	MD_RESULT_STATE_NORMAL,	// 通常
	MD_RESULT_STATE_MAX,
}MD_RESULT_STATE;

//****************************************
// 構造体の定義
//****************************************
// MD:リザルトの情報構造体
typedef struct
{
	// 状態関連
	MD_RESULT_STATE state;	// MD:リザルト画面[00] の状態
}Md_result;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 基本接続 ***
// MD:リザルトの初期化処理
void InitMd_result(void);
// MD:リザルトの終了処理
void UninitMd_result(void);
// MD:リザルトの更新処理
void UpdateMd_result(void);
// MD:リザルトの描画処理
void DrawMd_result(void);
//========== *** 取得 ***
// MD:リザルトの情報を取得
Md_result *GetMd_result(void);
//========== *** 設定 ***
// MD:リザルトの状態設定処理
void SetStateMd_result(MD_RESULT_STATE state);

#endif