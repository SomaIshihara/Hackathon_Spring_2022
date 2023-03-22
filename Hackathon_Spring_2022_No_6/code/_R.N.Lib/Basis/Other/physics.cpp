//========================================
// 
// �����֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** physics.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
// �`�悷�铖���蔻��̍ő吔
#define DRAWHITTEST_MAX (256)
// �����蔻��̐��̍ő吔
#define HITTESTLINE_MAX (1024)
// �����蔻��̐F
#define HITTEST_COLOR Color{255,0,0,255}
// �����蔻��̉~�̕�����
#define HITTEST_CIRCLE_DIVISION (8)
// �����蔻�莞�̏����̈�
#define HIT_TEST_DECIMAL_PLACE	(20)
// �X���b�v���Ɏ�鋗��
#define SLIP_DISTANCE (0.1f)

//****************************************
// �\���̂̒�`
//****************************************
// �`�悷�铖���蔻����\����
typedef struct
{
	HIT_TEST_FORM hitTestForm;		// �����蔻��̌`
	float fWidth;					// ��
	float fHeight;					// ����
	float fDepth;					// ���s��
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 rot;				// ����
	bool aGhost[HITDIRECTION_MAX];	// ���蔲�����
}HitTestDraw;

// �����֘A�����̊Ǘ����\����
typedef struct
{
	// �`�悷�铖���蔻��̃��X�g
	CollisionInfo aDrawHitTestList[DRAWHITTEST_MAX];
	int nDrawHitTestSet;	// �`�悷�铖���蔻��̐ݒ萔
	bool bDrawHitTest;		// �����蔻��`��t���O
	int nHitTestLineNum;	// �����蔻��̐��̐�
}PhysicsControl;

//****************************************
// �v���g�^�C�v�錾
//****************************************
// �l�p����l�p�̏Փ˃`�F�b�N(3D���[�h)
void SquareSquareCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts);
// �~������l�p�̏Փ˃`�F�b�N(3D���[�h)
void CylinderSquareCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts,
	bool bRflc, bool bSlip);
// �~������~���̏Փ˃`�F�b�N(3D���[�h)
void CylinderCylinderCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts,
	bool bRflc, bool bSlip);
//========== *** �擾 ***
// �����蔻��ɕK�v�ȏ��̃p�����[�^�[�����l��Ԃ�
CollisionInfo InitParameterCollisionInfo(void);
// �`�悷�铖���蔻����̃p�����[�^�[�����l��Ԃ�
HitTestDraw InitParameterDrawHitTest(void);
// �����֘A�����̊Ǘ����̃p�����[�^�[�����l��Ԃ�
PhysicsControl InitParameterPhysicsControl(void);
//========== *** �����蔻��`��֘A ***
// �����蔻��̐��̐ݒ菈��
void SetHitTestLine(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);

