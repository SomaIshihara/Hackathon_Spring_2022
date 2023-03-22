//========================================
// 
// �e�L�X�g(3D)�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// *** text3D.h ***
//========================================
#ifndef _TEXT3D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _TEXT3D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "../Graphic/text.h"

//****************************************
// �\���̂̒�`
//****************************************
// �e�L�X�g(3D)�̐ݒ���
typedef struct 
{
	char *pString = NULL;	// ������̃|�C���^
	int nFont = 0;			// �t�H���g�ԍ�
	TEXT_DISP disp = TEXT_DISP_CENTER;	// �\���`��
	D3DXVECTOR3 pos = INITD3DXVECTOR3;	// �ʒu
	D3DXVECTOR3 rot = INITD3DXVECTOR3;	// ����
	Color col = INITCOLOR;	// �F
	float fWidth = 0.0f;	// ��
	float fHeight = 0.0f;	// ����
	bool bZtest = false;		// Z�e�X�g�t���O
	bool bLighting = false;		// ���C�e�B���O�t���O
	bool bBillboard = false;	// �r���{�[�h�t���O
#if /* �ݒ�t�H�[�}�b�g */0
	// �e�L�X�g(3D)�̐ݒ菈��
	Text3DSet text3DSet;
	/* ������̃|�C���^ */text3DSet.*pString = ;
	/* �t�H���g�ԍ�		*/text3DSet.nFont = ;
	/* �\���`��			*/text3DSet.disp = ;
	/* �ʒu				*/text3DSet.pos = ;
	/* ����				*/text3DSet.rot = ;
	/* �F				*/text3DSet.col = ;
	/* ��				*/text3DSet.fWidth = ;
	/* ����				*/text3DSet.fHeight = ;
	/* Z�e�X�g			*/text3DSet.bZtest = ;
	/* ���C�e�B���O		*/text3DSet.bLighting = ;
	/* �r���{�[�h		*/text3DSet.bBillboard = ;
	// �e�L�X�g(3D)�̐ݒ菈��
	SetText3D(text3DSet);
#endif
}Text3DSet;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �ݒ� ***
// �e�L�X�g(3D)�̐ݒ菈��
void SetText3D(Text3DSet text3DSet);

#endif