//========================================
// 
// ���f���̃Z�b�g�A�b�v�֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** model-setup.h ***
//========================================
#ifndef _MODELSETUP_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _MODELSETUP_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "model.h"
#include "motion3D.h"
#include "../Other/physics.h"

//****************************************
// �}�N����`
//****************************************

//****************************************
// �\���̂̒�`
//****************************************
// ���f���̃Z�b�g�A�b�v�̓ǂݍ��ݏ��\����
typedef struct
{
	char *pModelSetUpPath;	// ���f���̃Z�b�g�A�b�v�̃p�X
	bool bReload = false;	// �ēǂݍ��݃t���O
#if /* �ݒ�t�H�[�}�b�g   */0
	// ���f���̃Z�b�g�A�b�v�̓ǂݍ��ݏ��
	ModelSetUpLoad modelSetUpLoad;
	/* �Z�b�g�A�b�v�̃p�X */modelSetUpLoad.pModelSetUpPath = ;
	/* �ēǂݍ��݃t���O   */modelSetUpLoad.bReload = ;
	// ���f���̃Z�b�g�A�b�v��ǂݍ���
	 = LoadModelSetUp(modelSetUpLoad);
#endif
}ModelSetUpLoad;

// ���f���̃Z�b�g�A�b�v���\����
typedef struct 
{
	Parts3DSet partsSet;	// ���i�ݒ���(3D)
	HitTestSet hitTestSet;	// �����蔻��ݒ���
	Motion3DSet motionSet;	// ���[�V�����ݒ���
}ModelSetUp;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ���o�� ***
// ���f���̃Z�b�g�A�b�v�̓ǂݍ��ݏ���
int LoadModelSetUp(ModelSetUpLoad modelSetUpLoad);
// ���f���̃Z�b�g�A�b�v���X�g�̓ǂݍ��ݏ���
void LoadModelSetUpList(void);
//========== *** �擾 ***
// ���f���̃Z�b�g�A�b�v�����擾
ModelSetUp GetModelSetUp(int nSetUp);

#endif