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
// ���f���p�X
static char g_aModelPath[TARGET_MAX][TXT_MAX] = {
	"data//MODEL//Item//cheese.x",
	"data//MODEL//Item//cheese.x",
	"data//MODEL//Item//cheese.x",
};

// �ړ����x
static const float g_aItemSpeed[TARGET_MAX] = {
	5.0f,
	2.5f,
	1.0f,
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
			g_aTarget[nCntTarget].rot = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].move = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].type = TARGET_A;
			g_aTarget[nCntTarget].bUse = false;

			InitParts3DInfo(&g_aTarget[nCntTarget].partsInfo, 0);
		}
}
//========================================
// UninitTarget�֐� - �W�I�̏I������ -
// Author:KEISUKE OOTONO
//========================================
void UninitTarget(void)
{

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
			g_aTarget[nCntTar].pos = g_aTarget[nCntTar].move;

			g_aTarget[nCntTar].partsInfo.pos = g_aTarget[nCntTar].pos;
			g_aTarget[nCntTar].partsInfo.rot = g_aTarget[nCntTar].rot;
			UpdateParts3DInfo(&g_aTarget[nCntTar].partsInfo);
		}
	}
}
//========================================
// DrawTarget�֐� - �W�I�̕`�揈�� -
// Author:KEISUKE OOTONO
//========================================
void DrawTarget(void)
{
	
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
			if (g_aTarget[nCntTar].pos.x >= 640.0f)
			{
				g_aTarget[nCntTar].move.x = -g_aItemSpeed[type];
			}
			else
			{
				g_aTarget[nCntTar].move.x = g_aItemSpeed[type];
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