//========================================
// 
// ���[�V����(3D)�֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** motion3D.h ***
//========================================
#ifndef _MOTION3D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _MOTION3D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "parts3D.h"

//****************************************
// �}�N����`
//****************************************
// ���[�V����(3D)�̍ő吔
#define MOTION3D_MAX (16)
// ���[�V����(3D)�̃R�}���h�̍ő吔
#define MOTION3D_COMMAND_MAX (16)
// ���[�V����(3D)�̃R�}���h�̈����̍ő吔
#define MOTION3D_COMMAND_DATA_MAX (4)

//****************************************
// �񋓌^�̒�`
//****************************************
// ���[�V����(3D)�R�}���h
typedef enum
{
	MOTION3D_COMMAND_LABEL_MOVE,	// �ړ�
	MOTION3D_COMMAND_LABEL_SPIN,	// ��]
	MOTION3D_COMMAND_LABEL_MAX,
}MOTION3D_COMMAND_LABEL;

//****************************************
// �\���̂̒�`
//****************************************
// ���[�V�����R�}���h���\����
typedef struct
{
	unsigned int nTime;	// ����
	MOTION3D_COMMAND_LABEL command;	// �R�}���h�̎��
	// ����
	float aData[MOTION3D_COMMAND_DATA_MAX];
}MotionCommand;

// ���i���̃��[�V����(3D)���\����
typedef struct
{
	unsigned int nCommandNum;	// �R�}���h��
	// �R�}���h���
	MotionCommand aCommand[MOTION3D_COMMAND_MAX];
}PartsMotion3D;

// ���[�V����(3D)���\����
typedef struct
{
	int nLoopTime;	// ���[�v����
	bool bLoop;		// ���[�v���邩�t���O
	// ���i���̃��[�V�������
	PartsMotion3D aPartsMotion[PARTS_3D_MAX];
}Motion3D;

// ���[�V����(3D)�ݒ���\����
typedef struct
{
	int nMotionNum = 1;	// ���[�V������
	Motion3D aMotion[MOTION3D_MAX];	// ���[�V�����̏��
}Motion3DSet;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ���[�V����(3D)�֘A ***
// ���[�V����(3D)�ݒ���̓ǂݍ��ݏ���
void LoadMotion3DSet(FILE *pFile, Motion3DSet *pMotionSet);
// ���[�V����(3D)�̍X�V����
bool UpdateMotion3D(Motion3DSet motionSet, Parts3DInfo *pPartsInfo, Parts3DSet partsSet);
// ���[�V����(3D)�̐ݒ菈��
void SetMotion3D(Parts3DInfo *pPartsInfo);

#endif