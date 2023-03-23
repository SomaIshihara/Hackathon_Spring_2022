//========================================
// 
// MD:�Q�[���̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** md_game.cpp ***
//========================================
#include "md_game.h"
#include "../_R.N.Lib/R.N.Lib.h"
#include "../boomerang.h"
#include "../_R.N.Lib/Basis/2D/boomeUI.h"
#include "../target.h"
#include "../chr_player.h"
#include "../_R.N.Lib/Basis/2D/timer.h"

#include "../UserInterface/ui_menu.h"
#include "../UserInterface/ui_ranking-frame.h"
#include "../System/sys_ranking.h"
#include "../_R.N.Lib/Basis/2D/score.h"
#include "../../code/_R.N.Lib/Basis/Other/sound.h"
#include "../cloud.h"

//****************************************
// �}�N����`
//****************************************
#define MD_GAME_RESULT_MENU_POS D3DXVECTOR3(SCREEN_WIDTH*0.5f,SCREEN_HEIGHT+(PIXEL*-32),0.0f)
#define MD_GAME_RANKING_POS D3DXVECTOR3(SCREEN_WIDTH*0.5f,(SCREEN_HEIGHT*0.5f)-PIXEL*8,0.0f)
#define MAX_TYPE	(1)
//========== *** ��Ԋ֘A ***
// �����̏��
#define INIT_STATE (MD_GAME_STATE_NORMAL)

//****************************************
// �񋓌^�̒�`
//****************************************
// �Q�[�����[00] �̃��U���g���j���[
typedef enum
{
	MD_GAME_RESULT_MENU_RETRY,			// ���g���C
	MD_GAME_RESULT_MENU_BACK_TO_TITLE,	// �^�C�g���ɖ߂�
	MD_GAME_RESULT_MENU_MAX,
}MD_GAME_RESULT_MENU;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �擾 ***
// MD:�Q�[���̃p�����[�^�[������
void InitParameterMd_game(Md_game *pMd);

//****************************************
// �O���[�o���ϐ��錾
//****************************************
Md_game g_md_game;	// MD:�Q�[���̏��

static int g_aTex2[MAX_TYPE];

