//========================================
// 
// MD:�^�C�g���̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** md_title.cpp ***
//========================================
#include "../main.h"
#include "md_title.h"
#include "../_R.N.Lib/R.N.Lib.h"
#include "../UserInterface/ui_menu.h"
#include "../UserInterface/ui_title-logo.h"
#include "../../code/_R.N.Lib/Basis/Other/sound.h"
#include "../_R.N.Lib/Basis/2D/text2D.h"

//****************************************
// �}�N����`
//****************************************
// �^�C�g�����[00] �̃��C�����j���[�̈ʒu
#define MD_TITLE_MAIN_MENU_POS D3DXVECTOR3(SCREEN_WIDTH*0.5f,SCREEN_HEIGHT-PIXEL*64,0.0f)
// �^�C�g�����[00] �̃����L���O���j���[�̈ʒu
#define MD_TITLE_RANKING_MENU_POS D3DXVECTOR3(SCREEN_WIDTH*0.5f,SCREEN_HEIGHT-PIXEL*32,0.0f)
// �^�C�g�����[00] �̃����L���O�̈ʒu
#define MD_TITLE_RANKING_POS D3DXVECTOR3(SCREEN_WIDTH*0.5f,SCREEN_HEIGHT*0.5f,0.0f)

//========== *** ��Ԋ֘A ***
// �����̏��
#define INIT_STATE (MD_TITLE_STATE_NORMAL)

//****************************************
// �񋓌^�̒�`
//****************************************
// �^�C�g�����[00] �̃��[�U�[�K�C�h���j���[
typedef enum
{
	MD_TITLE_USERGUID_MENU_OK,	// OK
	MD_TITLE_USERGUID_MENU_MAX,
}MD_TITLE_USERGUID_MENU;

// �^�C�g�����[00] �̃����L���O���j���[
typedef enum
{
	MD_TITLE_RANKING_MENU_OK,	// OK
	MD_TITLE_RANKING_MENU_MAX,
}MD_TITLE_RANKING_MENU;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �擾 ***
// MD:�^�C�g���̃p�����[�^�[������
void InitParameterMd_title(Md_title *pMd);

//****************************************
// �O���[�o���ϐ��錾
//****************************************
Md_title g_md_title;	// MD:�^�C�g���̏��

// MD:�^�C�g�����[00] �̃��C�����j���[�ݒ���
Ui_menuSet g_aMd_titleMainMenuSet[MD_TITLE_MAIN_MENU_MAX] =
{
	{ UI_MENU_TYPE_NORMAL,"START"    ,false },
	{ UI_MENU_TYPE_NORMAL,"QUIT"     ,false },
};

// MD:�^�C�g�����[00] �̃����L���O���j���[�ݒ���
Ui_menuSet g_aMd_titleRankingMenuSet[MD_TITLE_RANKING_MENU_MAX] =
{
	{ UI_MENU_TYPE_NORMAL,"OK",true },
};

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================

//========================================
// StartMd_titleState�֐� - MD:�^�C�g����ʂ̏�Ԃɉ������J�n���� -
//========================================
void StartMd_titleState(void)
{
	Md_title	*pMd	// MD:�^�C�g�����[00] �̏��
		= &g_md_title;

	// ��ԃJ�E���^�[��������
	pMd->nCounterState = 0;

	switch (pMd->state)
	{
	case /*/ �ʏ� /*/MD_TITLE_STATE_NORMAL: {
		// UI:���j���[[00] �̒��S���W��ݒ�
		SetUi_menuPos(MD_TITLE_MAIN_MENU_POS);

		// UI:���j���[[00] �̐ݒ菈��(���C�����j���[)
		SetUi_menu(
			g_aMd_titleMainMenuSet,
			MD_TITLE_MAIN_MENU_MAX);

		break;
	}
	case /*/ �����L���O /*/MD_TITLE_STATE_RANKING: {
		// UI:���j���[[00] �̒��S���W��ݒ�
		SetUi_menuPos(MD_TITLE_RANKING_MENU_POS);

		// UI:���j���[[00] �̐ݒ菈��(�����L���O���j���[)
		SetUi_menu(
			g_aMd_titleRankingMenuSet,
			MD_TITLE_RANKING_MENU_MAX);

		break;
	}
	}
}

