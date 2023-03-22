//========================================
// 
// モーション(3D)関連の処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** motion3D.cpp ***
//========================================
#include <assert.h>
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** モーション(3D)関連 ***
// モーション(3D)のアニメーション読み込み処理
void LoadMotionAnim3D(Motion3DSet motionSet, Parts3DInfo *pPartsInfo, Parts3DSet partsSet);
// モーション(3D)のアニメーション処理
void MotionAnim3D(Parts3DInfo *pPartsInfo, Parts3DSet partsSet);

//****************************************
// 構造体の定義
//****************************************
// モーション(3D)コマンド情報
typedef struct 
{
	char *pLabelName;	// ラベル名
	int nDataNum;		// 引数の数
}Motion3DCommandInfo;

//****************************************
// 
//****************************************
// モーションコマンドのラベル名
const Motion3DCommandInfo g_aMotionCommandInfo[MOTION3D_COMMAND_LABEL_MAX] =
{
	{"MOVE",4},	// 移動
	{"SPIN",4},	// 回転
};

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cppファイルの占有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** モーション(3D)関連 *** |----------
//============================================================

//========================================
// LoadMotionAnim3D関数 - モーション(3D)のアニメーション読み込み処理 -
// Author:RIKU NISHIMURA
//========================================
void LoadMotionAnim3D(Motion3DSet motionSet, Parts3DInfo *pPartsInfo, Parts3DSet partsSet)
{
	// 部品毎のアニメーションの読み込み
	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++)
	{
		// 部品毎のモーション(3D)の情報
		PartsMotion3D partsMotion3D = motionSet.aMotion[pPartsInfo->nMotion].aPartsMotion[nCntParts];

		for (int nCntCmd = 0; nCntCmd < partsMotion3D.nCommandNum; nCntCmd++)
		{
			MotionCommand cmd = partsMotion3D.aCommand[nCntCmd];	// コマンド情報
			Parts3D *pParts = &pPartsInfo->aParts[nCntParts];		// 部品(3D)の情報

			if (pPartsInfo->nCounterMotion != cmd.nTime)
			{// カウンターがタイムと一致した時、
				continue;
			}

			// コマンドラベルに応じた処理
			switch (cmd.command)
			{
			case MOTION3D_COMMAND_LABEL_MOVE:
			{
				// 位置
				D3DXVECTOR3 pos = D3DXVECTOR3(cmd.aData[0], cmd.aData[1], cmd.aData[2]);
				// 移動にかかる時間
				int nMoveTime = (int)cmd.aData[3];

				if (nMoveTime == 0)
				{// 移動にかかる時間が0の時、
					pParts->pos = pos;	// 位置を直接代入
				}
				else
				{// 移動にかかる時間が0でない時、
					// 元の位置を設定
					pParts->posOld = pParts->pos;
					// 目標位置を代入
					pParts->targetPos = pos;
					// 位置アニメーションにかかる時間を代入
					pParts->nPosAnimTime = nMoveTime;
					// 位置アニメーションカウンターを初期化
					pParts->nCounterPosAnim = 0;
					// 位置アニメーションフラグを真にする
					pParts->bPosAnim = true;
				}
			}
				break;
			case MOTION3D_COMMAND_LABEL_SPIN:
			{
				// 向き
				D3DXVECTOR3 rot = D3DXVECTOR3(cmd.aData[0], cmd.aData[1], cmd.aData[2]);
				// 回転にかかる時間
				int nSpinTime = (int)cmd.aData[3];

				if (nSpinTime == 0)
				{// 回転にかかる時間が0の時、
					pParts->rot = rot;	// 向きを直接代入
				}
				else
				{// 回転にかかる時間が0でない時、
					// 元の向きを設定
					pParts->rotOld = pParts->rot;
					// 目標向きを代入
					pParts->targetRot = rot;
					// 向きアニメーションにかかる時間を代入
					pParts->nRotAnimTime = nSpinTime;
					// 向きアニメーションカウンターを初期化
					pParts->nCounterRotAnim = 0;
					// 向きアニメーションフラグを真にする
					pParts->bRotAnim = true;
				}
			}
				break;
			}
		}
	}
}

