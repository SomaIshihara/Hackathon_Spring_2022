//========================================
// 
// UI:�����L���O�t���[��[00] �̏���
// Author:���� ����
// 
//========================================
//  *** ui_ranking-frame.cpp ***
//========================================
#include "../main.h"
#include "../_R.N.Lib/R.N.Lib.h"
#include "../Mode/md_game.h"				// MD :�Q�[��				[00]
#include "../System/sys_ranking.h"	// SYS:�����L���O			[00]
#include "ui_ranking-frame.h"	// UI :�����L���O�t���[��	[00]

//****************************************
// �}�N����`
//****************************************
// UI:�����L���O�t���[��[00] �̃e�N�X�`���̑��΃p�X
// UI:�����L���O�t���[��[00] �̕�
// UI:�����L���O�t���[��[00] �̍���
#define UI_RANKINGFRAME_TEXTURE_PATH		"data\\TEXTURE\\UserInterface\\ranking.png"
#define UI_RANKINGFRAME_TEXTURE_WIDTH	(PIXEL*256)
#define UI_RANKINGFRAME_TEXTURE_HEIGHT	(PIXEL*256)

// UI:�����L���O�t���[��[00] �̏o���ɂ����鎞��
// UI:�����L���O�t���[��[00] �̏�����̂ɂ����鎞��
#define UI_RANKINGFRAME_IN_POP_TIME		(10)
#define UI_RANKINGFRAME_IN_CLEAR_TIME	(10)

// UI:�����L���O�t���[��[00] �̃e�L�X�g�̊J�n�ʒuX
// UI:�����L���O�t���[��[00] �̃e�L�X�g�̏I���ʒuX
// UI:�����L���O�t���[��[00] �̃e�L�X�g�̈ʒuY
// UI:�����L���O�t���[��[00] �̃e�L�X�g�̊ԊuY
// UI:�����L���O�t���[��[00] �̃e�L�X�g�Z�b�g�ɂ����鎞��
// UI:�����L���O�t���[��[00] �̖��O�̑��ΈʒuX
#define UI_RANKINGFRAME_TEXT_START_POS_X		(PIXEL*-90)
#define UI_RANKINGFRAME_TEXT_END_POS_X		(PIXEL*-50)
#define UI_RANKINGFRAME_TEXT_POS_Y			(PIXEL*-56)
#define UI_RANKINGFRAME_TEXT_SPACE_Y			(PIXEL*16)
#define UI_RANKINGFRAME_TEXT_SET_TIME		(60)
#define UI_RANKINGFRAME_NAME_RERATIVE_POS_X	(PIXEL*36)

// UI:�����L���O�t���[��[00] �̓_�łɂ����鎞��
// UI:�����L���O�t���[��[00] �̓_�ŐF
#define UI_RANKINGFRAME_BLINK_TIME	(4)
#define UI_RANKINGFRAME_BLINK_COLOR	Color{243,189,63,255}

// UI:�����L���O�t���[��[00] �̖��̑��ΈʒuX
#define UI_RANKINGFRAME_ARROW_RERATIVE_POS_X	(PIXEL*6*6)

// UI:�����L���O�t���[��[00] �̏���̕\���`��
// UI:�����L���O�t���[��[00] �̏���̑��ΈʒuY
#define UI_RANKINGFRAME_UP_ARROW_DISPLAY			"^"
#define UI_RANKINGFRAME_UP_ARROW_RERATIVE_POS_Y	(PIXEL*-8)

// UI:�����L���O�t���[��[00] �̉����̕\���`��
// UI:�����L���O�t���[��[00] �̉����̑��ΈʒuY
#define UI_RANKINGFRAME_DOWN_ARROW_DISPLAY			"_"
#define UI_RANKINGFRAME_DOWN_ARROW_RERATIVE_POS_Y	(PIXEL*8)

// UI:�����L���O�t���[��[00] �̑I��SE
// UI:�����L���O�t���[��[00] �̌���SE
#define UI_RANKINGFRAME_SELECT_SE		(SOUND_LABEL_SE_SELECT0)
#define UI_RANKINGFRAME_DETERMINATION_SE	(SOUND_LABEL_SE_DETERMINATION1)

