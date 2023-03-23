//=======================================================================================================
//
//�X�R�AUI����[score.cpp]
//Author:���V����
//
//=======================================================================================================
#include "../../RNmain.h"
#include "../../../main.h"
#include "../../../chr_player.h"
#include "text2D.h"
#include "score.h"

//****************************************
// �}�N����`
//****************************************
//UI�T�C�Y
#define SCORE_NAME_SIZE		(32.0f)
#define SCORE_DEJIT_SIZE	(64.0f)
//UI�ʒu
#define SCORE_NAME_POS		(D3DXVECTOR3(1100.0f, 630.0f, 0.0f))
#define SCORE_DEJIT_POS		(D3DXVECTOR3(1100.0f, 680.0f, 0.0f))
//�\������UI�̕�����
#define SCORE_DEJIT_NUM_TXT	(6)

//========================================
// SetScoreUI�֐� - �����u�[����������UI�ݒ菈�� -
// Author:SHION HIRASAWA
//========================================
void SetScoreUI(void)
{
	// �e�L�X�g(2D)�̐ݒ菈��
	Text2DSet text2DSet[2];

	//************************************
	//			"SCORE" ��\��
	//************************************
	/* ������̃|�C���^ */text2DSet[0].pString = "SCORE";
	/* �t�H���g�ԍ�		*/text2DSet[0].nFont = 0;
	/* �\���`��			*/text2DSet[0].disp = TEXT_DISP_RIGHT;
	/* �ʒu				*/text2DSet[0].pos = SCORE_NAME_POS;
	/* ����				*/text2DSet[0].rot = INITD3DXVECTOR3;
	/* �F				*/text2DSet[0].col = INITCOLOR;
	/* ��				*/text2DSet[0].fWidth = SCORE_NAME_SIZE;
	/* ����				*/text2DSet[0].fHeight = SCORE_NAME_SIZE;
	/* �J�������킹		*/text2DSet[0].bMatchCamera = false;

	//************************************
	//		�v���C���[�̃X�R�A ��\��
	//************************************
	//�v���C���[�̃X�R�A�𕶎����
	char c_nScoreUI[SCORE_DEJIT_NUM_TXT];

	//�v���C���[�̃X�R�A�𕶎���ɒu������
	snprintf(c_nScoreUI, SCORE_DEJIT_NUM_TXT, "%d", GetChr_player()->nScore);

	/* ������̃|�C���^ */text2DSet[1].pString = c_nScoreUI;
	/* �t�H���g�ԍ�		*/text2DSet[1].nFont = 1;
	/* �\���`��			*/text2DSet[1].disp = TEXT_DISP_CENTER;
	/* �ʒu				*/text2DSet[1].pos = SCORE_DEJIT_POS;
	/* ����				*/text2DSet[1].rot = INITD3DXVECTOR3;
	/* �F				*/text2DSet[1].col = INITCOLOR;
	/* ��				*/text2DSet[1].fWidth = SCORE_DEJIT_SIZE;
	/* ����				*/text2DSet[1].fHeight = SCORE_DEJIT_SIZE;
	/* �J�������킹		*/text2DSet[1].bMatchCamera = false;

	for (int nCntScore = 0; nCntScore < 2; nCntScore++)
	{
		// �e�L�X�g(2D)�̐ݒ菈��
		SetText2D(text2DSet[nCntScore]);
	}
}