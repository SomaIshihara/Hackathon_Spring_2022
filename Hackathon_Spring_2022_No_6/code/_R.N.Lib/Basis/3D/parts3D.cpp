//========================================
// 
// 部品(3D)関連の処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** parts3D.cpp ***
//========================================
#include <assert.h>
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** モーション(3D)関連 ***
// 部品(3D)のトランスフォームの取得処理
void GetParts3DTransform(Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet);
// 部品(3D)のモデル設定の取得処理
void ModelSetParts3D(Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet);

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 部品(3D)関連 *** |----------------
//============================================================

//========================================
// GetParts3DTransform関数 - 部品(3D)のトランスフォームの取得処理 -
// Author:RIKU NISHIMURA
//========================================
void GetParts3DTransform(Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet)
{
	for (int nCntParts = 0; nCntParts < pPartsSet->nPartsNum; nCntParts++)
	{
		Parts3D		*pParts = &pPartsInfo->aParts[nCntParts];		// 部品の情報のポインタ
		Parts3DType *pPartsType = &pPartsSet->aPartsType[nCntParts];	// 部品の種類毎の情報のポインタ

		if (pParts->bPosAnim)
		{// 位置アニメーションフラグが真の時、
			// カウンターの進行率
			float fRate = (float)pParts->nCounterPosAnim / (float)pParts->nPosAnimTime;

			// 位置を更新
			pParts->pos = (pParts->posOld * (1.0f - fRate)) + (pParts->targetPos * fRate);
		}

		// 位置(結果)を更新
		pParts->posResult = (pParts->pos + pPartsType->fixedRelativePos);

		if (pPartsType->nParent == -1)
		{// 親番号が-1の時、結果位置に拡大倍率を乗算
			pParts->posResult *= pPartsSet->fScale;
		}

		if (pParts->bRotAnim)
		{// 向きアニメーションフラグが真の時、
			// カウンターの進行率
			float fRate = (float)pParts->nCounterRotAnim / (float)pParts->nRotAnimTime;

			// 向きを更新
			pParts->rot = (pParts->rotOld * (1.0f - fRate)) + (pParts->targetRot * fRate);
		}

		// 向き(結果)を更新
		pParts->rotResult = pParts->rot + pPartsType->fixedRelativeRot;
	}
}

