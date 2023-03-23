//==========================================
//
//�v���C���[�v���O�����̃w�b�_[player.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _BOOMERANG_H_
#define _BOOMERANG_H_

#include "main.h"

//�v���C���[�\����
struct Boomerang
{
	//�ʒu��
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 move;		//�ړ���
	D3DXVECTOR3 rot;		//����

	//�`���
	D3DXMATRIX mtxWorld;	//���[���h�}�g��
	bool bUse;		//�v���C���[�g�p�̗L��
};

//�v���g�^�C�v�錾
void InitBoomerang(void);
void UninitBoomerang(void);
void UpdateBoomerang(void);
void DrawBoomerang(void);
Boomerang *GetBoomerang(void);

#endif // !_BOOMERANG_H_
