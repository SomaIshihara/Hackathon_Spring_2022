//========================================
// 
// UI:���j���[ �̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** ui_menu.cpp ***
//========================================
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "../_R.N.Lib/R.N.Lib.h"

#include "ui_menu.h"	// UI:���j���[

//****************************************
// �}�N����`
//****************************************
// UI:���j���[ �̍ő吔
#define UI_MENU_MAX (16)
// UI:���j���[ �̕�
#define UI_MENU_WIDTH (PIXEL * 256)
// UI:���j���[ �̍���
#define UI_MENU_HEIGHT (PIXEL * 16)
// UI:���j���[ �̑I�����̐F
#define UI_MENU_SELECT_COLOR (Color{243, 189, 63, 255})

// UI:���j���[ �̔z�u�ԊuX
#define UI_MENU_SPACE_X (PIXEL * 0)
// UI:���j���[ �̔z�u�ԊuY
#define UI_MENU_SPACE_Y (PIXEL * 16)
// UI:���j���[ ��������̂ɂ����鎞��
#define UI_MENU_CLEAR_TIME (4)

// UI:���j���[ �̏o���ɂ����鎞��
#define UI_MENU_APPEAR_TIME (10)
// UI:���j���[ �̏o�����Ă��鎞�̑傫���ɂ�����{��
#define UI_MENU_APPEAR_SCALE Scale{1.0f,1.0f,0.0f}
// UI:���j���[ �̏����Ă��鎞�̑傫���ɂ�����{��
#define UI_MENU_DISAPPEAR_SCALE Scale{1.0f,0.0f,0.0f}

//****************************************
// �\���̂̒�`
//****************************************
// UI:���j���[ �̗\����
typedef struct 
{
	bool			bReservation;	// �\��t���O
	Ui_menuSet	*pSet;			// �ݒ���̃|�C���^
	int				nNum;			// ���j���[��
}Ui_menuReservation;

//****************************************
// �v���g�^�C�v�錾
//****************************************
// UI:���j���[ �̃p�����[�^�[����������
// UI:���j���[ �̊Ǘ����̃p�����[�^�[����������
// UI:���j���[ �̗\����̃p�����[�^�[����������
void InitParameterUi_menu(Ui_menu *pUi);
void InitParameterUi_menuControl(void);
void InitParameterUi_menuReservation(void);

// UI:���j���[ �̏�ԏ���
// UI:���j���[ �̍쐬����
void StateProcessUi_menu(void);
void CreateUi_menu(void);

//****************************************
// �O���[�o���錾
//****************************************
static int g_aTex[UI_MENU_TYPE_MAX];		// �e�N�X�`��
Ui_menu g_aUi_menu[UI_MENU_MAX];			// UI:���j���[ �̏��
Ui_menuControl g_ui_menuControl;			// UI:���j���[ �̊Ǘ����
Ui_menuReservation g_ui_menuReservation;	// UI:���j���[ �̗\����

// UI:���j���[ �̃e�N�X�`���t�@�C���̑��΃p�X
char g_aTexturePath[UI_MENU_TYPE_MAX][TXT_MAX] =
{
	"data\\TEXTURE\\UserInterface\\ui_menu\\normal.png",
	"data\\TEXTURE\\UserInterface\\ui_menu\\select.png",
};

//========== *** UI:���j���[ �̏����擾 ***
Ui_menu *GetUi_menu(void) 
{
	return g_aUi_menu;
}

//========== *** UI:���j���[ �̑S�̊Ǘ��̏����擾 ***
Ui_menuControl *GetUi_menuControl(void) 
{
	return &g_ui_menuControl;
}

//========== *** UI:���j���[ �̌��݂̑I��ԍ����擾 ***
int *GetSelect(void) 
{
	return &g_ui_menuControl.nSelect;
}


//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitParameterUi_menu�֐� - UI:���j���[ �̃p�����[�^�[���������� -
//========================================
void InitParameterUi_menu(Ui_menu *pUi)
{
	pUi->pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	pUi->type		= (UI_MENU_TYPE)0;				// ���
	pUi->bUse		= false;							// �g�p����Ă��邩�t���O
	pUi->bSelect	= false;							// �I������Ă��邩�t���O
	sprintf(pUi->aString, "");							// �\�����镶����
	pUi->nSelectNum = 0;								// ���݂̑I�����̔ԍ�
}

