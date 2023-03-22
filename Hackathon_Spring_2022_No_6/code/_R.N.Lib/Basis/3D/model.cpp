//========================================
// 
// ���f���֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** model.cpp ***
//========================================
#include "assert.h"
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �O���[�o���ϐ��錾
//****************************************
// ���f���֘A�̃e�N�X�`���ԍ�
static int g_aTextureIdxModel[MODELTYPE_MAX][MATERIAL_3D_MAX] = {};
// ���f���֘A�̃��b�V��(���_���)�ւ̃|�C���^
static LPD3DXMESH g_aMeshModel[MODELTYPE_MAX] = {};
// ���f���֘A�̃}�e���A���ւ̃|�C���^
static LPD3DXBUFFER g_pBuffMatModel[MODELTYPE_MAX] = {};
// ���f���֘A�̃}�e���A���̐�
static DWORD g_aNumMatModel[MODELTYPE_MAX] = {};
// ���f���̊Ǘ����
static ModelInfo g_modelSetUpInfo;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================
#if 1
//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================
#if 1
//========================================
// InitModel�֐� - ���f���̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitModel(void)
{
	
}

//========================================
// UninitModel�֐� - ���f���̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitModel(void)
{
	for (int nCntType = 0; nCntType < MODELTYPE_MAX; nCntType++)
	{
		// ���b�V���̔j��
		if (g_aMeshModel[nCntType] != NULL)
		{
			g_aMeshModel[nCntType]->Release();
			g_aMeshModel[nCntType] = NULL;
		}

		// �}�e���A���̔j��
		if (g_pBuffMatModel[nCntType] != NULL)
		{
			g_pBuffMatModel[nCntType]->Release();
			g_pBuffMatModel[nCntType] = NULL;
		}
	}
}

//========================================
// DrawModel�֐� - ���f���̕`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void DrawModel(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DMATERIAL9 matDef;	// ���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;		// �}�e���A���f�[�^�ւ̃|�C���^

	// ���f���̐ݒ萔���`��
	for (int nCntModel = 0; nCntModel < g_modelSetUpInfo.nModelSetNum; nCntModel++)
	{
		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// ��ޔԍ�
		int nType = g_modelSetUpInfo.aModelSet[nCntModel].nModelIdx;

		// �{�̂̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_modelSetUpInfo.aModelSet[nCntModel].mtx);

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatModel[nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aNumMatModel[nType]; nCntMat++)
		{
			// �}�e���A���̐ݒ�
			SetMaterial(pDevice, &pMat[nCntMat].MatD3D, g_modelSetUpInfo.aModelSet[nCntModel].col);

			// �e�N�X�`���̐ݒ�
			SetTexture(pDevice, g_aTextureIdxModel[nType][nCntMat]);

			// �|���S��(�p�[�c)�̕`��
			g_aMeshModel[nType]->DrawSubset(nCntMat);
		}
	}
}

