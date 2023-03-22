//========================================
// 
// ���i(3D)�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** parts3D.cpp ***
//========================================
#include <assert.h>
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ���[�V����(3D)�֘A ***
// ���i(3D)�̃g�����X�t�H�[���̎擾����
void GetParts3DTransform(Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet);
// ���i(3D)�̃��f���ݒ�̎擾����
void ModelSetParts3D(Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet);

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ���i(3D)�֘A *** |----------------
//============================================================

//========================================
// GetParts3DTransform�֐� - ���i(3D)�̃g�����X�t�H�[���̎擾���� -
// Author:RIKU NISHIMURA
//========================================
void GetParts3DTransform(Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet)
{
	for (int nCntParts = 0; nCntParts < pPartsSet->nPartsNum; nCntParts++)
	{
		Parts3D		*pParts = &pPartsInfo->aParts[nCntParts];		// ���i�̏��̃|�C���^
		Parts3DType *pPartsType = &pPartsSet->aPartsType[nCntParts];	// ���i�̎�ޖ��̏��̃|�C���^

		if (pParts->bPosAnim)
		{// �ʒu�A�j���[�V�����t���O���^�̎��A
			// �J�E���^�[�̐i�s��
			float fRate = (float)pParts->nCounterPosAnim / (float)pParts->nPosAnimTime;

			// �ʒu���X�V
			pParts->pos = (pParts->posOld * (1.0f - fRate)) + (pParts->targetPos * fRate);
		}

		// �ʒu(����)���X�V
		pParts->posResult = (pParts->pos + pPartsType->fixedRelativePos);

		if (pPartsType->nParent == -1)
		{// �e�ԍ���-1�̎��A���ʈʒu�Ɋg��{������Z
			pParts->posResult *= pPartsSet->fScale;
		}

		if (pParts->bRotAnim)
		{// �����A�j���[�V�����t���O���^�̎��A
			// �J�E���^�[�̐i�s��
			float fRate = (float)pParts->nCounterRotAnim / (float)pParts->nRotAnimTime;

			// �������X�V
			pParts->rot = (pParts->rotOld * (1.0f - fRate)) + (pParts->targetRot * fRate);
		}

		// ����(����)���X�V
		pParts->rotResult = pParts->rot + pPartsType->fixedRelativeRot;
	}
}

//========================================
// ModelSetParts3D�֐� - ���i(3D)�̃��f���ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void ModelSetParts3D(Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet) 
{
	// �f�o�C�X���擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	// �{�̂̃}�g���b�N�X
	D3DXMATRIX mtxSelf;
	// ���i���̃}�g���b�N�X
	D3DXMATRIX aMtxParts[PARTS_3D_MAX];

	// �{�̂̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxSelf);

	// �{�̂̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, pPartsInfo->rot.y, pPartsInfo->rot.x, pPartsInfo->rot.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);

	// �{�̂̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pPartsInfo->pos.x, pPartsInfo->pos.y, pPartsInfo->pos.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);

	// �{�̂̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);

	for (int nCntParts = 0; nCntParts < pPartsSet->nPartsNum; nCntParts++)
	{
		// ���i(3D)�̏��̃|�C���^
		Parts3D *pParts = &pPartsInfo->aParts[nCntParts];
		// ���i(3D)�̕��i�̎�ޖ��̏��̃|�C���^
		Parts3DType *pPartsType = &pPartsSet->aPartsType[nCntParts];

		// ���i�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&aMtxParts[nCntParts]);

		if (pPartsType->nParent == -1)
		{// �e�ԍ���-1�̎��A
			// ���f���̃T�C�Y��ύX
			D3DXMatrixScaling(&aMtxParts[nCntParts], pPartsSet->fScale, pPartsSet->fScale, pPartsSet->fScale);
		}

		// ���i�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pParts->rotResult.y, pParts->rotResult.x, pParts->rotResult.z);
		D3DXMatrixMultiply(&aMtxParts[nCntParts], &aMtxParts[nCntParts], &mtxRot);

		// ���i�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, pParts->posResult.x, pParts->posResult.y, pParts->posResult.z);
		D3DXMatrixMultiply(&aMtxParts[nCntParts], &aMtxParts[nCntParts], &mtxTrans);

		// �e�̕��i�̃}�g���b�N�X
		D3DXMATRIX mtxParent;

		if (pPartsType->nParent != -1)
		{// ���i�̐e�ԍ���-1(�e����)�łȂ����A�e�}�g���b�N�X��ݒ�
			mtxParent = aMtxParts[pPartsType->nParent];
		}
		else
		{// ���i�̐e�ԍ���-1(�e����)�̎��A�e�}�g���b�N�X��{�̃}�g���b�N�X�Őݒ�
			mtxParent = mtxSelf;
		}

		// �Z�o�������i�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(
			&aMtxParts[nCntParts],
			&aMtxParts[nCntParts],
			&mtxParent);

		// ���f���̐ݒ���
		ModelSet modelSet;
		/* ���f���ԍ�	*/modelSet.nModelIdx = pPartsType->nModelIdx;
		/* �}�g���b�N�X	*/modelSet.mtx = aMtxParts[nCntParts];
		/* �F			*/modelSet.col = pPartsInfo->col;
		// ���f���̐ݒ�
		SetModel(modelSet);
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ���i(3D)�֘A *** |----------------
//============================================================

//========================================
// LoadParts3DSet�֐� - ���i�ݒ���(3D)�̓ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void LoadParts3DSet(FILE *pFile, Parts3DSet *pPartsSet)
{
	// �f�[�^�����p
	char aDataSearch[TXT_MAX];
	float fAllScale;	// �S�̂̊g��{��

	// ���i����������
	pPartsSet->nPartsNum = 0;

	// �g��{����������
	pPartsSet->fScale = 1.0f;

	// ���i�ݒ���̓ǂݍ��݂��J�n
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); // ����

		if (!strcmp(aDataSearch, "PARTSSET_END"))
		{// �ǂݍ��݂��I��
			break; 
		}
		else if (!strcmp(aDataSearch, "SCALE:"))
		{// �g��{��
			fscanf(pFile, "%f", &pPartsSet->fScale);
		}
		else if (!strcmp(aDataSearch, "PARTS"))
		{
			// ���i�̎�ޖ��̏��̃|�C���^
			Parts3DType *pPartsType = &pPartsSet->aPartsType[pPartsSet->nPartsNum];

			// ���i���̓ǂݍ��݂��J�n
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); // ����

				if (!strcmp(aDataSearch, "PARTS_END"))
				{// �ǂݍ��݂��I��
					pPartsSet->nPartsNum++;
					break;
				}
				else if (!strcmp(aDataSearch, "MODEL_PATH:"))
				{// ���f���̑��΃p�X
					// ������x������������
					fscanf(pFile, "%s", aDataSearch);

					// ���f���̓ǂݍ��ݏ���ݒ�
					ModelLoad modelLoad =
					{
						aDataSearch,	// ���f���̃p�X
					};

					// ���f����ǂݍ��݁A���f���ԍ����擾
					pPartsType->nModelIdx = LoadModel(modelLoad);
				}
				else if (!strcmp(aDataSearch, "PARENT:"))
				{// �e�p�[�c�ԍ� 
					fscanf(pFile, "%d", &pPartsType->nParent); 
				}
				else if (!strcmp(aDataSearch, "RELATIVE_POS:"))
				{// �Œ�̑��Έʒu
					fscanf(pFile, "%f", &pPartsType->fixedRelativePos.x);	// X
					fscanf(pFile, "%f", &pPartsType->fixedRelativePos.y);	// Y
					fscanf(pFile, "%f", &pPartsType->fixedRelativePos.z);	// Z
				}
				else if (!strcmp(aDataSearch, "RELATIVE_ROT:"))
				{// �Œ�̑��Ίp�x
					fscanf(pFile, "%f", &pPartsType->fixedRelativeRot.x);	// X
					fscanf(pFile, "%f", &pPartsType->fixedRelativeRot.y);	// Y
					fscanf(pFile, "%f", &pPartsType->fixedRelativeRot.z);	// Z
					pPartsType->fixedRelativeRot.x *= D3DX_PI;				// �~�����␳
					pPartsType->fixedRelativeRot.y *= D3DX_PI;				// �~�����␳
					pPartsType->fixedRelativeRot.z *= D3DX_PI;				// �~�����␳
				}
				else if (!strcmp(aDataSearch, "ROT_RELATIVE_POS:"))
				{// ��]���̑��Έʒu
					fscanf(pFile, "%f", &pPartsType->rotRelativePos.x);	// X
					fscanf(pFile, "%f", &pPartsType->rotRelativePos.y);	// Y
					fscanf(pFile, "%f", &pPartsType->rotRelativePos.z);	// Z
				}
			}
		}
	}
}

