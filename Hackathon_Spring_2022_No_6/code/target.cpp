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
#include "_R.N.Lib\Basis\2D\timer.h"
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
static Target g_aTarget[MAX_TARGET];				// �W�I�̏��
static TargetType g_TargetType[MAXTEX_TARGET_TYPE];	// �W�I��ނ̏��
static Summon g_Summon[MAX_SUMMON];					// �����̏��
static Point g_aPoint[MAX_POINT];					// �ʒu�̏��
static int g_aTex1[MAXTEX_TARGET_TYPE];
static int g_nGameTime;	//��������
static int g_nCounterFrame;	//�t���[���J�E���^�[

//****************************************
// �O���[�o���萔�錾
//****************************************
// �e�N�X�`���p�X
char g_aTexturePath1[MAXTEX_TARGET_TYPE][TXT_MAX] =
{
	"data//TEXTURE//Target//00.PNG",
	"data//TEXTURE//Target//01.PNG",
	"data//TEXTURE//Target//02.PNG",
};

// �ړ����x
static const float g_aTargetSpeed[TARGET_MAX] = {
	0.35f,
	0.25f,
	1.05f,
};

// �G���
// �`�[���ԍ�
const TARGET_ITEM g_Target[TARGET_MAX] = {
	{ TARGET_A },
	{ TARGET_B },
	{ TARGET_C },
};