// �e�N�X�`���p�X
char g_aTexturePath2[MAX_TYPE][TXT_MAX] =
{
	"data//TEXTURE//UserInterface//guid.PNG",
};
// MD:�Q�[�����[00] �̃��U���g���j���[�ݒ���
Ui_menuSet g_aMd_gameResultMenuSet[MD_GAME_RESULT_MENU_MAX] =
{
	{ UI_MENU_TYPE_NORMAL,"RETRY"        ,true },
	{ UI_MENU_TYPE_NORMAL,"BACK TO TITLE",true },
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
// StartMd_gameState�֐� - MD:�Q�[����ʂ̏�Ԃɉ������J�n���� -
//========================================
void StartMd_gameState(void)
{
	// MD:�Q�[����ʂ̏��̃|�C���^
	Md_game *pMd = &g_md_game;

	switch (pMd->state)
	{
	case MD_GAME_STATE_NORMAL:

		break;
	case /*/ �����L���O /*/MD_GAME_STATE_RANKING: {
		// UI:�����L���O�t���[��[00] �̖��O���͐ݒ菈��
		SetNameEntryUi_rankingFrame(SetScore(GetChr_player()->nScore));

		// UI:�����L���O�t���[��[00] �̐ݒ菈��
		SetUi_rankingFrame(MD_GAME_RANKING_POS);

		break;
	}
	case /*/ ���U���g /*/MD_GAME_STATE_RESULT: {
		// UI:���j���[[00] �̒��S���W��ݒ�
		SetUi_menuPos(MD_GAME_RESULT_MENU_POS);

		// UI:���j���[[00] �̐ݒ菈��(���U���g���j���[)
		SetUi_menu(
			g_aMd_gameResultMenuSet,
			MD_GAME_RESULT_MENU_MAX);

		break;
	}
	}
}

//========================================
// EndMd_gameState�֐� - MD:�Q�[����ʂ̏�Ԃɉ������I������ -
//========================================
void EndMd_gameState(void)
{
	// MD:�Q�[����ʂ̏��̃|�C���^
	Md_game *pMd = &g_md_game;

	switch (pMd->state)
	{
	case MD_GAME_STATE_NORMAL:

		break;
	}
}

//========================================
// UpdateMd_gameState�֐� - MD:�Q�[����ʂ̏�Ԃɉ������X�V���� -
//========================================
void UpdateMd_gameState(void)
{
	// MD:�Q�[����ʂ̏��̃|�C���^
	Md_game *pMd = &g_md_game;

	switch (pMd->state)
	{
	case MD_GAME_STATE_NORMAL:

		break;
	case /*/ �����L���O /*/MD_GAME_STATE_RANKING: {
		if (GetUi_rankingFrame()->state == UI_RANKINGFRAME_STATE_POP)
		{// UI:�����L���O�t���[��[00] �̏�Ԃ��o���̎��A
			SetStateMd_game(MD_GAME_STATE_RESULT);	// ��Ԃ����U���g�ɂ���
		}

		break;
	}
	case /*/ ���U���g /*/MD_GAME_STATE_RESULT: {
		// ���U���g���j���[�̑I������
		switch (Ui_menuInput(UI_MENU_INPUT_MODE_UP_AND_DOWN))
		{
		case /*/ ���g���C /*/MD_GAME_RESULT_MENU_RETRY: {
			// ��ʂ��Q�[�����[00] �ɐݒ�
			SetFade();
			pMd->mode = MODE_GAME;
			break;
		}
		case /*/ �^�C�g���ɖ߂� /*/MD_GAME_RESULT_MENU_BACK_TO_TITLE: {
			// ��ʂ��^�C�g�����[00] �ɐݒ�
			SetFade();
			pMd->mode = MODE_TITLE;
			break;
		}
		}

		if (GetFadeSwap())
		{// �t�F�[�h�؂�ւ����A
			SetMode(pMd->mode);
		}

		break;
	}
	}
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================

//========================================
// InitParameterMd_game�֐� - MD:�Q�[���̃p�����[�^�[������ -
// Author:RIKU NISHIMURA
//========================================
void InitParameterMd_game(Md_game *pMd)
{
	pMd->state = MD_GAME_STATE_NONE;	// ���
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
// InitMd_game�֐� - MD:�Q�[���̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitMd_game(void)
{
	// MD:�Q�[����ʂ̏��̃|�C���^
	Md_game *pMd = &g_md_game;

	g_aTex2[0] = LoadTexture(g_aTexturePath2[0]);


	// �G�̏o���ʒu�̓ǂݍ��ݏ���
	LoadSummon();

	// �G�̏o�����̓ǂݍ��ݏ���
	LoadTarget();

	// �G�̏��̓ǂݍ��ݏ���
	LoadTargetType();

	// �p�����[�^�[������
	InitParameterMd_game(pMd);

	// ������Ԃ�ݒ�
	SetStateMd_game(INIT_STATE);

	//�J����������
	InitCamera3D();
	{
		GetCamera3D()->posR = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		GetCamera3D()->posV = D3DXVECTOR3(0.0f, 140.0f, -140.0f);
	}

	// �u�[������������
	InitBoomerang();

	// �G������
	InitTarget();

	// �v���C���[������
	InitChr_player();

	//�������Ԑݒ�
	InitTimer();

	//�u�[�������̏�����UI������
	InitBoomeUI();

	//�u�[�������̏�����UI�ݒ�
	SetBoomeUI();

	InitUi_menu();			// ���j���[
	InitUi_rankingFrame();	// �����L���O(UI)
	InitSys_ranking();		// �����L���O

	//�X�R�AUI�ݒ�
	SetScoreUI();

	//�_�ݒ�
	InitCloud();

	//�Q�[��BGM�Đ�
	PlaySound(1);
}

//========================================
// UninitMd_game�֐� - MD:�Q�[���̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitMd_game(void)
{
	UninitUi_menu();			// ���j���[
	UninitUi_rankingFrame();	// �����L���O(UI)
	UninitSys_ranking();		// �����L���O
}

//========================================
// UpdateMd_game�֐� - MD:�Q�[���̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateMd_game(void)
{
	// ��Ԃɉ������X�V����
	UpdateMd_gameState();

	//�J�����X�V����
	UpdateCamera3D();

	// �v���C���[�X�V
	UpdateChr_player();

	// �u�[�������X�V����
	UpdateBoomerang();

	// �G �X�V����
	UpdateTarget();

	//�_�̍X�V����
	UpdateCloud();

	//�u�[�������̏�����UI�ݒ�
	SetBoomeUI();

	UpdateUi_menu();			// ���j���[
	UpdateUi_rankingFrame();	// �����L���O(UI)
	UpdateSys_ranking();		// �����L���O

	if (GetMd_game()->state == MD_GAME_STATE_NORMAL)
	{
		//�������ԍX�V����
		UpdateTimer();

		SetScoreUI();	// �X�R�AUI
	}

	// �|���S��(3D)�̐ݒ���
	Polygon3DSet polygon3DSet;
	polygon3DSet.nTex = g_aTex2[0];
	polygon3DSet.nPtn = 0;
	polygon3DSet.nPtnX = 1;
	polygon3DSet.nPtnY = 1;
	polygon3DSet.fWidth = 80;
	polygon3DSet.fHeight = 80;
	polygon3DSet.pos = D3DXVECTOR3(-110.0f, -10.0f, 30.0f);
	polygon3DSet.rot = D3DXVECTOR3(-D3DX_PI * 0.25f, 0.0f, 0.0f);
	polygon3DSet.col = Color{ 255,255,255,255 };
	// �|���S��(3D)�̐ݒ菈��
	SetPolygon3D(polygon3DSet);
}

//========================================
// DrawMd_game�֐� - MD:�Q�[���̕`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void DrawMd_game(void)
{
	//�J�����ݒ�
	SetCamera3D();

	//�u�[�������i�R���{�\���j
	DrawBoomerang();
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================
//========================================
// GetMd_game�֐� - MD:�Q�[���̏����擾 -
// Author:RIKU NISHIMURA
//========================================
Md_game *GetMd_game(void)
{
	return &g_md_game;
}

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================

//========================================
// SetStateMd_game�֐� - MD:�Q�[���̏�Ԑݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetStateMd_game(MD_GAME_STATE state)
{
	// MD:�Q�[����ʂ̏��̃|�C���^
	Md_game *pMd = &g_md_game;

	// ��Ԃɉ������I������
	EndMd_gameState();

	// ��Ԃ���
	pMd->state = state;

	// ��Ԃɉ������J�n����
	StartMd_gameState();
}