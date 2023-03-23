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
#include "_R.N.Lib\Basis\2D\timer.h"
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
static Target g_aTarget[MAX_TARGET];				// 標的の情報
static TargetType g_TargetType[MAXTEX_TARGET_TYPE];	// 標的種類の情報
static Summon g_Summon[MAX_SUMMON];					// 召喚の情報
static Point g_aPoint[MAX_POINT];					// 位置の情報
static int g_aTex1[MAXTEX_TARGET_TYPE];
static int g_nGameTime;	//制限時間
static int g_nCounterFrame;	//フレームカウンター

//****************************************
// グローバル定数宣言
//****************************************
// テクスチャパス
char g_aTexturePath1[MAXTEX_TARGET_TYPE][TXT_MAX] =
{
	"data//TEXTURE//Target//00.PNG",
	"data//TEXTURE//Target//01.PNG",
	"data//TEXTURE//Target//02.PNG",
};

// 移動速度
static const float g_aTargetSpeed[TARGET_MAX] = {
	0.35f,
	0.25f,
	1.05f,
};

// 敵種類
// チーム番号
const TARGET_ITEM g_Target[TARGET_MAX] = {
	{ TARGET_A },
	{ TARGET_B },
	{ TARGET_C },
};

//========== *** 標的の情報を取得 ***
Target *GetTarget(void)
{
	return &g_aTarget[0];
}
//========== *** 標的種類の情報を取得 ***
TargetType *GetTargetType(void)
{
	return &g_TargetType[0];
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

		for (int nCntType = 0; nCntType < MAXTEX_TARGET_TYPE; nCntType++)
		{
			g_aTex1[nCntType] = LoadTexture(g_aTexturePath1[nCntType]);
		}

		// グローバル変数の初期化
		g_nGameTime = GAME_TIME;
		g_nCounterFrame = 0;
		// 標的の初期化処理
		for (int nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
		{
			g_aTarget[nCntTarget].pos = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].Tarpos = 0.0f;
			g_aTarget[nCntTarget].rot = D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f);
			g_aTarget[nCntTarget].move = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].type = TARGET_A;
			g_aTarget[nCntTarget].nPtn = 0;
			g_aTarget[nCntTarget].nCntFlame = 0;
			g_aTarget[nCntTarget].nCntMFLame = 0;
			g_aTarget[nCntTarget].nCntMove = 0;
			g_aTarget[nCntTarget].nCntSwit = 0;

			g_aTarget[nCntTarget].bRot = false;
			g_aTarget[nCntTarget].bUse = false;
		}
}
//========================================
// UpdateTarget関数 - 標的の更新処理 -
// Author:KEISUKE OOTONO
//========================================
void UpdateTarget(void)
{
	//1秒が経過した
	if (++g_nCounterFrame % 60 == 0)
	{
		//制限時間減少
		g_nGameTime--;
	}

	for (int nCntTar = 0; nCntTar < MAX_TARGET; nCntTar++)
	{
		if (g_aTarget[nCntTar].bUse == true)
		{
			// 各敵の移動処理
			if (g_aTarget[nCntTar].type == TARGET_C)
			{
				if (g_aTarget[nCntTar].bMove == false)
				{
					g_aTarget[nCntTar].nCntMFLame++;
					if ((g_aTarget[nCntTar].nCntMFLame % g_aTarget[nCntTar].nCntMove) == 0)
					{
						if (g_aTarget[nCntTar].bMove == false)
						{
							g_aTarget[nCntTar].nCntMove = 80;
							g_aTarget[nCntTar].nCntSwit++;

							if (g_aTarget[nCntTar].nCntSwit == 2)
							{
								g_aTarget[nCntTar].nCntSwit = 0;
								g_aTarget[nCntTar].bMove = true;
							}
						}
						if (g_aTarget[nCntTar].bRot == false)
						{
							g_aTarget[nCntTar].move.x = g_aTargetSpeed[g_aTarget[nCntTar].type];
							g_aTarget[nCntTar].Tarpos = -g_aTarget[nCntTar].Tarpos;
							g_aTarget[nCntTar].bRot = true;
						}
						else
						{
							g_aTarget[nCntTar].move.x = -g_aTargetSpeed[g_aTarget[nCntTar].type];
							g_aTarget[nCntTar].Tarpos = -g_aTarget[nCntTar].Tarpos;
							g_aTarget[nCntTar].bRot = false;
						}
					}
				}
				
			}


			// 移動量を代入する
			if (g_aTarget[nCntTar].Tarpos <= g_aTarget[nCntTar].pos.x && g_aTarget[nCntTar].bRot == true)
			{
				g_aTarget[nCntTar].bUse = false;
			}
			else if (g_aTarget[nCntTar].Tarpos >= g_aTarget[nCntTar].pos.x && g_aTarget[nCntTar].bRot == false)
			{
				g_aTarget[nCntTar].bUse = false;
			}
			else
			{
				g_aTarget[nCntTar].pos += g_aTarget[nCntTar].move;
			}

			// 移動量を代入

			Polygon3DSet polygon3Dset;

			polygon3Dset.pos = g_aTarget[nCntTar].pos;

			// ポリゴン(3D)の設定情報
			Polygon3DSet polygon3DSet;
			polygon3DSet.nTex = g_aTex1[g_aTarget[nCntTar].type];
			polygon3DSet.nPtn = g_aTarget[nCntTar].nPtn;
			polygon3DSet.nPtnX = 2;
			polygon3DSet.nPtnY = 1;
			polygon3DSet.fWidth = g_TargetType[g_aTarget[nCntTar].type].fWidth;
			polygon3DSet.fHeight = g_TargetType[g_aTarget[nCntTar].type].fHeight;
			polygon3DSet.pos = g_aTarget[nCntTar].pos;
			polygon3DSet.rot = g_aTarget[nCntTar].rot;
			polygon3DSet.col = Color{ 255,255,255,255 };

			// ポリゴン(3D)の設定処理
			SetPolygon3D(polygon3DSet);

			g_aTarget[nCntTar].nCntFlame++;
			if ((g_aTarget[nCntTar].nCntFlame % 24) == 0)
			{
				if (g_aTarget[nCntTar].nPtn <= 0)
				{
					g_aTarget[nCntTar].nPtn++;
				}
				else if (g_aTarget[nCntTar].nPtn == 1)
				{
					g_aTarget[nCntTar].nPtn = 0;
				}
			}

		}
	}

	for (int nCntTar = 0; nCntTar < MAX_SUMMON; nCntTar++)
	{
		if (g_Summon[nCntTar].bUse == true)
		{
			if (g_nGameTime == g_Summon[nCntTar].nTime)
			{
				SetTarget(g_Summon[nCntTar].nPoint, g_Target[g_Summon[nCntTar].nType], g_Summon[nCntTar].nMTyoe);
				g_Summon[nCntTar].bUse = false;
			}

		}
	}
}
//========================================
// SetTarget関数 - 標的の設定処理 -
// Author:KEISUKE OOTONO
//========================================
void SetTarget(int nPos, TARGET_ITEM type,int MType)
{
	for (int nCntTar = 0; nCntTar < MAX_TARGET; nCntTar++)
	{
		if (g_aTarget[nCntTar].bUse == false)
		{//使用されていないとき
			g_aTarget[nCntTar].pos = g_aPoint[nPos].pos;				// 位置
			g_aTarget[nCntTar].type = type;								// 種類の設定
			g_aTarget[nCntTar].bUse = true;								// 使用フラグ

			// マップの中心から右の方で生成されると移動速度をマイナスに
			if (MType == 0)
			{
				g_aTarget[nCntTar].move.x = -g_aTargetSpeed[type];
				g_aTarget[nCntTar].Tarpos = -g_aPoint[nPos].pos.x;
				g_aTarget[nCntTar].bRot = false;
			}
			else if(MType == 1)
			{
				g_aTarget[nCntTar].Tarpos = g_aPoint[nPos].pos.x;
				g_aTarget[nCntTar].pos.x = -g_aPoint[nPos].pos.x;				// 位置
				g_aTarget[nCntTar].move.x = g_aTargetSpeed[type];
				g_aTarget[nCntTar].bRot = true;
			}
			g_aTarget[nCntTar].nCntMove = 160;
			break;
		}
	}
}
//========================================
// LoadTarget関数 - 敵の読み込み処理 -
// Author:KEISUKE OOTONO
//========================================
void LoadTarget(void)
{

	{
		int c = 0;	   //1文字ずつ確認する変数
		int column = 1;//列数を数える変数
		int row = 0;   //行数を数える変数

		char aData[500];//つなげる文字数
		FILE *pFile;

		memset(aData, 0, sizeof(aData));

		//ファイルを開く
		pFile = fopen("data/CSV/enemydata.csv", "r");

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
			case 1:	g_Summon[row].nType = atoi(aData);	break;	// 1列目：種類
			case 2:	g_Summon[row].nPoint = atoi(aData);	break;	// 2列目：出現位置
			case 3:	g_Summon[row].nTime = atoi(aData);	break;	// 3列目：出現時間
			case 4:	g_Summon[row].nMTyoe = atoi(aData);	break;	// 4列目：移動方向
			}
			//バッファを初期化
			memset(aData, 0, sizeof(aData));

			//列数を足す
			column++;

			//もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
			if (c == '\n')
			{
				g_Summon[row].bUse = true;

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

		assert(row < MAX_POINT);

		switch (column)
		{
			//atoi関数で数値として代入
		case 1:	g_aPoint[row].pos.x = (float)(atoi(aData));	break;	// 1列目：X座標
		case 2:	g_aPoint[row].pos.y = (float)(atoi(aData));	break;	// 2列目：Y座標
		case 3:	g_aPoint[row].pos.z = (float)(atoi(aData));	break;	// 3列目：Z座標
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

			if (row == MAX_POINT)
			{// 最大値に達した時、処理を抜ける
				break;
			}
		}
	}
	//ファイルを閉じる
	fclose(pFile);
}
//========================================
// LoadTargetType関数 - 敵の情報読み込み処理 -
// Author:KEISUKE OOTONO
//========================================
void LoadTargetType(void)
{
	int c = 0;	   //1文字ずつ確認する変数
	int column = 1;//列数を数える変数
	int row = 0;   //行数を数える変数

	char aData[500];//つなげる文字数
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//ファイルを開く
	pFile = fopen("data/CSV/TargetType.csv", "r");

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

		assert(row < MAXTEX_TARGET_TYPE);

		switch (column)
		{
			//atoi関数で数値として代入
		case 1:	g_TargetType[row].nLife = atoi(aData);			break;	// 1列目：寿命
		case 2:	g_TargetType[row].nScore = atoi(aData);			break;	// 2列目：スコア
		case 3:	g_TargetType[row].fWidth = (float)(atoi(aData)); break;	// 3列目：幅
		case 4:	g_TargetType[row].fHeight = (float)(atoi(aData)); break;	// 4列目：高さ
		}
		//バッファを初期化
		memset(aData, 0, sizeof(aData));

		//列数を足す
		column++;

		//もし読み込んだ文字が改行だったら列数を初期化して行数を増やす
		if (c == '\n')
		{
			g_Summon[row].bUse = true;

			column = 1;
			row++;

			if (row == MAXTEX_TARGET_TYPE)
			{// 最大値に達した時、処理を抜ける
				break;
			}
		}
	}
	//ファイルを閉じる
	fclose(pFile);
}