//========================================
// InitParts3DInfo�֐� - ���i(3D)�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitParts3DInfo(Parts3DInfo *pPartsInfo, int nModelSetUp)
{
	// ���f���̃Z�b�g�A�b�v���
	ModelSetUp setUp = GetModelSetUp(nModelSetUp);

	pPartsInfo->pos = INITD3DXVECTOR3;		// �ʒu(�{��)
	pPartsInfo->rot = INITD3DXVECTOR3;		// ����(�{��)
	pPartsInfo->bStop = false;				// ��~�t���O
	pPartsInfo->nModelSetUp = nModelSetUp;	// ���f���̃Z�b�g�A�b�v�ԍ�
	pPartsInfo->nCounterMotion = 0;	// ���[�V�����J�E���^�[
	pPartsInfo->nMotion = 0;		// ���[�V�����ԍ�
	pPartsInfo->nMotionOld = 0;		// ���[�V�����ԍ�(�ߋ�)
	pPartsInfo->col = INITCOLOR;	// �F

	for (int nCntParts = 0; nCntParts < setUp.partsSet.nPartsNum; nCntParts++)
	{
		// ���i�̏��̃|�C���^
		Parts3D *pParts = &pPartsInfo->aParts[nCntParts];
		// ���i�̎�ޖ��̏��̃|�C���^
		Parts3DType *pPartsType = &setUp.partsSet.aPartsType[nCntParts];

		// �ʒu�ƌ����̌��ʂ��X�V
		pParts->posResult = pPartsType->fixedRelativePos;
		pParts->rotResult = pPartsType->fixedRelativeRot;

		pParts->pos				= INITD3DXVECTOR3;	// �ʒu
		pParts->rot				= INITD3DXVECTOR3;	// ����
		pParts->bPosAnim		= false;			// �ʒu�A�j���[�V�����t���O
		pParts->nCounterPosAnim = 0;				// �ʒu�A�j���[�V�����J�E���^�[
		pParts->nPosAnimTime	= 0;				// �ʒu�A�j���[�V�����ɂ����鎞��
		pParts->posOld			= INITD3DXVECTOR3;	// ���̈ʒu
		pParts->targetPos		= INITD3DXVECTOR3;	// �ڕW�ʒu
		pParts->bRotAnim		= false;			// �p�x�A�j���[�V�����t���O
		pParts->nCounterRotAnim = 0;				// �p�x�A�j���[�V�����J�E���^�[
		pParts->nRotAnimTime	= 0;				// �p�x�A�j���[�V�����ɂ����鎞��
		pParts->rotOld			= INITD3DXVECTOR3;	// ���̊p�x
		pParts->targetRot		= INITD3DXVECTOR3;	// �ڕW�p�x
	}
}

