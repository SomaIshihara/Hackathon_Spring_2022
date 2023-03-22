//========================================
// 
// �}�b�v�`�b�v(3D)�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** map-chip3D.h ***
//========================================
#ifndef _MAPCHIP3D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _MAPCHIP3D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "motion3D.h"

//****************************************
// �}�N����`
//****************************************
// �}�b�v�`�b�v(3D)�̍ő吔
#define MAPCHIP3D_MAX (1024)
// �}�b�v�`�b�v(3D)�̎�ނ̍ő吔
#define MAPCHIP3D_TYPE_MAX (64)
// �}�b�v�`�b�v(3D)�̎�ނ̒��̎�ނ̍ő吔
#define MAPCHIP3D_SUBTYPE_MAX (4)

//****************************************
// �\���̂̒�`
//****************************************
// �}�b�v�`�b�v(3D)�̏��\����
typedef struct
{
	// ���ފ֘A
	int nType;		// ���
	int nSubType;	// ��ނ̒��̎��

	// ��Ԋ֘A
	bool bUse;	// �g�p����Ă���t���O

	// ���i�֘A
	Parts3DInfo partsInfo;	// ���i�Ǘ�
}MapChip3D;

// �}�b�v�`�b�v(3D)�̊Ǘ����\����
typedef struct
{
	// �}�b�v�`�b�v(3D)�̎�ޖ��̎�ސ�
	int aSubTypeNum[MAPCHIP3D_TYPE_MAX];
	// �}�b�v�`�b�v(3D)�̃p�X
	char aMapChipPath[MAPCHIP3D_TYPE_MAX][TXT_MAX];
}MapChip3DControl;

// �}�b�v�`�b�v(3D)�̎�ޖ��̏��\����
typedef struct
{
	int nSetUp = -1;	// ���f���̃Z�b�g�A�b�v�ԍ�
}MapChip3DType;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// �}�b�v�`�b�v(3D)�̏���������
void InitMapChip3D(void);
// �}�b�v�`�b�v(3D)�̏I������
void UninitMapChip3D(void);
// �}�b�v�`�b�v(3D)�̍X�V����
void UpdateMapChip3D(void);
// �}�b�v�`�b�v(3D)�̕`�揈��
void DrawMapChip3D(void);
//========== *** �`�� ***
// �}�b�v�`�b�v(3D)�̕\���`�揈��
void RenderMapChip3D(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nSubType, Color col);
//========== *** ���o�� ***
// �}�b�v�`�b�v(3D)���X�g�̓ǂݍ��ݏ���
void LoadMapChip3DList(void);
//========== *** �擾 ***
// �}�b�v�`�b�v(3D)�̏����擾
MapChip3D *GetMapChip3D(void);
// �}�b�v�`�b�v(3D)�̊Ǘ������擾
MapChip3DControl *GetMapChip3DControl(void);
// �}�b�v�`�b�v(3D)�̎�ޖ��̏����擾
MapChip3DType *GetMapChip3DType(void);
//========== *** �ݒ� ***
// �}�b�v�`�b�v(3D)�̐ݒ菈��
void SetMapChip3D(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType, int nSubType);
//========== *** ��� ***
// �}�b�v�`�b�v(3D)�̃N���A����
void ClearMapChip3D(void);

#endif