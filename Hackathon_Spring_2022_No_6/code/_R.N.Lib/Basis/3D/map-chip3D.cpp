//========================================
// 
// �}�b�v�`�b�v(3D)�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** map-chip3D.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
// �}�b�v�`�b�v(3D)���X�g�̑��΃p�X
#define MAPCHIP3DLIST_PATH "data\\GAMEOBJECT\\3D\\MAPCHIP3D_LIST.txt"
// �}�b�v�`�b�v(3D)�̒����_�̑��Έʒu�̈ړ��{��
#define MAPCHIP3D_RELATIVE_POS_R_MOVE_DIAMETER (0.25f)

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �擾 ***
// �}�b�v�`�b�v(3D)�̃p�����[�^�[�̏����l��Ԃ�
void InitParameterMapChip3D(MapChip3D *pMapChip);
//========== *** ���o�� ***
// �}�b�v�`�b�v(3D)�̓ǂݍ��ݏ���
void LoadMapChip3D(char *pPath, int nType);

//****************************************
// �O���[�o���ϐ��錾
//****************************************
// �}�b�v�`�b�v(3D)�̏��
MapChip3D g_aMapChip3D[MAPCHIP3D_MAX];
// �}�b�v�`�b�v(3D)�̊Ǘ����
MapChip3DControl g_mapChip3DControl;
// �}�b�v�`�b�v(3D)�̎�ޖ��̏��
MapChip3DType g_aMapChip3DType[MAPCHIP3D_TYPE_MAX][MAPCHIP3D_SUBTYPE_MAX];

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================

//========================================
// InitParameterMapChip3D�֐� - �}�b�v�`�b�v(3D)�̃p�����[�^�[�̏����l��Ԃ� -
// Author:RIKU NISHIMURA
//========================================
void InitParameterMapChip3D(MapChip3D *pMapChip)
{
	pMapChip->nType = 0;	// ���
	pMapChip->bUse = false;	// �g�p����Ă��邩�t���O

	// �}�b�v�`�b�v(3D)�̎�ޖ��̏��̃|�C���^
	MapChip3DType *pType = &g_aMapChip3DType[pMapChip->nType][pMapChip->nSubType];
	
	// ���i�Ǘ��̏���������
	InitParts3DInfo(&pMapChip->partsInfo, pType->nSetUp);
}

//============================================================
//--------------------| *** ���o�� *** |----------------------
//============================================================

//========================================
// LoadMapChip3D�֐� - �}�b�v�`�b�v(3D)�̓ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void LoadMapChip3D(char *pPath,int nType)
{
	FILE *pFile;				// �t�@�C���|�C���^
	char aDataSearch[TXT_MAX];	// �f�[�^�����p
	// �}�b�v�`�b�v(3D)�̎�ޖ��̏��̃|�C���^
	MapChip3DType *pMapChipType = g_aMapChip3DType[nType];
	// �}�b�v�`�b�v(3D)�̊Ǘ����̃|�C���^
	MapChip3DControl *pMapChipCtl = &g_mapChip3DControl;

	// �}�b�v�`�b�v(3D)�̎�ނ̒��̎�ސ���������
	pMapChipCtl->aSubTypeNum[nType] = 0;

	// ��ޖ��̏��̃f�[�^�t�@�C�����J��
	pFile = fopen(pPath, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
		//�������I������
		return;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (!strcmp(aDataSearch, "END"))
		{// END���������A�ǂݍ��݂��I��
			fclose(pFile);	// �f�[�^�t�@�C�������
			break; 
		}

		if (!strcmp(aDataSearch, "TYPE"))
		{
			// �}�b�v�`�b�v(3D)�̎�ޖ��̏��̓ǂݍ��݃��[�v
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); // ����

				if (!strcmp(aDataSearch, "TYPE_END"))
				{// �ǂݍ��݂��I��
					pMapChipType++;	// ��ނ̃|�C���^��i�߂�

					// ��ނ̒��̎�ސ������Z
					pMapChipCtl->aSubTypeNum[nType]++;
					break;
				}
				else if (!strcmp(aDataSearch, "MODEL_SETUP:"))
				{// ���f���̃Z�b�g�A�b�v�ԍ�
					fscanf(pFile, "%d", &pMapChipType->nSetUp);
				}
			}
		}
	}
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
// InitMapChip3D�֐� - �}�b�v�`�b�v(3D)�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitMapChip3D(void)
{
	// �N���A����
	ClearMapChip3D();
}

//========================================
// UninitMapChip3D�֐� - �}�b�v�`�b�v(3D)�̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitMapChip3D(void)
{

}

//========================================
// UpdateMapChip3D�֐� - �}�b�v�`�b�v(3D)�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateMapChip3D(void)
{
	// �}�b�v�`�b�v(3D)�̏��̃|�C���^
	MapChip3D *pMapChip = g_aMapChip3D;

	for (int nCntMapChip = 0; nCntMapChip < MAPCHIP3D_MAX; nCntMapChip++, pMapChip++)
	{
		if (!pMapChip->bUse) 
		{// �g�p����Ă��Ȃ���Ԃ̎��A
			continue;	// �J��Ԃ�������܂�Ԃ�
		}

		// ���i(3D)�̍X�V����
		UpdateParts3DInfo(&pMapChip->partsInfo);
	}
}

//========================================
// DrawMapChip3D�֐� - �}�b�v�`�b�v(3D)�̕`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void DrawMapChip3D(void)
{
	
}