//========================================
// ModelSetParts3D関数 - 部品(3D)のモデル設定処理 -
// Author:RIKU NISHIMURA
//========================================
void ModelSetParts3D(Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet) 
{
	// デバイスを取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	// 計算用マトリックス
	D3DXMATRIX mtxRot, mtxTrans;
	// 本体のマトリックス
	D3DXMATRIX mtxSelf;
	// 部品毎のマトリックス
	D3DXMATRIX aMtxParts[PARTS_3D_MAX];

	// 本体のワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxSelf);

	// 本体の向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pPartsInfo->rot.y, pPartsInfo->rot.x, pPartsInfo->rot.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);

	// 本体の位置を反映
	D3DXMatrixTranslation(&mtxTrans, pPartsInfo->pos.x, pPartsInfo->pos.y, pPartsInfo->pos.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);

	// 本体のワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);

	for (int nCntParts = 0; nCntParts < pPartsSet->nPartsNum; nCntParts++)
	{
		// 部品(3D)の情報のポインタ
		Parts3D *pParts = &pPartsInfo->aParts[nCntParts];
		// 部品(3D)の部品の種類毎の情報のポインタ
		Parts3DType *pPartsType = &pPartsSet->aPartsType[nCntParts];

		// 部品のワールドマトリックスの初期化
		D3DXMatrixIdentity(&aMtxParts[nCntParts]);

		if (pPartsType->nParent == -1)
		{// 親番号が-1の時、
			// モデルのサイズを変更
			D3DXMatrixScaling(&aMtxParts[nCntParts], pPartsSet->fScale, pPartsSet->fScale, pPartsSet->fScale);
		}

		// 部品の向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pParts->rotResult.y, pParts->rotResult.x, pParts->rotResult.z);
		D3DXMatrixMultiply(&aMtxParts[nCntParts], &aMtxParts[nCntParts], &mtxRot);

		// 部品の位置を反映
		D3DXMatrixTranslation(&mtxTrans, pParts->posResult.x, pParts->posResult.y, pParts->posResult.z);
		D3DXMatrixMultiply(&aMtxParts[nCntParts], &aMtxParts[nCntParts], &mtxTrans);

		// 親の部品のマトリックス
		D3DXMATRIX mtxParent;

		if (pPartsType->nParent != -1)
		{// 部品の親番号が-1(親無し)でない時、親マトリックスを設定
			mtxParent = aMtxParts[pPartsType->nParent];
		}
		else
		{// 部品の親番号が-1(親無し)の時、親マトリックスを本体マトリックスで設定
			mtxParent = mtxSelf;
		}

		// 算出した部品のワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(
			&aMtxParts[nCntParts],
			&aMtxParts[nCntParts],
			&mtxParent);

		// モデルの設定情報
		ModelSet modelSet;
		/* モデル番号	*/modelSet.nModelIdx = pPartsType->nModelIdx;
		/* マトリックス	*/modelSet.mtx = aMtxParts[nCntParts];
		/* 色			*/modelSet.col = pPartsInfo->col;
		// モデルの設定
		SetModel(modelSet);
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 部品(3D)関連 *** |----------------
//============================================================

//========================================
// LoadParts3DSet関数 - 部品設定情報(3D)の読み込み処理 -
// Author:RIKU NISHIMURA
//========================================
void LoadParts3DSet(FILE *pFile, Parts3DSet *pPartsSet)
{
	// データ検索用
	char aDataSearch[TXT_MAX];
	float fAllScale;	// 全体の拡大倍率

	// 部品数を初期化
	pPartsSet->nPartsNum = 0;

	// 拡大倍率を初期化
	pPartsSet->fScale = 1.0f;

	// 部品設定情報の読み込みを開始
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); // 検索

		if (!strcmp(aDataSearch, "PARTSSET_END"))
		{// 読み込みを終了
			break; 
		}
		else if (!strcmp(aDataSearch, "SCALE:"))
		{// 拡大倍率
			fscanf(pFile, "%f", &pPartsSet->fScale);
		}
		else if (!strcmp(aDataSearch, "PARTS"))
		{
			// 部品の種類毎の情報のポインタ
			Parts3DType *pPartsType = &pPartsSet->aPartsType[pPartsSet->nPartsNum];

			// 部品情報の読み込みを開始
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); // 検索

				if (!strcmp(aDataSearch, "PARTS_END"))
				{// 読み込みを終了
					pPartsSet->nPartsNum++;
					break;
				}
				else if (!strcmp(aDataSearch, "MODEL_PATH:"))
				{// モデルの相対パス
					// もう一度検索をかける
					fscanf(pFile, "%s", aDataSearch);

					// モデルの読み込み情報を設定
					ModelLoad modelLoad =
					{
						aDataSearch,	// モデルのパス
					};

					// モデルを読み込み、モデル番号を取得
					pPartsType->nModelIdx = LoadModel(modelLoad);
				}
				else if (!strcmp(aDataSearch, "PARENT:"))
				{// 親パーツ番号 
					fscanf(pFile, "%d", &pPartsType->nParent); 
				}
				else if (!strcmp(aDataSearch, "RELATIVE_POS:"))
				{// 固定の相対位置
					fscanf(pFile, "%f", &pPartsType->fixedRelativePos.x);	// X
					fscanf(pFile, "%f", &pPartsType->fixedRelativePos.y);	// Y
					fscanf(pFile, "%f", &pPartsType->fixedRelativePos.z);	// Z
				}
				else if (!strcmp(aDataSearch, "RELATIVE_ROT:"))
				{// 固定の相対角度
					fscanf(pFile, "%f", &pPartsType->fixedRelativeRot.x);	// X
					fscanf(pFile, "%f", &pPartsType->fixedRelativeRot.y);	// Y
					fscanf(pFile, "%f", &pPartsType->fixedRelativeRot.z);	// Z
					pPartsType->fixedRelativeRot.x *= D3DX_PI;				// 円周率補正
					pPartsType->fixedRelativeRot.y *= D3DX_PI;				// 円周率補正
					pPartsType->fixedRelativeRot.z *= D3DX_PI;				// 円周率補正
				}
				else if (!strcmp(aDataSearch, "ROT_RELATIVE_POS:"))
				{// 回転軸の相対位置
					fscanf(pFile, "%f", &pPartsType->rotRelativePos.x);	// X
					fscanf(pFile, "%f", &pPartsType->rotRelativePos.y);	// Y
					fscanf(pFile, "%f", &pPartsType->rotRelativePos.z);	// Z
				}
			}
		}
	}
}

