//========================================
// 
// �t�F�[�h�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** fade.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
// �t�F�[�h�̓����x�̐��ڒl
#define FADE_ALPHA_TRANSITIVE_VALUE (5)

//****************************************
// �O���[�o���ϐ��錾
//****************************************
FADE g_fade;		// �t�F�[�h�̏��
FADE g_fadeTemp;	// �t�F�[�h�̏�Ԃ�ۑ�
Color g_colorFade;	// �|���S��(�t�F�[�h)�̐F

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================
//========================================
// InitFade�֐� - �t�F�[�h�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitFade(void)
{
	g_fade = FADE_IN;				// �t�F�[�h�C����Ԃ�
	g_colorFade = { 0,0,0,255 };	// �����|���S��(�s����)�ɂ���
}

//========================================
// UpdateFade�֐� - �t�F�[�h�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateFade(void)
{
	// �t�F�[�h�̏�Ԃ�ۑ�
	g_fadeTemp = g_fade;

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{// �t�F�[�h�C�����
			// �|���S���𓧖��ɂ��Ă���
			g_colorFade.a -= FADE_ALPHA_TRANSITIVE_VALUE;

			// BGM��SE�̉��ʂ�ύX����
			SoundTypeVolumeChange(SOUND_TYPE_BGM, 1.0f - ((float)g_colorFade.a / (float)255));
			SoundTypeVolumeChange(SOUND_TYPE_SE, 1.0f - ((float)g_colorFade.a / (float)255));

			if (g_colorFade.a <= 0) 
			{// �����x��0�ȉ��̎��A
				g_colorFade.a = 0;	// �����x��0�ɐݒ�
				g_fade = FADE_NONE;	// �t�F�[�h������Ԃɂ���
			}
		}
		else if (g_fade == FADE_OUT) 
		{// �t�F�[�h�A�E�g���
			// �|���S����s�����ɂ��Ă���
			g_colorFade.a += FADE_ALPHA_TRANSITIVE_VALUE;

			// BGM��SE�̉��ʂ�ύX����
			SoundTypeVolumeChange(SOUND_TYPE_BGM, 1.0f - ((float)g_colorFade.a / (float)255));
			SoundTypeVolumeChange(SOUND_TYPE_SE, 1.0f - ((float)g_colorFade.a / (float)255));

			if (g_colorFade.a > 255) 
			{// �����x���ő�l�����������A
				g_colorFade.a = 255;	// �����x���ő�l�ɐݒ�
				g_fade = FADE_IN;		// �t�F�[�h�C����Ԃɂ���

				// BGM��SE���ꊇ�Œ�~
				StopSoundType(SOUND_TYPE_BGM);
				StopSoundType(SOUND_TYPE_SE);
			}
		}
	}

	// �E�B���h�E�̏��
	WindowMemory windowInfo = *GetWindowMemory();

	// �|���S��(2D)�̐ݒ���
	Polygon2DSet polySet;
	/* �e�N�X�`���ԍ�	*/polySet.nTex = -1;
	/* �p�^�[���ԍ�		*/polySet.nPtn = 0;
	/* �p�^�[�����X	*/polySet.nPtnX = 1;
	/* �p�^�[�����Y	*/polySet.nPtnY = 1;
	/* ��				*/polySet.fWidth = windowInfo.fWindowWidth;
	/* ����				*/polySet.fHeight = windowInfo.fWindowHeight;
	/* �ʒu				*/polySet.pos = D3DXVECTOR3(windowInfo.fWindowWidth * 0.5f, windowInfo.fWindowHeight * 0.5f, 0.0f);
	/* ����				*/polySet.rot = INITD3DXVECTOR3;
	/* �F				*/polySet.col = g_colorFade;
	/* �J�������킹		*/polySet.bMatchCamera = false;
	// �|���S��(2D)��ݒ�
	SetPolygon2D(polySet);
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================
//========================================
// GetFade�֐� - �t�F�[�h�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
FADE GetFade(void)
{
	return g_fade;
}

//========================================
// GetFadeSwap�֐� - �t�F�[�h�̐؂�ւ��擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetFadeSwap(void)
{
	return (g_fadeTemp == FADE_OUT) && (g_fade == FADE_IN);
}

//========================================
// GetFadeInEnd�֐� - �t�F�[�h�C���I���擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetFadeInEnd(void)
{
	return (g_fadeTemp == FADE_IN) && (g_fade == FADE_NONE);
}

//========================================
// SetFade�֐� - �t�F�[�h�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetFade(void)
{
	g_fade		= FADE_OUT;			// �t�F�[�h�A�E�g��Ԃ�
	g_colorFade = { 0, 0, 0, 0 };	// �����|���S��(����)�ɂ���
}