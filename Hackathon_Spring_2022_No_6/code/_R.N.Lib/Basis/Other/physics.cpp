//========================================
// 
// 物理関連の処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** physics.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// マクロ定義
//****************************************
// 描画する当たり判定の最大数
#define DRAWHITTEST_MAX (256)
// 当たり判定の線の最大数
#define HITTESTLINE_MAX (1024)
// 当たり判定の色
#define HITTEST_COLOR Color{255,0,0,255}
// 当たり判定の円の分割数
#define HITTEST_CIRCLE_DIVISION (8)

//****************************************
// 構造体の定義
//****************************************
// 描画する当たり判定情報構造体
typedef struct
{
	HIT_TEST_FORM hitTestForm;		// 当たり判定の形
	float fWidth;					// 幅
	float fHeight;					// 高さ
	float fDepth;					// 奥行き
	D3DXVECTOR3 pos;				// 位置
	D3DXVECTOR3 rot;				// 向き
	bool aGhost[HITDIRECTION_MAX];	// すり抜け情報
}HitTestDraw;

// 物理関連処理の管理情報構造体
typedef struct
{
	// 描画する当たり判定のリスト
	CollisionInfo aDrawHitTestList[DRAWHITTEST_MAX];
	int nDrawHitTestSet;	// 描画する当たり判定の設定数
	bool bDrawHitTest;		// 当たり判定描画フラグ
	int nHitTestLineNum;	// 当たり判定の線の数
}PhysicsControl;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 取得 ***
// 当たり判定に必要な情報のパラメーター初期値を返す
CollisionInfo InitParameterCollisionInfo(void);
// 描画する当たり判定情報のパラメーター初期値を返す
HitTestDraw InitParameterDrawHitTest(void);
// 物理関連処理の管理情報のパラメーター初期値を返す
PhysicsControl InitParameterPhysicsControl(void);
//========== *** 当たり判定描画関連 ***
// 当たり判定の線の設定処理
void SetHitTestLine(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);

//****************************************
// グローバル変数宣言
//****************************************
// 当たり判定の線の頂点バッファへのポインタ
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHitTestLine = NULL;
static PhysicsControl g_physicsControl;	// 当たり判定の管理情報

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================
//========================================
// InitParameterCollisionInfo関数 - 衝突判定に必要な情報のパラメーター初期値を返す -
// Author:RIKU NISHIMURA
//========================================
CollisionInfo InitParameterCollisionInfo(void) 
{
	return{
		NULL,				// 現在の位置のポインタ
		INITD3DXVECTOR3,	// 過去の位置
		NULL,				// 移動量のポインタ
		NULL,				// 現在の向きのポインタ
		INITD3DXVECTOR3,	// 過去の向き
		{},					// 部品管理情報
		{},					// 部品設定情報
		{},					// 当たり判定の情報
		(COLLCHK_MODE)0,	// 衝突チェックのモード
	};
}

//========================================
// InitParameterDrawHitTest関数 - 描画する当たり判定情報のパラメーター初期値を返す -
// Author:RIKU NISHIMURA
//========================================
HitTestDraw InitParameterDrawHitTest(void)
{
	return{
		(HIT_TEST_FORM)0,							// 当たり判定の形
		0.0f,										// 幅
		0.0f,										// 高さ
		0.0f,										// 奥行き
		INITD3DXVECTOR3,							// 位置
		INITD3DXVECTOR3,							// 向き
		{ false,false,false,false,false,false },	// すり抜け情報
	};
}

//========================================
// InitParameterPhysicsControl関数 - 物理関連処理の管理情報のパラメーター初期値を返す -
// Author:RIKU NISHIMURA
//========================================
PhysicsControl InitParameterPhysicsControl(void)
{
	return{
		{ InitParameterCollisionInfo() },	// 描画する当たり判定のリスト
		0,									// 描画する当たり判定の設定数
		false,								// 当たり判定描画フラグ
		0,									// 当たり判定の線の数
	};
}

//============================================================
//--------------------| *** 当たり判定描画関連 *** |----------
//============================================================
//========================================
// SetHitTestLine関数 - 当たり判定の線の設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetHitTestLine(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	// 物理関連処理の管理情報のポインタ
	PhysicsControl *pPhy = &g_physicsControl;

	if (pPhy->nHitTestLineNum >= HITTESTLINE_MAX) 
	{
		return;	// 当たり判定の線の数が最大数に達している時、
	}

	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHitTestLine->Lock(0, 0, (void**)&pVtx, 0);

	// 頂点情報へのポインタを進める
	pVtx += pPhy->nHitTestLineNum * 2;

	// 位置を代入
	pVtx[0].pos = pos1;
	pVtx[1].pos = pos2;

	// 頂点座標をアンロックする
	g_pVtxBuffHitTestLine->Unlock();

	// 当たり判定の線の数を加算
	pPhy->nHitTestLineNum++;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 基本接続 *** |--------------------
