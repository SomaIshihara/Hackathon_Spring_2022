//=======================================================================================================
//
//�u�[�������̏�����UI����[boomerangUI.cpp]
//Author:���V���� �Ό��D�n
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
#define BOOME_UI_POS		(D3DXVECTOR3(100.0f, 680.0f, 0.0f))
//�\������UI�̕�����
#define BOOME_UI_NUM_TXT	(5)
//�Ԃ��甒�ɖ߂����x
#define BOOME_UI_AFTERLOST	(5)

//****************************************
// �O���[�o���ϐ�
//****************************************
int g_nAfterLostColor = 255;

//========================================
// SetBoomeUI�֐� - �����u�[����������UI�ݒ菈�� -
// Author:SHION HIRASAWA
//========================================
void SetBoomeUI(void)
{
	//�����u�[���������𕶎����
	char cBoomeUI[BOOME_UI_NUM_TXT];

	//�Ԃ��珙�X�ɔ��ɖ߂�
	g_nAfterLostColor += BOOME_UI_AFTERLOST;
	if (g_nAfterLostColor > 255)
	{
		g_nAfterLostColor = 255;
	}

	//�����u�[���������𕶎���ɒu������
	snprintf(cBoomeUI, BOOME_UI_NUM_TXT, "! *%d", GetChr_player()->nBoomerang);

	// �e�L�X�g(2D)�̐ݒ菈��
	Text2DSet text2DSet;
	/* ������̃|�C���^ */text2DSet.pString = cBoomeUI;
	/* �t�H���g�ԍ�		*/text2DSet.nFont = 1;
	/* �\���`��			*/text2DSet.disp = TEXT_DISP_CENTER;
	/* �ʒu				*/text2DSet.pos = BOOME_UI_POS;
	/* ����				*/text2DSet.rot = INITD3DXVECTOR3;
	/* �F				*/text2DSet.col = Color{ 255,g_nAfterLostColor,g_nAfterLostColor,255 };
	/* ��				*/text2DSet.fWidth = BOOME_UI_SIZE;
	/* ����				*/text2DSet.fHeight = BOOME_UI_SIZE;
	/* �J�������킹		*/text2DSet.bMatchCamera = false;
	// �e�L�X�g(2D)�̐ݒ菈��
	SetText2D(text2DSet);
}

//========================================
// InitBoomeUI�֐� - �u�[������UI�̏��������� -
// Author:ISHIHARA SOMA
//========================================
void InitBoomeUI(void)
{
	g_nAfterLostColor = 255;
}

//========================================
// LostBoomeUI�֐� - �Ԃ����鏈�� -
// Author:ISHIHARA SOMA
//========================================
void LostBoomeUI(void)
{
	g_nAfterLostColor = 0;
}