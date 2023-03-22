//========================================
// 
// �}�b�v����(3D)�̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** map-generator3D.h ***
//========================================
#ifndef _MAPGENERATOR3D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _MAPGENERATOR3D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

// R.N.Lib
#include "map-chip3D.h"

//****************************************
// �\���̂̒�`
//****************************************
//========== *** �}�b�v��� ***
// �}�b�v�`�b�v(3D)�ݒ���\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu
	D3DXVECTOR3 rot;	// ����
	int nType;			// ���
}Obj3DSet;

// �}�b�v�ݒ���\����
typedef struct
{
	// �}�b�v�`�b�v(3D)�ݒ���
	Obj3DSet aObj3DSet[MAPCHIP3D_MAX];
	int nObj3DNum;	// �}�b�v�`�b�v(3D)�̐ݒ萔
}MapSet3D;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �|�C���^�擾 ***
// �}�b�v���̃|�C���^�擾
MapSet3D *GetMapSet(void);
//========== *** �擾 ***
// �}�b�v�ݒ���̃p�����[�^�[�����l��Ԃ�
MapSet3D InitParameterMapSet3D(void);
//========== *** ���o�� ***
// �}�b�v���̓ǂݍ��ݏ���
void LoadMapData(char *pPath);
// �}�b�v���̏������ݏ���
void SaveMapData(char *pPath);

#endif