//============================================================
//========================================
// InitPhysics関数 - 物理関連の初期化処理 -
// Author:RIKU NISHIMURA
//========================================
void InitPhysics(void) 
{
	// 物理関連処理の管理情報のポインタ
	PhysicsControl pPhy = g_physicsControl;

	// パラメーターの初期化
	pPhy = InitParameterPhysicsControl();

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// 頂点バッファの生成
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * HITTESTLINE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHitTestLine,
		NULL);

	VERTEX_3D *pVtx;	// 頂点情報へのポインタ

	// 頂点バッファをロックし、頂点情報へのポインタを取得
	g_pVtxBuffHitTestLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < HITTESTLINE_MAX; nCntLine++, pVtx += 2)
	{
		// 頂点カラーを設定
		pVtx[0].col = ColorToD3DCOLOR(HITTEST_COLOR);
		pVtx[1].col = ColorToD3DCOLOR(HITTEST_COLOR);
	}

	// 頂点座標をアンロックする
	g_pVtxBuffHitTestLine->Unlock();
}

//============================================================
//--------------------| *** 入出力 *** |----------------------
//============================================================
//========================================
// LoadHitTestSet関数 - 当たり判定設定情報の読み込み処理 -
// Author:RIKU NISHIMURA
//========================================
void LoadHitTestSet(FILE *pFile, HitTestSet *pHitTestSet)
{
	char aDataSearch[TXT_MAX];	// データ検索用

	// 当たり判定の数を初期化
	pHitTestSet->nHitTestNum = 0;
	
	// 当たり判定設定情報の読み込みを開始
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); // 検索

		if (!strcmp(aDataSearch, "HITTESTSET_END"))
		{// 読み込みを終了
			break;
		}
		else if (!strcmp(aDataSearch, "HITTEST"))
		{
			pHitTestSet->aHitTest[pHitTestSet->nHitTestNum].nHitTestPartsNum = 0;	// 当たり判定の部品数を初期化

			// 当たり判定情報の読み込みを開始
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); // 検索

				if (!strcmp(aDataSearch, "HITTEST_END"))
				{
					pHitTestSet->nHitTestNum++;	// 当たり判定数を加算
					break;						// 読み込みを終了
				}
				else if (!strcmp(aDataSearch, "HITTEST_PARTS")) 
				{
					// 部品の種類毎の情報のポインタ
					HitTestParts *pHitTest = &pHitTestSet->aHitTest[pHitTestSet->nHitTestNum].aHitTestParts[pHitTestSet->aHitTest[pHitTestSet->nHitTestNum].nHitTestPartsNum];

					// 当たり判定情報の読み込みを開始
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch); // 検索

						if (!strcmp(aDataSearch, "HITTEST_PARTS_END")) 
						{
							pHitTestSet->aHitTest[pHitTestSet->nHitTestNum].nHitTestPartsNum++;	// 当たり判定の部品数を加算
							break;	// 読み込みを終了
						}
						else if (!strcmp(aDataSearch, "FORM:"))
						{// 当たり判定の形 
							fscanf(pFile, "%d", &pHitTest->hitTestForm);
						}
						else if (!strcmp(aDataSearch, "PARENT:"))
						{// 親番号 
							fscanf(pFile, "%d", &pHitTest->nParent); 
						}
						else if (!strcmp(aDataSearch, "WIDTH:"))
						{// 幅
							fscanf(pFile, "%f", &pHitTest->fWidth); 
						}
						else if (!strcmp(aDataSearch, "HEIGHT:"))
						{// 高さ
							fscanf(pFile, "%f", &pHitTest->fHeight);
						}
						else if (!strcmp(aDataSearch, "DEPTH:"))
						{// 奥行き 
							fscanf(pFile, "%f", &pHitTest->fDepth); 
						}
						else if (!strcmp(aDataSearch, "RELATIVE_POS:")) 
						{// 相対位置
							fscanf(pFile, "%f", &pHitTest->fixedRelativePos.x);	// X
							fscanf(pFile, "%f", &pHitTest->fixedRelativePos.y);	// Y
							fscanf(pFile, "%f", &pHitTest->fixedRelativePos.z);	// Z
						}
						else if (!strcmp(aDataSearch, "RELATIVE_ROT:"))
						{// 相対向き
							fscanf(pFile, "%f", &pHitTest->fixedRelativeRot.x);	// X
							fscanf(pFile, "%f", &pHitTest->fixedRelativeRot.y);	// Y
							fscanf(pFile, "%f", &pHitTest->fixedRelativeRot.z);	// Z
							pHitTest->fixedRelativeRot.x *= D3DX_PI;	// 円周率補正
							pHitTest->fixedRelativeRot.y *= D3DX_PI;	// 円周率補正
							pHitTest->fixedRelativeRot.z *= D3DX_PI;	// 円周率補正
						}
						else if (!strcmp(aDataSearch, "GHOST:"))
						{// すり抜けフラグ
							for (int nCntDir = 0; nCntDir < HITDIRECTION_MAX; nCntDir++) 
							{
								int nTemp;
								fscanf(pFile, "%d", &nTemp);
								pHitTest->aGhost[nCntDir] = (nTemp != 0);
							}
						}
					}
				}
			}
		}
	}
}