//****************************************
// �v���g�^�C�v�錾
//****************************************
// UI:�����L���O�t���[��[00] �̃p�����[�^�[�̏���������
void InitParameterUi_rankingFrame(void);

// UI:�����L���O�t���[��[00] �̏�ԏ���
void StateProcessUi_rankingFrame(void);

//****************************************
// �O���[�o���錾
//****************************************
static int g_nTex;
Ui_rankingFrame		g_ui_rankingFrame;			// UI:�����L���O�t���[��[00] �̏��

//========== *** UI:�����L���O�t���[��[00] �̏����擾 ***
Ui_rankingFrame *GetUi_rankingFrame(void) 
{
	return &g_ui_rankingFrame;
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitParameterUi_rankingFrame�֐� - UI:�����L���O�t���[��[00] �̃p�����[�^�[�̏��������� -
//========================================
void InitParameterUi_rankingFrame(void)
{
	Ui_rankingFrame	*pUi	// UI:�����L���O�t���[��[00] �̏��̃|�C���^ 
						= &g_ui_rankingFrame;

	pUi->state			= UI_RANKINGFRAME_STATE_CLEAR;	// ���
	pUi->nCounterState	= 0;								// ��ԃJ�E���^�[
	pUi->fAlpha			= 0.0f;								// �S�̂̓����x
	pUi->pos			= INITD3DXVECTOR3;					// �ʒu
	pUi->scale			= { 1.0f,0.0f,0.0f };				// �g��{��
	pUi->bNameEntry		= false;							// ���O���̓t���O
	pUi->nUpdateRank	= -1;								// �X�V����
	pUi->nCounterBlink	= 0;								// �_�ŃJ�E���^�[
}

//========================================
// NameEntryUi_rankingFrame�֐� - UI:�����L���O�t���[��[00] �̖��O���͏��� -
//========================================
void NameEntryUi_rankingFrame(void)
{
	Ui_rankingFrame	*pUi	// UI:�����L���O�t���[��[00] �̏��̃|�C���^ 
						= &g_ui_rankingFrame;

	if ((!pUi->bNameEntry) || (pUi->nCounterState < UI_RANKINGFRAME_TEXT_SET_TIME))
	{// ���O���̓t���O���U or ��ԃJ�E���^�[���e�L�X�g�Z�b�g�ɂ����鎞�Ԃ�������Ă��鎞�A
		return;	// �������I������
	}

	if ((GetKeyboardRepeat(DIK_DOWN))
		||
		(GetKeyboardRepeat(DIK_S))
		||
		(GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_DOWN])
		||
		(GetButtonRepeat(BUTTON_DOWN)))
	{// ���ɓ��͂��ꂽ���A
		pUi->nCountChar--;	// �����J�E���g�����Z
		// �I��SE���Đ�
		//PlaySound(UI_RANKINGFRAME_SELECT_SE);
	}
	else if (
		(GetKeyboardRepeat(DIK_UP))
		||
		(GetKeyboardRepeat(DIK_W))
		||
		(GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_UP])
		||
		(GetButtonRepeat(BUTTON_UP)))
	{// ��ɓ��͂��ꂽ���A
		pUi->nCountChar++;	// �����J�E���g�����Z
		// �I��SE���Đ�
		//PlaySound(UI_RANKINGFRAME_SELECT_SE);
	}

	// �����J�E���g�����[�v����
	IntLoopControl(&pUi->nCountChar, RANKING_NAME_MAX_CHAR, RANKING_NAME_MIN_CHAR);

	if (((GetKeyboardTrigger(DIK_BACKSPACE))
		||
		(GetButtonTrigger(BUTTON_B)))
		&&
		(pUi->nCountName > 0))
	{// �폜�����͂��ꂽ���A�����O�J�E���g��0�������Ă��鎞�A
		// ���O���͂̃J�E���g�����Z
		pUi->nCountName--;

		// ���݂̃J�E���g�ȍ~�̕������󔒂ɂ���
		GetSys_ranking()[pUi->nUpdateRank].aName[pUi->nCountName + 1] = '\0';

		// �����J�E���g��ݒ�
		pUi->nCountChar = GetSys_ranking()[pUi->nUpdateRank].aName[pUi->nCountName];
	}
	else if ((GetKeyboardTrigger(DIK_RETURN)) || (GetButtonTrigger(BUTTON_A)))
	{// ENTER�L�[ or A�{�^�� or �}�E�X���{�^�������͂��ꂽ���A
		// ����SE���Đ�
		//PlaySound(UI_RANKINGFRAME_DETERMINATION_SE);

		if (++pUi->nCountName >= RANKING_NAME_NUM) 
		{// ���O���͂̃J�E���g�����Z�������ʁA�����L���O���̕������ɒB�������A
			pUi->bNameEntry = false;	// ���O���̓t���O���U�ɂ���
			return;						// �������I������
		}
		pUi->nCountChar	// �����J�E���g��������
			= RANKING_NAME_START_CHAR;
	}

	// ���݂̃J�E���g�̕����𔽉f����
	GetSys_ranking()[pUi->nUpdateRank].aName[pUi->nCountName] = pUi->nCountChar;

	// ���̊�ʒu
	/*D3DXVECTOR3 arrowPos = pUi->pos +
		D3DXVECTOR3(
			UI_RANKINGFRAME_TEXT_END_POS_X + (pUi->nCountName * (GetFont()[FONT0].c_fSpaceX * PIXEL)) + UI_RANKINGFRAME_ARROW_RERATIVE_POS_X,
			UI_RANKINGFRAME_TEXT_POS_Y + (UI_RANKINGFRAME_TEXT_SPACE_Y * pUi->nUpdateRank),
			0.0f);*/

	// ����
	/*SetText2D(
		UI_RANKINGFRAME_UP_ARROW_DISPLAY,
		FONT2,
		DISPLAY_CENTER,
		arrowPos +
		D3DXVECTOR3(0.0f, UI_RANKINGFRAME_UP_ARROW_RERATIVE_POS_Y, 0.0f),
		INITCOLOR,
		1.0f,
		1.0f);*/

	// �����
	/*SetText2D(
		UI_RANKINGFRAME_DOWN_ARROW_DISPLAY,
		FONT2,
		DISPLAY_CENTER,
		arrowPos +
		D3DXVECTOR3(0.0f, UI_RANKINGFRAME_DOWN_ARROW_RERATIVE_POS_Y, 0.0f),
		INITCOLOR,
		1.0f,
		1.0f);*/
}

//========================================
// StateProcess�֐� - ��ԏ��� -
//========================================
void StateProcessUi_rankingFrame(void)
{
	Ui_rankingFrame	*pUi	// UI:�����L���O�t���[��[00] �̏��̃|�C���^ 
						= &g_ui_rankingFrame;

	++pUi->nCounterBlink %= (UI_RANKINGFRAME_BLINK_TIME * 2);	// �_�ŃJ�E���^�[�����Z����

	switch (pUi->state)
	{
		//========== *** �o�� ***
	case UI_RANKINGFRAME_STATE_POP:
	{
		Sys_ranking	*pSys	// �����L���O[00] �̏��̃|�C���^
						= GetSys_ranking();

		for (int nCntRanking = 0; nCntRanking < RANKING_NUM; nCntRanking++, pSys++)
		{
			char aString[TXT_MAX];
			sprintf(aString, " %s  %-3s %8d", GetRankText(nCntRanking), pSys->aName, pSys->nScore);
			Color setColor =
				pUi->nUpdateRank == nCntRanking ?
				!(pUi->nCounterBlink / UI_RANKINGFRAME_BLINK_TIME) ?
				INITCOLOR : UI_RANKINGFRAME_BLINK_COLOR :
				INITCOLOR;
			// �e�L�X�g(2D)�̐ݒ菈��
			Text2DSet text2DSet;
			/* ������̃|�C���^ */text2DSet.pString = aString;
			/* �t�H���g�ԍ�		*/text2DSet.nFont = 0;
			/* �\���`��			*/text2DSet.disp = TEXT_DISP_LEFT;
			/* �ʒu				*/text2DSet.pos = pUi->pos +
				D3DXVECTOR3(
					UI_RANKINGFRAME_TEXT_END_POS_X,
					UI_RANKINGFRAME_TEXT_POS_Y + (UI_RANKINGFRAME_TEXT_SPACE_Y * nCntRanking),
					0.0f);
			/* ����				*/text2DSet.rot = INITD3DXVECTOR3;
			/* �F				*/text2DSet.col = setColor;
			/* ��				*/text2DSet.fWidth = 8 * PIXEL;
			/* ����				*/text2DSet.fHeight = 8 * PIXEL;
			/* �J�������킹		*/text2DSet.bMatchCamera = false;
			// �e�L�X�g(2D)�̐ݒ菈��
			SetText2D(text2DSet);
		}
		break;
	}
		//========== *** �e�L�X�g�Z�b�g ***
	case UI_RANKINGFRAME_STATE_TEXT_SET: {
		// ��ԃJ�E���^�[�����Z
		pUi->nCounterState++;

		// ��ԃJ�E���^�[�𐧌�
		IntControl(&pUi->nCounterState, UI_RANKINGFRAME_TEXT_SET_TIME, 0);

		Sys_ranking	*pSys	// �����L���O[00] �̏��̃|�C���^
						= GetSys_ranking();

		const int	nTime	// 1�̃����L���O������ɂ����鎞��
					= UI_RANKINGFRAME_TEXT_SET_TIME / RANKING_NUM;

		if (pUi->nCounterState % nTime == 0) 
		{
			//PlaySound(SOUND_LABEL_SE_SELECT0);
		}

		for (int nCntRanking = 0; nCntRanking < IntControlReturn((pUi->nCounterState / nTime) + 1, RANKING_NUM, 0); nCntRanking++, pSys++)
		{
			char aString[TXT_MAX];
			sprintf(aString, " %s  %-3s %8d", GetRankText(nCntRanking), pSys->aName, pSys->nScore);
			float fRate =	// �i�s����
				(float)(IntControlReturn(pUi->nCounterState, nTime * (nCntRanking + 1), 0) -
				(nTime * nCntRanking)) / (float)nTime;
			
			// �e�L�X�g(2D)�̐ݒ菈��
			Text2DSet text2DSet;
			/* ������̃|�C���^ */text2DSet.pString = aString;
			/* �t�H���g�ԍ�		*/text2DSet.nFont = 0;
			/* �\���`��			*/text2DSet.disp = TEXT_DISP_LEFT;
			/* �ʒu				*/text2DSet.pos = pUi->pos +
				D3DXVECTOR3(
				(UI_RANKINGFRAME_TEXT_START_POS_X * (1.0f - fRate)) + (UI_RANKINGFRAME_TEXT_END_POS_X * fRate),
					UI_RANKINGFRAME_TEXT_POS_Y + (UI_RANKINGFRAME_TEXT_SPACE_Y * nCntRanking), 0.0f);
			/* ����				*/text2DSet.rot = INITD3DXVECTOR3;
			/* �F				*/text2DSet.col = { 255,255,255,(int)(255 * fRate) };
			/* ��				*/text2DSet.fWidth = 8 * PIXEL;
			/* ����				*/text2DSet.fHeight = 8 * PIXEL;
			/* �J�������킹		*/text2DSet.bMatchCamera = false;
			// �e�L�X�g(2D)�̐ݒ菈��
			SetText2D(text2DSet);

			if (pUi->nUpdateRank == nCntRanking)
			{// �X�V���ʂƃJ�E���g����v���Ă��鎞�A
				Color setColor =
					!(pUi->nCounterBlink / UI_RANKINGFRAME_BLINK_TIME) ?
					INITCOLOR : UI_RANKINGFRAME_BLINK_COLOR;
				// �e�L�X�g(2D)�̐ݒ菈��
				Text2DSet text2DSet;
				/* ������̃|�C���^ */text2DSet.pString = pSys->aName;
				/* �t�H���g�ԍ�		*/text2DSet.nFont = 0;
				/* �\���`��			*/text2DSet.disp = TEXT_DISP_LEFT;
				/* �ʒu				*/text2DSet.pos = pUi->pos +
					D3DXVECTOR3(
					(UI_RANKINGFRAME_TEXT_START_POS_X * (1.0f - fRate)) + (UI_RANKINGFRAME_TEXT_END_POS_X * fRate) + UI_RANKINGFRAME_NAME_RERATIVE_POS_X,
						UI_RANKINGFRAME_TEXT_POS_Y + (UI_RANKINGFRAME_TEXT_SPACE_Y * nCntRanking),
						0.0f);
				/* ����				*/text2DSet.rot = INITD3DXVECTOR3;
				/* �F				*/text2DSet.col = { setColor.r,setColor.g,setColor.b,(int)(255 * fRate) };
				/* ��				*/text2DSet.fWidth = 8 * PIXEL;
				/* ����				*/text2DSet.fHeight = 8 * PIXEL;
				/* �J�������킹		*/text2DSet.bMatchCamera = false;
				// �e�L�X�g(2D)�̐ݒ菈��
				SetText2D(text2DSet);
			}
		}

		if ((pUi->nCounterState >= UI_RANKINGFRAME_TEXT_SET_TIME)
			&&
			(!pUi->bNameEntry))
		{// ��ԃJ�E���^�[���e�L�X�g�Z�b�g�ɂ����鎞�ԂɒB���� & ���O���̓t���O���U�̎��A
			SetStateUi_rankingFrame(UI_RANKINGFRAME_STATE_POP);	// ��Ԃ��o���ɂ���
		}

		break;
	}
		//========== *** �o���� ***
	case UI_RANKINGFRAME_STATE_IN_POP: {
		// ��ԃJ�E���^�[�����Z
		pUi->nCounterState++;

		float	fRate	// ����
				= (float)pUi->nCounterState / (float)UI_RANKINGFRAME_IN_POP_TIME;

		// �����x�ƍ����̔{�����X�V
		pUi->fAlpha			= fRate;
		pUi->scale.fHeight	= fRate;

		if (pUi->nCounterState >= UI_RANKINGFRAME_IN_POP_TIME)
		{// ��ԃJ�E���^�[���o���ɂ����鎞�ԂɒB�������A
			// ��Ԃ��e�L�X�g�Z�b�g�ɂ���
			SetStateUi_rankingFrame(UI_RANKINGFRAME_STATE_TEXT_SET);
		}

		break;
	}
		//========== *** �����Ă��� ***
	case UI_RANKINGFRAME_STATE_CLEAR: {
		break;
	}
		//========== *** ������ ***
	case UI_RANKINGFRAME_STATE_IN_CLEAR: {
		// ��ԃJ�E���^�[�����Z
		pUi->nCounterState++;

		float	fRate	// ����
				= (float)pUi->nCounterState / (float)UI_RANKINGFRAME_IN_POP_TIME;

		// �����x�ƍ����̔{�����X�V
		pUi->fAlpha			= 1.0f - fRate;
		pUi->scale.fHeight	= 1.0f - fRate;

		if (pUi->nCounterState >= UI_RANKINGFRAME_IN_CLEAR_TIME)
		{// ��ԃJ�E���^�[��������̂ɂ����鎞�ԂɒB�������A
			// �����Ă����Ԃɂ���
			SetStateUi_rankingFrame(UI_RANKINGFRAME_STATE_CLEAR);
		}

		break;
	}
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitUi_rankingFrame�֐� - UI:�����L���O�t���[��[00] �̏��������� -
//========================================
void InitUi_rankingFrame(void)
{
	// �p�����[�^�[�̏���������
	InitParameterUi_rankingFrame();

	g_nTex = LoadTexture(UI_RANKINGFRAME_TEXTURE_PATH);
}

//========================================
// UninitUi_rankingFrame�֐� - UI:�����L���O�t���[��[00] �̏I������ -
//========================================
void UninitUi_rankingFrame(void)
{

}

//========================================
// UpdateUi_rankingFrame�֐� - UI:�����L���O�t���[��[00] �̍X�V���� -
//========================================
void UpdateUi_rankingFrame(void) 
{
	Ui_rankingFrame	*pUi	// UI:�����L���O�t���[��[00] �̏��̃|�C���^
						= &g_ui_rankingFrame;

	// ���O���͏���
	NameEntryUi_rankingFrame();

	// �|���S��(2D)�̐ݒ���
	Polygon2DSet polySet;
	/* �e�N�X�`���ԍ�	*/polySet.nTex = g_nTex;
	/* �p�^�[���ԍ�		*/polySet.nPtn = 0;
	/* �p�^�[�����X	*/polySet.nPtnX = 1;
	/* �p�^�[�����Y	*/polySet.nPtnY = 1;
	/* ��				*/polySet.fWidth = UI_RANKINGFRAME_TEXTURE_WIDTH;
	/* ����				*/polySet.fHeight = UI_RANKINGFRAME_TEXTURE_HEIGHT;
	/* �ʒu				*/polySet.pos = g_ui_rankingFrame.pos;
	/* ����				*/polySet.rot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI);
	/* �F				*/polySet.col = { 255,255,255,(int)(255 * g_ui_rankingFrame.fAlpha) };
	/* �J�������킹		*/polySet.bMatchCamera = false;
	// �|���S��(2D)�̐ݒ菈��
	SetPolygon2D(polySet);

	// ��ԏ���
	StateProcessUi_rankingFrame();
}

//========================================
// DrawUi_rankingFrame�֐� - UI:�����L���O�t���[��[00] �̕`�揈�� -
//========================================
void DrawUi_rankingFrame(void)
{
	
}

//========================================
// SetState�֐� - UI:�����L���O�t���[��[00] �̏�Ԑݒ菈�� -
//========================================
void SetStateUi_rankingFrame(UI_RANKINGFRAME_STATE state) 
{
	Ui_rankingFrame	*pUi	// UI:�����L���O�t���[��[00] �̏��̃|�C���^
						= &g_ui_rankingFrame;

	// ��Ԃ���
	pUi->state = state;

	// ��ԃJ�E���^�[��������
	pUi->nCounterState = 0;
}

//========================================
// SetUi_rankingFrame�֐� - UI:�����L���O�t���[��[00] �̐ݒ菈�� -
//========================================
void SetUi_rankingFrame(D3DXVECTOR3 pos)
{
	Ui_rankingFrame	*pUi	// UI:�����L���O�t���[��[00] �̏��̃|�C���^ 
						= &g_ui_rankingFrame;

	if (pUi->state != UI_RANKINGFRAME_STATE_CLEAR) 
	{// �����Ă����ԂłȂ����A
		// �������I������
		return;
	}

	// �ʒu����
	pUi->pos = pos;

	// �o�����̏�Ԃɂ���
	SetStateUi_rankingFrame(UI_RANKINGFRAME_STATE_IN_POP);
}

//========================================
// SetNameEntryUi_rankingFrame�֐� - UI:�����L���O�t���[��[00] �̖��O���͐ݒ菈�� -
//========================================
void SetNameEntryUi_rankingFrame(int nUpdateRank)
{
	Ui_rankingFrame	*pUi	// UI:�����L���O�t���[��[00] �̏��̃|�C���^ 
						= &g_ui_rankingFrame;

	pUi->nUpdateRank = nUpdateRank;	// �X�V���ʂ���

	if (pUi->nUpdateRank != -1) 
	{// �X�V���ʂ�-1(�X�V����)�łȂ����A
		pUi->bNameEntry = true;	// ���O���̓t���O��^�ɂ���
		pUi->nCountName = 0;	// ���O�J�E���g��������
		pUi->nCountChar			// �����J�E���g��������
			= RANKING_NAME_START_CHAR;
		pUi->nCounterBlink = 0;	// �_�ŃJ�E���^�[��������

		// �X�V�������ʂ̖��O��������
		sprintf(GetSys_ranking()[pUi->nUpdateRank].aName, "   ");
	}
	else 
	{// �X�V������-1(�X�V����)�̎��A
		pUi->bNameEntry = false;	// ���O���̓t���O���U�ɂ���
	}
}