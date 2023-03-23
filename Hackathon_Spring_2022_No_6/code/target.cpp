//========================================
// 
// 標的の処理
// Author:KEISUKE OOTONO
// 
//========================================
//  *** target.cpp ***
//========================================
#include "target.h"
#include "assert.h"
#include "_R.N.Lib\R.N.Lib.h"

//****************************************
// マクロ定義
//****************************************
#define MAXTEX_TARGET_TYPE	(TARGET_MAX)		// 標的の種類の最大数
#define MAX_TEXTURE			(16)				// テクスチャの最大数
//****************************************
// プロトタイプ宣言
//****************************************

//****************************************
// グローバル変数宣言
//****************************************
static Target g_aTarget[MAX_TARGET];		// アイテムの情報
static Summon g_aSummon[MAX_SUMMON];		// 召喚の情報

//****************************************
// グローバル定数宣言
//****************************************
// モデルパス
static char g_aModelPath[TARGET_MAX][TXT_MAX] = {
	"data//MODEL//Item//cheese.x",
	"data//MODEL//Item//cheese.x",
	"data//MODEL//Item//cheese.x",
};

// 移動速度
static const float g_aItemSpeed[TARGET_MAX] = {
	5.0f,
	2.5f,
	1.0f,
};

//========== *** 標的の情報を取得 ***
Target *GetTarget(void)
{
	return &g_aTarget[0];
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitTarget関数 - 標的の初期化処理 -
// Author:KEISUKE OOTONO
//========================================
void InitTarget(void)
{
		// デバイス取得
		LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

		D3DXMATERIAL *pMat;	// マテリアルへのポインタ

		for (int nCntType = 0; nCntType < MAXTEX_TARGET_TYPE; nCntType++)
		{
			
		}

		// 標的の初期化処理
		for (int nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
		{
			g_aTarget[nCntTarget].pos = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].rot = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].move = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].type = TARGET_A;
			g_aTarget[nCntTarget].bUse = false;

			InitParts3DInfo(&g_aTarget[nCntTarget].partsInfo, 0);
		}
}
//========================================
// UninitTarget関数 - 標的の終了処理 -
// Author:KEISUKE OOTONO
//========================================
void UninitTarget(void)
{

}
//========================================
// UpdateTarget関数 - 標的の更新処理 -
// Author:KEISUKE OOTONO
//========================================
void UpdateTarget(void)
{
	for (int nCntTar = 0; nCntTar < MAX_TARGET; nCntTar++)
	{
		if (g_aTarget[nCntTar].bUse == true)
		{
			// 移動量を代入する
			g_aTarget[nCntTar].pos = g_aTarget[nCntTar].move;

			g_aTarget[nCntTar].partsInfo.pos = g_aTarget[nCntTar].pos;
			g_aTarget[nCntTar].partsInfo.rot = g_aTarget[nCntTar].rot;
			UpdateParts3DInfo(&g_aTarget[nCntTar].partsInfo);
		}
	}
}
//========================================
// DrawTarget関数 - 標的の描画処理 -
// Author:KEISUKE OOTONO
//========================================
void DrawTarget(void)
{
	
}
//========================================
// SetTarget関数 - 標的の設定処理 -
// Author:KEISUKE OOTONO
//========================================
void SetTarget(int nPos, TARGET_ITEM type)
{
	for (int nCntTar = 0; nCntTar < MAX_TARGET; nCntTar++)
	{
		if (g_aTarget[nCntTar].bUse == false)
		{//使用されていないとき
			g_aTarget[nCntTar].pos = g_aSummon[nPos].pos;				// 位置
			g_aTarget[nCntTar].type = type;								// 種類の設定
			g_aTarget[nCntTar].bUse = true;								// 使用フラグ

			// マップの中心から右の方で生成されると移動速度をマイナスに
			if (g_aTarget[nCntTar].pos.x >= 640.0f)
			{
				g_aTarget[nCntTar].move.x = -g_aItemSpeed[type];
			}
			else
			{
				g_aTarget[nCntTar].move.x = g_aItemSpeed[type];
			}
			break;
		}
	}
}
//========================================
// LoadSummon関数 - 位置の読み込み処理 -
// Author:KEISUKE OOTONO
//========================================
void LoadSummon(void)
{
	int c = 0;	   //1文字ずつ確認する変数
	int column = 1;//列数を数える変数
	int row = 0;   //行数を数える変数

	char aData[500];//つなげる文字数
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//ファイルを開く
	pFile = fopen("data/CSV/PointData.csv", "r");

	//ファイルから１文字ずつ読み込む
	while (fgetc(pFile) != '\n');

	while (c != EOF)
	{
		//１セル分の文字列を作る
		while (1)
		{
			c = fgetc(pFile);

			//末尾ならループを抜ける
			if (c == EOF)
				break;

			//カンマか改行でなければ、文字としてつなげる
			if (c != ',' && c != '\n')
				strcat(aData, (const char*)&c);

			//カンマが改行ならループ抜ける
			else
				break;
		}

		assert(row < MAX_SUMMON);

		switch (column)
		{
			//atoi関数で数値として代入
		case 1:	g_aSummon[row].pos.x = (float)(atoi(aData));	break;	// 1列目：X座標
		case 2:	g_aSummon[row].pos.y = (float)(atoi(aData));	break;	// 2列目：Y座標
		case 3:	g_aSummon[row].pos.z = (float)(atoi(aData));	break;	// 3列目：Z座標
		}
		//バッファを初期化
		memset(aData, 0, sizeof(aData));

		//列数を足す
		column++;

		//もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
		if (c == '\n')
		{
			column = 1;
			row++;

			if (row == MAX_SUMMON)
			{// 最大値に達した時、処理を抜ける
				break;
			}
		}
	}
	//ファイルを閉じる
	fclose(pFile);
}