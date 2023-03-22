//========================================
// 
// �`��(3D)�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** draw3D.cpp ***
//========================================
#include "assert.h"
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
// �`��3D�I�u�W�F�N�g�̍ő吔
#define DRAW3D_MAX (MODEL_MAX+POLYGON3D_MAX)
// ���፷�ɂ��X�R�A
#define VERTICAL_INTERVAL_SCORE (10)

//****************************************
// �񋓌^�̒�`
//****************************************
// �`��3D�I�u�W�F�N�g�̎��
typedef enum 
{
	DRAW3D_TYPE_MODEL,
	DRAW3D_TYPE_POLYGON,
	DRAW3D_TYPE_MAX,
}DRAW3D_TYPE;

//****************************************
// �\���̂̒�`
//****************************************
// �`��3D�I�u�W�F�N�g�̏��\����
typedef struct
{
	DRAW3D_TYPE type;	// ���
	unsigned int nIdx;	// �ԍ�
	float fDistance;	// ����
}draw3D;

//****************************************
// �O���[�o���ϐ��錾
//****************************************
// �`��3D�I�u�W�F�N�g�̏��
static draw3D g_aDraw3D[DRAW3D_MAX];
// �`��3D�I�u�W�F�N�g�̐�
static unsigned int g_nDraw3DNum = 0;

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
// SortDraw3D�֐� - �`�悷��3D�I�u�W�F�N�g�̃\�[�g���� -
// Author:RIKU NISHIMURA
//========================================
void SortDraw3D(void)
{
	// ���_�ʒu
	D3DXVECTOR3 posV = GetCamera3D()->posV;

	// �`��3D�I�u�W�F�N�g�̐���������
	g_nDraw3DNum = 0;

	for (int nCntModel = 0; nCntModel < GetModelInfo()->nModelSetNum; nCntModel++)
	{
		D3DXVECTOR3 modelPos = ConvMatrixToPos(GetModelInfo()->aModelSet[nCntModel].mtx);
		// ���_�ʒu���烂�f���̈ʒu�܂ł̋����𑪂�
		g_aDraw3D[g_nDraw3DNum].fDistance = 
			FindDistanceLookDown(posV, modelPos)
			+ (fabsf(posV.y - modelPos.y) * VERTICAL_INTERVAL_SCORE);
		// �ԍ����w��
		g_aDraw3D[g_nDraw3DNum].nIdx = nCntModel;
		// ��ނ��w��
		g_aDraw3D[g_nDraw3DNum].type = DRAW3D_TYPE_MODEL;
		g_nDraw3DNum++;	// �`�搔�J�E���g�����Z
	}

	for (int nCntPoly = 0; nCntPoly < GetPolygon3DControl()->nPolygonNum; nCntPoly++)
	{
		// ���_�ʒu���烂�f���̈ʒu�܂ł̋����𑪂�
		g_aDraw3D[g_nDraw3DNum].fDistance =
			FindDistanceLookDown(posV, GetPolygon3DControl()->aPolySet[nCntPoly].pos)
			+ (fabsf(posV.y - GetPolygon3DControl()->aPolySet[nCntPoly].pos.y) * VERTICAL_INTERVAL_SCORE);
		// �ԍ����w��
		g_aDraw3D[g_nDraw3DNum].nIdx = nCntPoly;
		// ��ނ��w��
		g_aDraw3D[g_nDraw3DNum].type = DRAW3D_TYPE_POLYGON;
		g_nDraw3DNum++;	// �`�搔�J�E���g�����Z
	}

	if (g_nDraw3DNum == 0) 
	{// �`�搔�J�E���g��0�̎��A�������I��
		return;
	}

	draw3D draw;		// �ꎞ�I�ɒl���i�[
	int nTempCnt = 0;	// �J�E���g���i�[

	for (int nCntCompare1 = 0; nCntCompare1 < g_nDraw3DNum - 1; nCntCompare1++)
	{
		// �擪�̗v�f���ő�l�Ƃ��ċL��
		draw = g_aDraw3D[nCntCompare1];

		for (int nCntCompare2 = nCntCompare1 + 1; nCntCompare2 < g_nDraw3DNum; nCntCompare2++)
		{
			if (g_aDraw3D[nCntCompare2].fDistance > draw.fDistance)
			{// �v�f�̒l���ő�l�������Ă������A
				// �l���L��
				draw = g_aDraw3D[nCntCompare2];
				// �J�E���g���L��
				nTempCnt = nCntCompare2;
			}
		}

		if (g_aDraw3D[nCntCompare1].fDistance < draw.fDistance)
		{// �ő�l���擪�̗v�f�̒l�������Ă������A
			// �l�����ւ���
			g_aDraw3D[nTempCnt] = g_aDraw3D[nCntCompare1];
			g_aDraw3D[nCntCompare1] = draw;
		}
	}
}

//========================================
// Draw3D�֐� - 3D�I�u�W�F�N�g�̕`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void Draw3D(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	for (int nCnt3D = 0; nCnt3D < g_nDraw3DNum; nCnt3D++) 
	{
		// �`��3D�I�u�W�F�N�g�̏��
		draw3D draw3D = g_aDraw3D[nCnt3D];

		switch (draw3D.type) 
		{
		case DRAW3D_TYPE_MODEL:
			DrawSingleModel(pDevice, draw3D.nIdx);
			break;
		case DRAW3D_TYPE_POLYGON:
			DrawSinglePolygon3D(pDevice, draw3D.nIdx);
			break;
		}
	}
}
#endif
#endif