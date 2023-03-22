//========================================
// 
// ��(3D)�֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** line3D.h ***
//========================================
#ifndef _LINE3D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _LINE3D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �\���̂̒�`
//****************************************
// ��(3D)�֘A�̊Ǘ����\����
typedef struct
{
	int nLineNum;	// �����蔻��̐��̐�
}Line3DControl;

// ��(3D)�̐ݒ���\����
typedef struct 
{
	D3DXVECTOR3 pos1;	// �_�ʒu1
	D3DXVECTOR3 pos2;	// �_�ʒu2
	Color col1;	// �_�F1
	Color col2;	// �_�F2
#if /* �ݒ�t�H�[�}�b�g */0
	// ��(3D)�̐ݒ���
	Line3DSet lineSet;
	/* �_1 */lineSet.pos1 = ;
	/* �_2 */lineSet.pos2 = ;
	/* �F1 */lineSet.col1 = ;
	/* �F2 */lineSet.col2 = ;
	// ��(3D)�̐ݒ菈��
	SetLine3D(lineSet);
#endif
}Line3DSet;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// ��(3D)�֘A�̏���������
void InitLine3D(void);
// ��(3D)�֘A�̏I������
void UninitLine3D(void);
// ��(3D)�֘A�̕`�揈��
void DrawLine3D(void);
//========== *** �擾 ***
// ��(3D)�̊Ǘ������擾
Line3DControl *GetLine3DControl(void);
//========== *** �ݒ� ***
// ��(3D)�̐ݒ菈��
void SetLine3D(Line3DSet lineSet);

#endif