//========================================
// 
// CHR:プレイヤーのヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
//  *** chr_player.h ***
//========================================
#ifndef _CHR_PLAYER_H_	// このマクロ定義がされていなかった時
#define _CHR_PLAYER_H_	// 二重インクルード防止のマクロを定義する

#include "_R.N.Lib/R.N.Lib.h"
#include "boomerang.h"

//マクロ
#define PLAYER_HIT_RADIUS	(8.0f)	//プレイヤーの当たり判定の半径

//****************************************
// 構造体の定義
//****************************************
// CHR:プレイヤーの情報構造体
typedef struct
{
	// ブーメラン所持数
	int nBoomerang = MAX_USE_BOOMERANG;
	// スコア
	int nScore = 0;
	// 投げカウンター
	int nSlowCounter = 0;

	// 部品関連
	Parts3DInfo partsInfo;	// 部品管理
}Chr_player;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 基本接続 ***
// CHR:プレイヤーの初期化処理
void InitChr_player(void);
// CHR:プレイヤーの更新処理
void UpdateChr_player(void);
//========== *** 取得 ***
// CHR:プレイヤーの情報のポインタを取得
Chr_player *GetChr_player(void);

#endif