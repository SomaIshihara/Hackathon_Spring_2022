//========================================
// 
// SYS:ランキング[00] のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
// *** sys_ranking.h ***
//========================================
#ifndef _SYS_RANKING_H_	// このマクロ定義がされていなかった時
#define _SYS_RANKING_H_	// 二重インクルード防止のマクロを定義する

//****************************************
// マクロ定義
//****************************************
// ランキングの順位数
// ランキング名の文字数
// ランキング名の文字下限
// ランキング名の文字上限
// ランキング名の開始文字
#define RANKING_NUM				(8)
#define RANKING_NAME_NUM		(3)
#define RANKING_NAME_MIN_CHAR	('0')
#define RANKING_NAME_MAX_CHAR	('Z' + 1)
#define RANKING_NAME_START_CHAR	('A')

//****************************************
// 構造体の定義
//****************************************
// ランキング構造体
typedef struct
{
	char	aName	// 名前
			[RANKING_NAME_NUM + 1];
	int		nScore;	// スコア
}Sys_ranking;

//****************************************
// プロトタイプ宣言
//****************************************
// 順位の表示形式を取得
char *GetRankText(int nRank);

// SYS:ランキング[00] の情報を取得
Sys_ranking *GetSys_ranking(void);

// SYS:ランキング[00] の初期化処理
// SYS:ランキング[00] の終了処理
// SYS:ランキング[00] の更新処理
void InitSys_ranking(void);
void UninitSys_ranking(void);
void UpdateSys_ranking(void);

// SYS:ランキング[00] の読み込み処理
// SYS:ランキング[00] の書き込み処理
void LoadSys_ranking(void);
void SaveSys_ranking(void);

// ランキングにスコアを挿入する
int SetScore(int nScore);

#endif