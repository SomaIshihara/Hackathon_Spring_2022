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
	/* ������̃|�C���^ */char *pString = NULL;
	/* �t�H���g�ԍ�		*/int nFont = 0;
	/* �\���`��			*/TEXT_DISP disp = TEXT_DISP_CENTER;
	/* �ʒu				*/D3DXVECTOR3 pos = INITD3DXVECTOR3;
	/* ����				*/D3DXVECTOR3 rot = INITD3DXVECTOR3;
	/* �F				*/Color col = INITCOLOR;
	/* ��				*/float fWidth = 0.0f;
	/* ����				*/float fHeight = 0.0f;
	/* �J�������킹		*/bool bMatchCamera = false;
}Text2DSet;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �ݒ� ***
// �e�L�X�g(2D)�̐ݒ菈��
void SetText2D(Text2DSet text2DSet);

#endif