//============================================================
//--------------------| *** 当たり判定 *** |------------------
//============================================================
//========================================
// HitTestSignUp関数 - 当たり判定登録処理 -
// Author:RIKU NISHIMURA
//========================================
void HitTestSignUp(CollisionInfo myCollInfo)
{
	// 物理関連処理の管理情報のポインタ
	PhysicsControl *pPhy = &g_physicsControl;

	if (pPhy->nDrawHitTestSet >= DRAWHITTEST_MAX)
	{
		return;	// 描画する当たり判定の設定数が最大数に達している時、
	}

	// 当たり判定に必要な情報を登録
	pPhy->aDrawHitTestList[pPhy->nDrawHitTestSet] = myCollInfo;
	pPhy->nDrawHitTestSet++;
}

//========================================
// HitTestSignOut関数 - 当たり判定登録解除処理 -
// Author:RIKU NISHIMURA
//========================================
void HitTestSignOut(void)
{
	// 物理関連処理の管理情報のポインタ
	PhysicsControl *pPhy = &g_physicsControl;

	// 描画する当たり判定の設定数を初期化
	pPhy->nDrawHitTestSet = 0;
}

//========================================
// CollisionCheck関数 - 衝突チェック -
// Author:RIKU NISHIMURA
//========================================
void CollisionCheck(VECTOR vector, Collision *pCollision, CollisionInfo pMyCollInfo, CollisionInfo pairCollInfo, COLLCHK_MODE mode)
{
	for (int nCntMyParts = 0; nCntMyParts < pMyCollInfo.pHitTest->nHitTestPartsNum; nCntMyParts++)
	{
		for (int nCntPairParts = 0; nCntPairParts < pairCollInfo.pHitTest->nHitTestPartsNum; nCntPairParts++)
		{
			HIT_TEST_FORM	my					= pMyCollInfo.pHitTest->aHitTestParts[nCntMyParts].hitTestForm;		// 自分の当たり判定の種類
			HIT_TEST_FORM	pr					= pairCollInfo.pHitTest->aHitTestParts[nCntPairParts].hitTestForm;	// 相手の当たり判定の種類
			HitTestParts	myHitTestParts		= pMyCollInfo.pHitTest->aHitTestParts[nCntMyParts];					// 自分の当たり判定の部品
			HitTestParts	pairHitTestParts	= pairCollInfo.pHitTest->aHitTestParts[nCntPairParts];				// 相手の当たり判定の部品

			// モードに応じた処理
			switch (mode)
			{
			case COLLCHK_MODE_NORMAL:
				
				break;
			case COLLCHK_MODE_LOOKDOWN:
				
				break;
			}
		}
	}
}

//========================================
// CollisionOverwrite関数 - 衝突情報の上書き -
// Author:RIKU NISHIMURA
//========================================
void CollisionOverwrite(Collision *pOverwriteColl, Collision collision) 
{
	pOverwriteColl->bHit	|= collision.bHit;	// 当たりフラグ
	pOverwriteColl->bColl	|= collision.bColl;	// 衝突フラグ
	pOverwriteColl->bOvl	|= collision.bOvl;	// 内側フラグ
}