//========================================
// UpdateParts3DInfo�֐� - ���i(3D)�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateParts3DInfo(Parts3DInfo *pPartsInfo)
{
	// ���f���̃Z�b�g�A�b�v���
	ModelSetUp setUp = GetModelSetUp(pPartsInfo->nModelSetUp);

	if (!pPartsInfo->bStop)
	{// ��~���Ă��Ȃ����A
		// ���[�V�����ݒ�
		SetMotion3D(pPartsInfo);

		// ���[�V�����̍X�V����
		UpdateMotion3D(setUp.motionSet, pPartsInfo, setUp.partsSet);

		// ���i(3D)�̃g�����X�t�H�[�����擾
		GetParts3DTransform(pPartsInfo, &setUp.partsSet);
	}

	// ���f���̐ݒ菈��
	ModelSetParts3D(pPartsInfo, &setUp.partsSet);
}

//========================================
// GetMatrixParts3D�֐� - ���i(3D)�̃}�g���b�N�X���擾 -
// Author:RIKU NISHIMURA
//========================================
D3DXMATRIX GetMatrixParts3D(int nParts, D3DXVECTOR3 pos, D3DXVECTOR3 rot, Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	// ���i�̃}�g���b�N�X
	D3DXMATRIX aMtxParts[PARTS_3D_MAX];
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxSelf;				// �{�̂̃}�g���b�N�X

	// �{�̂̃��[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxSelf);

	// �{�̂̌����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);

	// �{�̂̈ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);

	for (int nCntParts = 0; nCntParts < pPartsSet->nPartsNum; nCntParts++)
	{
		// ���i(3D)�̏��̃|�C���^
		Parts3D *pParts = &pPartsInfo->aParts[nCntParts];
		// ���i(3D)�̕��i�̎�ޖ��̏��̃|�C���^
		Parts3DType *pPartsType = &pPartsSet->aPartsType[nCntParts];

		D3DXMATRIX	mtxParent;	// �e�}�g���b�N�X

		// ���i�̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&aMtxParts[nCntParts]);

		if (pPartsType->nParent == -1)
		{// �e�ԍ���-1�̎��A
			// ���f���̃T�C�Y��ύX
			D3DXMatrixScaling(&aMtxParts[nCntParts], pPartsSet->fScale, pPartsSet->fScale, pPartsSet->fScale);
		}

		// ���i�̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, pParts->rotResult.y, pParts->rotResult.x, pParts->rotResult.z);
		D3DXMatrixMultiply(&aMtxParts[nCntParts], &aMtxParts[nCntParts], &mtxRot);

		// ���i�̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, pParts->posResult.x, pParts->posResult.y, pParts->posResult.z);
		D3DXMatrixMultiply(&aMtxParts[nCntParts], &aMtxParts[nCntParts], &mtxTrans);

		if (pPartsType->nParent != -1)
		{// ���i�̐e�ԍ���-1(�e����)�łȂ����A�e�}�g���b�N�X��ݒ�
			mtxParent = aMtxParts[pPartsType->nParent];
		}
		else
		{// ���i�̐e�ԍ���-1(�e����)�̎��A�e�}�g���b�N�X��{�̃}�g���b�N�X�Őݒ�
			mtxParent = mtxSelf;
		}

		// �Z�o�������i�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
		D3DXMatrixMultiply(
			&aMtxParts[nCntParts],
			&aMtxParts[nCntParts],
			&mtxParent);

		if (nCntParts >= nParts) 
		{// ���i�̃J�E���g���擾���������i�ԍ��ɒB�������A
			return aMtxParts[nParts];	// �}�g���b�N�X��Ԃ�
		}
	}

	assert(false);
	return mtxSelf;
}