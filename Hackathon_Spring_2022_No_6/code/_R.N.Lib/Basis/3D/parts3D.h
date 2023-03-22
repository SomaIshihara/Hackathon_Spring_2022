//========================================
// 
// ���i(3D)�֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** parts3D.h ***
//========================================
#ifndef _PARTS3D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _PARTS3D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �}�N����`
//****************************************
// �}�e���A��(3D)�̏��
#define MATERIAL_3D_MAX (16)
// ���i(3D)�̍ő吔
#define PARTS_3D_MAX (16)

//****************************************
// �\���̂̒�`
//****************************************
// ���i(3D)�\����
typedef struct
{
	// �ʒu�֘A
	D3DXVECTOR3 posResult;	// �ʒu(����)
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rotResult;	// ����(����)
	D3DXVECTOR3 rot;		// ����

	// ���[�V�����֘A
	bool bPosAnim;			// �ʒu�A�j���[�V�����t���O
	int nCounterPosAnim;	// �ʒu�A�j���[�V�����J�E���^�[
	int nPosAnimTime;		// �ʒu�A�j���[�V�����ɂ����鎞��
	D3DXVECTOR3 posOld;		// ���̈ʒu
	D3DXVECTOR3 targetPos;	// �ڕW�ʒu
	bool bRotAnim;			// �p�x�A�j���[�V�����t���O
	int nCounterRotAnim;	// �p�x�A�j���[�V�����J�E���^�[
	int nRotAnimTime;		// �p�x�A�j���[�V�����ɂ����鎞��
	D3DXVECTOR3 rotOld;		// ���̊p�x
	D3DXVECTOR3 targetRot;	// �ڕW�p�x
}Parts3D;

// ���i(3D)�Ǘ��\����
typedef struct
{
	D3DXVECTOR3 pos;	// �ʒu(�{��)
	D3DXVECTOR3 rot;	// ����(�{��)
	bool bStop;			// ��~�t���O
	int nModelSetUp;	// ���f���̃Z�b�g�A�b�v�ԍ�
	int nMotion;		// ���[�V�����ԍ�
	int nMotionOld;		// ���[�V�����ԍ�(�ߋ�)
	int nCounterMotion;	// ���[�V�����J�E���^�[
	Color col;			// �F
	// ���i���
	Parts3D aParts[PARTS_3D_MAX];
#if /* �ݒ�t�H�[�}�b�g */0
	// ���i(3D)�Ǘ����
	Parts3DInfo parts3DInfo;
	InitParts3DInfo(&parts3DInfo, );
	/* �ʒu */parts3DInfo.pos = ;
	/* ���� */parts3DInfo.rot = ;
	/* ��~ */parts3DInfo.bStop = ;
	/* �F   */parts3DInfo.col = ;
	// ���i(3D)�̍X�V����
	UpdateParts3DInfo(&parts3DInfo);
#endif
}Parts3DInfo;

// ���i(3D)�̎�ޖ��̏��\����
typedef struct
{
	// �ǂݍ��ݏ��
	int nModelIdx;	// ���f���̔ԍ�
	int nParent;	// �e�ԍ�
	D3DXVECTOR3 fixedRelativePos;	// �Œ�̑��Έʒu
	D3DXVECTOR3 fixedRelativeRot;	// �Œ�̑��Ίp�x
	D3DXVECTOR3 rotRelativePos;		// ��]���̑��Έʒu
}Parts3DType;

// ���i�ݒ���\����
typedef struct
{
	float fScale;	// �g��{��
	int nPartsNum;	// ���i��
	// ���i�̎�ޖ��̏��
	Parts3DType aPartsType[PARTS_3D_MAX];
}Parts3DSet;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ���i(3D)�֘A ***
// ���i�ݒ���(3D)�̓ǂݍ��ݏ���
void LoadParts3DSet(FILE *pFile, Parts3DSet *pPartsSet);
// ���i(3D)�̏���������
void InitParts3DInfo(Parts3DInfo *pPartsInfo, int nModelSetUp);
// ���i(3D)�̍X�V����
void UpdateParts3DInfo(Parts3DInfo *pPartsInfo);
// ���i(3D)�̃}�g���b�N�X���擾
D3DXMATRIX GetMatrixParts3D(int nParts, D3DXVECTOR3 pos, D3DXVECTOR3 rot, Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet);

#endif