//============================================================
//--------------------| *** 当たり判定描画関連 *** |----------
//============================================================
//========================================
// DrawHitTestSetUp関数 - 当たり判定の描画準備処理 -
// Author:RIKU NISHIMURA
//========================================
void DrawHitTestSetUp(void) 
{
	if (!g_physicsControl.bDrawHitTest)
	{
		return;	// 当たり判定の描画フラグが偽の時、処理を終了する
	}

	// 物理関連処理の管理情報のポインタ
	PhysicsControl *pPhy = &g_physicsControl;
	// 描画する当たり判定情報のポインタ
	CollisionInfo *pDrawHitTest = pPhy->aDrawHitTestList;

	for (int nCntHitTest = 0; nCntHitTest < pPhy->nDrawHitTestSet; nCntHitTest++, pDrawHitTest++)
	{
		for (int nCntMyParts = 0; nCntMyParts < pDrawHitTest->pHitTest->nHitTestPartsNum; nCntMyParts++)
		{
			// 当たり判定の部品情報のポインタ
			HitTestParts *pParts = &pDrawHitTest->pHitTest->aHitTestParts[nCntMyParts];

			// 親パーツのマトリックス
			D3DXMATRIX mtxParent =
				pParts->nParent == -1 ?
				ConvPosRotToMatrix(*pDrawHitTest->pPos, *pDrawHitTest->pRot):
				GetMatrixParts3D(pParts->nParent, *pDrawHitTest->pPos, *pDrawHitTest->pRot, pDrawHitTest->pPartsInfo, pDrawHitTest->pPartsSet);

			// 当たり判定のマトリックス
			D3DXMATRIX mtxHitTest = ConvPosRotToMatrix(pParts->fixedRelativePos, pParts->fixedRelativeRot);

			if (pParts->nParent == -1) 
			{
				mtxHitTest *= pDrawHitTest->pPartsSet->fScale;
			}

			switch (pParts->hitTestForm)
			{
			case HIT_TEST_FORM_SQUARE: {
				//   A1-----B1
				//  /      /|
				// C1-----D1B2
				// |      |/
				// C2-----D2
				enum { l_A1, l_B1, l_C1, l_D1, l_A2, l_B2, l_C2, l_D2, l_MAX };
				D3DXVECTOR3 aPos[l_MAX] = {
					D3DXVECTOR3(-1, 1, 1),
					D3DXVECTOR3( 1, 1, 1),
					D3DXVECTOR3(-1, 1,-1),
					D3DXVECTOR3( 1, 1,-1),
					D3DXVECTOR3(-1,-1, 1),
					D3DXVECTOR3( 1,-1, 1),
					D3DXVECTOR3(-1,-1,-1),
					D3DXVECTOR3( 1,-1,-1)
				};

				// 部品の幅/高さ/奥行きを反映
				for (int nCntVtx = 0; nCntVtx < l_MAX; nCntVtx++)
				{
					aPos[nCntVtx] *= 0.5f;
					aPos[nCntVtx].x *= pParts->fWidth;
					aPos[nCntVtx].y *= pParts->fHeight;
					aPos[nCntVtx].z *= pParts->fDepth;

					// 位置を親のマトリックスを反映させた上で再設定
					aPos[nCntVtx] =
						ConvMatrixToPos(
							MultiplyMatrix(
								MultiplyMatrix(mtxParent, mtxHitTest),
								ConvPosRotToMatrix(aPos[nCntVtx], INITD3DXVECTOR3)));
				}

				// 上の辺
				SetHitTestLine(aPos[l_A1], aPos[l_B1]);
				SetHitTestLine(aPos[l_A1], aPos[l_C1]);
				SetHitTestLine(aPos[l_D1], aPos[l_C1]);
				SetHitTestLine(aPos[l_D1], aPos[l_B1]);
				// 下の辺
				SetHitTestLine(aPos[l_A2], aPos[l_B2]);
				SetHitTestLine(aPos[l_A2], aPos[l_C2]);
				SetHitTestLine(aPos[l_D2], aPos[l_C2]);
				SetHitTestLine(aPos[l_D2], aPos[l_B2]);
				// 縦の辺
				SetHitTestLine(aPos[l_A1], aPos[l_A2]);
				SetHitTestLine(aPos[l_B1], aPos[l_B2]);
				SetHitTestLine(aPos[l_C1], aPos[l_C2]);
				SetHitTestLine(aPos[l_D1], aPos[l_D2]);

				break; 
			}// HIT_TEST_FORM_SQUARE
			case HIT_TEST_FORM_CYLINDER: {
				enum { l_SIRCLE_UPPER, l_SIRCLE_BOTTOM, l_SIRCLE_MAX };
				D3DXVECTOR3 aCirclePos[l_SIRCLE_MAX][HITTEST_CIRCLE_DIVISION];

				for (int nCntCircle = 0; nCntCircle < l_SIRCLE_MAX; nCntCircle++)
				{
					for (int nCntDiv = 0; nCntDiv < HITTEST_CIRCLE_DIVISION; nCntDiv++)
					{
						// 円のカウントに応じたY座標を設定
						switch (nCntCircle)
						{
						case l_SIRCLE_UPPER:
							aCirclePos[nCntCircle][nCntDiv].y = 1;
							break;
						case l_SIRCLE_BOTTOM:
							aCirclePos[nCntCircle][nCntDiv].y = -1;
							break;
						}

						// 分割カウントに応じてXZ座標を設定
						aCirclePos[nCntCircle][nCntDiv].x = sinf(nCntDiv * ((D3DX_PI * 2) / (float)HITTEST_CIRCLE_DIVISION));
						aCirclePos[nCntCircle][nCntDiv].z = cosf(nCntDiv * ((D3DX_PI * 2) / (float)HITTEST_CIRCLE_DIVISION));

						// 部品の幅/高さ/奥行きを反映
						aCirclePos[nCntCircle][nCntDiv] *= 0.5f;
						aCirclePos[nCntCircle][nCntDiv].x *= pParts->fWidth;
						aCirclePos[nCntCircle][nCntDiv].y *= pParts->fHeight;
						aCirclePos[nCntCircle][nCntDiv].z *= pParts->fDepth;

						// 位置を親のマトリックスを反映させた上で再設定
						aCirclePos[nCntCircle][nCntDiv] =
							ConvMatrixToPos(
								MultiplyMatrix(
									MultiplyMatrix(mtxParent, mtxHitTest),
									ConvPosRotToMatrix(aCirclePos[nCntCircle][nCntDiv], INITD3DXVECTOR3)));
					}
				}

				for (int nCntDiv = 0; nCntDiv < HITTEST_CIRCLE_DIVISION; nCntDiv++)
				{
					// 縦の辺
					SetHitTestLine(
						aCirclePos[l_SIRCLE_UPPER][nCntDiv],
						aCirclePos[l_SIRCLE_BOTTOM][nCntDiv]);

					// 上の周囲辺
					SetHitTestLine(
						aCirclePos[l_SIRCLE_UPPER][nCntDiv],
						aCirclePos[l_SIRCLE_UPPER][(nCntDiv + 1) % HITTEST_CIRCLE_DIVISION]);

					// 下の周囲辺
					SetHitTestLine(
						aCirclePos[l_SIRCLE_BOTTOM][nCntDiv],
						aCirclePos[l_SIRCLE_BOTTOM][(nCntDiv + 1) % HITTEST_CIRCLE_DIVISION]);
				}

				break;
			}// HIT_TEST_FORM_CYLINDER
			}
		}
	}

	// 描画する当たり判定の設定数を初期化
	pPhy->nDrawHitTestSet = 0;
}