//========================================
// DrawSingleModel�֐� - ���f���̕`�揈��(�P��) -
// Author:RIKU NISHIMURA
//========================================
void DrawSingleModel(LPDIRECT3DDEVICE9 pDevice,int nIdx)
{
	D3DMATERIAL9 matDef;	// ���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;		// �}�e���A���f�[�^�ւ̃|�C���^

	// ���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	// ��ޔԍ�
	int nType = g_modelSetUpInfo.aModelSet[nIdx].nModelIdx;

	// �{�̂̃��[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &g_modelSetUpInfo.aModelSet[nIdx].mtx);

	// �}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)g_pBuffMatModel[nType]->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)g_aNumMatModel[nType]; nCntMat++)
	{
		// �}�e���A���̐ݒ�
		SetMaterial(pDevice, &pMat[nCntMat].MatD3D, g_modelSetUpInfo.aModelSet[nIdx].col);

		// �e�N�X�`���̐ݒ�
		SetTexture(pDevice, g_aTextureIdxModel[nType][nCntMat]);

		// �|���S��(�p�[�c)�̕`��
		g_aMeshModel[nType]->DrawSubset(nCntMat);
	}
}
#endif
//============================================================
//--------------------| *** ���o�� *** |----------------------
//============================================================
#if 1
//========================================
// LoadModel�֐� - ���f���̓ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
int LoadModel(ModelLoad modelLoad)
{
	// ���f���̃p�X
	char *pModelPath = modelLoad.pModelPath;

	// ���ɓǂݍ��܂�Ă��郂�f�����m�F
	for (int nCntType = 0; nCntType < g_modelSetUpInfo.nModelTypeNum; nCntType++) 
	{
		if (!strcmp(pModelPath, g_modelSetUpInfo.aLoadModelPath[nCntType])) 
		{// ���ɓ����p�X�̃��f����ǂݍ���ł������A
			return nCntType;	// ��ޔԍ���Ԃ�
		}
	}

	if (g_modelSetUpInfo.nModelTypeNum == MODELTYPE_MAX - 1) 
	{// ���Ƀ��f���̎�ސ����ő�ɒB���Ă������A
		assert(false);
		return 0;
	}

	// ���f���̃p�X��ۑ�
	sprintf(g_modelSetUpInfo.aLoadModelPath[g_modelSetUpInfo.nModelTypeNum], "%s", pModelPath);

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	// �}�e���A���ւ̃|�C���^
	D3DXMATERIAL *pMat;

	// ��ޔԍ�
	int nType = g_modelSetUpInfo.nModelTypeNum;

	// X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(
		pModelPath,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&g_pBuffMatModel[nType],
		NULL,
		&g_aNumMatModel[nType],
		&g_aMeshModel[nType]);

	if (g_pBuffMatModel[nType] == NULL) 
	{// NULL���������A
		char aMessage[TXT_MAX];
		sprintf(aMessage, "���f���̓ǂݍ��݂Ɏ��s�I %s", pModelPath);
		MessageBox(*GetWindowHandle(), aMessage, "�x���I", MB_ICONWARNING);

		nType = -1;	// ��ޔԍ���-1�w��
	}
	else
	{
		// �}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatModel[nType]->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)g_aNumMatModel[nType]; nCntMat++)
		{
			if (pMat[nCntMat].pTextureFilename != NULL)
			{// �e�N�X�`���̃t�@�C������NULL�łȂ����A
				// �e�N�X�`����ǂݍ���
				g_aTextureIdxModel[nType][nCntMat] = LoadTexture(pMat[nCntMat].pTextureFilename);
			}
			else
			{// �e�N�X�`���̃t�@�C������NULL�̎��A
				// �e�N�X�`���ԍ���-1�Ŏw��
				g_aTextureIdxModel[nType][nCntMat] = -1;
			}
		}

		// ���f���̐������Z
		g_modelSetUpInfo.nModelTypeNum++;
	}

	// ��ޔԍ���Ԃ�
	return nType;
}
#endif
//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================
#if 1
//========================================
// SetModel�֐� - ���f���̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetModel(ModelSet modelSet)
{
	if (modelSet.nModelIdx < 0 || modelSet.nModelIdx >= g_modelSetUpInfo.nModelTypeNum) 
	{// ���f���̎�ޔԍ����͈͊O�̎��A
		return;	// �������I��
	}
	else if (g_modelSetUpInfo.nModelSetNum == MODEL_MAX)
	{// ���f���̐ݒ萔���ő吔�ɒB���Ă��鎞�A
		assert(false);
		return;	// �������I��
	}

	// ���f���̐ݒ������
	g_modelSetUpInfo.aModelSet[g_modelSetUpInfo.nModelSetNum] = modelSet;

	// ���f���̐ݒ萔�����Z
	g_modelSetUpInfo.nModelSetNum++;
}

//========================================
// GetModelInfo�֐� - ���f���̊Ǘ����擾 -
// Author:RIKU NISHIMURA
//========================================
ModelInfo *GetModelInfo(void)
{
	return &g_modelSetUpInfo;
}
#endif
#endif