//****************************************
// �O���[�o���ϐ��錾
//****************************************
// �����蔻��̐��̒��_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffHitTestLine = NULL;
static PhysicsControl g_physicsControl;	// �����蔻��̊Ǘ����

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// SquareSquareCollision3D�֐� - �l�p����l�p�̏Փ˃`�F�b�N(3D���[�h) -
// Author:RIKU NISHIMURA
//========================================
void SquareSquareCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts)
{
	HitTest myHitTest	// �����̓����蔻����
		= *myCollInfo.pHitTest;
	HitTest pairHitTest	// ����̓����蔻����
		= *pairCollInfo.pHitTest;

	// �����蔻��̌v�Z�ɕK�v�ȃp�����[�^�[�𐮐��^�ɕϊ�(���Z�덷�΍�)
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
	case /*/ X���� /*/VECTOR_X: {
		if (((nMyZ + nMyPartsZ) + (nMyDepth * 0.5f) > (nPairZ + nPairPartsZ) - (nPairDepth * 0.5f)) &&
			((nMyZ + nMyPartsZ) - (nMyDepth * 0.5f) < (nPairZ + nPairPartsZ) + (nPairDepth * 0.5f)) &&
			((nMyY + nMyPartsY) + (nMyHeight * 0.5f) > (nPairY + nPairPartsY) - (nPairHeight * 0.5f)) &&
			((nMyY + nMyPartsY) - (nMyHeight * 0.5f) < (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
		{// ���ӂƎ�O�ӂ�����̕��̓����̎��A
			if (((nMyX + nMyPartsX) + (nMyWidth * 0.5f) >= (nPairX + nPairPartsX) - (nPairWidth * 0.5f))		// ���݂̉E�ӂ�����̍��ӂ����E�Ɉʒu���Ă���
				&&																								// &
				((nMyOldX + nMyPartsX) + (nMyWidth * 0.5f) <= (nPairOldX + nPairPartsX) - (nPairWidth * 0.5f)))	// �ߋ��̉E�ӂ�����̍��ӂ������Ɉʒu���Ă���
			{// ������߂荞��ł��鎞�A
				if (!pairHitTestParts.aGhost[HITDIRECTION_LEFT])
				{// ������̂��蔲�����U�̎��A
					if (pCollision != NULL)
					{// �Փˏ��NULL�łȂ����A
						pCollision->bColl =	// �Փ˃t���O��^�ɂ���
							pCollision->aColl[HITDIRECTION_LEFT] = true;
					}
					myCollInfo.pPos->x =	// �ʒu�𑊎�̓����蔻��̍��ɂ���
						(nPairX + nPairPartsX - (nPairWidth * 0.5f) - nMyPartsX - (nMyWidth * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}
			else if (((nMyX + nMyPartsX) - (nMyWidth * 0.5f) <= (nPairX + nPairPartsX) + (nPairWidth * 0.5f))	// ���ӂ�����̉E�ӂ������Ɉʒu���Ă���
				&&																								// &
				((nMyOldX + nMyPartsX) - (nMyWidth * 0.5f) >= (nPairOldX + nPairPartsX) + (nPairWidth * 0.5f)))	// �ߋ��̍��ӂ�����̉E�ӂ����E�Ɉʒu���Ă���
			{// �E����߂荞��ł��鎞�A
				if (!pairHitTestParts.aGhost[HITDIRECTION_RIGHT])
				{// ������̂��蔲�����U�̎��A
					if (pCollision != NULL)
					{// �Փˏ��NULL�łȂ����A
						pCollision->bColl =	// �Փ˃t���O��^�ɂ���
							pCollision->aColl[HITDIRECTION_RIGHT] = true;
					}
					myCollInfo.pPos->x =	// �ʒu�𑊎�̓����蔻��̉E�ɂ���
						(nPairX + nPairPartsX + (nPairWidth * 0.5f) - nMyPartsX + (nMyWidth * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}

			if (pCollision != NULL)
			{// �Փˏ��NULL�łȂ����A
				if (((nMyX + nMyPartsX) + (nMyWidth * 0.5f) >= (nPairX + nPairPartsX) - (nPairWidth * 0.5f))
					&&
					((nMyX + nMyPartsX) + (nMyWidth * 0.5f) <= (nPairX + nPairPartsX) + (nPairWidth * 0.5f)))
				{// ���݂̉E�ӂ�����̓����蔻��̓����̎��A
					pCollision->aOvl[HITDIRECTION_LEFT] = true;	// ����������̓����t���O��^�ɂ���


					if (!pairHitTestParts.aGhost[HITDIRECTION_LEFT])
					{// �E����̂��蔲�����U�̎��A
						pCollision->bHit = true;						// ������t���O��^�ɂ���
						pCollision->aHit[HITDIRECTION_LEFT] = true;	// ����������̓�����t���O��^�ɂ���
					}
				}

				if (((nMyX + nMyPartsX) - (nMyWidth * 0.5f) >= (nPairX + nPairPartsX) - (nPairWidth * 0.5f))
					&&
					((nMyX + nMyPartsX) - (nMyWidth * 0.5f) <= (nPairX + nPairPartsX) + (nPairWidth * 0.5f)))
				{// ���݂̍��ӂ�����̓����蔻��̓����̎��A
					pCollision->aOvl[HITDIRECTION_RIGHT] = true;	// �E��������̓����t���O��^�ɂ���


					if (!pairHitTestParts.aGhost[HITDIRECTION_RIGHT])
					{// �E����̂��蔲�����U�̎��A
						pCollision->bHit = true;							// ������t���O��^�ɂ���
						pCollision->aHit[HITDIRECTION_RIGHT] = true;		// �E��������̓�����t���O��^�ɂ���
					}
				}
			}
		}
	}
							  break;
	case /*/ Y���� /*/VECTOR_Y: {
		if (((nMyX + nMyPartsX) + (nMyWidth * 0.5f) > (nPairX + nPairPartsX) - (nPairWidth * 0.5f)) &&
			((nMyX + nMyPartsX) - (nMyWidth * 0.5f) < (nPairX + nPairPartsX) + (nPairWidth * 0.5f)) &&
			((nMyZ + nMyPartsZ) + (nMyDepth * 0.5f) > (nPairZ + nPairPartsZ) - (nPairDepth * 0.5f)) &&
			((nMyZ + nMyPartsZ) - (nMyDepth * 0.5f) < (nPairZ + nPairPartsZ) + (nPairDepth * 0.5f)))
		{// ���ӂƉE�ӂ�����̕��̓����̎��A
			if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) > (nPairY + nPairPartsY) - (nPairHeight * 0.5f))			// ����������̉��ӂ�����O�Ɉʒu���Ă���
				&&																									// &
				((nMyOldY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairOldY + nPairPartsY) - (nPairHeight * 0.5f)))	// �ߋ��̑���������̉��ӂ������Ɉʒu���Ă���
			{// ������߂荞��ł��鎞�A
				if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
				{// ������̂��蔲�����U�̎��A
					if (pCollision != NULL)
					{// �Փˏ��NULL�łȂ����A
						pCollision->bColl =	// �Փ˃t���O��^�ɂ���
							pCollision->aColl[HITDIRECTION_BOTTOM] = true;
					}
					myCollInfo.pPos->y = 	// �ʒu�𑊎�̓����蔻��̉��ɂ���
						(nPairY + nPairPartsY - (nPairHeight * 0.5f) - nMyPartsY - (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}
			else if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) < (nPairY + nPairPartsY) + (nPairHeight * 0.5f))		// ��������̏�ӂ������Ɉʒu���Ă���
				&&																									// &
				((nMyOldY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairOldY + nPairPartsY) + (nPairHeight * 0.5f)))	// �ߋ��̓�������̏�ӂ�����Ɉʒu���Ă���
			{// �ォ��߂荞��ł��鎞�A
				if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
				{// �ォ��̂��蔲�����U�̎��A
					if (pCollision != NULL)
					{// �Փˏ��NULL�łȂ����A
						pCollision->bColl =	// �Փ˃t���O��^�ɂ���
							pCollision->aColl[HITDIRECTION_TOP] = true;
					}
					myCollInfo.pPos->y = // �ʒu�𑊎�̓����蔻��̏�ɂ���
						(nPairY + nPairPartsY + (nPairHeight * 0.5f) - nMyPartsY + (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}

			if (pCollision != NULL)
			{// �Փˏ��NULL�łȂ����A
				if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
					&&
					((nMyY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
				{// ���݂̏�ӂ�����̓����蔻��̓����̎��A
					pCollision->aOvl[HITDIRECTION_BOTTOM] = true;	// ����������̓����t���O��^�ɂ���

					if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
					{// ������̂��蔲�����U�̎��A
						pCollision->bHit = true;						// ������t���O��^�ɂ���
						pCollision->aHit[HITDIRECTION_BOTTOM] = true;	// ����������̓�����t���O��^�ɂ���
					}
				}

				if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
					&&
					((nMyY + nMyPartsY) - (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
				{// ���݂̉��ӂ�����̓����蔻��̓����̎��A
					pCollision->aOvl[HITDIRECTION_TOP] = true;	// ���������̓����t���O��^�ɂ���


					if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
					{// �ォ��̂��蔲�����U�̎��A
						pCollision->bHit = true;						// ������t���O��^�ɂ���
						pCollision->aHit[HITDIRECTION_TOP] = true;	// ���������̓�����t���O��^�ɂ���
					}
				}
			}
		}
	}
							  break;
	case /*/ Z���� /*/VECTOR_Z: {
		if (((nMyX + nMyPartsX) + (nMyWidth * 0.5f) > (nPairX + nPairPartsX) - (nPairWidth * 0.5f)) &&
			((nMyX + nMyPartsX) - (nMyWidth * 0.5f) < (nPairX + nPairPartsX) + (nPairWidth * 0.5f)) &&
			((nMyY + nMyPartsY) + (nMyHeight * 0.5f) > (nPairY + nPairPartsY) - (nPairHeight * 0.5f)) &&
			((nMyY + nMyPartsY) - (nMyHeight * 0.5f) < (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
		{// ���ӂƉE�ӂ�����̕��̓����̎��A
			if (((nMyZ + nMyPartsZ) + (nMyDepth * 0.5f) > (nPairZ + nPairPartsZ) - (nPairDepth * 0.5f))			// ����������̉��ӂ�����O�Ɉʒu���Ă���
				&&																								// &
				((nMyOldZ + nMyPartsZ) + (nMyDepth * 0.5f) <= (nPairOldZ + nPairPartsZ) - (nPairDepth * 0.5f)))	// �ߋ��̑���������̉��ӂ������Ɉʒu���Ă���
			{// ������߂荞��ł��鎞�A
				if (!pairHitTestParts.aGhost[HITDIRECTION_BACK])
				{// ������̂��蔲�����U�̎��A
					if (pCollision != NULL)
					{// �Փˏ��NULL�łȂ����A
						pCollision->bColl =	// �Փ˃t���O��^�ɂ���
							pCollision->aColl[HITDIRECTION_BACK] = true;
					}
					myCollInfo.pPos->z = 	// �ʒu�𑊎�̓����蔻��̉��ɂ���
						(nPairZ + nPairPartsZ - (nPairDepth * 0.5f) - nMyPartsZ - (nMyDepth * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}
			else if (((nMyZ + nMyPartsZ) - (nMyDepth * 0.5f) < (nPairZ + nPairPartsZ) + (nPairDepth * 0.5f))	// ��������̎�O�ӂ������Ɉʒu���Ă���
				&&																								// &
				((nMyOldZ + nMyPartsZ) - (nMyDepth * 0.5f) >= (nPairOldZ + nPairPartsZ) + (nPairDepth * 0.5f)))	// �ߋ��̓�������̎�O�ӂ�����O�Ɉʒu���Ă���
			{// ��O����߂荞��ł��鎞�A
				if (!pairHitTestParts.aGhost[HITDIRECTION_FRONT])
				{// ��O����̂��蔲�����U�̎��A
					if (pCollision != NULL)
					{// �Փˏ��NULL�łȂ����A
						pCollision->bColl =	// �Փ˃t���O��^�ɂ���
							pCollision->aColl[HITDIRECTION_FRONT] = true;
					}
					myCollInfo.pPos->z = // �ʒu�𑊎�̓����蔻��̎�O�ɂ���
						(nPairZ + nPairPartsZ + (nPairDepth * 0.5f) - nMyPartsZ + (nMyDepth * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
				}
			}

			if (pCollision != NULL)
			{// �Փˏ��NULL�łȂ����A
				if (((nMyZ + nMyPartsZ) + (nMyDepth * 0.5f) >= (nPairZ + nPairPartsZ) - (nPairDepth * 0.5f))
					&&
					((nMyZ + nMyPartsZ) + (nMyDepth * 0.5f) <= (nPairZ + nPairPartsZ) + (nPairDepth * 0.5f)))
				{// ���݂̎�O�ӂ�����̓����蔻��̓����̎��A
					pCollision->aOvl[HITDIRECTION_BACK] = true;	// ����������̓����t���O��^�ɂ���

					if (!pairHitTestParts.aGhost[HITDIRECTION_BACK])
					{// ������̂��蔲�����U�̎��A
						pCollision->bHit = true;						// ������t���O��^�ɂ���
						pCollision->aHit[HITDIRECTION_BACK] = true;	// ����������̓�����t���O��^�ɂ���
					}
				}

				if (((nMyZ + nMyPartsZ) - (nMyDepth * 0.5f) >= (nPairZ + nPairPartsZ) - (nPairDepth * 0.5f))
					&&
					((nMyZ + nMyPartsZ) - (nMyDepth * 0.5f) <= (nPairZ + nPairPartsZ) + (nPairDepth * 0.5f)))
				{// ���݂̉��ӂ�����̓����蔻��̓����̎��A
					pCollision->aOvl[HITDIRECTION_FRONT] = true;	// ��O��������̓����t���O��^�ɂ���

					if (!pairHitTestParts.aGhost[HITDIRECTION_FRONT])
					{// ��O����̂��蔲�����U�̎��A
						pCollision->bHit = true;						// ������t���O��^�ɂ���
						pCollision->aHit[HITDIRECTION_FRONT] = true;	// ��O��������̓�����t���O��^�ɂ���
					}
				}
			}
		}
	}
							  break;
	}
}

//========================================
// CylinderSquareCollision3D�֐� - �~������l�p�̏Փ˃`�F�b�N(3D���[�h) -
// Author:RIKU NISHIMURA
//========================================
void CylinderSquareCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts,
	bool bRflc, bool bSlip)
{
	// ���g�̑傫��
	float fMyScale = (myHitTestParts.fWidth + myHitTestParts.fDepth) * 0.5f * myCollInfo.fScale;
	// ��
	float fWidth = (pairHitTestParts.fWidth * pairCollInfo.fScale) + fMyScale;
	// ���s��
	float fDepth = (pairHitTestParts.fDepth * pairCollInfo.fScale) + fMyScale;

	pairCollInfo.pRot->y += D3DX_PI;
	pairCollInfo.rotOld.y += D3DX_PI;

	D3DXVECTOR3 pos0, pos1, pos2, pos3;	// ���v���Ɍ��ĉE�������4���_�̈ʒu(����)
	{
		// �ʒu
		D3DXVECTOR3 pos = *pairCollInfo.pPos;
		// ���Έʒu
		D3DXVECTOR3 relativePos = pairHitTestParts.fixedRelativePos * pairCollInfo.fScale;
		// ����
		D3DXVECTOR3 rot1 = *pairCollInfo.pRot;

		// �ʒu��X���Έʒu�𔽉f
		pos.x += sinf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		pos.z += cosf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		// �ʒu��Z���Έʒu�𔽉f
		pos.x += sinf(rot1.y) * relativePos.z;
		pos.z += cosf(rot1.y) * relativePos.z;

		// ����
		D3DXVECTOR3 rot2 = *pairCollInfo.pRot + pairHitTestParts.fixedRelativeRot;

		// 4���_�̈ʒu��ݒ�
		pos0.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (sinf(rot2.y) * (fDepth * -0.5f));
		pos0.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (cosf(rot2.y) * (fDepth * -0.5f));
		pos1.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (sinf(rot2.y) * (fDepth * -0.5f));
		pos1.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (cosf(rot2.y) * (fDepth * -0.5f));
		pos2.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (sinf(rot2.y) * (fDepth * 0.5f));
		pos2.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth *  0.5f)) + (cosf(rot2.y) * (fDepth * 0.5f));
		pos3.x = pos.x + (sinf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (sinf(rot2.y) * (fDepth * 0.5f));
		pos3.z = pos.z + (cosf(rot2.y - (D3DX_PI * 0.5f)) * (fWidth * -0.5f)) + (cosf(rot2.y) * (fDepth * 0.5f));
	}
	D3DXVECTOR3 posOld0, posOld1, posOld2, posOld3;	// ���v���Ɍ��ĉE�������4���_�̉ߋ��̈ʒu(����)
	{
		// �ʒu
		D3DXVECTOR3 pos = pairCollInfo.posOld;
		// ���Έʒu
		D3DXVECTOR3 relativePos = pairHitTestParts.fixedRelativePos * pairCollInfo.fScale;
		// ����
		D3DXVECTOR3 rot1 = pairCollInfo.rotOld;

		// �ʒu��X���Έʒu�𔽉f
		pos.x += sinf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		pos.z += cosf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		// �ʒu��Z���Έʒu�𔽉f
		pos.x += sinf(rot1.y) * relativePos.z;
		pos.z += cosf(rot1.y) * relativePos.z;

		// ����
		D3DXVECTOR3 rot2 = pairCollInfo.rotOld + pairHitTestParts.fixedRelativeRot;

		// 4���_�̈ʒu��ݒ�
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
	case /*/ Z���� /*/VECTOR_Z:
	{
		if (!(
			((myCollInfo.pPos->y + (myHitTestParts.fixedRelativePos.y * myCollInfo.fScale)) + (myHitTestParts.fHeight * 0.5f * myCollInfo.fScale) > (pairCollInfo.pPos->y + (pairHitTestParts.fixedRelativePos.y * pairCollInfo.fScale)) - (pairHitTestParts.fHeight * 0.5f * pairCollInfo.fScale)) &&
			((myCollInfo.pPos->y + (myHitTestParts.fixedRelativePos.y * myCollInfo.fScale)) - (myHitTestParts.fHeight * 0.5f * myCollInfo.fScale) < (pairCollInfo.pPos->y + (pairHitTestParts.fixedRelativePos.y * pairCollInfo.fScale)) + (pairHitTestParts.fHeight * 0.5f * pairCollInfo.fScale))
			))
		{// Y���Őڂ��Ă��Ȃ����A
			break;	// �����𔲂���
		}

		bool aInside[HITDIRECTION_MAX];	// �����t���O

											// ����
		{
			D3DXVECTOR3 vecToPos = *myCollInfo.pPos - pos2;
			D3DXVECTOR3 vecToPosOld = myCollInfo.posOld - posOld2;
			D3DXVECTOR3 point =	// ��_�̍��W
				FindIntersectionPointLookDown(myCollInfo.posOld, *myCollInfo.pPos, pos2, pos3);
			float	fDistance3toP = FindDistanceLookDown(pos3, point);	// ���_3�����_�܂ł̋���
			float	fDistance2toP = FindDistanceLookDown(pos2, point);	// ���_2�����_�܂ł̋���
			float	fDistance3to2 = FindDistanceLookDown(pos3, pos2);	// ���_3���璸�_2�܂ł̋���

																		// ���ӂ���̓����t���O���擾
			aInside[HITDIRECTION_BACK] = (((pos3 - pos2).z * vecToPos.x) - ((pos3 - pos2).x * vecToPos.z) >= 0);

			if (((aInside[HITDIRECTION_BACK]) && (((posOld3 - posOld2).z * vecToPosOld.x) - ((posOld3 - posOld2).x * vecToPosOld.z) <= 0))
				&&
				(fDistance3toP <= fDistance3to2)
				&&
				(fDistance2toP <= fDistance3to2))
			{// ���ӂ��瓖�����Ă��鎞�A
				if (!pairHitTestParts.aGhost[HITDIRECTION_BACK]) {
					pCollision->bColl =	// �Փ˃t���O��^�ɂ���
						pCollision->aColl[HITDIRECTION_BACK] = true;

					if (!pairHitTestParts.aGhost[HITDIRECTION_BACK])
					{// ����̂��蔲���t���O���U�̎��A
						pCollision->bHit =	// ������t���O��^�ɂ���
							pCollision->aHit[HITDIRECTION_BACK] = true;
					}
				}

				if (!pairHitTestParts.aGhost[HITDIRECTION_BACK])
				{
					if (bSlip)
					{// ����t���O���^�̎��A
						float fAngle = FindAngleLookDown(pos2, pos3) - (D3DX_PI * 0.5f);	// ����

																							// �ʒu���X�V
						D3DXVECTOR3 pos = FindIntersectionPointLookDown(
							*myCollInfo.pPos,
							*myCollInfo.pPos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)),
							pos3,
							pos2);
						myCollInfo.pPos->x = pos.x + sinf(fAngle) * SLIP_DISTANCE;
						myCollInfo.pPos->z = pos.z + cosf(fAngle) * SLIP_DISTANCE;
					}
					else
					{// ����t���O���U�̎��A
						// �ʒu���X�V
						myCollInfo.pPos->x = point.x;
						myCollInfo.pPos->z = point.z;
					}
				}

				return;
			}
		}

		// ��O��
		{
			D3DXVECTOR3 vecToPos = *myCollInfo.pPos - pos0;
			D3DXVECTOR3 vecToPosOld = myCollInfo.posOld - posOld0;
			D3DXVECTOR3 point =	// ��_�̍��W
				FindIntersectionPointLookDown(myCollInfo.posOld, *myCollInfo.pPos, pos0, pos1);
			float	fDistance1toP = FindDistanceLookDown(pos1, point);	// ���_1�����_�܂ł̋���
			float	fDistance0toP = FindDistanceLookDown(pos0, point);	// ���_0�����_�܂ł̋���
			float	fDistance1to0 = FindDistanceLookDown(pos1, pos0);	// ���_1���璸�_0�܂ł̋���

																		// ��O�ӂ���̓����t���O���擾
			aInside[HITDIRECTION_FRONT] = (((pos1 - pos0).z * vecToPos.x) - ((pos1 - pos0).x * vecToPos.z) >= 0);

			if (((aInside[HITDIRECTION_FRONT]) && (((posOld1 - posOld0).z * vecToPosOld.x) - ((posOld1 - posOld0).x * vecToPosOld.z) <= 0))
				&&
				(fDistance1toP <= fDistance1to0)
				&&
				(fDistance0toP <= fDistance1to0))
			{// ��O�ӂ��瓖�����Ă��鎞�A
				if (!pairHitTestParts.aGhost[HITDIRECTION_FRONT]) {
					pCollision->bColl =	// �Փ˃t���O��^�ɂ���
						pCollision->aColl[HITDIRECTION_FRONT] = true;

					if (!pairHitTestParts.aGhost[HITDIRECTION_FRONT])
					{// ����̂��蔲���t���O���U�̎��A
						pCollision->bHit =	// ������t���O��^�ɂ���
							pCollision->aHit[HITDIRECTION_FRONT] = true;
					}
				}

				if (!pairHitTestParts.aGhost[HITDIRECTION_FRONT])
				{
					if (bSlip)
					{// ����t���O���^�̎��A
						float fAngle = FindAngleLookDown(pos0, pos1) - (D3DX_PI * 0.5f);	// ����

																							// �ʒu���X�V
						D3DXVECTOR3 pos = FindIntersectionPointLookDown(
							*myCollInfo.pPos,
							*myCollInfo.pPos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)),
							pos1,
							pos0);
						myCollInfo.pPos->x = pos.x + sinf(fAngle) * SLIP_DISTANCE;
						myCollInfo.pPos->z = pos.z + cosf(fAngle) * SLIP_DISTANCE;
					}
					else
					{// ����t���O���U�̎��A
					 // �ʒu���X�V
						myCollInfo.pPos->x = point.x;
						myCollInfo.pPos->z = point.z;
					}
				}

				return;
			}
		}

		// ����
		{
			D3DXVECTOR3 vecToPos = *myCollInfo.pPos - pos1;
			D3DXVECTOR3 vecToPosOld = myCollInfo.posOld - posOld1;
			D3DXVECTOR3 point =	// ��_�̍��W
				FindIntersectionPointLookDown(myCollInfo.posOld, *myCollInfo.pPos, pos1, pos2);
			float	fDistance2toP = FindDistanceLookDown(pos2, point);	// ���_2�����_�܂ł̋���
			float	fDistance1toP = FindDistanceLookDown(pos1, point);	// ���_1�����_�܂ł̋���
			float	fDistance2to1 = FindDistanceLookDown(pos2, pos1);	// ���_2���璸�_1�܂ł̋���

																		// ���ӂ���̓����t���O���擾
			aInside[HITDIRECTION_LEFT] = (((pos2 - pos1).z * vecToPos.x) - ((pos2 - pos1).x * vecToPos.z) >= 0);

			if (((aInside[HITDIRECTION_LEFT]) && (((posOld2 - posOld1).z * vecToPosOld.x) - ((posOld2 - posOld1).x * vecToPosOld.z) <= 0))
				&&
				(FindDistanceLookDown(pos2, point) <= FindDistanceLookDown(pos2, pos1))
				&&
				(FindDistanceLookDown(pos1, point) <= FindDistanceLookDown(pos2, pos1)))
			{// ���ӂ��瓖�����Ă��鎞�A
				if (!pairHitTestParts.aGhost[HITDIRECTION_LEFT]) {
					pCollision->bColl =	// �Փ˃t���O��^�ɂ���
						pCollision->aColl[HITDIRECTION_LEFT] = true;

					if (!pairHitTestParts.aGhost[HITDIRECTION_LEFT])
					{// ����̂��蔲���t���O���U�̎��A
						pCollision->bHit =	// ������t���O��^�ɂ���
							pCollision->aHit[HITDIRECTION_LEFT] = true;
					}
				}

				if (!pairHitTestParts.aGhost[HITDIRECTION_LEFT])
				{
					if (bSlip)
					{// ����t���O���^�̎��A
						float fAngle = FindAngleLookDown(pos1, pos2) - (D3DX_PI * 0.5f);	// ����

																							// �ʒu���X�V
						D3DXVECTOR3 pos = FindIntersectionPointLookDown(
							*myCollInfo.pPos,
							*myCollInfo.pPos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)),
							pos2,
							pos1);
						myCollInfo.pPos->x = pos.x + sinf(fAngle) * SLIP_DISTANCE;
						myCollInfo.pPos->z = pos.z + cosf(fAngle) * SLIP_DISTANCE;
					}
					else
					{// ����t���O���U�̎��A
					 // �ʒu���X�V
						myCollInfo.pPos->x = point.x;
						myCollInfo.pPos->z = point.z;
					}
				}

				return;
			}
		}

		// �E��
		{
			D3DXVECTOR3 vecToPos = *myCollInfo.pPos - pos3;
			D3DXVECTOR3 vecToPosOld = myCollInfo.posOld - posOld3;
			D3DXVECTOR3 point =	// ��_�̍��W
				FindIntersectionPointLookDown(myCollInfo.posOld, *myCollInfo.pPos, pos3, pos0);
			float	fDistance0toP = FindDistanceLookDown(pos0, point);	// ���_0�����_�܂ł̋���
			float	fDistance3toP = FindDistanceLookDown(pos3, point);	// ���_3�����_�܂ł̋���
			float	fDistance0to3 = FindDistanceLookDown(pos0, pos3);	// ���_0���璸�_3�܂ł̋���

																		// �E�ӂ���̓����t���O���擾
			aInside[HITDIRECTION_RIGHT] = (((pos0 - pos3).z * vecToPos.x) - ((pos0 - pos3).x * vecToPos.z) >= 0);

			if (((aInside[HITDIRECTION_RIGHT]) && (((posOld0 - posOld3).z * vecToPosOld.x) - ((posOld0 - posOld3).x * vecToPosOld.z) <= 0))
				&&
				(fDistance0toP <= fDistance0to3)
				&&
				(fDistance3toP <= fDistance0to3))
			{// �E�ӂ��瓖�����Ă��鎞�A
				if (!pairHitTestParts.aGhost[HITDIRECTION_RIGHT]) {
					pCollision->bColl =	// �Փ˃t���O��^�ɂ���
						pCollision->aColl[HITDIRECTION_RIGHT] = true;

					if (!pairHitTestParts.aGhost[HITDIRECTION_RIGHT])
					{// ����̂��蔲���t���O���U�̎��A
						pCollision->bHit =	// ������t���O��^�ɂ���
							pCollision->aHit[HITDIRECTION_RIGHT] = true;
					}
				}

				if (!pairHitTestParts.aGhost[HITDIRECTION_RIGHT])
				{
					if (bSlip)
					{// ����t���O���^�̎��A
						float fAngle = FindAngleLookDown(pos3, pos0) - (D3DX_PI * 0.5f);	// ����

																							// �ʒu���X�V
						D3DXVECTOR3 pos = FindIntersectionPointLookDown(
							*myCollInfo.pPos,
							*myCollInfo.pPos + D3DXVECTOR3(sinf(fAngle), 0.0f, cosf(fAngle)),
							pos0,
							pos3);
						myCollInfo.pPos->x = pos.x + sinf(fAngle) * SLIP_DISTANCE;
						myCollInfo.pPos->z = pos.z + cosf(fAngle) * SLIP_DISTANCE;
					}
					else
					{// ����t���O���U�̎��A
					 // �ʒu���X�V
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
			{// �S�Ă̕�����������̎��A
				pCollision->bOvl = true;	// ������t���O��^�ɂ���
			}
		}

		break;
	}
	case /*/ Y���� /*/VECTOR_Y: {
		bool aInside[HITDIRECTION_MAX];	// �����t���O

											// ���ӂ���̓����t���O���擾
		aInside[HITDIRECTION_BACK] = (((pos3 - pos2).z * (*myCollInfo.pPos - pos2).x) - ((pos3 - pos2).x * (*myCollInfo.pPos - pos2).z) >= 0);
		// ��O�ӂ���̓����t���O���擾
		aInside[HITDIRECTION_FRONT] = (((pos1 - pos0).z * (*myCollInfo.pPos - pos0).x) - ((pos1 - pos0).x * (*myCollInfo.pPos - pos0).z) >= 0);
		// ���ӂ���̓����t���O���擾
		aInside[HITDIRECTION_LEFT] = (((pos2 - pos1).z * (*myCollInfo.pPos - pos1).x) - ((pos2 - pos1).x * (*myCollInfo.pPos - pos1).z) >= 0);
		// �E�ӂ���̓����t���O���擾
		aInside[HITDIRECTION_RIGHT] = (((pos0 - pos3).z * (*myCollInfo.pPos - pos3).x) - ((pos0 - pos3).x * (*myCollInfo.pPos - pos3).z) >= 0);

		if (!(
			aInside[HITDIRECTION_BACK] &&
			aInside[HITDIRECTION_FRONT] &&
			aInside[HITDIRECTION_LEFT] &&
			aInside[HITDIRECTION_RIGHT]))
		{// �S�Ă̕�����������łȂ����A
			break;	// �����𔲂���
		}

		// �����蔻��̌v�Z�ɕK�v�ȃp�����[�^�[�𐮐��^�ɕϊ�(���Z�덷�΍�)
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

		if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) > (nPairY + nPairPartsY) - (nPairHeight * 0.5f))			// ����������̉��ӂ�����O�Ɉʒu���Ă���
			&&																									// &
			((nMyOldY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairOldY + nPairPartsY) - (nPairHeight * 0.5f)))	// �ߋ��̑���������̉��ӂ������Ɉʒu���Ă���
		{// ������߂荞��ł��鎞�A
			if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
			{// ������̂��蔲�����U�̎��A
				if (pCollision != NULL)
				{// �Փˏ��NULL�łȂ����A
					pCollision->bColl =	// �Փ˃t���O��^�ɂ���
						pCollision->aColl[HITDIRECTION_BOTTOM] = true;
				}
				myCollInfo.pPos->y = 	// �ʒu�𑊎�̓����蔻��̉��ɂ���
					(nPairY + nPairPartsY - (nPairHeight * 0.5f) - nMyPartsY - (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
			}
		}
		else if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) < (nPairY + nPairPartsY) + (nPairHeight * 0.5f))		// ��������̏�ӂ������Ɉʒu���Ă���
			&&																									// &
			((nMyOldY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairOldY + nPairPartsY) + (nPairHeight * 0.5f)))	// �ߋ��̓�������̏�ӂ�����Ɉʒu���Ă���
		{// �ォ��߂荞��ł��鎞�A
			if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
			{// �ォ��̂��蔲�����U�̎��A
				if (pCollision != NULL)
				{// �Փˏ��NULL�łȂ����A
					pCollision->bColl =	// �Փ˃t���O��^�ɂ���
						pCollision->aColl[HITDIRECTION_TOP] = true;
				}
				myCollInfo.pPos->y = // �ʒu�𑊎�̓����蔻��̏�ɂ���
					(nPairY + nPairPartsY + (nPairHeight * 0.5f) - nMyPartsY + (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
			}
		}

		if (pCollision != NULL)
		{// �Փˏ��NULL�łȂ����A
			if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
				&&
				((nMyY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
			{// ���݂̏�ӂ�����̓����蔻��̓����̎��A
				pCollision->aOvl[HITDIRECTION_BOTTOM] = true;	// ����������̓����t���O��^�ɂ���

				if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
				{// ������̂��蔲�����U�̎��A
					pCollision->bHit = true;						// ������t���O��^�ɂ���
					pCollision->aHit[HITDIRECTION_BOTTOM] = true;	// ����������̓�����t���O��^�ɂ���
				}
			}

			if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
				&&
				((nMyY + nMyPartsY) - (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
			{// ���݂̉��ӂ�����̓����蔻��̓����̎��A
				pCollision->aOvl[HITDIRECTION_TOP] = true;	// ���������̓����t���O��^�ɂ���

				if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
				{// �ォ��̂��蔲�����U�̎��A
					pCollision->bHit = true;					// ������t���O��^�ɂ���
					pCollision->aHit[HITDIRECTION_TOP] = true;	// ���������̓�����t���O��^�ɂ���
				}
			}
		}

		break;
	}
	}
}

//========================================
// CylinderCylinderCollision3D�֐� - �~������~���̏Փ˃`�F�b�N(3D���[�h) -
// Author:RIKU NISHIMURA
//========================================
void CylinderCylinderCollision3D(VECTOR vector, Collision *pCollision,
	CollisionInfo myCollInfo, HitTestParts myHitTestParts,
	CollisionInfo pairCollInfo, HitTestParts pairHitTestParts,
	bool bRflc, bool bSlip)
{
	// ���g�̒���
	float fMyLength = ((myHitTestParts.fWidth + myHitTestParts.fDepth) * 0.5f * myCollInfo.fScale) * 0.5f;
	// ����̒���
	float fPairLength = ((pairHitTestParts.fWidth + pairHitTestParts.fDepth) * 0.5f * pairCollInfo.fScale) * 0.5f;
	// �����钷��
	float fHitLength = fMyLength + fPairLength;

	pairCollInfo.pRot->y += D3DX_PI;
	pairCollInfo.rotOld.y += D3DX_PI;

	// �ʒu
	D3DXVECTOR3 pairPos = *pairCollInfo.pPos;
	{
		// ���Έʒu
		D3DXVECTOR3 relativePos = pairHitTestParts.fixedRelativePos * pairCollInfo.fScale;
		// ����
		D3DXVECTOR3 rot1 = *pairCollInfo.pRot;

		// �ʒu��X���Έʒu�𔽉f
		pairPos.x += sinf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		pairPos.z += cosf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		// �ʒu��Z���Έʒu�𔽉f
		pairPos.x += sinf(rot1.y) * relativePos.z;
		pairPos.z += cosf(rot1.y) * relativePos.z;
	}
	// �ʒu
	D3DXVECTOR3 pairPosOld = pairCollInfo.posOld;
	{
		// ���Έʒu
		D3DXVECTOR3 relativePos = pairHitTestParts.fixedRelativePos * pairCollInfo.fScale;
		// ����
		D3DXVECTOR3 rot1 = pairCollInfo.rotOld;

		// �ʒu��X���Έʒu�𔽉f
		pairPosOld.x += sinf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		pairPosOld.z += cosf(rot1.y + (D3DX_PI * 0.5f)) * relativePos.x;
		// �ʒu��Z���Έʒu�𔽉f
		pairPosOld.x += sinf(rot1.y) * relativePos.z;
		pairPosOld.z += cosf(rot1.y) * relativePos.z;
	}

	pairCollInfo.pRot->y -= D3DX_PI;
	pairCollInfo.rotOld.y -= D3DX_PI;

	// 2�_�̋���
	float fDistance = FindDistanceLookDown(*myCollInfo.pPos, pairPos);
	// 2�_�̉ߋ��̋���
	float fDistanceOld = FindDistanceLookDown(myCollInfo.posOld, pairPosOld);

	switch (vector)
	{
	case /*/ Z���� /*/VECTOR_Z:
	{
		if (!(
			((myCollInfo.pPos->y + (myHitTestParts.fixedRelativePos.y * myCollInfo.fScale)) + (myHitTestParts.fHeight * 0.5f * myCollInfo.fScale) > (pairPos.y + (pairHitTestParts.fixedRelativePos.y * pairCollInfo.fScale)) - (pairHitTestParts.fHeight * 0.5f * pairCollInfo.fScale)) &&
			((myCollInfo.pPos->y + (myHitTestParts.fixedRelativePos.y * myCollInfo.fScale)) - (myHitTestParts.fHeight * 0.5f * myCollInfo.fScale) < (pairPos.y + (pairHitTestParts.fixedRelativePos.y * pairCollInfo.fScale)) + (pairHitTestParts.fHeight * 0.5f * pairCollInfo.fScale))
			))
		{// Y���Őڂ��Ă��Ȃ����A
			break;	// �����𔲂���
		}

		if (fDistance <= fHitLength)
		{// ���݂������鋗�����̎��A
		 // ������t���O��^�ɂ���
			pCollision->bHit = true;

			// ���肩�玩�g�ւ̌���
			float fAngle = FindAngleLookDown(pairPos, *myCollInfo.pPos);

			// ����̈ʒu���瓖���钷�������Z�����ʒu�ɕ␳
			myCollInfo.pPos->x = pairPos.x + (sinf(fAngle) * fHitLength);
			myCollInfo.pPos->z = pairPos.z + (cosf(fAngle) * fHitLength);

			if (fDistanceOld >= fHitLength)
			{// �ߋ��������鋗���O�̎��A
			 // �Փ˃t���O��^�ɂ���
				pCollision->bColl = true;
			}
		}

		break;
	}
	case /*/ Y���� /*/VECTOR_Y: {
		if (fDistance >= fHitLength)
		{// ���݂������鋗���O�̎��A
			break;	// �����𔲂���
		}

		// �����蔻��̌v�Z�ɕK�v�ȃp�����[�^�[�𐮐��^�ɕϊ�(���Z�덷�΍�)
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

		if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) > (nPairY + nPairPartsY) - (nPairHeight * 0.5f))			// ����������̉��ӂ�����O�Ɉʒu���Ă���
			&&																									// &
			((nMyOldY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairOldY + nPairPartsY) - (nPairHeight * 0.5f)))	// �ߋ��̑���������̉��ӂ������Ɉʒu���Ă���
		{// ������߂荞��ł��鎞�A
			if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
			{// ������̂��蔲�����U�̎��A
				if (pCollision != NULL)
				{// �Փˏ��NULL�łȂ����A
					pCollision->bColl =	// �Փ˃t���O��^�ɂ���
						pCollision->aColl[HITDIRECTION_BOTTOM] = true;
				}
				myCollInfo.pPos->y = 	// �ʒu�𑊎�̓����蔻��̉��ɂ���
					(nPairY + nPairPartsY - (nPairHeight * 0.5f) - nMyPartsY - (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
			}
		}
		else if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) < (nPairY + nPairPartsY) + (nPairHeight * 0.5f))		// ��������̏�ӂ������Ɉʒu���Ă���
			&&																									// &
			((nMyOldY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairOldY + nPairPartsY) + (nPairHeight * 0.5f)))	// �ߋ��̓�������̏�ӂ�����Ɉʒu���Ă���
		{// �ォ��߂荞��ł��鎞�A
			if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
			{// �ォ��̂��蔲�����U�̎��A
				if (pCollision != NULL)
				{// �Փˏ��NULL�łȂ����A
					pCollision->bColl =	// �Փ˃t���O��^�ɂ���
						pCollision->aColl[HITDIRECTION_TOP] = true;
				}
				myCollInfo.pPos->y = // �ʒu�𑊎�̓����蔻��̏�ɂ���
					(nPairY + nPairPartsY + (nPairHeight * 0.5f) - nMyPartsY + (nMyHeight * 0.5f)) / HIT_TEST_DECIMAL_PLACE;
			}
		}

		if (pCollision != NULL)
		{// �Փˏ��NULL�łȂ����A
			if (((nMyY + nMyPartsY) + (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
				&&
				((nMyY + nMyPartsY) + (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
			{// ���݂̏�ӂ�����̓����蔻��̓����̎��A
				pCollision->aOvl[HITDIRECTION_BOTTOM] = true;	// ����������̓����t���O��^�ɂ���

				if (!pairHitTestParts.aGhost[HITDIRECTION_BOTTOM])
				{// ������̂��蔲�����U�̎��A
					pCollision->bHit = true;						// ������t���O��^�ɂ���
					pCollision->aHit[HITDIRECTION_BOTTOM] = true;	// ����������̓�����t���O��^�ɂ���
				}
			}

			if (((nMyY + nMyPartsY) - (nMyHeight * 0.5f) >= (nPairY + nPairPartsY) - (nPairHeight * 0.5f))
				&&
				((nMyY + nMyPartsY) - (nMyHeight * 0.5f) <= (nPairY + nPairPartsY) + (nPairHeight * 0.5f)))
			{// ���݂̉��ӂ�����̓����蔻��̓����̎��A
				pCollision->aOvl[HITDIRECTION_TOP] = true;	// ���������̓����t���O��^�ɂ���

				if (!pairHitTestParts.aGhost[HITDIRECTION_TOP])
				{// �ォ��̂��蔲�����U�̎��A
					pCollision->bHit = true;					// ������t���O��^�ɂ���
					pCollision->aHit[HITDIRECTION_TOP] = true;	// ���������̓�����t���O��^�ɂ���
				}
			}
		}

		break;
	}
	}
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================
//========================================
// InitParameterCollisionInfo�֐� - �Փ˔���ɕK�v�ȏ��̃p�����[�^�[�����l��Ԃ� -
// Author:RIKU NISHIMURA
//========================================
CollisionInfo InitParameterCollisionInfo(void) 
{
	return{
		NULL,				// ���݂̈ʒu�̃|�C���^
		INITD3DXVECTOR3,	// �ߋ��̈ʒu
		NULL,				// �ړ��ʂ̃|�C���^
		NULL,				// ���݂̌����̃|�C���^
		INITD3DXVECTOR3,	// �ߋ��̌���
		{},					// ���i�Ǘ����
		{},					// ���i�ݒ���
		{},					// �����蔻��̏��
		(COLLCHK_MODE)0,	// �Փ˃`�F�b�N�̃��[�h
	};
}

//========================================
// InitParameterDrawHitTest�֐� - �`�悷�铖���蔻����̃p�����[�^�[�����l��Ԃ� -
// Author:RIKU NISHIMURA
//========================================
HitTestDraw InitParameterDrawHitTest(void)
{
	return{
		(HIT_TEST_FORM)0,							// �����蔻��̌`
		0.0f,										// ��
		0.0f,										// ����
		0.0f,										// ���s��
		INITD3DXVECTOR3,							// �ʒu
		INITD3DXVECTOR3,							// ����
		{ false,false,false,false,false,false },	// ���蔲�����
	};
}

//========================================
// InitParameterPhysicsControl�֐� - �����֘A�����̊Ǘ����̃p�����[�^�[�����l��Ԃ� -
// Author:RIKU NISHIMURA
//========================================
PhysicsControl InitParameterPhysicsControl(void)
{
	return{
		{ InitParameterCollisionInfo() },	// �`�悷�铖���蔻��̃��X�g
		0,									// �`�悷�铖���蔻��̐ݒ萔
		false,								// �����蔻��`��t���O
		0,									// �����蔻��̐��̐�
	};
}

//============================================================
//--------------------| *** �����蔻��`��֘A *** |----------
//============================================================
//========================================
// SetHitTestLine�֐� - �����蔻��̐��̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetHitTestLine(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	// �����֘A�����̊Ǘ����̃|�C���^
	PhysicsControl *pPhy = &g_physicsControl;

	if (pPhy->nHitTestLineNum >= HITTESTLINE_MAX) 
	{
		return;	// �����蔻��̐��̐����ő吔�ɒB���Ă��鎞�A
	}

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHitTestLine->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���ւ̃|�C���^��i�߂�
	pVtx += pPhy->nHitTestLineNum * 2;

	// �ʒu����
	pVtx[0].pos = pos1;
	pVtx[1].pos = pos2;

	// ���_���W���A�����b�N����
	g_pVtxBuffHitTestLine->Unlock();

	// �����蔻��̐��̐������Z
	pPhy->nHitTestLineNum++;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================
//========================================
// InitPhysics�֐� - �����֘A�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitPhysics(void) 
{
	// �����֘A�����̊Ǘ����̃|�C���^
	PhysicsControl pPhy = g_physicsControl;

	// �p�����[�^�[�̏�����
	pPhy = InitParameterPhysicsControl();

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * HITTESTLINE_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffHitTestLine,
		NULL);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffHitTestLine->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < HITTESTLINE_MAX; nCntLine++, pVtx += 2)
	{
		// ���_�J���[��ݒ�
		pVtx[0].col = ColorToD3DCOLOR(HITTEST_COLOR);
		pVtx[1].col = ColorToD3DCOLOR(HITTEST_COLOR);
	}

	// ���_���W���A�����b�N����
	g_pVtxBuffHitTestLine->Unlock();
}

//============================================================
//--------------------| *** ���o�� *** |----------------------
//============================================================
//========================================
// LoadHitTestSet�֐� - �����蔻��ݒ���̓ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void LoadHitTestSet(FILE *pFile, HitTestSet *pHitTestSet)
{
	char aDataSearch[TXT_MAX];	// �f�[�^�����p

	// �����蔻��̐���������
	pHitTestSet->nHitTestNum = 0;
	
	// �����蔻��ݒ���̓ǂݍ��݂��J�n
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); // ����

		if (!strcmp(aDataSearch, "HITTESTSET_END"))
		{// �ǂݍ��݂��I��
			break;
		}
		else if (!strcmp(aDataSearch, "HITTEST"))
		{
			pHitTestSet->aHitTest[pHitTestSet->nHitTestNum].nHitTestPartsNum = 0;	// �����蔻��̕��i����������

			// �����蔻����̓ǂݍ��݂��J�n
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); // ����

				if (!strcmp(aDataSearch, "HITTEST_END"))
				{
					pHitTestSet->nHitTestNum++;	// �����蔻�萔�����Z
					break;						// �ǂݍ��݂��I��
				}
				else if (!strcmp(aDataSearch, "HITTEST_PARTS")) 
				{
					// ���i�̎�ޖ��̏��̃|�C���^
					HitTestParts *pHitTest = &pHitTestSet->aHitTest[pHitTestSet->nHitTestNum].aHitTestParts[pHitTestSet->aHitTest[pHitTestSet->nHitTestNum].nHitTestPartsNum];

					// �����蔻����̓ǂݍ��݂��J�n
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch); // ����

						if (!strcmp(aDataSearch, "HITTEST_PARTS_END")) 
						{
							pHitTestSet->aHitTest[pHitTestSet->nHitTestNum].nHitTestPartsNum++;	// �����蔻��̕��i�������Z
							break;	// �ǂݍ��݂��I��
						}
						else if (!strcmp(aDataSearch, "FORM:"))
						{// �����蔻��̌` 
							fscanf(pFile, "%d", &pHitTest->hitTestForm);
						}
						else if (!strcmp(aDataSearch, "PARENT:"))
						{// �e�ԍ� 
							fscanf(pFile, "%d", &pHitTest->nParent); 
						}
						else if (!strcmp(aDataSearch, "WIDTH:"))
						{// ��
							fscanf(pFile, "%f", &pHitTest->fWidth); 
						}
						else if (!strcmp(aDataSearch, "HEIGHT:"))
						{// ����
							fscanf(pFile, "%f", &pHitTest->fHeight);
						}
						else if (!strcmp(aDataSearch, "DEPTH:"))
						{// ���s�� 
							fscanf(pFile, "%f", &pHitTest->fDepth); 
						}
						else if (!strcmp(aDataSearch, "RELATIVE_POS:")) 
						{// ���Έʒu
							fscanf(pFile, "%f", &pHitTest->fixedRelativePos.x);	// X
							fscanf(pFile, "%f", &pHitTest->fixedRelativePos.y);	// Y
							fscanf(pFile, "%f", &pHitTest->fixedRelativePos.z);	// Z
						}
						else if (!strcmp(aDataSearch, "RELATIVE_ROT:"))
						{// ���Ό���
							fscanf(pFile, "%f", &pHitTest->fixedRelativeRot.x);	// X
							fscanf(pFile, "%f", &pHitTest->fixedRelativeRot.y);	// Y
							fscanf(pFile, "%f", &pHitTest->fixedRelativeRot.z);	// Z
							pHitTest->fixedRelativeRot.x *= D3DX_PI;	// �~�����␳
							pHitTest->fixedRelativeRot.y *= D3DX_PI;	// �~�����␳
							pHitTest->fixedRelativeRot.z *= D3DX_PI;	// �~�����␳
						}
						else if (!strcmp(aDataSearch, "GHOST:"))
						{// ���蔲���t���O
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
//--------------------| *** �����蔻�� *** |------------------
//============================================================
//========================================
// HitTestSignUp�֐� - �����蔻��o�^���� -
// Author:RIKU NISHIMURA
//========================================
void HitTestSignUp(CollisionInfo myCollInfo)
{
	// �����֘A�����̊Ǘ����̃|�C���^
	PhysicsControl *pPhy = &g_physicsControl;

	if (pPhy->nDrawHitTestSet >= DRAWHITTEST_MAX)
	{
		return;	// �`�悷�铖���蔻��̐ݒ萔���ő吔�ɒB���Ă��鎞�A
	}

	// �����蔻��ɕK�v�ȏ���o�^
	pPhy->aDrawHitTestList[pPhy->nDrawHitTestSet] = myCollInfo;
	pPhy->nDrawHitTestSet++;
}

//========================================
// HitTestSignOut�֐� - �����蔻��o�^�������� -
// Author:RIKU NISHIMURA
//========================================
void HitTestSignOut(void)
{
	// �����֘A�����̊Ǘ����̃|�C���^
	PhysicsControl *pPhy = &g_physicsControl;

	// �`�悷�铖���蔻��̐ݒ萔��������
	pPhy->nDrawHitTestSet = 0;
}

//========================================
// CollisionCheck�֐� - �Փ˃`�F�b�N -
// Author:RIKU NISHIMURA
//========================================
void CollisionCheck(VECTOR vector, Collision *pCollision, CollisionInfo myCollInfo, CollisionInfo pairCollInfo, COLLCHK_MODE mode)
{
	for (int nCntMyParts = 0; nCntMyParts < myCollInfo.pHitTest->nHitTestPartsNum; nCntMyParts++)
	{
		for (int nCntPairParts = 0; nCntPairParts < pairCollInfo.pHitTest->nHitTestPartsNum; nCntPairParts++)
		{
			HIT_TEST_FORM	my					= myCollInfo.pHitTest->aHitTestParts[nCntMyParts].hitTestForm;		// �����̓����蔻��̎��
			HIT_TEST_FORM	pr					= pairCollInfo.pHitTest->aHitTestParts[nCntPairParts].hitTestForm;	// ����̓����蔻��̎��
			HitTestParts	myHitTestParts		= myCollInfo.pHitTest->aHitTestParts[nCntMyParts];					// �����̓����蔻��̕��i
			HitTestParts	pairHitTestParts	= pairCollInfo.pHitTest->aHitTestParts[nCntPairParts];				// ����̓����蔻��̕��i

			// ���[�h�ɉ���������
			switch (mode)
			{
			case COLLCHK_MODE_NORMAL:
				/*/ �l�p����l�p /*/if (my == HIT_TEST_FORM_SQUARE   && pr == HIT_TEST_FORM_SQUARE)   { SquareSquareCollision3D(vector, pCollision, myCollInfo, myHitTestParts, pairCollInfo, pairHitTestParts); }
				/*/ �~������l�p /*/if (my == HIT_TEST_FORM_CYLINDER && pr == HIT_TEST_FORM_SQUARE)   { CylinderSquareCollision3D(vector, pCollision, myCollInfo, myHitTestParts, pairCollInfo, pairHitTestParts, false, true); }
				/*/ �~������~�� /*/if (my == HIT_TEST_FORM_CYLINDER && pr == HIT_TEST_FORM_CYLINDER) { CylinderCylinderCollision3D(vector, pCollision, myCollInfo, myHitTestParts, pairCollInfo, pairHitTestParts, false, true); }
				break;
			case COLLCHK_MODE_LOOKDOWN:
				
				break;
			}
		}
	}
}

//========================================
// CollisionOverwrite�֐� - �Փˏ��̏㏑�� -
// Author:RIKU NISHIMURA
//========================================
void CollisionOverwrite(Collision *pOverwriteColl, Collision collision) 
{
	pOverwriteColl->bHit	|= collision.bHit;	// ������t���O
	pOverwriteColl->bColl	|= collision.bColl;	// �Փ˃t���O
	pOverwriteColl->bOvl	|= collision.bOvl;	// �����t���O
}

//============================================================
//--------------------| *** �����蔻��`��֘A *** |----------
//============================================================
//========================================
// DrawHitTestSetUp�֐� - �����蔻��̕`�揀������ -
// Author:RIKU NISHIMURA
//========================================
void DrawHitTestSetUp(void) 
{
	if (!g_physicsControl.bDrawHitTest)
	{
		return;	// �����蔻��̕`��t���O���U�̎��A�������I������
	}

	// �����֘A�����̊Ǘ����̃|�C���^
	PhysicsControl *pPhy = &g_physicsControl;
	// �`�悷�铖���蔻����̃|�C���^
	CollisionInfo *pDrawHitTest = pPhy->aDrawHitTestList;

	for (int nCntHitTest = 0; nCntHitTest < pPhy->nDrawHitTestSet; nCntHitTest++, pDrawHitTest++)
	{
		for (int nCntMyParts = 0; nCntMyParts < pDrawHitTest->pHitTest->nHitTestPartsNum; nCntMyParts++)
		{
			// �����蔻��̕��i���̃|�C���^
			HitTestParts *pParts = &pDrawHitTest->pHitTest->aHitTestParts[nCntMyParts];

			// �e�p�[�c�̃}�g���b�N�X
			D3DXMATRIX mtxParent =
				pParts->nParent == -1 ?
				ConvPosRotToMatrix(*pDrawHitTest->pPos, *pDrawHitTest->pRot):
				GetMatrixParts3D(pParts->nParent, *pDrawHitTest->pPos, *pDrawHitTest->pRot, pDrawHitTest->pPartsInfo, pDrawHitTest->pPartsSet);

			// �����蔻��̃}�g���b�N�X
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

				// ���i�̕�/����/���s���𔽉f
				for (int nCntVtx = 0; nCntVtx < l_MAX; nCntVtx++)
				{
					aPos[nCntVtx] *= 0.5f;
					aPos[nCntVtx].x *= pParts->fWidth;
					aPos[nCntVtx].y *= pParts->fHeight;
					aPos[nCntVtx].z *= pParts->fDepth;

					// �ʒu��e�̃}�g���b�N�X�𔽉f��������ōĐݒ�
					aPos[nCntVtx] =
						ConvMatrixToPos(
							MultiplyMatrix(
								MultiplyMatrix(mtxParent, mtxHitTest),
								ConvPosRotToMatrix(aPos[nCntVtx], INITD3DXVECTOR3)));
				}

				// ��̕�
				SetHitTestLine(aPos[l_A1], aPos[l_B1]);
				SetHitTestLine(aPos[l_A1], aPos[l_C1]);
				SetHitTestLine(aPos[l_D1], aPos[l_C1]);
				SetHitTestLine(aPos[l_D1], aPos[l_B1]);
				// ���̕�
				SetHitTestLine(aPos[l_A2], aPos[l_B2]);
				SetHitTestLine(aPos[l_A2], aPos[l_C2]);
				SetHitTestLine(aPos[l_D2], aPos[l_C2]);
				SetHitTestLine(aPos[l_D2], aPos[l_B2]);
				// �c�̕�
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
						// �~�̃J�E���g�ɉ�����Y���W��ݒ�
						switch (nCntCircle)
						{
						case l_SIRCLE_UPPER:
							aCirclePos[nCntCircle][nCntDiv].y = 1;
							break;
						case l_SIRCLE_BOTTOM:
							aCirclePos[nCntCircle][nCntDiv].y = -1;
							break;
						}

						// �����J�E���g�ɉ�����XZ���W��ݒ�
						aCirclePos[nCntCircle][nCntDiv].x = sinf(nCntDiv * ((D3DX_PI * 2) / (float)HITTEST_CIRCLE_DIVISION));
						aCirclePos[nCntCircle][nCntDiv].z = cosf(nCntDiv * ((D3DX_PI * 2) / (float)HITTEST_CIRCLE_DIVISION));

						// ���i�̕�/����/���s���𔽉f
						aCirclePos[nCntCircle][nCntDiv] *= 0.5f;
						aCirclePos[nCntCircle][nCntDiv].x *= pParts->fWidth;
						aCirclePos[nCntCircle][nCntDiv].y *= pParts->fHeight;
						aCirclePos[nCntCircle][nCntDiv].z *= pParts->fDepth;

						// �ʒu��e�̃}�g���b�N�X�𔽉f��������ōĐݒ�
						aCirclePos[nCntCircle][nCntDiv] =
							ConvMatrixToPos(
								MultiplyMatrix(
									MultiplyMatrix(mtxParent, mtxHitTest),
									ConvPosRotToMatrix(aCirclePos[nCntCircle][nCntDiv], INITD3DXVECTOR3)));
					}
				}

				for (int nCntDiv = 0; nCntDiv < HITTEST_CIRCLE_DIVISION; nCntDiv++)
				{
					// �c�̕�
					SetHitTestLine(
						aCirclePos[l_SIRCLE_UPPER][nCntDiv],
						aCirclePos[l_SIRCLE_BOTTOM][nCntDiv]);

					// ��̎��͕�
					SetHitTestLine(
						aCirclePos[l_SIRCLE_UPPER][nCntDiv],
						aCirclePos[l_SIRCLE_UPPER][(nCntDiv + 1) % HITTEST_CIRCLE_DIVISION]);

					// ���̎��͕�
					SetHitTestLine(
						aCirclePos[l_SIRCLE_BOTTOM][nCntDiv],
						aCirclePos[l_SIRCLE_BOTTOM][(nCntDiv + 1) % HITTEST_CIRCLE_DIVISION]);
				}

				break;
			}// HIT_TEST_FORM_CYLINDER
			}
		}
	}

	// �`�悷�铖���蔻��̐ݒ萔��������
	pPhy->nDrawHitTestSet = 0;
}

//========================================
// DrawHitTest�֐� - �����蔻��̕`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void DrawHitTest(void)
{
	if (!g_physicsControl.bDrawHitTest)
	{
		return;	// �����蔻��̕`��t���O���U�̎��A�������I������
	}

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtx;
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtx);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	// �����_�����O�X�e�[�g��ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, false);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffHitTestLine, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntLine = 0; nCntLine < g_physicsControl.nHitTestLineNum; nCntLine++)
	{
		// �|���S�����̕`��
		pDevice->DrawPrimitive(D3DPT_LINELIST, 2 * nCntLine, 1);
	}

	// �����_�����O�X�e�[�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, true);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//========================================
// InitHitTestLineNum�֐� - �����蔻��̐��̐��������� -
// Author:RIKU NISHIMURA
//========================================
void InitHitTestLineNum(void)
{
	// �����蔻��̐��̐���������
	g_physicsControl.nHitTestLineNum = 0;
}

//========================================
// ShowHitTest�֐� - �����蔻��̕\���ݒ� -
// Author:RIKU NISHIMURA
//========================================
void ShowHitTest(bool bShow) 
{
	g_physicsControl.bDrawHitTest = bShow;
}