//========== *** �W�I�̏����擾 ***
Target *GetTarget(void)
{
	return &g_aTarget[0];
}
//========== *** �W�I��ނ̏����擾 ***
TargetType *GetTargetType(void)
{
	return &g_TargetType[0];
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

		for (int nCntType = 0; nCntType < MAXTEX_TARGET_TYPE; nCntType++)
		{
			g_aTex1[nCntType] = LoadTexture(g_aTexturePath1[nCntType]);
		}

		// �O���[�o���ϐ��̏�����
		g_nGameTime = GAME_TIME;
		g_nCounterFrame = 0;
		// �W�I�̏���������
		for (int nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
		{
			g_aTarget[nCntTarget].pos = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].Tarpos = 0.0f;
			g_aTarget[nCntTarget].rot = D3DXVECTOR3(-D3DX_PI * 0.5f, 0.0f, 0.0f);
			g_aTarget[nCntTarget].move = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].type = TARGET_A;
			g_aTarget[nCntTarget].nPtn = 0;
			g_aTarget[nCntTarget].nCntFlame = 0;
			g_aTarget[nCntTarget].nCntMFLame = 0;
			g_aTarget[nCntTarget].nCntMove = 0;
			g_aTarget[nCntTarget].nCntSwit = 0;

			g_aTarget[nCntTarget].bRot = false;
			g_aTarget[nCntTarget].bUse = false;
		}
}
//========================================
// UpdateTarget�֐� - �W�I�̍X�V���� -
// Author:KEISUKE OOTONO
//========================================
void UpdateTarget(void)
{
	//1�b���o�߂���
	if (++g_nCounterFrame % 60 == 0)
	{
		//�������Ԍ���
		g_nGameTime--;
	}

	for (int nCntTar = 0; nCntTar < MAX_TARGET; nCntTar++)
	{
		if (g_aTarget[nCntTar].bUse == true)
		{
			// �e�G�̈ړ�����
			if (g_aTarget[nCntTar].type == TARGET_C)
			{
				if (g_aTarget[nCntTar].bMove == false)
				{
					g_aTarget[nCntTar].nCntMFLame++;
					if ((g_aTarget[nCntTar].nCntMFLame % g_aTarget[nCntTar].nCntMove) == 0)
					{
						if (g_aTarget[nCntTar].bMove == false)
						{
							g_aTarget[nCntTar].nCntMove = 80;
							g_aTarget[nCntTar].nCntSwit++;

							if (g_aTarget[nCntTar].nCntSwit == 2)
							{
								g_aTarget[nCntTar].nCntSwit = 0;
								g_aTarget[nCntTar].bMove = true;
							}
						}
						if (g_aTarget[nCntTar].bRot == false)
						{
							g_aTarget[nCntTar].move.x = g_aTargetSpeed[g_aTarget[nCntTar].type];
							g_aTarget[nCntTar].Tarpos = -g_aTarget[nCntTar].Tarpos;
							g_aTarget[nCntTar].bRot = true;
						}
						else
						{
							g_aTarget[nCntTar].move.x = -g_aTargetSpeed[g_aTarget[nCntTar].type];
							g_aTarget[nCntTar].Tarpos = -g_aTarget[nCntTar].Tarpos;
							g_aTarget[nCntTar].bRot = false;
						}
					}
				}
				
			}


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

			// �|���S��(3D)�̐ݒ���
			Polygon3DSet polygon3DSet;
			polygon3DSet.nTex = g_aTex1[g_aTarget[nCntTar].type];
			polygon3DSet.nPtn = g_aTarget[nCntTar].nPtn;
			polygon3DSet.nPtnX = 2;
			polygon3DSet.nPtnY = 1;
			polygon3DSet.fWidth = g_TargetType[g_aTarget[nCntTar].type].fWidth;
			polygon3DSet.fHeight = g_TargetType[g_aTarget[nCntTar].type].fHeight;
			polygon3DSet.pos = g_aTarget[nCntTar].pos;
			polygon3DSet.rot = g_aTarget[nCntTar].rot;
			polygon3DSet.col = Color{ 255,255,255,255 };

			// �|���S��(3D)�̐ݒ菈��
			SetPolygon3D(polygon3DSet);

			g_aTarget[nCntTar].nCntFlame++;
			if ((g_aTarget[nCntTar].nCntFlame % 24) == 0)
			{
				if (g_aTarget[nCntTar].nPtn <= 0)
				{
					g_aTarget[nCntTar].nPtn++;
				}
				else if (g_aTarget[nCntTar].nPtn == 1)
				{
					g_aTarget[nCntTar].nPtn = 0;
				}
			}

		}
	}

	for (int nCntTar = 0; nCntTar < MAX_SUMMON; nCntTar++)
	{
		if (g_Summon[nCntTar].bUse == true)
		{
			if (g_nGameTime == g_Summon[nCntTar].nTime)
			{
				SetTarget(g_Summon[nCntTar].nPoint, g_Target[g_Summon[nCntTar].nType], g_Summon[nCntTar].nMTyoe);
				g_Summon[nCntTar].bUse = false;
			}

		}
	}
}
//========================================
// SetTarget�֐� - �W�I�̐ݒ菈�� -
// Author:KEISUKE OOTONO
//========================================
void SetTarget(int nPos, TARGET_ITEM type,int MType)
{
	for (int nCntTar = 0; nCntTar < MAX_TARGET; nCntTar++)
	{
		if (g_aTarget[nCntTar].bUse == false)
		{//�g�p����Ă��Ȃ��Ƃ�
			g_aTarget[nCntTar].pos = g_aPoint[nPos].pos;				// �ʒu
			g_aTarget[nCntTar].type = type;								// ��ނ̐ݒ�
			g_aTarget[nCntTar].bUse = true;								// �g�p�t���O

			// �}�b�v�̒��S����E�̕��Ő��������ƈړ����x���}�C�i�X��
			if (MType == 0)
			{
				g_aTarget[nCntTar].move.x = -g_aTargetSpeed[type];
				g_aTarget[nCntTar].Tarpos = -g_aPoint[nPos].pos.x;
				g_aTarget[nCntTar].bRot = false;
			}
			else if(MType == 1)
			{
				g_aTarget[nCntTar].Tarpos = g_aPoint[nPos].pos.x;
				g_aTarget[nCntTar].pos.x = -g_aPoint[nPos].pos.x;				// �ʒu
				g_aTarget[nCntTar].move.x = g_aTargetSpeed[type];
				g_aTarget[nCntTar].bRot = true;
			}
			g_aTarget[nCntTar].nCntMove = 160;
			break;
		}
	}
}
//========================================
// LoadTarget�֐� - �G�̓ǂݍ��ݏ��� -
// Author:KEISUKE OOTONO
//========================================
void LoadTarget(void)
{

	{
		int c = 0;	   //1�������m�F����ϐ�
		int column = 1;//�񐔂𐔂���ϐ�
		int row = 0;   //�s���𐔂���ϐ�

		char aData[500];//�Ȃ��镶����
		FILE *pFile;

		memset(aData, 0, sizeof(aData));

		//�t�@�C�����J��
		pFile = fopen("data/CSV/enemydata.csv", "r");

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
			case 1:	g_Summon[row].nType = atoi(aData);	break;	// 1��ځF���
			case 2:	g_Summon[row].nPoint = atoi(aData);	break;	// 2��ځF�o���ʒu
			case 3:	g_Summon[row].nTime = atoi(aData);	break;	// 3��ځF�o������
			case 4:	g_Summon[row].nMTyoe = atoi(aData);	break;	// 4��ځF�ړ�����
			}
			//�o�b�t�@��������
			memset(aData, 0, sizeof(aData));

			//�񐔂𑫂�
			column++;

			//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
			if (c == '\n')
			{
				g_Summon[row].bUse = true;

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

		assert(row < MAX_POINT);

		switch (column)
		{
			//atoi�֐��Ő��l�Ƃ��đ��
		case 1:	g_aPoint[row].pos.x = (float)(atoi(aData));	break;	// 1��ځFX���W
		case 2:	g_aPoint[row].pos.y = (float)(atoi(aData));	break;	// 2��ځFY���W
		case 3:	g_aPoint[row].pos.z = (float)(atoi(aData));	break;	// 3��ځFZ���W
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

			if (row == MAX_POINT)
			{// �ő�l�ɒB�������A�����𔲂���
				break;
			}
		}
	}
	//�t�@�C�������
	fclose(pFile);
}
//========================================
// LoadTargetType�֐� - �G�̏��ǂݍ��ݏ��� -
// Author:KEISUKE OOTONO
//========================================
void LoadTargetType(void)
{
	int c = 0;	   //1�������m�F����ϐ�
	int column = 1;//�񐔂𐔂���ϐ�
	int row = 0;   //�s���𐔂���ϐ�

	char aData[500];//�Ȃ��镶����
	FILE *pFile;

	memset(aData, 0, sizeof(aData));

	//�t�@�C�����J��
	pFile = fopen("data/CSV/TargetType.csv", "r");

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

		assert(row < MAXTEX_TARGET_TYPE);

		switch (column)
		{
			//atoi�֐��Ő��l�Ƃ��đ��
		case 1:	g_TargetType[row].nLife = atoi(aData);			break;	// 1��ځF����
		case 2:	g_TargetType[row].nScore = atoi(aData);			break;	// 2��ځF�X�R�A
		case 3:	g_TargetType[row].fWidth = (float)(atoi(aData)); break;	// 3��ځF��
		case 4:	g_TargetType[row].fHeight = (float)(atoi(aData)); break;	// 4��ځF����
		}
		//�o�b�t�@��������
		memset(aData, 0, sizeof(aData));

		//�񐔂𑫂�
		column++;

		//�����ǂݍ��񂾕��������s��������񐔂����������čs���𑝂₷
		if (c == '\n')
		{
			g_Summon[row].bUse = true;

			column = 1;
			row++;

			if (row == MAXTEX_TARGET_TYPE)
			{// �ő�l�ɒB�������A�����𔲂���
				break;
			}
		}
	}
	//�t�@�C�������
	fclose(pFile);
}