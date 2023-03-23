//========================================
// 
// SYS:ランキング[00] の処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** sys_ranking.cpp ***
//========================================
#include "../main.h"
#include "sys_ranking.h"
#include <stdio.h>

//****************************************
// マクロ定義
//****************************************
// ランキング[00] の情報のデータファイルの相対パス
#define SYS_RANKING_RANKING_DATA_FILE_PATH	"data\\SAVEDATA\\ranking.bin"

//****************************************
// プロトタイプ宣言
//****************************************
// スコアランキングを降順にソートする
void ScoreSortDesc(int *nScore, int *nUpdateRank);

//****************************************
// グローバル宣言
//****************************************
// ランキング[00] の情報
Sys_ranking	g_sys_ranking[RANKING_NUM] = 
{
	{ "AAA", 30000 },
	{ "BBB", 10000 },
	{ "CCC", 2500 },
	{ "---", 0 },
	{ "---", 0 },
	{ "---", 0 },
	{ "---", 0 },
	{ "---", 0 },
};

// 順位の表示形式
char g_aRankText[RANKING_NUM][TXT_MAX] =
{
	"1ST",
	"2ND",
	"3RD",
	"4TH",
	"5TH",
	"6TH",
	"7TH",
	"8TH",
};

//========== *** システム:ランキング[00] の情報を取得 ***
Sys_ranking *GetSys_ranking(void)
{
	return g_sys_ranking;
}

//========== *** 順位の表示形式を取得 ***
char *GetRankText(int nRank) 
{
	return g_aRankText[nRank];
}

//========================================
// InitSys_ranking関数 - システム:ランキング[00] の初期化処理 -
//========================================
void InitSys_ranking(void)
{
	
}

//========================================
// UninitSys_ranking関数 - システム:ランキング[00] の終了処理 -
//========================================
void UninitSys_ranking(void) 
{
	
}

//========================================
// UpdateSys_ranking関数 - システム:ランキング[00] の更新処理 -
//========================================
void UpdateSys_ranking(void) 
{
	
}

//========================================
// SetScore関数 - ランキングにスコアを挿入する -
//========================================
int SetScore(int nScore)
{
	int nUpdateRank = -1;	// スコアを更新した順位

	// スコアを降順にソートする
	ScoreSortDesc(&nScore, &nUpdateRank);

	if (nScore > g_sys_ranking[RANKING_NUM - 1].nScore)
	{// 最も小さい値より挿入する値が大きかった時
		// 最も小さい値に挿入する値を代入する
		g_sys_ranking[RANKING_NUM - 1].nScore = nScore;

		// スコアを更新した順位を代入する
		nUpdateRank = RANKING_NUM - 1;
	}

	// スコアを降順にソートする
	ScoreSortDesc(&nScore, &nUpdateRank);

	// スコアを更新した順位を返す
	return nUpdateRank;
}

//========================================
// ScoreSortDesc関数 - スコアランキングを降順にソートする -
//========================================
void ScoreSortDesc(int *nScore, int *nUpdateRank)
{
	int		nTemp;						// 一時的に値を格納
	char	aNameTemp					// 
			[RANKING_NAME_NUM + 1];		// 名前を一時的に格納
	int		nCntCompare1, nCntCompare2;	// 比較のカウント
	bool	bUpdateRank					//
			= false;					// 順位更新フラグ

	for (nCntCompare1 = 0; nCntCompare1 < RANKING_NUM - 1; nCntCompare1++)
	{
		for (nCntCompare2 = nCntCompare1 + 1; nCntCompare2 < RANKING_NUM; nCntCompare2++)
		{
			if (g_sys_ranking[nCntCompare2].nScore > g_sys_ranking[nCntCompare1].nScore)
			{// 要素2が要素1の値を上回っていた時、
				// 値を入れ替える
				nTemp = g_sys_ranking[nCntCompare1].nScore;
				g_sys_ranking[nCntCompare1].nScore = g_sys_ranking[nCntCompare2].nScore;
				g_sys_ranking[nCntCompare2].nScore = nTemp;

				// 名前を入れ替える
				sprintf(aNameTemp, "%s",g_sys_ranking[nCntCompare1].aName);
				sprintf(g_sys_ranking[nCntCompare1].aName, "%s", g_sys_ranking[nCntCompare2].aName);
				sprintf(g_sys_ranking[nCntCompare2].aName, "%s", aNameTemp);

				if (bUpdateRank == false)
				{// 順位更新フラグが偽の時、
					// 順位更新フラグを真にする
					bUpdateRank = true;

					// スコアを更新した順位を代入する
					*nUpdateRank = nCntCompare1;
				}
			}
		}
	}
}

//========================================
// LoadSys_ranking関数 - システム:ランキング[00] の読み込み処理 -
//========================================
void LoadSys_ranking(void)
{
	FILE *pFile;	//ファイルのポインタ

	//ファイルを開く
	pFile = fopen(SYS_RANKING_RANKING_DATA_FILE_PATH, "rb");

	if (pFile != NULL)
	{//ファイルが開けた時、
		//ファイルからランキングを読み込む
		fread(g_sys_ranking, sizeof(Sys_ranking), RANKING_NUM, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
}

//========================================
// SaveSys_ranking関数 - システム:ランキング[00] の書き込み処理 -
//========================================
void SaveSys_ranking(void)
{
	FILE *pFile;	//ファイルのポインタ

	//ファイルを開く
	pFile = fopen(SYS_RANKING_RANKING_DATA_FILE_PATH, "wb");

	if (pFile != NULL)
	{//ファイルが開けた時、
		//ファイルにランキングを書き出し
		fwrite(g_sys_ranking, sizeof(Sys_ranking), RANKING_NUM, pFile);

		//ファイルを閉じる
		fclose(pFile);
	}
}