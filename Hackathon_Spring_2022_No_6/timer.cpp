//=======================================================================================================
//
//�������ԏ���[timer.cpp]
//Author:���V����
//
//=======================================================================================================
#include "code\_R.N.Lib\RNmain.h"
#include "timer.h"
#include "code\_R.N.Lib\Basis\2D\text2D.h"

//****************************************
// �}�N����`
//****************************************
//�������Ԃ̌��_�ʒu
#define TIMER_ORIGIN_POS	(D3DXVECTOR3(0.0f, 60.0f, 0.0f))
//�������Ԃ�UI�T�C�Y
#define TIMER_UI_SIZE		(60.0f)
#define TIMER_UI_WIDTH		(40.0f)
#define TIMER_UI_HEIGHT		(60.0f)

//�O���[�o���ϐ��錾
int g_nGameTime = 0;	//��������
int g_nCounterFrame;	//�t���[���J�E���^�[

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
	//1�b���o�߂���
	if (++g_nCounterFrame % 60 == 0)
	{
		//�������Ԍ���
		g_nGameTime--;

		//UI�ݒ�
		SetTimer();
	}
}

//========================================
// SetTimer�֐� - �������Ԃ�UI�ݒ菈�� -
// Author:SHION HIRASAWA
//========================================
void SetTimer(void)
{
	//�\������
	int nCntDejit = 0;

	//�������ԕۑ�
	int nTempTimer = g_nGameTime;

	//�\�����錅�����v�Z����i�Œ�P��
	do
	{
		//�P�����炷
		nTempTimer /= 10;

		//�\�������𑝂₷
		nCntDejit++;

	} while (nTempTimer >= 0);

	// �e�L�X�g(2D)�̐ݒ菈��
	Text2DSet text2DSet;
	/* ������̃|�C���^ */snprintf(text2DSet.pString, nCntDejit, "%d", g_nGameTime);
	/* �t�H���g�ԍ�		*/text2DSet.nFont = 1;
	/* �\���`��			*/text2DSet.disp = TEXT_DISP_CENTER;
	/* �ʒu				*/text2DSet.pos = TIMER_ORIGIN_POS;
	/* ����				*/text2DSet.rot = INITD3DXVECTOR3;
	/* �F				*/text2DSet.col = INITCOLOR;
	/* ��				*/text2DSet.fWidth = TIMER_UI_WIDTH;
	/* ����				*/text2DSet.fHeight = TIMER_UI_HEIGHT;
	/* �J�������킹		*/text2DSet.bMatchCamera = false;
	// �e�L�X�g(2D)�̐ݒ菈��
	SetText2D(text2DSet);
}