//========================================
// InitParts3DInfo関数 - 部品(3D)の初期化処理 -
// Author:RIKU NISHIMURA
//========================================
void InitParts3DInfo(Parts3DInfo *pPartsInfo, int nModelSetUp)
{
	// モデルのセットアップ情報
	ModelSetUp setUp = GetModelSetUp(nModelSetUp);

	pPartsInfo->pos = INITD3DXVECTOR3;		// 位置(本体)
	pPartsInfo->rot = INITD3DXVECTOR3;		// 向き(本体)
	pPartsInfo->bStop = false;				// 停止フラグ
	pPartsInfo->nModelSetUp = nModelSetUp;	// モデルのセットアップ番号
	pPartsInfo->nCounterMotion = 0;	// モーションカウンター
	pPartsInfo->nMotion = 0;		// モーション番号
	pPartsInfo->nMotionOld = 0;		// モーション番号(過去)
	pPartsInfo->col = INITCOLOR;	// 色

	for (int nCntParts = 0; nCntParts < setUp.partsSet.nPartsNum; nCntParts++)
	{
		// 部品の情報のポインタ
		Parts3D *pParts = &pPartsInfo->aParts[nCntParts];
		// 部品の種類毎の情報のポインタ
		Parts3DType *pPartsType = &setUp.partsSet.aPartsType[nCntParts];

		// 位置と向きの結果を更新
		pParts->posResult = pPartsType->fixedRelativePos;
		pParts->rotResult = pPartsType->fixedRelativeRot;

		pParts->pos				= INITD3DXVECTOR3;	// 位置
		pParts->rot				= INITD3DXVECTOR3;	// 向き
		pParts->bPosAnim		= false;			// 位置アニメーションフラグ
		pParts->nCounterPosAnim = 0;				// 位置アニメーションカウンター
		pParts->nPosAnimTime	= 0;				// 位置アニメーションにかかる時間
		pParts->posOld			= INITD3DXVECTOR3;	// 元の位置
		pParts->targetPos		= INITD3DXVECTOR3;	// 目標位置
		pParts->bRotAnim		= false;			// 角度アニメーションフラグ
		pParts->nCounterRotAnim = 0;				// 角度アニメーションカウンター
		pParts->nRotAnimTime	= 0;				// 角度アニメーションにかかる時間
		pParts->rotOld			= INITD3DXVECTOR3;	// 元の角度
		pParts->targetRot		= INITD3DXVECTOR3;	// 目標角度
	}
}

//========================================
// UpdateParts3DInfo関数 - 部品(3D)の更新処理 -
// Author:RIKU NISHIMURA
//========================================
void UpdateParts3DInfo(Parts3DInfo *pPartsInfo)
{
	// モデルのセットアップ情報
	ModelSetUp setUp = GetModelSetUp(pPartsInfo->nModelSetUp);

	if (!pPartsInfo->bStop)
	{// 停止していない時、
		// モーション設定
		SetMotion3D(pPartsInfo);

		// モーションの更新処理
		UpdateMotion3D(setUp.motionSet, pPartsInfo, setUp.partsSet);

		// 部品(3D)のトランスフォームを取得
		GetParts3DTransform(pPartsInfo, &setUp.partsSet);
	}

	// モデルの設定処理
	ModelSetParts3D(pPartsInfo, &setUp.partsSet);
}

//========================================
// GetMatrixParts3D関数 - 部品(3D)のマトリックスを取得 -
// Author:RIKU NISHIMURA
//========================================
D3DXMATRIX GetMatrixParts3D(int nParts, D3DXVECTOR3 pos, D3DXVECTOR3 rot, Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet)
{
	// デバイス取得
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	// 部品のマトリックス
	D3DXMATRIX aMtxParts[PARTS_3D_MAX];
	D3DXMATRIX mtxRot, mtxTrans;	// 計算用マトリックス
	D3DXMATRIX mtxSelf;				// 本体のマトリックス

	// 本体のワールドマトリックスの初期化
	D3DXMatrixIdentity(&mtxSelf);

	// 本体の向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);

	// 本体の位置を反映
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);

	for (int nCntParts = 0; nCntParts < pPartsSet->nPartsNum; nCntParts++)
	{
		// 部品(3D)の情報のポインタ
		Parts3D *pParts = &pPartsInfo->aParts[nCntParts];
		// 部品(3D)の部品の種類毎の情報のポインタ
		Parts3DType *pPartsType = &pPartsSet->aPartsType[nCntParts];

		D3DXMATRIX	mtxParent;	// 親マトリックス

		// 部品のワールドマトリックスの初期化
		D3DXMatrixIdentity(&aMtxParts[nCntParts]);

		if (pPartsType->nParent == -1)
		{// 親番号が-1の時、
			// モデルのサイズを変更
			D3DXMatrixScaling(&aMtxParts[nCntParts], pPartsSet->fScale, pPartsSet->fScale, pPartsSet->fScale);
		}

		// 部品の向きを反映
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pParts->rotResult.y, pParts->rotResult.x, pParts->rotResult.z);
		D3DXMatrixMultiply(&aMtxParts[nCntParts], &aMtxParts[nCntParts], &mtxRot);

		// 部品の位置を反映
		D3DXMatrixTranslation(&mtxTrans, pParts->posResult.x, pParts->posResult.y, pParts->posResult.z);
		D3DXMatrixMultiply(&aMtxParts[nCntParts], &aMtxParts[nCntParts], &mtxTrans);

		if (pPartsType->nParent != -1)
		{// 部品の親番号が-1(親無し)でない時、親マトリックスを設定
			mtxParent = aMtxParts[pPartsType->nParent];
		}
		else
		{// 部品の親番号が-1(親無し)の時、親マトリックスを本体マトリックスで設定
			mtxParent = mtxSelf;
		}

		// 算出した部品のワールドマトリックスと親のマトリックスを掛け合わせる
		D3DXMatrixMultiply(
			&aMtxParts[nCntParts],
			&aMtxParts[nCntParts],
			&mtxParent);

		if (nCntParts >= nParts) 
		{// 部品のカウントが取得したい部品番号に達した時、
			return aMtxParts[nParts];	// マトリックスを返す
		}
	}

	assert(false);
	return mtxSelf;
}