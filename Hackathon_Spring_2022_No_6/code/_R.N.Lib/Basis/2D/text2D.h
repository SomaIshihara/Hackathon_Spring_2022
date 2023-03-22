//========================================
// 
// �e�L�X�g(2D)�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// *** text2D.h ***
//========================================
#ifndef _TEXT2D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _TEXT2D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "../Graphic/text.h"

//****************************************
// �\���̂̒�`
//****************************************
// �e�L�X�g(2D)�̐ݒ���
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
	bool bMatchCamera = false;	// �J�������킹�t���O
#if /* �ݒ�t�H�[�}�b�g */0
	// �e�L�X�g(2D)�̐ݒ菈��
	Text2DSet text2DSet;
	/* ������̃|�C���^ */text2DSet.*pString = ;
	/* �t�H���g�ԍ�		*/text2DSet.nFont = ;
	/* �\���`��			*/text2DSet.disp = ;
	/* �ʒu				*/text2DSet.pos = ;
	/* ����				*/text2DSet.rot = ;
	/* �F				*/text2DSet.col = ;
	/* ��				*/text2DSet.fWidth = ;
	/* ����				*/text2DSet.fHeight = ;
	/* �J�������킹		*/text2DSet.bMatchCamera = ;
	// �e�L�X�g(2D)�̐ݒ菈��
	SetText2D(text2DSet);
#endif
}Text2DSet;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �ݒ� ***
// �e�L�X�g(2D)�̐ݒ菈��
void SetText2D(Text2DSet text2DSet);

#endif