//============================================================
//--------------------| *** �`�� *** |------------------------
//============================================================
//========================================
// RenderMapChip3D�֐� - �}�b�v�`�b�v(3D)�̕\������ -
// Author:RIKU NISHIMURA
//========================================
void RenderMapChip3D(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType,int nSubType, Color col)
{
	// ���i(3D)�Ǘ����
	Parts3DInfo parts3DInfo;
	InitParts3DInfo(&parts3DInfo, g_aMapChip3DType[nType][nSubType].nSetUp);
	/* �ʒu */parts3DInfo.pos = pos;
	/* ���� */parts3DInfo.rot = rot;
	/* ��~ */parts3DInfo.bStop = true;
	/* �F   */parts3DInfo.col = col;
	// ���i(3D)�̍X�V����
	UpdateParts3DInfo(&parts3DInfo);
}

//============================================================
//--------------------| *** ���o�� *** |----------------------
//============================================================
//========================================
// LoadMapChip3DList�֐� - �}�b�v�`�b�v(3D)���X�g�̓ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void LoadMapChip3DList(void)
{
	FILE *pFile;				// �t�@�C���|�C���^
	char aDataSearch[TXT_MAX];	// �f�[�^�����p
	// �}�b�v�`�b�v(3D)�̊Ǘ����̃|�C���^
	MapChip3DControl *pMapChipCtl = &g_mapChip3DControl;
	
	// ��ޖ��̏��̃f�[�^�t�@�C�����J��
	pFile = fopen(MAPCHIP3DLIST_PATH, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
		return;	//�������I������
	}

	// �}�b�v�`�b�v(3D)�̎�ރJ�E���g
	int nCntType = 0;

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (!strcmp(aDataSearch, "END"))
		{// END���������A�ǂݍ��݂��I��
			fclose(pFile);	// �f�[�^�t�@�C�������

			// �]���̃p�X��NULL�w�肷��
			for (; nCntType < MAPCHIP3D_TYPE_MAX; nCntType++) 
			{
				sprintf(pMapChipCtl->aMapChipPath[nCntType], "NULL");
			}

			break;
		}
		else if (!strcmp(aDataSearch, "MAPCHIP3D"))
		{// END�Ŗ����������A
			fscanf(pFile, "%s", aDataSearch);	// ����

			// �ǂݍ��񂾕�������p�X�Ƃ��Ċi�[
			sprintf(pMapChipCtl->aMapChipPath[nCntType], aDataSearch);

			// �J�E���g�����Z
			nCntType++;
		}
	}

	// �ǂݍ��񂾃p�X�����Ƀ}�b�v�`�b�v(3D)��ǂݍ���
	for (nCntType = 0; nCntType < MAPCHIP3D_TYPE_MAX; nCntType++)
	{
		if (strcmp(pMapChipCtl->aMapChipPath[nCntType], "NULL"))
		{// ���J�E���g�̃p�X��NULL�łȂ����A�}�b�v�`�b�v(3D)�̓ǂݍ��ݏ���
			LoadMapChip3D(pMapChipCtl->aMapChipPath[nCntType], nCntType);
		}
	}
}

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================
//========================================
// GetMapChip3D�֐� - �}�b�v�`�b�v(3D)�̏����擾 -
// Author:RIKU NISHIMURA
//========================================
MapChip3D *GetMapChip3D(void)
{
	return g_aMapChip3D;
}

//========================================
// GetMapChip3DControl�֐� - �}�b�v�`�b�v(3D)�̊Ǘ������擾 -
// Author:RIKU NISHIMURA
//========================================
MapChip3DControl *GetMapChip3DControl(void)
{
	return &g_mapChip3DControl;
}

//========================================
// GetMapChip3DType�֐� - �}�b�v�`�b�v(3D)�̎�ޖ��̏����擾 -
// Author:RIKU NISHIMURA
//========================================
MapChip3DType *GetMapChip3DType(void)
{
	return &g_aMapChip3DType[0][0];
}

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================
//========================================
// SetMapChip3D�֐� - �}�b�v�`�b�v(3D)�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetMapChip3D(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nSubType)
{
	// �}�b�v�`�b�v(3D)�̏��̃|�C���^
	MapChip3D *pMapChip = g_aMapChip3D;

	for (int nCntMapChip = 0; nCntMapChip < MAPCHIP3D_MAX; nCntMapChip++, pMapChip++)
	{
		if (pMapChip->bUse)
		{// �g�p����Ă��鎞�A������܂�Ԃ�
			continue;
		}

		// �}�b�v�`�b�v(3D)�̎�ޖ��̏��̃|�C���^
		MapChip3DType *pType = &g_aMapChip3DType[nType][nSubType];

		// ���i�Ǘ��̏���������
		InitParts3DInfo(&pMapChip->partsInfo, pType->nSetUp);

		pMapChip->partsInfo.pos = pos;	// �ʒu���
		pMapChip->partsInfo.rot = rot;	// �������
		pMapChip->bUse = true;	// �g�p����Ă����Ԃɂ���

		break;
	}
}

//============================================================
//--------------------| *** ��� *** |------------------------
//============================================================
//========================================
// ClearMapChip3D�֐� - �}�b�v�`�b�v(3D)�̃N���A���� -
// Author:RIKU NISHIMURA
//========================================
void ClearMapChip3D(void) 
{
	// �}�b�v�`�b�v(3D)�̏��̃|�C���^
	MapChip3D *pMapChip = g_aMapChip3D;

	for (int nCntMapChip = 0; nCntMapChip < MAPCHIP3D_MAX; nCntMapChip++, pMapChip++)
	{
		// �p�����[�^�[�̏���������
		InitParameterMapChip3D(pMapChip);
	}
}