//========================================
// InitParameterUi_menuControl�֐� - UI:���j���[ �̊Ǘ����̃p�����[�^�[���������� -
//========================================
void InitParameterUi_menuControl(void)
{
	Ui_menuControl	*pUiCtl	// UI:���j���[ �̊Ǘ����̃|�C���^
						= &g_ui_menuControl;

	pUiCtl->state			= UI_MENU_STATE_NONE;			// ��� 
	pUiCtl->nCounterState	= 0;								// ��Ԃ̃J�E���^�[ 
	pUiCtl->scale			= { 0.0f,0.0f,0.0f };				// �g�嗦 
	pUiCtl->nNum			= 0;								// ���݂̎g�p�� 
	pUiCtl->nSelect			= 0;								// ���݂̑I��ԍ� 
	pUiCtl->centerPos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// ���S���W 
}

//========================================
// InitParameterUi_menuReservation�֐� - UI:���j���[ �̗\����̃p�����[�^�[���������� -
//========================================
void InitParameterUi_menuReservation(void)
{
	Ui_menuReservation	*pUiRsv	// UI:���j���[ �̗\����̃|�C���^
							= &g_ui_menuReservation;

	pUiRsv->bReservation	= false;	// �\��t���O
	pUiRsv->pSet			= NULL;		// �ݒ���̃|�C���^
	pUiRsv->nNum			= 0;		// ���j���[��
}

//========================================
// StateProcessUi_menu�֐� - UI:���j���[ �̏�ԏ��� -
//========================================
void StateProcessUi_menu(void)
{
	Ui_menuControl	*pUiCtl	// UI:���j���[ �̊Ǘ����̃|�C���^
						= &g_ui_menuControl;

	switch (pUiCtl->state)
	{
		//========== *** �o���� ***
	case UI_MENU_STATE_IN_POP: {
		if (--pUiCtl->nCounterState <= 0)
		{// ��Ԃ̃J�E���^�[�����Z��������0�ȉ��̎��A
			// �o����Ԃɂ���
			pUiCtl->state = UI_MENU_STATE_POP;
		}

		float	fRate	// ���� 
				= (float)pUiCtl->nCounterState / (float)UI_MENU_APPEAR_TIME;

		// �傫���ɂ�����{�����X�V
		pUiCtl->scale.fWidth =
			(UI_MENU_APPEAR_SCALE.fWidth * (1.0f - fRate)) +
			(UI_MENU_DISAPPEAR_SCALE.fWidth * fRate);
		pUiCtl->scale.fHeight =
			(UI_MENU_APPEAR_SCALE.fHeight * (1.0f - fRate)) +
			(UI_MENU_DISAPPEAR_SCALE.fHeight * fRate);
	}
		break;
		//========== *** �o�� ***
	case UI_MENU_STATE_POP: {
	}
		break;
		//========== *** ������ ***
	case UI_MENU_STATE_IN_CLEAR: {
		if (--pUiCtl->nCounterState <= 0)
		{// ��Ԃ̃J�E���^�[�����Z��������0�ȉ��̎��A
			// ��Ԃ𖳂��ɂ���
			pUiCtl->state = UI_MENU_STATE_NONE;

			// UI:���j���[ ��S�Ďg�p���Ă��Ȃ���Ԃɂ���
			for (int nCntUi = 0; nCntUi < UI_MENU_MAX; nCntUi++) {
				g_aUi_menu[nCntUi].bUse = false;
			}
		}

		float	fRate	// ���� 
				= (float)pUiCtl->nCounterState / (float)UI_MENU_CLEAR_TIME;

		// �傫���ɂ�����{�����X�V
		pUiCtl->scale.fWidth =
			(UI_MENU_APPEAR_SCALE.fWidth * fRate) +
			(UI_MENU_DISAPPEAR_SCALE.fWidth * (1.0f - fRate));
		pUiCtl->scale.fHeight =
			(UI_MENU_APPEAR_SCALE.fHeight * fRate) +
			(UI_MENU_DISAPPEAR_SCALE.fHeight * (1.0f - fRate));
	}
		break;
	}
}

