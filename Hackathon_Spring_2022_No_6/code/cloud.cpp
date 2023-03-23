//=======================================================================================================
//
//�w�i�̉_����[cloud.cpp]
//Author:���V����
//
//=======================================================================================================
#include "_R.N.Lib\RNmain.h"
#include "main.h"
#include "_R.N.Lib\Basis\3D\polygon3D.h"

//�_�̍\����
typedef struct
{
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 move;		//�ړ���
	int			nTexType;	//�e�N�X�`���̎��
	bool		bUse;		//�g�p����Ă��邩
}Cloud;

//****************************************
// �}�N����`
//****************************************
#define CLOUD_WIDTH		(200.0f)//�_�̉��ʒu
#define CLOUD_HEIGHT	(50.0f)	//�_�̍��x
#define CLOUD_DEPTH		(270.0f)//�_�̉���
#define MAX_CLOUD		(13)	//�_�̍ő吔
#define CLOUD_SIZE		(50.0f)	//�_�̃T�C�Y
#define CLOUD_INTERVAL	(150.0f)//�_�̊Ԋu
#define CLOUD_ROT		(D3DXVECTOR3(D3DX_PI* 0.25f, D3DX_PI, 0.0f))
#define RETURN_WIDTH	(-325.0f)//�܂�Ԃ��n�_
#define REVIVAL_WIDTH	(325.0f)//���A�n�_
#define CLOUD_CLEAR		(150)	//�_�̓����x

//�O���[�o���ϐ��錾
Cloud		g_Cloud[MAX_CLOUD];
float fRot = 0.0f;

//========================================
// InitCloud�֐� - �������Ԃ̏��������� -
// Author:SHION HIRASAWA
//========================================
void InitCloud(void)
{
	//�_�̃|�C���^�擾
	Cloud *pCloud = &g_Cloud[0];

	for (int nCntCloud = 0; nCntCloud < MAX_CLOUD; nCntCloud++, pCloud++)
	{
		pCloud->pos = D3DXVECTOR3(CLOUD_WIDTH + (nCntCloud * CLOUD_SIZE), CLOUD_HEIGHT, CLOUD_DEPTH);
		pCloud->move = INITD3DXVECTOR3;
		pCloud->bUse = false;
		pCloud->nTexType = LoadTexture("data/TEXTURE/BG/Sky_layer03.png");

		// �|���S��(3D)�̐ݒ���
		Polygon3DSet polygon3DSet;
		polygon3DSet.nTex = pCloud->nTexType;
		polygon3DSet.nPtn = 0;
		polygon3DSet.nPtnX = 1;
		polygon3DSet.nPtnY = 1;
		polygon3DSet.fWidth = CLOUD_SIZE;
		polygon3DSet.fHeight = CLOUD_SIZE;
		polygon3DSet.pos = pCloud->pos;
		polygon3DSet.rot = CLOUD_ROT;
		polygon3DSet.col = {255, 255, 255, CLOUD_CLEAR };
		// �|���S��(3D)�̐ݒ菈��
		SetPolygon3D(polygon3DSet);
	}
}

//========================================
// UninitCloud�֐� - �������Ԃ̏I������ -
// Author:SHION HIRASAWA
//========================================
void UninitCloud(void)
{

}

//========================================
// UpdateCloud�֐� - �������Ԃ̍X�V���� -
// Author:SHION HIRASAWA
//========================================
void UpdateCloud(void)
{
	//�_�̃|�C���^�擾
	Cloud *pCloud = &g_Cloud[0];

	for (int nCntCloud = 0; nCntCloud < MAX_CLOUD; nCntCloud++, pCloud++)
	{
		pCloud->pos.x -= 0.5f;

		if (pCloud->pos.x <= RETURN_WIDTH)
		{
			pCloud->pos.x = REVIVAL_WIDTH;
		}

		// �|���S��(3D)�̐ݒ���
		Polygon3DSet polygon3DSet;
		polygon3DSet.nTex = pCloud->nTexType;
		polygon3DSet.nPtn = 0;
		polygon3DSet.nPtnX = 1;
		polygon3DSet.nPtnY = 1;
		polygon3DSet.fWidth = CLOUD_SIZE;
		polygon3DSet.fHeight = CLOUD_SIZE;
		polygon3DSet.pos = pCloud->pos;
		polygon3DSet.rot = CLOUD_ROT;
		polygon3DSet.col = { 255, 255, 255, CLOUD_CLEAR };
		// �|���S��(3D)�̐ݒ菈��
		SetPolygon3D(polygon3DSet);
	}
}