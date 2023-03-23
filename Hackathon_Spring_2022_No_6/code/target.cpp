//========================================
// 
// �W�I�̏���
// Author:KEISUKE OOTONO
// 
//========================================
//  *** target.cpp ***
//========================================
#include "target.h"
#include "assert.h"
#include "_R.N.Lib\R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
#define MAXTEX_TARGET_TYPE	(TARGET_MAX)		// �W�I�̎�ނ̍ő吔
#define MAX_TEXTURE			(16)				// �e�N�X�`���̍ő吔
//****************************************
// �v���g�^�C�v�錾
//****************************************

//****************************************
// �O���[�o���ϐ��錾
//****************************************
static Target g_aTarget[MAX_TARGET];		// �A�C�e���̏��
static Summon g_aSummon[MAX_SUMMON];		// �����̏��

//****************************************
// �O���[�o���萔�錾
//****************************************

// �ړ����x
static const float g_aItemSpeed[TARGET_MAX] = {
	0.35f,
	0.4f,
	0.6f,
};

//========== *** �W�I�̏����擾 ***
Target *GetTarget(void)
{
	return &g_aTarget[0];
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitTarget�֐� - �W�I�̏��������� -
// Author:KEISUKE OOTONO
//========================================
void InitTarget(void)
{
		// �f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

		D3DXMATERIAL *pMat;	// �}�e���A���ւ̃|�C���^

		for (int nCntType = 0; nCntType < MAXTEX_TARGET_TYPE; nCntType++)
		{
			
		}

		// �W�I�̏���������
		for (int nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
		{
			g_aTarget[nCntTarget].pos = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].Tarpos = 0.0f;
			g_aTarget[nCntTarget].rot = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].move = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].type = TARGET_A;
			g_aTarget[nCntTarget].bRot = false;
			g_aTarget[nCntTarget].bUse = false;
		}

		SetTarget(0, TARGET_A);
		SetTarget(1, TARGET_A);
		SetTarget(2, TARGET_A);
		SetTarget(3, TARGET_A);
		SetTarget(4, TARGET_A);
		SetTarget(5, TARGET_A);
		SetTarget(6, TARGET_A);
		SetTarget(7, TARGET_A);
		SetTarget(8, TARGET_A);
		SetTarget(9, TARGET_A);
		SetTarget(10, TARGET_A);
		SetTarget(11, TARGET_A);
		SetTarget(12, TARGET_A);
		SetTarget(13, TARGET_A);
		SetTarget(14, TARGET_A);
		SetTarget(15, TARGET_A);
		SetTarget(16, TARGET_A);
		SetTarget(17, TARGET_A);
		SetTarget(18, TARGET_A);
		SetTarget(19, TARGET_A);
		SetTarget(20, TARGET_A);
		SetTarget(21, TARGET_A);
}
//========================================
// UpdateTarget�֐� - �W�I�̍X�V���� -
// Author:KEISUKE OOTONO
//========================================
void UpdateTarget(void)
{
	for (int nCntTar = 0; nCntTar < MAX_TARGET; nCntTar++)
	{
		if (g_aTarget[nCntTar].bUse == true)
		{
			// �ړ��ʂ�������
			if (g_aTarget[nCntTar].Tarpos <= g_aTarget[nCntTar].pos.x && g_aTarget[nCntTar].bRot == true)
			{
				g_aTarget[nCntTar].bUse = false;
			}
			else if (g_aTarget[nCntTar].Tarpos >= g_aTarget[nCntTar].pos.x && g_aTarget[nCntTar].bRot == false)
			{
				g_aTarget[nCntTar].bUse = false;
			}
			else
			{
				g_aTarget[nCntTar].pos += g_aTarget[nCntTar].move;
			}

			// �ړ��ʂ���

			Polygon3DSet polygon3Dset;

			polygon3Dset.pos = g_aTarget[nCntTar].pos;
		}
	}
}
//========================================
// SetTarget�֐� - �W�I�̐ݒ菈�� -
// Author:KEISUKE OOTONO
//========================================
void SetTarget(int nPos, TARGET_ITEM type)
{
	for (int nCntTar = 0; nCntTar < MAX_TARGET; nCntTar++)
	{
		if (g_aTarget[nCntTar].bUse == false)
		{//�g�p����Ă��Ȃ��Ƃ�
			g_aTarget[nCntTar].pos = g_aSummon[nPos].pos;				// �ʒu
			g_aTarget[nCntTar].type = type;								// ��ނ̐ݒ�
			g_aTarget[nCntTar].bUse = true;								// �g�p�t���O

			// �}�b�v�̒��S����E�̕��Ő��������ƈړ����x���}�C�i�X��
			if (g_aTarget[nCntTar].pos.x >= 0.0f)
			{
				g_aTarget[nCntTar].move.x = -g_aItemSpeed[type];
				g_aTarget[nCntTar].Tarpos = -g_aSummon[nPos].pos.x;
				g_aTarget[nCntTar].bRot = false;
			}
			else
			{
				g_aTarget[nCntTar].move.x = g_aItemSpeed[type];
				g_aTarget[nCntTar].Tarpos = -g_aSummon[nPos].pos.x;
				g_aTarget[nCntTar].bRot = true;
			}
			break;
		}
	}
}
//========================================
// LoadSummon�֐� - �ʒu�̓ǂݍ��ݏ��� -
// Author:KEISUKE OOTONO
//========================================
void LoadSummon(void)
{
	int c = 0;	   //1�������m�F����ϐ�
	int column = 1;//�񐔂𐔂���ϐ�
	int row = 0;   //�s���𐔂���ϐ�

	char aData[500];//�Ȃ��镶����
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//�t�@�C�����J��
	pFile = fopen("data/CSV/PointData.csv", "r");

	//�t�@�C������P�������ǂݍ���
	while (fgetc(pFile) != '\n');

	while (c != EOF)
	{
		//�P�Z�����̕���������
		while (1)
		{
			c = fgetc(pFile);

			//�����Ȃ烋�[�v�𔲂���
			if (c == EOF)
				break;

			//�J���}�����s�łȂ���΁A�����Ƃ��ĂȂ���
			if (c != ',' && c != '\n')
				strcat(aData, (const char*)&c);

			//�J���}�����s�Ȃ烋�[�v������
			else
				break;
		}

		assert(row < MAX_SUMMON);

		switch (column)
		{
			//atoi�֐��Ő��l�Ƃ��đ��
		case 1:	g_aSummon[row].pos.x = (float)(atoi(aData));	break;	// 1��ځFX���W
		case 2:	g_aSummon[row].pos.y = (float)(atoi(aData));	break;	// 2��ځFY���W
		case 3:	g_aSummon[row].pos.z = (float)(atoi(aData));	break;	// 3��ځFZ���W
		}
		//�o�b�t�@��������
		memset(aData, 0, sizeof(aData));

		//�񐔂𑫂�
		column++;

		//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (c == '\n')
		{
			column = 1;
			row++;

			if (row == MAX_SUMMON)
			{// �ő�l�ɒB�������A�����𔲂���
				break;
			}
		}
	}
	//�t�@�C�������
	fclose(pFile);
}