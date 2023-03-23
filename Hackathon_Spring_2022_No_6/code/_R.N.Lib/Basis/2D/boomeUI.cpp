//=======================================================================================================
//
//�u�[�������̏�����UI����[boomerangUI.h]
//Author:���V����
//
//=======================================================================================================
#include "../../RNmain.h"
#include "../../../main.h"
#include "../../../chr_player.h"
#include "text2D.h"
#include "boomeUI.h"

//****************************************
// �}�N����`
//****************************************
//UI�T�C�Y
#define BOOME_UI_SIZE		(60.0f)
//UI�ʒu
#define BOOME_UI_POS		(D3DXVECTOR3(100.0f, 30.0f, 0.0f))
//�\������UI�̕�����
#define BOOME_UI_NUM_TXT	(5)

//========================================
// SetBoomeUI�֐� - �����u�[����������UI�ݒ菈�� -
// Author:SHION HIRASAWA
//========================================
void SetBoomeUI(void)
{
	//�����u�[���������𕶎����
	char cBoomeUI[BOOME_UI_NUM_TXT];

	//�����u�[���������𕶎���ɒu������
	snprintf(cBoomeUI, BOOME_UI_NUM_TXT, "! *%d", GetChr_player()->nBoomerang);

	// �e�L�X�g(2D)�̐ݒ菈��
	Text2DSet text2DSet;
	/* ������̃|�C���^ */text2DSet.pString = cBoomeUI;
	/* �t�H���g�ԍ�		*/text2DSet.nFont = 1;
	/* �\���`��			*/text2DSet.disp = TEXT_DISP_CENTER;
	/* �ʒu				*/text2DSet.pos = BOOME_UI_POS;
	/* ����				*/text2DSet.rot = INITD3DXVECTOR3;
	/* �F				*/text2DSet.col = INITCOLOR;
	/* ��				*/text2DSet.fWidth = BOOME_UI_SIZE;
	/* ����				*/text2DSet.fHeight = BOOME_UI_SIZE;
	/* �J�������킹		*/text2DSet.bMatchCamera = false;
	// �e�L�X�g(2D)�̐ݒ菈��
	SetText2D(text2DSet);
}