//========================================
// MotionAnim3D関数 - モーション(3D)のアニメーション処理 -
// Author:RIKU NISHIMURA
//========================================
void MotionAnim3D(Parts3DInfo *pPartsInfo, Parts3DSet partsSet)
{
	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++)
	{
		// 部品の情報のポインタ
		Parts3D *pParts = &pPartsInfo->aParts[nCntParts];

		if (pParts->bPosAnim)
		{// 位置アニメーションフラグが真の時、
			if (++pParts->nCounterPosAnim >= pParts->nPosAnimTime)
			{// 位置アニメーションカウンターを加算した結果位置アニメーションにかかる時間を上回った時、
				// 位置アニメーションフラグを偽にする
				pParts->bPosAnim = false;

				// 位置に目標位置を代入
				pParts->pos = pParts->targetPos;
			}
		}

		if (pParts->bRotAnim)
		{// 角度アニメーションフラグが真の時、
			if (++pParts->nCounterRotAnim >= pParts->nRotAnimTime)
			{// 向きアニメーションカウンターを加算した結果向きアニメーションにかかる時間を上回った時、
				// 向きアニメーションフラグを偽にする
				pParts->bRotAnim = false;
				
				// 向きに目標向きを代入
				pParts->rot = pParts->targetRot;
			}
		}
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** モーション(3D)関連 *** |----------
//============================================================

//========================================
// LoadMotion3DSet関数 - モーション(3D)設定情報の読み込み処理 -
// Author:RIKU NISHIMURA
//========================================
void LoadMotion3DSet(FILE *pFile, Motion3DSet *pMotionSet)
{
	char aDataSearch[TXT_MAX];	// データ検索用

	// モーション数を初期化
	pMotionSet->nMotionNum = 0;

	// モーション設定情報の読み込みを開始
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); // 検索

		if (!strcmp(aDataSearch, "MOTIONSET_END"))
		{// 読み込みを終了
			break;
		}
		else if (!strcmp(aDataSearch, "MOTION"))
		{
			// モーションの情報のポインタ
			Motion3D *pMotion = &pMotionSet->aMotion[pMotionSet->nMotionNum];
			int nCntParts = 0;	// 部品のカウント

			// モーション情報の読み込みを開始
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); // 検索
				
				if (!strcmp(aDataSearch, "MOTION_END"))
				{// モーション数を加算し、読み込みを終了
					pMotionSet->nMotionNum++;
					break; 
				}
				else if (!strcmp(aDataSearch, "LOOP_TIME:"))
				{// ループ時間 
					fscanf(pFile, "%d", &pMotion->nLoopTime);
				}
				else if (!strcmp(aDataSearch, "LOOP:"))
				{// ループするかフラグ
					int nTemp;
					fscanf(pFile, "%d", &nTemp);
					pMotion->bLoop = (nTemp != 0);
				}
				else if (!strcmp(aDataSearch, "PARTS"))
				{
					// 部品毎のモーションの情報のポインタ
					PartsMotion3D *pPartsMotion = &pMotion->aPartsMotion[nCntParts];

					// コマンド数を初期化
					pPartsMotion->nCommandNum = 0;

					// 部品毎のモーションの情報の読み込みを開始
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch); // 検索

						if (!strcmp(aDataSearch, "PARTS_END"))
						{// 部品のカウントを加算し、読み込みを終了
							nCntParts++;
							break;
						}
						else if (!strcmp(aDataSearch, "TIME"))
						{
							// コマンド数
							int nCmdNum = pPartsMotion->nCommandNum;
							// コマンド開始時間
							fscanf(pFile, "%d", &pPartsMotion->aCommand[nCmdNum].nTime);

							// コマンド番号
							int nCmd = 0;
							// コマンドラベルを読み取る
							fscanf(pFile, "%s", aDataSearch);

							// 総当たりでラベルの判定を行う
							for (int nCntLabel = 0; nCntLabel < MOTION3D_COMMAND_LABEL_MAX; nCntLabel++) 
							{
								if (!strcmp(aDataSearch, g_aMotionCommandInfo[nCntLabel].pLabelName))
								{// 文字列がラベル名と一致している時、
									// ラベルを設定
									pPartsMotion->aCommand[nCmdNum].command = (MOTION3D_COMMAND_LABEL)nCntLabel;
									// コマンド番号を指定
									nCmd = nCntLabel;
									break;
								}
							}

							// 引数の読み込みを引数の数分行う
							for (int nCntData = 0; nCntData < g_aMotionCommandInfo[nCmd].nDataNum; nCntData++)
							{
								fscanf(pFile, "%f", &pPartsMotion->aCommand[nCmdNum].aData[nCntData]);
							}

							// コマンド数を加算
							pPartsMotion->nCommandNum++;
						}
					}
				}
			}
		}
	}
}

//========================================
// UpdateMotion3D関数 - モーション(3D)の更新処理 -
// Author:RIKU NISHIMURA
//========================================
bool UpdateMotion3D(Motion3DSet motionSet, Parts3DInfo *pPartsInfo, Parts3DSet partsSet)
{
	// モーション番号
	int nMotion = pPartsInfo->nMotion;

	if (motionSet.aMotion[nMotion].nLoopTime == -1)
	{// モーションのループ時間が-1の時、
		// 処理を終了する
		return false;
	}

	// モーションのアニメーション(3D)読み込み処理
	LoadMotionAnim3D(motionSet, pPartsInfo, partsSet);

	// モーションのアニメーション処理
	MotionAnim3D(pPartsInfo, partsSet);

	// モーションがループしたかフラグ
	bool bMotionLoop = false;

	if (++pPartsInfo->nCounterMotion > motionSet.aMotion[nMotion].nLoopTime)
	{// モーションカウンターを加算した結果ループ時間に達した時、
		bMotionLoop = true;	// モーションがループしたかフラグを真にする

		if (motionSet.aMotion[nMotion].bLoop)
		{// ループするかフラグが真の時、
			// モーションカウンターをループ制御
			IntLoopControl(&pPartsInfo->nCounterMotion, motionSet.aMotion[nMotion].nLoopTime, 0);
		}
		else
		{// ループするかフラグが偽の時、
			// モーションカウンターを制御
			IntControl(&pPartsInfo->nCounterMotion, motionSet.aMotion[nMotion].nLoopTime, 0);
		}
	}

	// モーションがループしたかフラグを返す
	return bMotionLoop;
}

//========================================
// SetMotion3D関数 - モーション(3D)の設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetMotion3D(Parts3DInfo *pPartsInfo)
{
	if (pPartsInfo->nMotion == pPartsInfo->nMotionOld)
	{// 既にそのモーション番号に設定されている時、
		return;	// 処理を終了する
	}

	// 過去のモーション番号として保存
	pPartsInfo->nMotionOld = pPartsInfo->nMotion;
	// モーションカウンターを初期化
	pPartsInfo->nCounterMotion = 0;
}