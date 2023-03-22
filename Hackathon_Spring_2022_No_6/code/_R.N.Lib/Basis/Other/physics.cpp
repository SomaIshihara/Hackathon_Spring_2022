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
void CollisionCheck(VECTOR vector, Collision *pCollision, CollisionInfo pMyCollInfo, CollisionInfo pairCollInfo, COLLCHK_MODE mode)
{
	for (int nCntMyParts = 0; nCntMyParts < pMyCollInfo.pHitTest->nHitTestPartsNum; nCntMyParts++)
	{
		for (int nCntPairParts = 0; nCntPairParts < pairCollInfo.pHitTest->nHitTestPartsNum; nCntPairParts++)
		{
			HIT_TEST_FORM	my					= pMyCollInfo.pHitTest->aHitTestParts[nCntMyParts].hitTestForm;		// �����̓����蔻��̎��
			HIT_TEST_FORM	pr					= pairCollInfo.pHitTest->aHitTestParts[nCntPairParts].hitTestForm;	// ����̓����蔻��̎��
			HitTestParts	myHitTestParts		= pMyCollInfo.pHitTest->aHitTestParts[nCntMyParts];					// �����̓����蔻��̕��i
			HitTestParts	pairHitTestParts	= pairCollInfo.pHitTest->aHitTestParts[nCntPairParts];				// ����̓����蔻��̕��i

			// ���[�h�ɉ���������
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