//========================================
// 
// ���f���̃Z�b�g�A�b�v�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** model-setup.cpp ***
//========================================
#include "assert.h"
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
// ���f���̃Z�b�g�A�b�v�̍ő吔
#define MODELSETUP_MAX (256)
// ���f���̃Z�b�g�A�b�v���X�g�̃p�X
#define MODELSETUP_LIST_PATH "data\\MODELSETUP_LIST.txt"

//****************************************
// �\���̂̒�`
//****************************************
// ���f���̊Ǘ����
typedef struct
{
	//========== *** �ǂݍ��݊֘A ***
	// �ǂݍ��ݍς̃��f���Z�b�g�A�b�v�p�X
	char aLoadModelSetUpPath[MODELSETUP_MAX][TXT_MAX] = {};
	unsigned int nModelSetUpNum = 0;	// ���f���̃Z�b�g�A�b�v��
}ModelSetUpInfo;

//****************************************
// �O���[�o���ϐ��錾
//****************************************
// ���f���̊Ǘ����
static ModelSetUpInfo g_modelSetUpInfo;
// ���f���̃Z�b�g�A�b�v���
static ModelSetUp g_aModelSetUp[MODELSETUP_MAX];

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ���o�� *** |----------------------
//============================================================

//========================================
// LoadModelSetUp�֐� - ���f���̃Z�b�g�A�b�v�̓ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
int LoadModelSetUp(ModelSetUpLoad modelSetUpLoad)
{
	// ���f���Z�b�g�A�b�v�̃p�X
	char *pModelSetUpPath = modelSetUpLoad.pModelSetUpPath;
	// ���f���̃Z�b�g�A�b�v�ԍ�
	int nSetUpIdx = g_modelSetUpInfo.nModelSetUpNum;
	// �ǂݍ��ݍσt���O
	bool bLoadDone = false;

	// ���ɓǂݍ��܂�Ă��郂�f���Z�b�g�A�b�v���m�F
	for (int nCntType = 0; nCntType < nSetUpIdx; nCntType++)
	{
		if (!strcmp(pModelSetUpPath, g_modelSetUpInfo.aLoadModelSetUpPath[nCntType]))
		{// ���ɓ����p�X�̃��f���Z�b�g�A�b�v��ǂݍ���ł������A
			// �ǂݍ��ݍσt���O��^�ɂ���
			bLoadDone = true;

			if (modelSetUpLoad.bReload) 
			{// �ēǂݍ��݃t���O���^�̎��A
				nSetUpIdx = nCntType;
				break;
			}
			else 
			{// �ēǂݍ��݃t���O���U�̎��A
				return nCntType;	// ��ޔԍ���Ԃ�
			}
		}
	}

	// �ǂݍ��ݍσt���O�ɉ����ăZ�b�g�A�b�v�������Z
	g_modelSetUpInfo.nModelSetUpNum += (int)bLoadDone ^ 1;

	if (nSetUpIdx == MODELSETUP_MAX - 1)
	{// ���Ƀ��f���̎�ސ����ő�ɒB���Ă������A
		assert(false);
		return 0;
	}

	// ���f���̃Z�b�g�A�b�v�̃p�X��ۑ�
	sprintf(g_modelSetUpInfo.aLoadModelSetUpPath[nSetUpIdx], "%s", pModelSetUpPath);

	// �f�[�^�����p
	char aDataSearch[TXT_MAX];
	FILE *pFile;	// �t�@�C���|�C���^

	// ��ޖ��̏��̃f�[�^�t�@�C�����J��
	pFile = fopen(pModelSetUpPath, "r");
	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A�������I������
		assert(false);
		return 0;
	}

	// ���f���̃Z�b�g�A�b�v���̃|�C���^
	ModelSetUp *pSetUp = &g_aModelSetUp[nSetUpIdx];

	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); // ����

		if (!strcmp(aDataSearch, "END"))
		{// �ǂݍ��݂��I��
			break;
		}
		else if (!strcmp(aDataSearch, "PARTSSET"))
		{// ���i�ݒ���
			LoadParts3DSet(pFile, &pSetUp->partsSet);
		}
		else if (!strcmp(aDataSearch, "HITTESTSET"))
		{// �����蔻��ݒ��� 
			LoadHitTestSet(pFile, &pSetUp->hitTestSet);
		}
		else if (!strcmp(aDataSearch, "MOTIONSET"))
		{// ���[�V�����ݒ���
			LoadMotion3DSet(pFile, &pSetUp->motionSet);
		}
	}

	// ���f���̃Z�b�g�A�b�v�ԍ���Ԃ�
	return nSetUpIdx;
}

//========================================
// LoadModelSetUpList�֐� - ���f���̃Z�b�g�A�b�v���X�g�̓ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void LoadModelSetUpList(void)
{
	// �f�[�^�����p
	char aDataSearch[TXT_MAX];
	FILE *pFile;	// �t�@�C���|�C���^

	// ��ޖ��̏��̃f�[�^�t�@�C�����J��
	pFile = fopen(MODELSETUP_LIST_PATH, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
		// �������I������
		return;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (!strcmp(aDataSearch, "END"))
		{// �ǂݍ��݂��I��
			fclose(pFile); break;
		}
		if (!strcmp(aDataSearch, "MODELSETUP"))
		{
			// �p�X��ǂݍ���
			fscanf(pFile, "%s", aDataSearch);

			// ���f���̃Z�b�g�A�b�v�ǂݍ��ݏ��
			ModelSetUpLoad setUpLoad;
			/* �Z�b�g�A�b�v�̃p�X */setUpLoad.pModelSetUpPath = aDataSearch;
			/* �ēǂݍ��݃t���O   */setUpLoad.bReload = true;
			// ���f���̃Z�b�g�A�b�v�ǂݍ��ݏ���
			LoadModelSetUp(setUpLoad);
		}
	}
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================

//========================================
// GetModelSetUp�֐� - ���f���̃Z�b�g�A�b�v�����擾 -
// Author:RIKU NISHIMURA
//========================================
ModelSetUp GetModelSetUp(int nSetUp) 
{
	return g_aModelSetUp[nSetUp];
}