//========================================
// DrawHitTest関数 - 当たり判定の描画処理 -
// Author:RIKU NISHIMURA
//========================================
void DrawHitTest(void)
{
	if (!g_physicsControl.bDrawHitTest)
	{
		return;	// 当たり判定の描画フラグが偽の時、処理を終了する
	}

	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtx;
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス

	// ワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtx);

	// 向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

	// 位置を反映
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	// ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	// レンダリングステートを設定
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Zテストを無効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// 頂点バッファをデータストリームに設定
	pDevice->SetStreamSource(0, g_pVtxBuffHitTestLine, 0, sizeof(VERTEX_3D));

	// 頂点フォーマットの設定
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntLine = 0; nCntLine < g_physicsControl.nHitTestLineNum; nCntLine++)
	{
		// ポリゴン床の描画
		pDevice->DrawPrimitive(D3DPT_LINELIST, 2 * nCntLine, 1);
	}

	// レンダリングステートを元に戻す
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// Zテストを有効にする
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//========================================
// InitHitTestLineNum関数 - 当たり判定の線の数を初期化 -
// Author:RIKU NISHIMURA
//========================================
void InitHitTestLineNum(void)
{
	// 当たり判定の線の数を初期化
	g_physicsControl.nHitTestLineNum = 0;
}

//========================================
// ShowHitTest関数 - 当たり判定の表示設定 -
// Author:RIKU NISHIMURA
//========================================
void ShowHitTest(bool bShow) 
{
	g_physicsControl.bDrawHitTest = bShow;
}