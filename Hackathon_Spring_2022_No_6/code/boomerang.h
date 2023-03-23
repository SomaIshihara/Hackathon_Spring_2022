//==========================================
//
//�u�[�������v���O�����̃w�b�_[player.h]
//Author:�Ό��D�n
//
//==========================================
#ifndef _BOOMERANG_H_
#define _BOOMERANG_H_

#include "main.h"

//�}�N��
#define MAX_USE_BOOMERANG		(3)		//�u�[�������̎g�p��
#define BOOMERANG_HIT_RADIUS	(4.0f)	//�u�[�������̓����蔻��̔��a

//����������
typedef enum
{
	THROWTYPE_LEFT = 0,
	THROWTYPE_RIGHT,
	THROWTYPE_MAX
} THROWTYPE;

//�v���C���[�\����
struct Boomerang
{
	//�ʒu��
	D3DXVECTOR3 pos;		//�ʒu
	D3DXVECTOR3 posOld;		//�O��̈ʒu
	D3DXVECTOR3 rot;		//����
	float fRotTotal;		//��]������
	D3DXVECTOR3 move;		//�ړ���
	int nCounterStraight;	//�����ړ����ԃJ�E���^
	float fRotForce;		//��]��
	bool bEndRotate;		//��]�͂�������̂��I�����邩
	bool bReturn;			//���˕Ԃ�t���O
	THROWTYPE throwType;	//��������

	//�`���
	D3DXMATRIX mtxWorld;	//���[���h�}�g��
	bool bUse;				//�u�[�������g�p�̗L��

	Parts3DInfo partsInfo;	// ���i(3D)�̏��
	Collision coll;			// �����蔻��̌���
};

//�v���g�^�C�v�錾
void InitBoomerang(void);
void UninitBoomerang(void);
void UpdateBoomerang(void);
void DrawBoomerang(void);
void SetBoomerang(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Boomerang *GetBoomerang(void);

#endif // !_BOOMERANG_H_