//========================================
// CreateUi_menu�֐� - UI:���j���[ �̍쐬���� -
//========================================
void CreateUi_menu(void)
{
	Ui_menuControl		*pUiCtl	// UI:���j���[ �̊Ǘ����̃|�C���^
							= &g_ui_menuControl;
	Ui_menuReservation	*pUiRsv	// UI:���j���[ �̗\����̃|�C���^
							= &g_ui_menuReservation;

	if ((!pUiRsv->bReservation)
		||
		(pUiCtl->state != UI_MENU_STATE_NONE))
	{// ���j���[�̗\�񂪖����A�������͏�Ԃ������łȂ����A
		// �������I������
		return;
	}

	pUiRsv->bReservation	= false;					// �\��t���O���U�ɂ���
	pUiCtl->state			= UI_MENU_STATE_IN_POP;	// �o�����ɂ���
	pUiCtl->nCounterState	= UI_MENU_APPEAR_TIME;	// ��ԃJ�E���^�[��ݒ�
	pUiCtl->nSelect			= 0;						// ���݂̑I��ԍ�������������
	pUiCtl->nNum			= pUiRsv->nNum;				// ���݂̎g�p����\���񂩂���

	Ui_menu	*pUi	// UI:���j���[ �̏��̃|�C���^ 
				= g_aUi_menu;

	for (int nCntUi = 0; nCntUi < pUiRsv->nNum; nCntUi++, pUi++)
	{
		Ui_menuSet	*pSet	// UI:���j���[ �̐ݒ���̃|�C���^
						= &pUiRsv->pSet[nCntUi];

		pUi->type		= pSet->type;			// ��ނ���
		pUi->bUse		= true;					// �g�p����Ă����Ԃɂ���
		pUi->bSelect	= false;				// �I������Ă��Ȃ���Ԃɂ���
		sprintf(pUi->aString, pSet->aString);	// ���������

		// �ʒu��ݒ�
		pUi->pos =
			D3DXVECTOR3(
				pUiCtl->centerPos.x - (((pUiRsv->nNum - 1) * UI_MENU_SPACE_X) * 0.5f) + (nCntUi * UI_MENU_SPACE_X),
				pUiCtl->centerPos.y - (((pUiRsv->nNum - 1) * UI_MENU_SPACE_Y) * 0.5f) + (nCntUi * UI_MENU_SPACE_Y), 0.0f);

		// �|���S��(2D)�̐ݒ���
		Polygon2DSet polySet;
		/* �e�N�X�`���ԍ�	*/polySet.nTex = g_aTex[pUi->type];
		/* �p�^�[���ԍ�		*/polySet.nPtn = 0;
		/* �p�^�[�����X	*/polySet.nPtnX = 1;
		/* �p�^�[�����Y	*/polySet.nPtnY = 1;
		/* ��				*/polySet.fWidth = UI_MENU_WIDTH * pUiCtl->scale.fWidth;
		/* ����				*/polySet.fHeight = UI_MENU_HEIGHT * pUiCtl->scale.fHeight;
		/* �ʒu				*/polySet.pos = pUi->pos;
		/* ����				*/polySet.rot = INITD3DXVECTOR3;
		/* �F				*/polySet.col = nCntUi == g_ui_menuControl.nSelect ? UI_MENU_SELECT_COLOR : Color{ 255,255,255,255 };
		/* �J�������킹		*/polySet.bMatchCamera = false;
		// �|���S��(2D)�̐ݒ菈��
		SetPolygon2D(polySet);
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitUi_menu�֐� - UI:���j���[ �̏��������� -
//========================================
void InitUi_menu(void)
{
	InitParameterUi_menuControl();		// �Ǘ����̃p�����[�^�[������
	InitParameterUi_menuReservation();	// �\����̃p�����[�^�[������

	for (int nCntTex = 0; nCntTex < UI_MENU_TYPE_MAX; nCntTex++) 
	{
		g_aTex[nCntTex] = LoadTexture(g_aTexturePath[nCntTex]);
	}
}

//========================================
// UninitUi_menu�֐� - UI:���j���[ �̏I������ -
//========================================
void UninitUi_menu(void)
{
	
}

//========================================
// UpdateUi_menu�֐� - UI:���j���[ �̍X�V���� -
//========================================
void UpdateUi_menu(void)
{
	StateProcessUi_menu();	// ��ԏ���
	CreateUi_menu();		// �쐬����

	Ui_menu			*pUi	// UI:���j���[ �̏��̃|�C���^
						= g_aUi_menu;
	Ui_menuControl	*pUiCtl	// UI:���j���[ �̊Ǘ����̃|�C���^
						= &g_ui_menuControl;

	for (int nCntUi = 0; nCntUi < UI_MENU_MAX; nCntUi++, pUi++)
	{
		if (!pUi->bUse)
		{// �g�p����Ă��Ȃ����A
			// �J��Ԃ����������Z�b�g
			continue;
		}

		// �|���S��(2D)�̐ݒ���
		Polygon2DSet polySet;
		/* �e�N�X�`���ԍ�	*/polySet.nTex = g_aTex[pUi->type];
		/* �p�^�[���ԍ�		*/polySet.nPtn = 0;
		/* �p�^�[�����X	*/polySet.nPtnX = 1;
		/* �p�^�[�����Y	*/polySet.nPtnY = 1;
		/* ��				*/polySet.fWidth = UI_MENU_WIDTH * pUiCtl->scale.fWidth;
		/* ����				*/polySet.fHeight = UI_MENU_HEIGHT * pUiCtl->scale.fHeight;
		/* �ʒu				*/polySet.pos = pUi->pos;
		/* ����				*/polySet.rot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI);
		/* �F				*/polySet.col = nCntUi == g_ui_menuControl.nSelect ? UI_MENU_SELECT_COLOR : Color{ 255,255,255,255 };
		/* �J�������킹		*/polySet.bMatchCamera = false;
		// �|���S��(2D)�̐ݒ菈��
		SetPolygon2D(polySet);

		// �e�L�X�g(2D)�̐ݒ菈��
		Text2DSet text2DSet;
		/* ������̃|�C���^ */text2DSet.pString = pUi->aString;
		/* �t�H���g�ԍ�		*/text2DSet.nFont = 0;
		/* �\���`��			*/text2DSet.disp = TEXT_DISP_CENTER;
		/* �ʒu				*/text2DSet.pos = pUi->pos;
		/* ����				*/text2DSet.rot = D3DXVECTOR3(0.0f,0.0f,0.0f);
		/* �F				*/text2DSet.col = INITCOLOR;
		/* ��				*/text2DSet.fWidth = pUiCtl->scale.fWidth * 8 * PIXEL;
		/* ����				*/text2DSet.fHeight = pUiCtl->scale.fHeight * 8 * PIXEL;
		/* �J�������킹		*/text2DSet.bMatchCamera = false;
		// �e�L�X�g(2D)�̐ݒ菈��
		SetText2D(text2DSet);
	}
}

//========================================
// Ui_menuInput�֐� - UI:���j���[ �̓��͏��� -
//========================================
int Ui_menuInput(UI_MENU_INPUT_MODE mode)
{
	int					nSelected	// �I�������ԍ�(-1�͑I�𖳂�)
						= -1;
	Ui_menuControl	*pUiCtl		// UI:���j���[ �̊Ǘ����̃|�C���^
						= &g_ui_menuControl;

	if ((pUiCtl->state != UI_MENU_STATE_POP)
		||
		(GetFade() != FADE_NONE))
	{// �o����ԂłȂ� or �t�F�[�h���̎��A
		// �������I������
		return nSelected;
	}

	{
		bool	bInput	// ���̓t���O
				= false;

		if (
			(((GetKeyboardRepeat(DIK_UP))
			|| (GetKeyboardRepeat(DIK_W))
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_UP])
			|| (GetButtonRepeat(BUTTON_UP)))
			&& (mode == UI_MENU_INPUT_MODE_UP_AND_DOWN))
			||
			(((GetKeyboardRepeat(DIK_LEFT))
			|| (GetKeyboardRepeat(DIK_A))
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_LEFT])
			|| (GetButtonRepeat(BUTTON_LEFT)))
			&& (mode == UI_MENU_INPUT_MODE_LEFT_AND_RIGHT)))
		{// ����͎��A
			g_ui_menuControl.nSelect--;	// ���݂̑I��ԍ������Z
			bInput = true;					// ���̓t���O��^�ɂ���
		}
		else if (
			(((GetKeyboardRepeat(DIK_DOWN))
			|| (GetKeyboardRepeat(DIK_S))
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_DOWN])
			|| (GetButtonRepeat(BUTTON_DOWN)))
			&& (mode == UI_MENU_INPUT_MODE_UP_AND_DOWN))
			||
			(((GetKeyboardRepeat(DIK_RIGHT))
			|| (GetKeyboardRepeat(DIK_D))
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_RIGHT])
			|| (GetButtonRepeat(BUTTON_RIGHT)))
			&& (mode == UI_MENU_INPUT_MODE_LEFT_AND_RIGHT)))
		{// ��/�E���͎��A
			g_ui_menuControl.nSelect++;	// ���݂̑I��ԍ������Z
			bInput = true;					// ���̓t���O��^�ɂ���
		}

		if ((g_ui_menuReservation.nNum != 1) && (bInput))
		{// ���j���[�̐���1�Ŗ��� & ���̓t���O���^�̎��A
			//PlaySound(UI_MENU_SELECT_SE);	// �I��SE���Đ�
		}
	}

	// �I��ԍ������[�v����
	IntLoopControl(&pUiCtl->nSelect, pUiCtl->nNum, 0);

	if (g_aUi_menu[g_ui_menuControl.nSelect].type == UI_MENU_TYPE_SELECTION)
	{// ��ނ��I���̎��A
		if (
			(GetKeyboardRepeat(DIK_LEFT))
			|| (GetKeyboardRepeat(DIK_RIGHT))
			|| (GetKeyboardRepeat(DIK_A))
			|| (GetKeyboardRepeat(DIK_D))
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_LEFT])
			|| (GetStick().aAngleRepeat[STICK_TYPE_LEFT][STICK_ANGLE_RIGHT])
			|| (GetButtonRepeat(BUTTON_LEFT))
			|| (GetButtonRepeat(BUTTON_RIGHT)))
		{// ��/�E���͎��A
			nSelected = g_ui_menuControl.nSelect;	// �I�������ԍ��Ɍ��݂̑I��ԍ�����
			//PlaySound(UI_MENU_SELECT_SE);			// �I��SE���Đ�
		}
	}
	else if ((GetKeyboardTrigger(DIK_RETURN)) || (GetButtonTrigger(BUTTON_A)))
	{// ENTER�L�[ or A�{�^�� or �}�E�X���{�^�������͂��ꂽ���A
		nSelected = g_ui_menuControl.nSelect;					// �I�������ԍ��Ɍ��݂̑I��ԍ�����
		g_ui_menuControl.state = UI_MENU_STATE_IN_CLEAR;		// �������ɂ���
		g_ui_menuControl.nCounterState = UI_MENU_CLEAR_TIME;	// ��ԃJ�E���^�[��ݒ肷��
		if (g_ui_menuReservation.pSet[nSelected].bDecisionSE)
		{// ����SE�t���O���^�̎��A����SE���Đ�
			//PlaySound(UI_MENU_DETERMINATION_SE);
		}
	}
	
	// �I�������ԍ���Ԃ�
	return nSelected;
}

//========================================
// DrawUi_menu�֐� - UI:���j���[ �̕`�揈�� -
//========================================
void DrawUi_menu(void)
{
	
}

//========================================
// SetUi_menuPos�֐� - UI:���j���[ �̒��S���W��ݒ� -
//========================================
void SetUi_menuPos(D3DXVECTOR3 pos)
{
	Ui_menuControl	*pUiCtl		// UI:���j���[ �̊Ǘ����̃|�C���^
						= &g_ui_menuControl;

	// ���S���W����
	pUiCtl->centerPos = pos;
}

//========================================
// SetUi_menu�֐� - UI:���j���[ �̐ݒ菈�� -
//========================================
void SetUi_menu(Ui_menuSet *pSet, int nNum)
{
	g_ui_menuReservation.bReservation	= true;	// �\��t���O��^�ɂ���
	g_ui_menuReservation.pSet			= pSet;	// �ݒ���̃|�C���^����
	g_ui_menuReservation.nNum			= nNum;	// ���j���[������
}