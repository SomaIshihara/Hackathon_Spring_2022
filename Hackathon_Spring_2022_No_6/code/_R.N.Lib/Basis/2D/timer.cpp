//=======================================================================================================
//
//�������ԏ���[timer.cpp]
//Author:���V����
//
//=======================================================================================================
#include "../../RNmain.h"
#include "../../../main.h"
#include "text2D.h"
#include "timer.h"
#include "../../../Mode/md_game.h"

//****************************************
// �}�N����`
//****************************************
//�ő包��
#define MAX_DEJIT_TIMER		(256)
//�������Ԃ̌��_�ʒu
#define TIMER_ORIGIN_POS	(D3DXVECTOR3(SCREEN_WIDTH * 0.5f, 30.0f, 0.0f))
//�������Ԃ�UI�T�C�Y
#define TIMER_UI_SIZE		(60.0f)

//�O���[�o���ϐ��錾
int g_nGameTime = 0;	//��������
int g_nCounterFrame;	//�t���[���J�E���^�[
bool g_bEnd = false;

//========================================
// InitTimer�֐� - �������Ԃ̏��������� -
// Author:SHION HIRASAWA
//========================================
void InitTimer(void)
{
	//�������ԏ�����
	g_nGameTime = GAME_TIME;

	//�t���[���J�E���^�[������
	g_nCounterFrame = 0;

	//��������UI�ݒ�
	SetTimer();

	g_bEnd = false;
}

//========================================
// UninitTimer�֐� - �������Ԃ̏I������ -
// Author:SHION HIRASAWA
//========================================
void UninitTimer(void)
{

}

//========================================
// UpdateTimer�֐� - �������Ԃ̍X�V���� -
// Author:SHION HIRASAWA
//========================================
void UpdateTimer(void)
{
	if (!g_bEnd)
	{
		//1�b���o�߂���
		if (++g_nCounterFrame % 60 == 0)
		{
			//�������Ԍ���
			g_nGameTime--;

			if (g_nGameTime == 0) 
			{
				g_bEnd = true;
				SetStateMd_game(MD_GAME_STATE_RANKING);
			}
		}
	}

	//UI�ݒ�
	SetTimer();
}

//========================================
// SetTimer�֐� - �������Ԃ�UI�ݒ菈�� -
// Author:SHION HIRASAWA
//========================================
void SetTimer(void)
{
	//�\������
	int nCntDejit = 1;

	//�������ԕۑ�
	int nTempTimer = g_nGameTime;

	//�\�����錅�����v�Z����i�Œ�P��
	do
	{
		//�\�������𑝂₷
		nCntDejit++;

		//�P�����炷
		nTempTimer /= 10;

	} while (nTempTimer > 0);

	//�������Ԃ𕶎����
	char cGameTimer[MAX_DEJIT_TIMER];

	//�������Ԃ𕶎���ɒu������
	sprintf(cGameTimer, "TIME %d", g_nGameTime);

	// �e�L�X�g(2D)�̐ݒ菈��
	Text2DSet text2DSet;
	/* ������̃|�C���^ */text2DSet.pString = cGameTimer;
	/* �t�H���g�ԍ�		*/text2DSet.nFont = 1;
	/* �\���`��			*/text2DSet.disp = TEXT_DISP_CENTER;
	/* �ʒu				*/text2DSet.pos = TIMER_ORIGIN_POS;
	/* ����				*/text2DSet.rot = INITD3DXVECTOR3;
	/* �F				*/text2DSet.col = INITCOLOR;
	/* ��				*/text2DSet.fWidth = TIMER_UI_SIZE;
	/* ����				*/text2DSet.fHeight = TIMER_UI_SIZE;
	/* �J�������킹		*/text2DSet.bMatchCamera = false;
	// �e�L�X�g(2D)�̐ݒ菈��
	SetText2D(text2DSet);
}