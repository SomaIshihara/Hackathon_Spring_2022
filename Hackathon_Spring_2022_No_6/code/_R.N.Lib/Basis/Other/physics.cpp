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
// 当たり判定時の小数の位
#define HIT_TEST_DECIMAL_PLACE	(20)
// スリップ時に取る距離
#define SLIP_DISTANCE (0.1f)

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
// 四角から四角の衝突チェック(3Dモード)
void SquareSquareCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts);
// 円筒から四角の衝突チェック(3Dモード)
void CylinderSquareCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts,
	bool bRflc, bool bSlip);
// 円筒から円筒の衝突チェック(3Dモード)
void CylinderCylinderCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts,
	bool bRflc, bool bSlip);
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

//========================================
// SquareSquareCollision3D関数 - 四角から四角の衝突チェック(3Dモード) -
// Author:RIKU NISHIMURA
//========================================
void SquareSquareCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts)
{
	HitTest myHitTest	// 自分の当たり判定情報
		= *myCollInfo.pHitTest;
	HitTest pairHitTest	// 相手の当たり判定情報
		= *pairCollInfo.pHitTest;

	// 当たり判定の計算に必要なパラメーターを整数型に変換(演算誤差対策)
	int nMyX = myCollInfo.pPos->x					* HIT_TEST_DECIMAL_PLACE;
	int nMyY = myCollInfo.pPos->y					* HIT_TEST_DECIMAL_PLACE;
	int nMyZ = myCollInfo.pPos->z					* HIT_TEST_DECIMAL_PLACE;
	int nMyPartsX = myHitTestParts.fixedRelativePos.x		* HIT_TEST_DECIMAL_PLACE;
	int nMyPartsY = myHitTestParts.fixedRelativePos.y		* HIT_TEST_DECIMAL_PLACE;
	int nMyPartsZ = myHitTestParts.fixedRelativePos.z		* HIT_TEST_DECIMAL_PLACE;
	int nMyOldX = myCollInfo.posOld.x					* HIT_TEST_DECIMAL_PLACE;
	int nMyOldY = myCollInfo.posOld.y					* HIT_TEST_DECIMAL_PLACE;
	int nMyOldZ = myCollInfo.posOld.z					* HIT_TEST_DECIMAL_PLACE;
	int nMyWidth = myHitTestParts.fWidth					* HIT_TEST_DECIMAL_PLACE;
	int nMyHeight = myHitTestParts.fHeight				* HIT_TEST_DECIMAL_PLACE;
	int nMyDepth = myHitTestParts.fDepth					* HIT_TEST_DECIMAL_PLACE;
	int nPairX = pairCollInfo.pPos->x					* HIT_TEST_DECIMAL_PLACE;
	int nPairY = pairCollInfo.pPos->y					* HIT_TEST_DECIMAL_PLACE;
	int nPairZ = pairCollInfo.pPos->z					* HIT_TEST_DECIMAL_PLACE;
	int nPairPartsX = pairHitTestParts.fixedRelativePos.x	* HIT_TEST_DECIMAL_PLACE;
	int nPairPartsY = pairHitTestParts.fixedRelativePos.y	* HIT_TEST_DECIMAL_PLACE;
	int nPairPartsZ = pairHitTestParts.fixedRelativePos.z	* HIT_TEST_DECIMAL_PLACE;
	int nPairOldX = pairCollInfo.posOld.x					* HIT_TEST_DECIMAL_PLACE;
	int nPairOldY = pairCollInfo.posOld.y					* HIT_TEST_DECIMAL_PLACE;
	int nPairOldZ = pairCollInfo.posOld.z					* HIT_TEST_DECIMAL_PLACE;
	int nPairWidth = pairHitTestParts.fWidth				* HIT_TEST_DECIMAL_PLACE;
	int nPairHeight = pairHitTestParts.fHeight				* HIT_TEST_DECIMAL_PLACE;
	int nPairDepth = pairHitTestParts.fDepth				* HIT_TEST_DECIMAL_PLACE;

	switch (vector)
	{
	case /*/ X方向 /*/VECTOR_X: {
		if (((nMyZ + nMyPartsZ) + (nMyDepth * 0.5f) > (nPairZ + nPairPartsZ) - (nPairDepth * 0.5f)) &&
			((nMyZ + nMyPartsZ) - (nMyDepth * 0.5f) < (nPairZ + nPairPartsZ) + (nPairDepth * 0.5f)) &&
			((nMyY + nMyPartsY) + (nMyHeight * 0.5f) > (nPairY + nPairPartsY) - (nPairHeight * 0.5f)) &&
			((nMyY + nMyPartsY) - (nMyHeight * 0.5f) < (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
		{// 奥辺と手前辺が相手の幅の内側の時、
			if (((nMyX + nMyPartsX) + (nMyWidth * 0.5f) >= (nPairX + nPairPartsX) - (nPairWidth * 0.5f))		// 現在の右辺が相手の左辺よりも右に位置している
				&&																								// &
				((nMyOldX + nMyPartsX) + (nMyWidth * 0.5f) <= (nPairOldX + nPairPartsX) - (nPairWidth * 0.5f)))	// 過去の右辺が相手の左辺よりも左に位置している
			{// 左からめり込んでいる時、
				if (!pairHitTestParts.aGhost[HITDIRECTION_LEFT])
				{// 左からのすり抜けが偽の時、
					if (pCollision != NULL)
					{// 衝突情報がNULLでない時、
						pCollision->bColl =	// 衝突フラグを真にする
							pCollision->aColl[HITDIRECTION_LEFT] = true;
					}
					myCollInfo.pPos->x =	// 位置を相手の当たり判定の左にする
						(nPairX + nPairPartsX - (nPairWidth * 0.5f) - nMyPartsX - (nMyWidth * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}
			else if (((nMyX + nMyPartsX) - (nMyWidth * 0.5f) <= (nPairX + nPairPartsX) + (nPairWidth * 0.5f))	// 左辺が相手の右辺よりも左に位置している
				&&																								// &
				((nMyOldX + nMyPartsX) - (nMyWidth * 0.5f) >= (nPairOldX + nPairPartsX) + (nPairWidth * 0.5f)))	// 過去の左辺が相手の右辺よりも右に位置している
			{// 右からめり込んでいる時、
				if (!pairHitTestParts.aGhost[HITDIRECTION_RIGHT])
				{// 左からのすり抜けが偽の時、
					if (pCollision != NULL)
					{// 衝突情報がNULLでない時、
						pCollision->bColl =	// 衝突フラグを真にする
							pCollision->aColl[HITDIRECTION_RIGHT] = true;
					}
					myCollInfo.pPos->x =	// 位置を相手の当たり判定の右にする
						(nPairX + nPairPartsX + (nPairWidth * 0.5f) - nMyPartsX + (nMyWidth * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}

			if (pCollision != NULL)
			{// 衝突情報がNULLでない時、
				if (((nMyX + nMyPartsX) + (nMyWidth * 0.5f) >= (nPairX + nPairPartsX) - (nPairWidth * 0.5f))
					&&
					((nMyX + nMyPartsX) + (nMyWidth * 0.5f) <= (nPairX + nPairPartsX) + (nPairWidth * 0.5f)))
				{// 現在の右辺が相手の当たり判定の内側の時、
					pCollision->aOvl[HITDIRECTION_LEFT] = true;	// 左方向からの内側フラグを真にする


					if (!pairHitTestParts.aGhost[HITDIRECTION_LEFT])
					{// 右からのすり抜けが偽の時、
						pCollision->bHit = true;						// 当たりフラグを真にする
						pCollision->aHit[HITDIRECTION_LEFT] = true;	// 左方向からの当たりフラグを真にする
					}
				}

				if (((nMyX + nMyPartsX) - (nMyWidth * 0.5f) >= (nPairX + nPairPartsX) - (nPairWidth * 0.5f))
					&&
					((nMyX + nMyPartsX) - (nMyWidth * 0.5f) <= (nPairX + nPairPartsX) + (nPairWidth * 0.5f)))
				{// 現在の左辺が相手の当たり判定の内側の時、
					pCollision->aOvl[HITDIRECTION_RIGHT] = true;	// 右方向からの内側フラグを真にする


					if (!pairHitTestParts.aGhost[HITDIRECTION_RIGHT])
					{// 右からのすり抜けが偽の時、
						pCollision->bHit = true;							// 当たりフラグを真にする
						pCollision->aHit[HITDIRECTION_RIGHT] = true;		// 右方向からの当たりフラグを真にする
					}
				}
			}
		}
	}
							  break;
	case /*/ Y方向 /*/VECTOR_Y: {
		if (((nMyX + nMyPartsX) + (nMyWidth * 0.5f) > (nPairX + nPairPartsX) - (nPairWidth * 0.5f)) &&
			((nMyX + nMyPartsX) - (nMyWidth * 0.5f) < (nPairX + nPairPartsX) + (nPairWidth * 0.5f)) &&
			((nMyZ + nMyPartsZ) + (nMyDepth * 0.5f) > (nPairZ + nPairPartsZ) - (nPairDepth * 0.5f)) &&
			((nMyZ + nMyPartsZ) - (nMyDepth * 0.5f) < (nPairZ + nPairPartsZ) + (nPairDepth * 0.5f)))
		{// 左辺と右辺が相手の幅の内側の時、
			if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) > (nPairY + nPairPartsY) - (nPairHeight * 0.5f))			// 足元が相手の奥辺よりも手前に位置している
				&&																									// &
				((nMyOldY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairOldY + nPairPartsY) - (nPairHeight * 0.5f)))	// 過去の足元が相手の下辺よりも下に位置している
			{// 下からめり込んでいる時、
				if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
				{// 左からのすり抜けが偽の時、
					if (pCollision != NULL)
					{// 衝突情報がNULLでない時、
						pCollision->bColl =	// 衝突フラグを真にする
							pCollision->aColl[HITDIRECTION_BOTTOM] = true;
					}
					myCollInfo.pPos->y = 	// 位置を相手の当たり判定の下にする
						(nPairY + nPairPartsY - (nPairHeight * 0.5f) - nMyPartsY - (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}
			else if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) < (nPairY + nPairPartsY) + (nPairHeight * 0.5f))		// 頭が相手の上辺よりも下に位置している
				&&																									// &
				((nMyOldY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairOldY + nPairPartsY) + (nPairHeight * 0.5f)))	// 過去の頭が相手の上辺よりも上に位置している
			{// 上からめり込んでいる時、
				if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
				{// 上からのすり抜けが偽の時、
					if (pCollision != NULL)
					{// 衝突情報がNULLでない時、
						pCollision->bColl =	// 衝突フラグを真にする
							pCollision->aColl[HITDIRECTION_TOP] = true;
					}
					myCollInfo.pPos->y = // 位置を相手の当たり判定の上にする
						(nPairY + nPairPartsY + (nPairHeight * 0.5f) - nMyPartsY + (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}

			if (pCollision != NULL)
			{// 衝突情報がNULLでない時、
				if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
					&&
					((nMyY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
				{// 現在の上辺が相手の当たり判定の内側の時、
					pCollision->aOvl[HITDIRECTION_BOTTOM] = true;	// 下方向からの内側フラグを真にする

					if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
					{// 下からのすり抜けが偽の時、
						pCollision->bHit = true;						// 当たりフラグを真にする
						pCollision->aHit[HITDIRECTION_BOTTOM] = true;	// 下方向からの当たりフラグを真にする
					}
				}

				if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
					&&
					((nMyY + nMyPartsY) - (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
				{// 現在の下辺が相手の当たり判定の内側の時、
					pCollision->aOvl[HITDIRECTION_TOP] = true;	// 上方向からの内側フラグを真にする


					if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
					{// 上からのすり抜けが偽の時、
						pCollision->bHit = true;						// 当たりフラグを真にする
						pCollision->aHit[HITDIRECTION_TOP] = true;	// 上方向からの当たりフラグを真にする
					}
				}
			}
		}
	}
							  break;
	case /*/ Z方向 /*/VECTOR_Z: {
		if (((nMyX + nMyPartsX) + (nMyWidth * 0.5f) > (nPairX + nPairPartsX) - (nPairWidth * 0.5f)) &&
			((nMyX + nMyPartsX) - (nMyWidth * 0.5f) < (nPairX + nPairPartsX) + (nPairWidth * 0.5f)) &&
			((nMyY + nMyPartsY) + (nMyHeight * 0.5f) > (nPairY + nPairPartsY) - (nPairHeight * 0.5f)) &&
			((nMyY + nMyPartsY) - (nMyHeight * 0.5f) < (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
		{// 左辺と右辺が相手の幅の内側の時、
			if (((nMyZ + nMyPartsZ) + (nMyDepth * 0.5f) > (nPairZ + nPairPartsZ) - (nPairDepth * 0.5f))			// 足元が相手の奥辺よりも手前に位置している
				&&																								// &
				((nMyOldZ + nMyPartsZ) + (nMyDepth * 0.5f) <= (nPairOldZ + nPairPartsZ) - (nPairDepth * 0.5f)))	// 過去の足元が相手の奥辺よりも奥に位置している
			{// 奥からめり込んでいる時、
				if (!pairHitTestParts.aGhost[HITDIRECTION_BACK])
				{// 左からのすり抜けが偽の時、
					if (pCollision != NULL)
					{// 衝突情報がNULLでない時、
						pCollision->bColl =	// 衝突フラグを真にする
							pCollision->aColl[HITDIRECTION_BACK] = true;
					}
					myCollInfo.pPos->z = 	// 位置を相手の当たり判定の奥にする
						(nPairZ + nPairPartsZ - (nPairDepth * 0.5f) - nMyPartsZ - (nMyDepth * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}
			else if (((nMyZ + nMyPartsZ) - (nMyDepth * 0.5f) < (nPairZ + nPairPartsZ) + (nPairDepth * 0.5f))	// 頭が相手の手前辺よりも奥に位置している
				&&																								// &
				((nMyOldZ + nMyPartsZ) - (nMyDepth * 0.5f) >= (nPairOldZ + nPairPartsZ) + (nPairDepth * 0.5f)))	// 過去の頭が相手の手前辺よりも手前に位置している
			{// 手前からめり込んでいる時、
				if (!pairHitTestParts.aGhost[HITDIRECTION_FRONT])
				{// 手前からのすり抜けが偽の時、
					if (pCollision != NULL)
					{// 衝突情報がNULLでない時、
						pCollision->bColl =	// 衝突フラグを真にする
							pCollision->aColl[HITDIRECTION_FRONT] = true;
					}
					myCollInfo.pPos->z = // 位置を相手の当たり判定の手前にする
						(nPairZ + nPairPartsZ + (nPairDepth * 0.5f) - nMyPartsZ + (nMyDepth * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}

			if (pCollision != NULL)
			{// 衝突情報がNULLでない時、
				if (((nMyZ + nMyPartsZ) + (nMyDepth * 0.5f) >= (nPairZ + nPairPartsZ) - (nPairDepth * 0.5f))
					&&
					((nMyZ + nMyPartsZ) + (nMyDepth * 0.5f) <= (nPairZ + nPairPartsZ) + (nPairDepth * 0.5f)))
				{// 現在の手前辺が相手の当たり判定の内側の時、
					pCollision->aOvl[HITDIRECTION_BACK] = true;	// 奥方向からの内側フラグを真にする

					if (!pairHitTestParts.aGhost[HITDIRECTION_BACK])
					{// 奥からのすり抜けが偽の時、
						pCollision->bHit = true;						// 当たりフラグを真にする
						pCollision->aHit[HITDIRECTION_BACK] = true;	// 奥方向からの当たりフラグを真にする
					}
				}

				if (((nMyZ + nMyPartsZ) - (nMyDepth * 0.5f) >= (nPairZ + nPairPartsZ) - (nPairDepth * 0.5f))
					&&
					((nMyZ + nMyPartsZ) - (nMyDepth * 0.5f) <= (nPairZ + nPairPartsZ) + (nPairDepth * 0.5f)))
				{// 現在の奥辺が相手の当たり判定の内側の時、
					pCollision->aOvl[HITDIRECTION_FRONT] = true;	// 手前方向からの内側フラグを真にする

					if (!pairHitTestParts.aGhost[HITDIRECTION_FRONT])
					{// 手前からのすり抜けが偽の時、
						pCollision->bHit = true;						// 当たりフラグを真にする
						pCollision->aHit[HITDIRECTION_FRONT] = true;	// 手前方向からの当たりフラグを真にする
					}
				}
			}
		}
	}
							  break;
	}
}

//========================================
// CylinderSquareCollision3D関数 - 円筒から四角の衝突チェック(3Dモード) -
// Author:RIKU NISHIMURA
//========================================
void CylinderSquareCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts,
	bool bRflc, bool bSlip)
{
	// 自身の大きさ
	float fMyScale = (myHitTestParts.fWidth + myHitTestParts.fDepth) * 0.5f * myCollInfo.fScale;
	// 幅
	float fWidth = (pairHitTestParts.fWidth * pairCollInfo.fScale) + fMyScale;
	// 奥行き
	float fDepth = (pairHitTestParts.fDepth * pairCollInfo.fScale) + fMyScale;

	pairCollInfo.pRot->y += D3DX_PI;
	pairCollInfo.rotOld.y += D3DX_PI;

	D3DXVECTOR3 pos0, pos1, pos2, pos3;	// 時計回りに見て右下からの4頂点の位置(相手)
	{
		// 位置
		D3DXVECTOR3 pos = *pairCollInfo.pPos;
		// 相対位置
		D3DXVECTOR3 relativePos = pairHitTestParts.fixedRelativePos * pairCollInfo.fScale;
		// 向き
		D3DXVECTOR3 rot1 = *pairCollInfo.pRot;

		// 位置にX相対位置を反映
		pos.x += sinf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		pos.z += cosf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		// 位置にZ相対位置を反映
		pos.x += sinf(rot1.y) * relativePos.z;
		pos.z += cosf(rot1.y) * relativePos.z;

		// 向き
		D3DXVECTOR3 rot2 = *pairCollInfo.pRot + pairHitTestParts.fixedRelativeRot;

		// 4頂点の位置を設定
		pos0.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (sinf(rot2.y) * (fDepth * -0.5f));
		pos0.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (cosf(rot2.y) * (fDepth * -0.5f));
		pos1.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (sinf(rot2.y) * (fDepth * -0.5f));
		pos1.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (cosf(rot2.y) * (fDepth * -0.5f));
		pos2.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (sinf(rot2.y) * (fDepth * 0.5f));
		pos2.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (cosf(rot2.y) * (fDepth * 0.5f));
		pos3.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (sinf(rot2.y) * (fDepth * 0.5f));
		pos3.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (cosf(rot2.y) * (fDepth * 0.5f));
	}
	D3DXVECTOR3 posOld0, posOld1, posOld2, posOld3;	// 時計回りに見て右下からの4頂点の過去の位置(相手)
	{
		// 位置
		D3DXVECTOR3 pos = pairCollInfo.posOld;
		// 相対位置
		D3DXVECTOR3 relativePos = pairHitTestParts.fixedRelativePos * pairCollInfo.fScale;
		// 向き
		D3DXVECTOR3 rot1 = pairCollInfo.rotOld;

		// 位置にX相対位置を反映
		pos.x += sinf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		pos.z += cosf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		// 位置にZ相対位置を反映
		pos.x += sinf(rot1.y) * relativePos.z;
		pos.z += cosf(rot1.y) * relativePos.z;

		// 向き
		D3DXVECTOR3 rot2 = pairCollInfo.rotOld + pairHitTestParts.fixedRelativeRot;

		// 4頂点の位置を設定
		posOld0.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (sinf(rot2.y) * (fDepth * -0.5f));
		posOld0.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (cosf(rot2.y) * (fDepth * -0.5f));
		posOld1.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (sinf(rot2.y) * (fDepth * -0.5f));
		posOld1.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (cosf(rot2.y) * (fDepth * -0.5f));
		posOld2.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (sinf(rot2.y) * (fDepth * 0.5f));
		posOld2.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (cosf(rot2.y) * (fDepth * 0.5f));
		posOld3.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (sinf(rot2.y) * (fDepth * 0.5f));
		posOld3.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (cosf(rot2.y) * (fDepth * 0.5f));
	}

	pairCollInfo.pRot->y -= D3DX_PI;
	pairCollInfo.rotOld.y -= D3DX_PI;

	switch (vector)
	{
	case /*/ Z方向 /*/VECTOR_Z:
	{
		if (!(
			((myCollInfo.pPos->y + (myHitTestParts.fixedRelativePos.y * myCollInfo.fScale)) + (myHitTestParts.fHeight * 0.5f * myCollInfo.fScale) > (pairCollInfo.pPos->y + (pairHitTestParts.fixedRelativePos.y * pairCollInfo.fScale)) - (pairHitTestParts.fHeight * 0.5f * pairCollInfo.fScale)) &&
			((myCollInfo.pPos->y + (myHitTestParts.fixedRelativePos.y * myCollInfo.fScale)) - (myHitTestParts.fHeight * 0.5f * myCollInfo.fScale) < (pairCollInfo.pPos->y + (pairHitTestParts.fixedRelativePos.y * pairCollInfo.fScale)) + (pairHitTestParts.fHeight * 0.5f * pairCollInfo.fScale))
			))
		{// Y軸で接していない時、
			break;	// 処理を抜ける
		}

		bool aInside[HITDIRECTION_MAX];	// 内側フラグ

											// 奥辺
		{
			D3DXVECTOR3 vecToPos = *myCollInfo.pPos - pos2;
			D3DXVECTOR3 vecToPosOld = myCollInfo.posOld - posOld2;
			D3DXVECTOR3 point =	// 交点の座標
				FindIntersectionPointLookDown(myCollInfo.posOld, *myCollInfo.pPos, pos2, pos3);
			float	fDistance3toP = FindDistanceLookDown(pos3, point);	// 頂点3から交点までの距離
			float	fDistance2toP = FindDistanceLookDown(pos2, point);	// 頂点2から交点までの距離
			float	fDistance3to2 = FindDistanceLookDown(pos3, pos2);	// 頂点3から頂点2までの距離

																		// 奥辺からの内側フラグを取得
			aInside[HITDIRECTION_BACK] = (((pos3 - pos2).z * vecToPos.x) - ((pos3 - pos2).x * vecToPos.z) >= 0);

			if (((aInside[HITDIRECTION_BACK]) && (((posOld3 - posOld2).z * vecToPosOld.x) - ((posOld3 - posOld2).x * vecToPosOld.z) <= 0))
				&&
				(fDistance3toP <= fDistance3to2)
				&&
				(fDistance2toP <= fDistance3to2))
			{// 奥辺から当たっている時、
				if (!pairHitTestParts.aGhost[HITDIRECTION_BACK]) {
					pCollision->bColl =	// 衝突フラグを真にする
						pCollision->aColl[HITDIRECTION_BACK] = true;

					if (!pairHitTestParts.aGhost[HITDIRECTION_BACK])
					{// 相手のすり抜けフラグが偽の時、
						pCollision->bHit =	// 当たりフラグを真にする
							pCollision->aHit[HITDIRECTION_BACK] = true;
					}
				}

				if (!pairHitTestParts.aGhost[HITDIRECTION_BACK])
				{
					if (bSlip)
					{// 滑りフラグが真の時、
						float fAngle = FindAngleLookDown(pos2, pos3) - (D3DX_PI * 0.5f);	// 向き

																							// 位置を更新
						D3DXVECTOR3 pos = FindIntersectionPointLookDown(
							*myCollInfo.pPos,
							*myCollInfo.pPos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)),
							pos3,
							pos2);
						myCollInfo.pPos->x = pos.x + sinf(fAngle) * SLIP_DISTANCE;
						myCollInfo.pPos->z = pos.z + cosf(fAngle) * SLIP_DISTANCE;
					}
					else
					{// 滑りフラグが偽の時、
						// 位置を更新
						myCollInfo.pPos->x = point.x;
						myCollInfo.pPos->z = point.z;
					}
				}

				return;
			}
		}

		// 手前辺
		{
			D3DXVECTOR3 vecToPos = *myCollInfo.pPos - pos0;
			D3DXVECTOR3 vecToPosOld = myCollInfo.posOld - posOld0;
			D3DXVECTOR3 point =	// 交点の座標
				FindIntersectionPointLookDown(myCollInfo.posOld, *myCollInfo.pPos, pos0, pos1);
			float	fDistance1toP = FindDistanceLookDown(pos1, point);	// 頂点1から交点までの距離
			float	fDistance0toP = FindDistanceLookDown(pos0, point);	// 頂点0から交点までの距離
			float	fDistance1to0 = FindDistanceLookDown(pos1, pos0);	// 頂点1から頂点0までの距離

																		// 手前辺からの内側フラグを取得
			aInside[HITDIRECTION_FRONT] = (((pos1 - pos0).z * vecToPos.x) - ((pos1 - pos0).x * vecToPos.z) >= 0);

			if (((aInside[HITDIRECTION_FRONT]) && (((posOld1 - posOld0).z * vecToPosOld.x) - ((posOld1 - posOld0).x * vecToPosOld.z) <= 0))
				&&
				(fDistance1toP <= fDistance1to0)
				&&
				(fDistance0toP <= fDistance1to0))
			{// 手前辺から当たっている時、
				if (!pairHitTestParts.aGhost[HITDIRECTION_FRONT]) {
					pCollision->bColl =	// 衝突フラグを真にする
						pCollision->aColl[HITDIRECTION_FRONT] = true;

					if (!pairHitTestParts.aGhost[HITDIRECTION_FRONT])
					{// 相手のすり抜けフラグが偽の時、
						pCollision->bHit =	// 当たりフラグを真にする
							pCollision->aHit[HITDIRECTION_FRONT] = true;
					}
				}

				if (!pairHitTestParts.aGhost[HITDIRECTION_FRONT])
				{
					if (bSlip)
					{// 滑りフラグが真の時、
						float fAngle = FindAngleLookDown(pos0, pos1) - (D3DX_PI * 0.5f);	// 向き

																							// 位置を更新
						D3DXVECTOR3 pos = FindIntersectionPointLookDown(
							*myCollInfo.pPos,
							*myCollInfo.pPos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)),
							pos1,
							pos0);
						myCollInfo.pPos->x = pos.x + sinf(fAngle) * SLIP_DISTANCE;
						myCollInfo.pPos->z = pos.z + cosf(fAngle) * SLIP_DISTANCE;
					}
					else
					{// 滑りフラグが偽の時、
					 // 位置を更新
						myCollInfo.pPos->x = point.x;
						myCollInfo.pPos->z = point.z;
					}
				}

				return;
			}
		}

		// 左辺
		{
			D3DXVECTOR3 vecToPos = *myCollInfo.pPos - pos1;
			D3DXVECTOR3 vecToPosOld = myCollInfo.posOld - posOld1;
			D3DXVECTOR3 point =	// 交点の座標
				FindIntersectionPointLookDown(myCollInfo.posOld, *myCollInfo.pPos, pos1, pos2);
			float	fDistance2toP = FindDistanceLookDown(pos2, point);	// 頂点2から交点までの距離
			float	fDistance1toP = FindDistanceLookDown(pos1, point);	// 頂点1から交点までの距離
			float	fDistance2to1 = FindDistanceLookDown(pos2, pos1);	// 頂点2から頂点1までの距離

																		// 左辺からの内側フラグを取得
			aInside[HITDIRECTION_LEFT] = (((pos2 - pos1).z * vecToPos.x) - ((pos2 - pos1).x * vecToPos.z) >= 0);

			if (((aInside[HITDIRECTION_LEFT]) && (((posOld2 - posOld1).z * vecToPosOld.x) - ((posOld2 - posOld1).x * vecToPosOld.z) <= 0))
				&&
				(FindDistanceLookDown(pos2, point) <= FindDistanceLookDown(pos2, pos1))
				&&
				(FindDistanceLookDown(pos1, point) <= FindDistanceLookDown(pos2, pos1)))
			{// 左辺から当たっている時、
				if (!pairHitTestParts.aGhost[HITDIRECTION_LEFT]) {
					pCollision->bColl =	// 衝突フラグを真にする
						pCollision->aColl[HITDIRECTION_LEFT] = true;

					if (!pairHitTestParts.aGhost[HITDIRECTION_LEFT])
					{// 相手のすり抜けフラグが偽の時、
						pCollision->bHit =	// 当たりフラグを真にする
							pCollision->aHit[HITDIRECTION_LEFT] = true;
					}
				}

				if (!pairHitTestParts.aGhost[HITDIRECTION_LEFT])
				{
					if (bSlip)
					{// 滑りフラグが真の時、
						float fAngle = FindAngleLookDown(pos1, pos2) - (D3DX_PI * 0.5f);	// 向き

																							// 位置を更新
						D3DXVECTOR3 pos = FindIntersectionPointLookDown(
							*myCollInfo.pPos,
							*myCollInfo.pPos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)),
							pos2,
							pos1);
						myCollInfo.pPos->x = pos.x + sinf(fAngle) * SLIP_DISTANCE;
						myCollInfo.pPos->z = pos.z + cosf(fAngle) * SLIP_DISTANCE;
					}
					else
					{// 滑りフラグが偽の時、
					 // 位置を更新
						myCollInfo.pPos->x = point.x;
						myCollInfo.pPos->z = point.z;
					}
				}

				return;
			}
		}

		// 右辺
		{
			D3DXVECTOR3 vecToPos = *myCollInfo.pPos - pos3;
			D3DXVECTOR3 vecToPosOld = myCollInfo.posOld - posOld3;
			D3DXVECTOR3 point =	// 交点の座標
				FindIntersectionPointLookDown(myCollInfo.posOld, *myCollInfo.pPos, pos3, pos0);
			float	fDistance0toP = FindDistanceLookDown(pos0, point);	// 頂点0から交点までの距離
			float	fDistance3toP = FindDistanceLookDown(pos3, point);	// 頂点3から交点までの距離
			float	fDistance0to3 = FindDistanceLookDown(pos0, pos3);	// 頂点0から頂点3までの距離

																		// 右辺からの内側フラグを取得
			aInside[HITDIRECTION_RIGHT] = (((pos0 - pos3).z * vecToPos.x) - ((pos0 - pos3).x * vecToPos.z) >= 0);

			if (((aInside[HITDIRECTION_RIGHT]) && (((posOld0 - posOld3).z * vecToPosOld.x) - ((posOld0 - posOld3).x * vecToPosOld.z) <= 0))
				&&
				(fDistance0toP <= fDistance0to3)
				&&
				(fDistance3toP <= fDistance0to3))
			{// 右辺から当たっている時、
				if (!pairHitTestParts.aGhost[HITDIRECTION_RIGHT]) {
					pCollision->bColl =	// 衝突フラグを真にする
						pCollision->aColl[HITDIRECTION_RIGHT] = true;

					if (!pairHitTestParts.aGhost[HITDIRECTION_RIGHT])
					{// 相手のすり抜けフラグが偽の時、
						pCollision->bHit =	// 当たりフラグを真にする
							pCollision->aHit[HITDIRECTION_RIGHT] = true;
					}
				}

				if (!pairHitTestParts.aGhost[HITDIRECTION_RIGHT])
				{
					if (bSlip)
					{// 滑りフラグが真の時、
						float fAngle = FindAngleLookDown(pos3, pos0) - (D3DX_PI * 0.5f);	// 向き

																							// 位置を更新
						D3DXVECTOR3 pos = FindIntersectionPointLookDown(
							*myCollInfo.pPos,
							*myCollInfo.pPos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)),
							pos0,
							pos3);
						myCollInfo.pPos->x = pos.x + sinf(fAngle) * SLIP_DISTANCE;
						myCollInfo.pPos->z = pos.z + cosf(fAngle) * SLIP_DISTANCE;
					}
					else
					{// 滑りフラグが偽の時、
					 // 位置を更新
						myCollInfo.pPos->x = point.x;
						myCollInfo.pPos->z = point.z;
					}
				}

				return;
			}

		}

		if (pCollision != NULL) {
			if (aInside[HITDIRECTION_BACK] &&
				aInside[HITDIRECTION_FRONT] &&
				aInside[HITDIRECTION_LEFT] &&
				aInside[HITDIRECTION_RIGHT])
			{// 全ての方向から内側の時、
				pCollision->bOvl = true;	// 当たりフラグを真にする
			}
		}

		break;
	}
	case /*/ Y方向 /*/VECTOR_Y: {
		bool aInside[HITDIRECTION_MAX];	// 内側フラグ

											// 奥辺からの内側フラグを取得
		aInside[HITDIRECTION_BACK] = (((pos3 - pos2).z * (*myCollInfo.pPos - pos2).x) - ((pos3 - pos2).x * (*myCollInfo.pPos - pos2).z) >= 0);
		// 手前辺からの内側フラグを取得
		aInside[HITDIRECTION_FRONT] = (((pos1 - pos0).z * (*myCollInfo.pPos - pos0).x) - ((pos1 - pos0).x * (*myCollInfo.pPos - pos0).z) >= 0);
		// 左辺からの内側フラグを取得
		aInside[HITDIRECTION_LEFT] = (((pos2 - pos1).z * (*myCollInfo.pPos - pos1).x) - ((pos2 - pos1).x * (*myCollInfo.pPos - pos1).z) >= 0);
		// 右辺からの内側フラグを取得
		aInside[HITDIRECTION_RIGHT] = (((pos0 - pos3).z * (*myCollInfo.pPos - pos3).x) - ((pos0 - pos3).x * (*myCollInfo.pPos - pos3).z) >= 0);

		if (!(
			aInside[HITDIRECTION_BACK] &&
			aInside[HITDIRECTION_FRONT] &&
			aInside[HITDIRECTION_LEFT] &&
			aInside[HITDIRECTION_RIGHT]))
		{// 全ての方向から内側でない時、
			break;	// 処理を抜ける
		}

		// 当たり判定の計算に必要なパラメーターを整数型に変換(演算誤差対策)
		int nMyX = myCollInfo.pPos->x							* HIT_TEST_DECIMAL_PLACE;
		int nMyY = myCollInfo.pPos->y							* HIT_TEST_DECIMAL_PLACE;
		int nMyZ = myCollInfo.pPos->z							* HIT_TEST_DECIMAL_PLACE;
		int nMyPartsX = myHitTestParts.fixedRelativePos.x		* HIT_TEST_DECIMAL_PLACE;
		int nMyPartsY = myHitTestParts.fixedRelativePos.y		* HIT_TEST_DECIMAL_PLACE;
		int nMyPartsZ = myHitTestParts.fixedRelativePos.z		* HIT_TEST_DECIMAL_PLACE;
		int nMyOldX = myCollInfo.posOld.x						* HIT_TEST_DECIMAL_PLACE;
		int nMyOldY = myCollInfo.posOld.y						* HIT_TEST_DECIMAL_PLACE;
		int nMyOldZ = myCollInfo.posOld.z						* HIT_TEST_DECIMAL_PLACE;
		int nMyWidth = myHitTestParts.fWidth					* HIT_TEST_DECIMAL_PLACE;
		int nMyHeight = myHitTestParts.fHeight					* HIT_TEST_DECIMAL_PLACE;
		int nMyDepth = myHitTestParts.fDepth					* HIT_TEST_DECIMAL_PLACE;
		int nPairX = pairCollInfo.pPos->x						* HIT_TEST_DECIMAL_PLACE;
		int nPairY = pairCollInfo.pPos->y						* HIT_TEST_DECIMAL_PLACE;
		int nPairZ = pairCollInfo.pPos->z						* HIT_TEST_DECIMAL_PLACE;
		int nPairPartsX = pairHitTestParts.fixedRelativePos.x	* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;
		int nPairPartsY = pairHitTestParts.fixedRelativePos.y	* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;
		int nPairPartsZ = pairHitTestParts.fixedRelativePos.z	* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;
		int nPairOldX = pairCollInfo.posOld.x					* HIT_TEST_DECIMAL_PLACE;
		int nPairOldY = pairCollInfo.posOld.y					* HIT_TEST_DECIMAL_PLACE;
		int nPairOldZ = pairCollInfo.posOld.z					* HIT_TEST_DECIMAL_PLACE;
		int nPairWidth = pairHitTestParts.fWidth				* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;
		int nPairHeight = pairHitTestParts.fHeight				* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;
		int nPairDepth = pairHitTestParts.fDepth				* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;

		if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) > (nPairY + nPairPartsY) - (nPairHeight * 0.5f))			// 足元が相手の奥辺よりも手前に位置している
			&&																									// &
			((nMyOldY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairOldY + nPairPartsY) - (nPairHeight * 0.5f)))	// 過去の足元が相手の下辺よりも下に位置している
		{// 下からめり込んでいる時、
			if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
			{// 左からのすり抜けが偽の時、
				if (pCollision != NULL)
				{// 衝突情報がNULLでない時、
					pCollision->bColl =	// 衝突フラグを真にする
						pCollision->aColl[HITDIRECTION_BOTTOM] = true;
				}
				myCollInfo.pPos->y = 	// 位置を相手の当たり判定の下にする
					(nPairY + nPairPartsY - (nPairHeight * 0.5f) - nMyPartsY - (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
			}
		}
		else if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) < (nPairY + nPairPartsY) + (nPairHeight * 0.5f))		// 頭が相手の上辺よりも下に位置している
			&&																									// &
			((nMyOldY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairOldY + nPairPartsY) + (nPairHeight * 0.5f)))	// 過去の頭が相手の上辺よりも上に位置している
		{// 上からめり込んでいる時、
			if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
			{// 上からのすり抜けが偽の時、
				if (pCollision != NULL)
				{// 衝突情報がNULLでない時、
					pCollision->bColl =	// 衝突フラグを真にする
						pCollision->aColl[HITDIRECTION_TOP] = true;
				}
				myCollInfo.pPos->y = // 位置を相手の当たり判定の上にする
					(nPairY + nPairPartsY + (nPairHeight * 0.5f) - nMyPartsY + (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
			}
		}

		if (pCollision != NULL)
		{// 衝突情報がNULLでない時、
			if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
				&&
				((nMyY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
			{// 現在の上辺が相手の当たり判定の内側の時、
				pCollision->aOvl[HITDIRECTION_BOTTOM] = true;	// 下方向からの内側フラグを真にする

				if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
				{// 下からのすり抜けが偽の時、
					pCollision->bHit = true;						// 当たりフラグを真にする
					pCollision->aHit[HITDIRECTION_BOTTOM] = true;	// 下方向からの当たりフラグを真にする
				}
			}

			if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
				&&
				((nMyY + nMyPartsY) - (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
			{// 現在の下辺が相手の当たり判定の内側の時、
				pCollision->aOvl[HITDIRECTION_TOP] = true;	// 上方向からの内側フラグを真にする

				if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
				{// 上からのすり抜けが偽の時、
					pCollision->bHit = true;					// 当たりフラグを真にする
					pCollision->aHit[HITDIRECTION_TOP] = true;	// 上方向からの当たりフラグを真にする
				}
			}
		}

		break;
	}
	}
}

//========================================
// CylinderCylinderCollision3D関数 - 円筒から円筒の衝突チェック(3Dモード) -
// Author:RIKU NISHIMURA
//========================================
void CylinderCylinderCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts,
	bool bRflc, bool bSlip)
{
	// 自身の長さ
	float fMyLength = ((myHitTestParts.fWidth + myHitTestParts.fDepth) * 0.5f * myCollInfo.fScale) * 0.5f;
	// 相手の長さ
	float fPairLength = ((pairHitTestParts.fWidth + pairHitTestParts.fDepth) * 0.5f * pairCollInfo.fScale) * 0.5f;
	// 当たる長さ
	float fHitLength = fMyLength + fPairLength;

	pairCollInfo.pRot->y += D3DX_PI;
	pairCollInfo.rotOld.y += D3DX_PI;

	// 位置
	D3DXVECTOR3 pairPos = *pairCollInfo.pPos;
	{
		// 相対位置
		D3DXVECTOR3 relativePos = pairHitTestParts.fixedRelativePos * pairCollInfo.fScale;
		// 向き
		D3DXVECTOR3 rot1 = *pairCollInfo.pRot;

		// 位置にX相対位置を反映
		pairPos.x += sinf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		pairPos.z += cosf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		// 位置にZ相対位置を反映
		pairPos.x += sinf(rot1.y) * relativePos.z;
		pairPos.z += cosf(rot1.y) * relativePos.z;
	}
	// 位置
	D3DXVECTOR3 pairPosOld = pairCollInfo.posOld;
	{
		// 相対位置
		D3DXVECTOR3 relativePos = pairHitTestParts.fixedRelativePos * pairCollInfo.fScale;
		// 向き
		D3DXVECTOR3 rot1 = pairCollInfo.rotOld;

		// 位置にX相対位置を反映
		pairPosOld.x += sinf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		pairPosOld.z += cosf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		// 位置にZ相対位置を反映
		pairPosOld.x += sinf(rot1.y) * relativePos.z;
		pairPosOld.z += cosf(rot1.y) * relativePos.z;
	}

	pairCollInfo.pRot->y -= D3DX_PI;
	pairCollInfo.rotOld.y -= D3DX_PI;

	// 2点の距離
	float fDistance = FindDistanceLookDown(*myCollInfo.pPos, pairPos);
	// 2点の過去の距離
	float fDistanceOld = FindDistanceLookDown(myCollInfo.posOld, pairPosOld);

	switch (vector)
	{
	case /*/ Z方向 /*/VECTOR_Z:
	{
		if (!(
			((myCollInfo.pPos->y + (myHitTestParts.fixedRelativePos.y * myCollInfo.fScale)) + (myHitTestParts.fHeight * 0.5f * myCollInfo.fScale) > (pairPos.y + (pairHitTestParts.fixedRelativePos.y * pairCollInfo.fScale)) - (pairHitTestParts.fHeight * 0.5f * pairCollInfo.fScale)) &&
			((myCollInfo.pPos->y + (myHitTestParts.fixedRelativePos.y * myCollInfo.fScale)) - (myHitTestParts.fHeight * 0.5f * myCollInfo.fScale) < (pairPos.y + (pairHitTestParts.fixedRelativePos.y * pairCollInfo.fScale)) + (pairHitTestParts.fHeight * 0.5f * pairCollInfo.fScale))
			))
		{// Y軸で接していない時、
			break;	// 処理を抜ける
		}

		if (fDistance <= fHitLength)
		{// 現在が当たる距離内の時、
		 // 当たりフラグを真にする
			pCollision->bHit = true;

			// 相手から自身への向き
			float fAngle = FindAngleLookDown(pairPos, *myCollInfo.pPos);

			// 相手の位置から当たる長さ分加算した位置に補正
			myCollInfo.pPos->x = pairPos.x + (sinf(fAngle) * fHitLength);
			myCollInfo.pPos->z = pairPos.z + (cosf(fAngle) * fHitLength);

			if (fDistanceOld >= fHitLength)
			{// 過去が当たる距離外の時、
			 // 衝突フラグを真にする
				pCollision->bColl = true;
			}
		}

		break;
	}
	case /*/ Y方向 /*/VECTOR_Y: {
		if (fDistance >= fHitLength)
		{// 現在が当たる距離外の時、
			break;	// 処理を抜ける
		}

		// 当たり判定の計算に必要なパラメーターを整数型に変換(演算誤差対策)
		int nMyX = myCollInfo.pPos->x							* HIT_TEST_DECIMAL_PLACE;
		int nMyY = myCollInfo.pPos->y							* HIT_TEST_DECIMAL_PLACE;
		int nMyZ = myCollInfo.pPos->z							* HIT_TEST_DECIMAL_PLACE;
		int nMyPartsX = myHitTestParts.fixedRelativePos.x		* HIT_TEST_DECIMAL_PLACE;
		int nMyPartsY = myHitTestParts.fixedRelativePos.y		* HIT_TEST_DECIMAL_PLACE;
		int nMyPartsZ = myHitTestParts.fixedRelativePos.z		* HIT_TEST_DECIMAL_PLACE;
		int nMyOldX = myCollInfo.posOld.x						* HIT_TEST_DECIMAL_PLACE;
		int nMyOldY = myCollInfo.posOld.y						* HIT_TEST_DECIMAL_PLACE;
		int nMyOldZ = myCollInfo.posOld.z						* HIT_TEST_DECIMAL_PLACE;
		int nMyWidth = myHitTestParts.fWidth					* HIT_TEST_DECIMAL_PLACE;
		int nMyHeight = myHitTestParts.fHeight					* HIT_TEST_DECIMAL_PLACE;
		int nMyDepth = myHitTestParts.fDepth					* HIT_TEST_DECIMAL_PLACE;
		int nPairX = pairPos.x						* HIT_TEST_DECIMAL_PLACE;
		int nPairY = pairPos.y						* HIT_TEST_DECIMAL_PLACE;
		int nPairZ = pairPos.z						* HIT_TEST_DECIMAL_PLACE;
		int nPairPartsX = pairHitTestParts.fixedRelativePos.x	* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;
		int nPairPartsY = pairHitTestParts.fixedRelativePos.y	* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;
		int nPairPartsZ = pairHitTestParts.fixedRelativePos.z	* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;
		int nPairOldX = pairPosOld.x					* HIT_TEST_DECIMAL_PLACE;
		int nPairOldY = pairPosOld.y					* HIT_TEST_DECIMAL_PLACE;
		int nPairOldZ = pairPosOld.z					* HIT_TEST_DECIMAL_PLACE;
		int nPairWidth = pairHitTestParts.fWidth				* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;
		int nPairHeight = pairHitTestParts.fHeight				* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;
		int nPairDepth = pairHitTestParts.fDepth				* HIT_TEST_DECIMAL_PLACE * pairCollInfo.fScale;

		if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) > (nPairY + nPairPartsY) - (nPairHeight * 0.5f))			// 足元が相手の奥辺よりも手前に位置している
			&&																									// &
			((nMyOldY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairOldY + nPairPartsY) - (nPairHeight * 0.5f)))	// 過去の足元が相手の下辺よりも下に位置している
		{// 下からめり込んでいる時、
			if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
			{// 下からのすり抜けが偽の時、
				if (pCollision != NULL)
				{// 衝突情報がNULLでない時、
					pCollision->bColl =	// 衝突フラグを真にする
						pCollision->aColl[HITDIRECTION_BOTTOM] = true;
				}
				myCollInfo.pPos->y = 	// 位置を相手の当たり判定の下にする
					(nPairY + nPairPartsY - (nPairHeight * 0.5f) - nMyPartsY - (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
			}
		}
		else if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) < (nPairY + nPairPartsY) + (nPairHeight * 0.5f))		// 頭が相手の上辺よりも下に位置している
			&&																									// &
			((nMyOldY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairOldY + nPairPartsY) + (nPairHeight * 0.5f)))	// 過去の頭が相手の上辺よりも上に位置している
		{// 上からめり込んでいる時、
			if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
			{// 上からのすり抜けが偽の時、
				if (pCollision != NULL)
				{// 衝突情報がNULLでない時、
					pCollision->bColl =	// 衝突フラグを真にする
						pCollision->aColl[HITDIRECTION_TOP] = true;
				}
				myCollInfo.pPos->y = // 位置を相手の当たり判定の上にする
					(nPairY + nPairPartsY + (nPairHeight * 0.5f) - nMyPartsY + (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
			}
		}

		if (pCollision != NULL)
		{// 衝突情報がNULLでない時、
			if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
				&&
				((nMyY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
			{// 現在の上辺が相手の当たり判定の内側の時、
				pCollision->aOvl[HITDIRECTION_BOTTOM] = true;	// 下方向からの内側フラグを真にする

				if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
				{// 下からのすり抜けが偽の時、
					pCollision->bHit = true;						// 当たりフラグを真にする
					pCollision->aHit[HITDIRECTION_BOTTOM] = true;	// 下方向からの当たりフラグを真にする
				}
			}

			if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
				&&
				((nMyY + nMyPartsY) - (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
			{// 現在の下辺が相手の当たり判定の内側の時、
				pCollision->aOvl[HITDIRECTION_TOP] = true;	// 上方向からの内側フラグを真にする

				if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
				{// 上からのすり抜けが偽の時、
					pCollision->bHit = true;					// 当たりフラグを真にする
					pCollision->aHit[HITDIRECTION_TOP] = true;	// 上方向からの当たりフラグを真にする
				}
			}
		}

		break;
	}
	}
}

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
void CollisionCheck(VECTOR vector, Collision *pCollision, CollisionInfo myCollInfo, CollisionInfo pairCollInfo, COLLCHK_MODE mode)
{
	for (int nCntMyParts = 0; nCntMyParts < myCollInfo.pHitTest->nHitTestPartsNum; nCntMyParts++)
	{
		for (int nCntPairParts = 0; nCntPairParts < pairCollInfo.pHitTest->nHitTestPartsNum; nCntPairParts++)
		{
			HIT_TEST_FORM	my					= myCollInfo.pHitTest->aHitTestParts[nCntMyParts].hitTestForm;		// 自分の当たり判定の種類
			HIT_TEST_FORM	pr					= pairCollInfo.pHitTest->aHitTestParts[nCntPairParts].hitTestForm;	// 相手の当たり判定の種類
			HitTestParts	myHitTestParts		= myCollInfo.pHitTest->aHitTestParts[nCntMyParts];					// 自分の当たり判定の部品
			HitTestParts	pairHitTestParts	= pairCollInfo.pHitTest->aHitTestParts[nCntPairParts];				// 相手の当たり判定の部品

			// モードに応じた処理
			switch (mode)
			{
			case COLLCHK_MODE_NORMAL:
				/*/ 四角から四角 /*/if (my == HIT_TEST_FORM_SQUARE   && pr == HIT_TEST_FORM_SQUARE)   { SquareSquareCollision3D(vector, pCollision, myCollInfo, myHitTestParts, pairCollInfo, pairHitTestParts); }
				/*/ 円筒から四角 /*/if (my == HIT_TEST_FORM_CYLINDER && pr == HIT_TEST_FORM_SQUARE)   { CylinderSquareCollision3D(vector, pCollision, myCollInfo, myHitTestParts, pairCollInfo, pairHitTestParts, false, true); }
				/*/ 円筒から円筒 /*/if (my == HIT_TEST_FORM_CYLINDER && pr == HIT_TEST_FORM_CYLINDER) { CylinderCylinderCollision3D(vector, pCollision, myCollInfo, myHitTestParts, pairCollInfo, pairHitTestParts, false, true); }
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