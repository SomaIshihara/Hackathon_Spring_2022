//========================================
// 
// モデルのセットアップ関連の処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** model-setup.cpp ***
//========================================
#include "assert.h"
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// マクロ定義
//****************************************
// モデルのセットアップの最大数
#define MODELSETUP_MAX (256)
// モデルのセットアップリストのパス
#define MODELSETUP_LIST_PATH "data\\MODELSETUP_LIST.txt"

//****************************************
// 構造体の定義
//****************************************
// モデルの管理情報
typedef struct
{
	//========== *** 読み込み関連 ***
	// 読み込み済のモデルセットアップパス
	char aLoadModelSetUpPath[MODELSETUP_MAX][TXT_MAX] = {};
	unsigned int nModelSetUpNum = 0;	// モデルのセットアップ数
}ModelSetUpInfo;

//****************************************
// グローバル変数宣言
//****************************************
// モデルの管理情報
static ModelSetUpInfo g_modelSetUpInfo;
// モデルのセットアップ情報
static ModelSetUp g_aModelSetUp[MODELSETUP_MAX];

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 入出力 *** |----------------------
//============================================================

//========================================
// LoadModelSetUp関数 - モデルのセットアップの読み込み処理 -
// Author:RIKU NISHIMURA
//========================================
int LoadModelSetUp(ModelSetUpLoad modelSetUpLoad)
{
	// モデルセットアップのパス
	char *pModelSetUpPath = modelSetUpLoad.pModelSetUpPath;
	// モデルのセットアップ番号
	int nSetUpIdx = g_modelSetUpInfo.nModelSetUpNum;
	// 読み込み済フラグ
	bool bLoadDone = false;

	// 既に読み込まれているモデルセットアップか確認
	for (int nCntType = 0; nCntType < nSetUpIdx; nCntType++)
	{
		if (!strcmp(pModelSetUpPath, g_modelSetUpInfo.aLoadModelSetUpPath[nCntType]))
		{// 既に同じパスのモデルセットアップを読み込んでいた時、
			// 読み込み済フラグを真にする
			bLoadDone = true;

			if (modelSetUpLoad.bReload) 
			{// 再読み込みフラグが真の時、
				nSetUpIdx = nCntType;
				break;
			}
			else 
			{// 再読み込みフラグが偽の時、
				return nCntType;	// 種類番号を返す
			}
		}
	}

	// 読み込み済フラグに応じてセットアップ数を加算
	g_modelSetUpInfo.nModelSetUpNum += (int)bLoadDone ^ 1;

	if (nSetUpIdx == MODELSETUP_MAX - 1)
	{// 既にモデルの種類数が最大に達していた時、
		assert(false);
		return 0;
	}

	// モデルのセットアップのパスを保存
	sprintf(g_modelSetUpInfo.aLoadModelSetUpPath[nSetUpIdx], "%s", pModelSetUpPath);

	// データ検索用
	char aDataSearch[TXT_MAX];
	FILE *pFile;	// ファイルポインタ

	// 種類毎の情報のデータファイルを開く
	pFile = fopen(pModelSetUpPath, "r");
	if (pFile == NULL)
	{// 種類毎の情報のデータファイルが開けなかった場合、処理を終了する
		assert(false);
		return 0;
	}

	// モデルのセットアップ情報のポインタ
	ModelSetUp *pSetUp = &g_aModelSetUp[nSetUpIdx];

	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); // 検索

		if (!strcmp(aDataSearch, "END"))
		{// 読み込みを終了
			break;
		}
		else if (!strcmp(aDataSearch, "PARTSSET"))
		{// 部品設定情報
			LoadParts3DSet(pFile, &pSetUp->partsSet);
		}
		else if (!strcmp(aDataSearch, "HITTESTSET"))
		{// 当たり判定設定情報 
			LoadHitTestSet(pFile, &pSetUp->hitTestSet);
		}
		else if (!strcmp(aDataSearch, "MOTIONSET"))
		{// モーション設定情報
			LoadMotion3DSet(pFile, &pSetUp->motionSet);
		}
	}

	// モデルのセットアップ番号を返す
	return nSetUpIdx;
}

//========================================
// LoadModelSetUpList関数 - モデルのセットアップリストの読み込み処理 -
// Author:RIKU NISHIMURA
//========================================
void LoadModelSetUpList(void)
{
	// データ検索用
	char aDataSearch[TXT_MAX];
	FILE *pFile;	// ファイルポインタ

	// 種類毎の情報のデータファイルを開く
	pFile = fopen(MODELSETUP_LIST_PATH, "r");

	if (pFile == NULL)
	{// 種類毎の情報のデータファイルが開けなかった場合、
		// 処理を終了する
		return;
	}

	// ENDが見つかるまで読み込みを繰り返す
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// 検索

		if (!strcmp(aDataSearch, "END"))
		{// 読み込みを終了
			fclose(pFile); break;
		}
		if (!strcmp(aDataSearch, "MODELSETUP"))
		{
			// パスを読み込み
			fscanf(pFile, "%s", aDataSearch);

			// モデルのセットアップ読み込み情報
			ModelSetUpLoad setUpLoad;
			/* セットアップのパス */setUpLoad.pModelSetUpPath = aDataSearch;
			/* 再読み込みフラグ   */setUpLoad.bReload = true;
			// モデルのセットアップ読み込み処理
			LoadModelSetUp(setUpLoad);
		}
	}
}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================

//========================================
// GetModelSetUp関数 - モデルのセットアップ情報を取得 -
// Author:RIKU NISHIMURA
//========================================
ModelSetUp GetModelSetUp(int nSetUp) 
{
	return g_aModelSetUp[nSetUp];
}