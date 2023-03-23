//==========================================
//
//�v���C���[�v���O����[player.cpp]
//Author:�Ό��D�n  �i�e�֌W�F���V�����j
//
//==========================================
#include "main.h"
#include "_R.N.Lib\R.N.Lib.h"
#include "boomerang.h"

//�}�N��
#define BOOMERANG_SETUP_NUM		(2)		//�u�[�������Z�b�g�A�b�v�ԍ�
#define BOOMERANG_ONE_ROTATE	(15)	//�u�[��������1������̂ɂ�����t���[�����i2PI�Ŋ���j
#define BOOMERANG_THROW_ROT		(0.12f * D3DX_PI)	//�u�[�������𓊂���p�x
#define BOOMERANG_THROW_LENGTH	(300.0f)//�u�[�������̉�钆�S�ƃv���C���[�̋���
#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//�p�x��-PI~PI�ɏC��

//�O���[�o��
Boomerang g_aBoomerang[MAX_USE_BOOMERANG] = {};

//========================
//����������
//========================
void InitBoomerang(void)
{
	//�ϐ�������
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_BOOMERANG; nCntBoomerang++)
	{
		//�ϐ�������
		g_aBoomerang[nCntBoomerang].posOld = g_aBoomerang[nCntBoomerang].pos = INITD3DXVECTOR3;
		g_aBoomerang[nCntBoomerang].move = INITD3DXVECTOR3;
		g_aBoomerang[nCntBoomerang].rot = INITD3DXVECTOR3;

		// ���i(3D)�̏���������
		InitParts3DInfo(&g_aBoomerang[nCntBoomerang].partsInfo, BOOMERANG_SETUP_NUM);

		//�g�p�L��������
		g_aBoomerang[nCntBoomerang].bUse = false;
	}
}

//========================
//�I������
//========================
void UninitBoomerang(void)
{
	
}

//========================
//�X�V����
//========================
void UpdateBoomerang(void)
{
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_BOOMERANG; nCntBoomerang++)
	{
		if (g_aBoomerang[nCntBoomerang].bUse == true)
		{
			//[����]

			//[����]�u�[�������ƃI�u�W�F�N�g�̓����蔻��
			CollisionInfo collInfo;
			collInfo.pPos = &g_aBoomerang[nCntBoomerang].pos;
			collInfo.posOld;
			collInfo.pRot;
			collInfo.rotOld;
			collInfo.fScale = 1.0f;
			collInfo.mode = COLLCHK_MODE_NORMAL;
			collInfo.pMove = NULL;
			collInfo.pHitTest = &GetModelSetUp(BOOMERANG_SETUP_NUM).hitTestSet.aHitTest[0];



			//[������]�u�[�������̉�]����
			g_aBoomerang[nCntBoomerang].partsInfo.rot.y = FIX_ROT(g_aBoomerang[nCntBoomerang].rot.y + ((2 * D3DX_PI) / BOOMERANG_ONE_ROTATE));

			// ���i(3D)�̍X�V����
			UpdateParts3DInfo(&g_aBoomerang[nCntBoomerang].partsInfo);
		}
	}
}

//========================
//�`�揈��
//========================
void DrawBoomerang(void)
{
	
}

//========================
//�u�[�������z�u����
//========================
void SetBoomerang(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_BOOMERANG; nCntBoomerang++)
	{
		//�g�p����Ă��Ȃ����m�F
		if (g_aBoomerang[nCntBoomerang].bUse == false)
		{
			//�ϐ�������
			g_aBoomerang[nCntBoomerang].posOld = g_aBoomerang[nCntBoomerang].pos = pos;
			g_aBoomerang[nCntBoomerang].move = INITD3DXVECTOR3;
			g_aBoomerang[nCntBoomerang].rot = INITD3DXVECTOR3;

			//�v�Z
			//g_aBoomerang[nCntBoomerang].posCenter.x = 

			// ���i(3D)�̏���������
			InitParts3DInfo(&g_aBoomerang[nCntBoomerang].partsInfo, BOOMERANG_SETUP_NUM);

			//�g�p���Ă����Ԃɂ���
			g_aBoomerang[nCntBoomerang].bUse = true;

			//�z�u�I��
			break;
		}
	}
}

//========================
//�u�[���������擾����
//========================
Boomerang *GetBoomerang(void)
{
	return &g_aBoomerang[0];
}