//========================================
// EndMd_titleState�֐� - MD:�^�C�g����ʂ̏�Ԃɉ������I������ -
//========================================
void EndMd_titleState(void)
{
	Md_title	*pMd	// MD:�^�C�g�����[00] �̏��
		= &g_md_title;

	switch (pMd->state)
	{
	case /*/ �ʏ� /*/MD_TITLE_STATE_NORMAL: {
		break;
	}
	case /*/ �����L���O /*/MD_TITLE_STATE_RANKING: {
		break;
	}
	}
}

//========================================
// UpdateMd_titleState�֐� - MD:�^�C�g����ʂ̏�Ԃɉ������X�V���� -
//========================================
void UpdateMd_titleState(void)
{
	Md_title	*pMd	// MD:�^�C�g�����[00] �̏��
		= &g_md_title;

	switch (pMd->state)
	{
	case /*/ �ʏ� /*/MD_TITLE_STATE_NORMAL: {
		// ���C�����j���[�̑I������
		switch (Ui_menuInput(UI_MENU_INPUT_MODE_UP_AND_DOWN))
		{
		case /*/ �J�n /*/MD_TITLE_MAIN_MENU_START: {
			// ��ʂ��Q�[�����[00] �ɐݒ�
			SetFade();

			// ����SE���Đ�
			//PlaySound(MD_TITLE_DETERMINATION_SE);
			break;
		}
		//case /*/ �����L���O /*/MD_TITLE_MAIN_MENU_RANKING: {
		//	// UI:�����L���O�t���[��[00] �̐ݒ菈��
		//	//SetUi_rankingFrame(MD_TITLE_RANKING_POS);

		//	break;
		//}
		case /*/ �I�� /*/MD_TITLE_MAIN_MENU_EXIT: {
			// �E�C���h�E��j������
			DestroyWindow(*GetWindowHandle());
			break;
		}
		}

		if (GetFadeSwap()) 
		{// �t�F�[�h�̐؂�ւ����擾�������A
			SetMode(MODE_GAME);
		}

		//if (GetUi_rankingFrame()->state == UI_RANKINGFRAME_STATE_POP)
		//{// UI:�����L���O�t���[��[00] �̏�Ԃ��o���̎��A
		//	SetMd_titleState(MD_TITLE_STATE_RANKING);	// ��Ԃ������L���O�ɂ���
		//}

		break;
	}
	case /*/ �����L���O /*/MD_TITLE_STATE_RANKING: {
		// �����L���O���j���[�̑I������
		switch (Ui_menuInput(UI_MENU_INPUT_MODE_UP_AND_DOWN))
		{
		case /*/ OK /*/MD_TITLE_RANKING_MENU_OK: {
			//// UI:�����L���O�t���[��[00] �̏�Ԃ��������ɂ���
			//SetStateUi_rankingFrame(UI_RANKINGFRAME_STATE_IN_CLEAR);

			break;
		}
		}

		//if (GetUi_rankingFrame()->state == UI_RANKINGFRAME_STATE_CLEAR)
		//{// UI:�����L���O�t���[��[00] �̏�Ԃ������Ă��鎞�A
		//	SetMd_titleState(MD_TITLE_STATE_NORMAL);	// ��Ԃ�ʏ�ɂ���
		//}

		break;
	}
	}
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================

//========================================
// InitParameterMd_title�֐� - MD:�^�C�g���̃p�����[�^�[������ -
// Author:RIKU NISHIMURA
//========================================
void InitParameterMd_title(Md_title *pMd)
{
	pMd->state = MD_TITLE_STATE_NONE;	// ���
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================

//========================================
// InitMd_title�֐� - MD:�^�C�g���̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitMd_title(void) 
{
	// MD:�^�C�g����ʂ̏��̃|�C���^
	Md_title *pMd = &g_md_title;

	// �p�����[�^�[������
	InitParameterMd_title(pMd);

	InitUi_menu();
	InitUi_titleLogo();

	// ������Ԃ�ݒ�
	SetStateMd_title(INIT_STATE);

	// �}�b�v����ǂݍ���
	LoadMapData("data\\GAMEOBJECT\\3D\\MAP\\STAGE_000.txt");

	//�J����������
	InitCamera3D();
	{
		GetCamera3D()->posR = D3DXVECTOR3(0.0f, 40.0f, 0.0f);
		GetCamera3D()->posV = D3DXVECTOR3(0.0f, 120.0f, -140.0f);
	}

	//�^�C�g��BGM�Đ�
	PlaySound(0);

	// �e�L�X�g(2D)�̐ݒ菈��
	Text2DSet text2DSet;
	/* ������̃|�C���^ */text2DSet.pString = "(C)TENK IPPIN -2022-";
	/* �t�H���g�ԍ�		*/text2DSet.nFont = 0;
	/* �\���`��			*/text2DSet.disp = TEXT_DISP_CENTER;
	/* �ʒu				*/text2DSet.pos = D3DXVECTOR3(SCREEN_CENTER_X, 650.0f, 0.0f);
	/* ����				*/text2DSet.rot = INITD3DXVECTOR3;
	/* �F				*/text2DSet.col = INITCOLOR;
	/* ��				*/text2DSet.fWidth = 30.0f;
	/* ����				*/text2DSet.fHeight = 30.0f;
	/* �J�������킹		*/text2DSet.bMatchCamera = false;
	// �e�L�X�g(2D)�̐ݒ菈��
	SetText2D(text2DSet);

}

//========================================
// UninitMd_title�֐� - MD:�^�C�g���̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitMd_title(void) 
{
	UninitUi_menu();
	UninitUi_titleLogo();
}

//========================================
// UpdateMd_title�֐� - MD:�^�C�g���̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateMd_title(void) 
{
	// ��Ԃɉ������X�V����
	UpdateMd_titleState();

	UpdateUi_menu();
	UpdateUi_titleLogo();

	// �e�L�X�g(2D)�̐ݒ菈��
	Text2DSet text2DSet;
	/* ������̃|�C���^ */text2DSet.pString = "(C)2023 TENKA IPPIN INC.";
	/* �t�H���g�ԍ�		*/text2DSet.nFont = 0;
	/* �\���`��			*/text2DSet.disp = TEXT_DISP_CENTER;
	/* �ʒu				*/text2DSet.pos = D3DXVECTOR3(SCREEN_CENTER_X, 650.0f, 0.0f);
	/* ����				*/text2DSet.rot = INITD3DXVECTOR3;
	/* �F				*/text2DSet.col = INITCOLOR;
	/* ��				*/text2DSet.fWidth = 30.0f;
	/* ����				*/text2DSet.fHeight = 30.0f;
	/* �J�������킹		*/text2DSet.bMatchCamera = false;
	// �e�L�X�g(2D)�̐ݒ菈��
	SetText2D(text2DSet);
}

//========================================
// DrawMd_title�֐� - MD:�^�C�g���̕`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void DrawMd_title(void)
{
	DrawUi_menu();
	DrawUi_titleLogo();
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================
//========================================
// GetMd_title�֐� - MD:�^�C�g���̏����擾 -
// Author:RIKU NISHIMURA
//========================================
Md_title *GetMd_title(void) 
{
	return &g_md_title;
}

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================

//========================================
// SetStateMd_title�֐� - MD:�^�C�g���̏�Ԑݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetStateMd_title(MD_TITLE_STATE state)
{
	// MD:�^�C�g����ʂ̏��̃|�C���^
	Md_title *pMd = &g_md_title;

	// ��Ԃɉ������I������
	EndMd_titleState();
	
	// ��Ԃ���
	pMd->state = state;

	// ��Ԃɉ������J�n����
	StartMd_titleState();
}