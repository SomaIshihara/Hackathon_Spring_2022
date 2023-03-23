//========================================
// 
// CHR:�v���C���[�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** chr_player.cpp ***
//========================================
#include <stdio.h>
#include "main.h"

#include "chr_player.h"	// CHR:�v���C���[
// R.N.Lib
#include "_R.N.Lib/R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
// CHR:�v���C���[�̏�������
#define CHR_PLAYER_INIT_ROT D3DXVECTOR3(0.0f,D3DX_PI,0.0f)
// CHR:�v���C���[�̒����_�̑��Έʒu�̈ړ��{��
#define CHR_PLAYER_RELATIVE_POS_R_MOVE_DIAMETER (0.25f)
// CHR:�v���C���[�̃��f���̃Z�b�g�A�b�v�ԍ�
#define CHR_PLAYER_MODEL_SETUP (3)
// CHR:�v���C���[�̈ړ���
#define CHR_PLAYER_MOVE (1.0f)
// CHR;�v���C���[�̈ړ���
#define CHR_PLAYER_MOVEWIDTH (80.0f)
// CHR;�v���C���[�̈ړ����s��
#define CHR_PLAYER_MOVEDEPTH (40.0f)
// CHR:�v���C���[�̉�]��
#define CHR_PLAYER_SPIN (0.1f)

//****************************************
// �񋓌^�̒�`
//****************************************
// ���[�V�����ԍ�
typedef enum 
{
	CHR_PLAYER_MOTION_WAIT,
	CHR_PLAYER_MOTION_MOVE,
	CHR_PLAYER_MOTION_SLOW,
	CHR_PLAYER_MOTION_MAX,
}CHR_PLAYER_MOTION;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �擾 ***
// CHR:�v���C���[�̃p�����[�^�[�̏����l��Ԃ�
void InitParameterChr_player(Chr_player *pChr);

//****************************************
// �O���[�o���錾
//****************************************
// CHR:�v���C���[�̏��
Chr_player g_chr_player;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================
//========================================
// InitParameterChr_player�֐� - CHR:�v���C���[�̃p�����[�^�[�̏����l��Ԃ� -
//========================================
void InitParameterChr_player(Chr_player *pChr)
{
	// ���i�Ǘ��̃p�����[�^�[������
	InitParts3DInfo(&pChr->partsInfo, CHR_PLAYER_MODEL_SETUP);
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
// InitChr_player�֐� - CHR:�v���C���[�̏��������� -
//========================================
void InitChr_player(void)
{
	// CHR:�v���C���[�̏��̃|�C���^
	Chr_player *pChr = &g_chr_player;

	// �p�����[�^�[�̏�����
	InitParameterChr_player(pChr);
}

//========================================
// UpdateChr_player�֐� - CHR:�v���C���[�̍X�V���� -
//========================================
void UpdateChr_player(void)
{
	// CHR:�v���C���[�̏��̃|�C���^
	Chr_player *pChr = &g_chr_player;
	// �v���C���[�̃Z�b�g�A�b�v���
	ModelSetUp setUp = GetModelSetUp(CHR_PLAYER_MODEL_SETUP);

	// ���i(3D)�̍X�V����
	UpdateParts3DInfo(&pChr->partsInfo);

	// �ړ�
	if (GetStick().aTplDiameter[STICK_TYPE_LEFT] > 0.01f)
	{
		// ���[�V�������ړ��ɐݒ�
		pChr->partsInfo.nMotion = CHR_PLAYER_MOTION_MOVE;

		// �ڕW�����ɃX�e�B�b�N�̊p�x����
		float fAngle = -GetStick().aAngle[STICK_TYPE_LEFT] + D3DX_PI;

		// �ړ�
		pChr->partsInfo.pos.x += sinf(fAngle) * CHR_PLAYER_MOVE;
		pChr->partsInfo.pos.z += cosf(fAngle) * CHR_PLAYER_MOVE;
	}
	else 
	{
		// ���[�V������ҋ@�ɐݒ�
		pChr->partsInfo.nMotion = CHR_PLAYER_MOTION_WAIT;
	}

	// ��]
	float fTplDiameter = GetStick().aTplDiameter[STICK_TYPE_RIGHT];
	if (fTplDiameter > 0.01f) 
	{
		if (GetStick().aAnglePress[STICK_TYPE_RIGHT][STICK_ANGLE_LEFT])
		{
			pChr->partsInfo.rot.y -= CHR_PLAYER_SPIN * fTplDiameter;
		}
		else if(GetStick().aAnglePress[STICK_TYPE_RIGHT][STICK_ANGLE_RIGHT])
		{
			pChr->partsInfo.rot.y += CHR_PLAYER_SPIN * fTplDiameter;
		}

		// �����𐧌�
		ControlAngle(&pChr->partsInfo.rot.y);
	}

	// �Փ˔���ɕK�v�ȏ����쐬
	CollisionInfo myCollInfo =
	{
		&pChr->partsInfo.pos,			// ���݂̈ʒu�̃|�C���^
		pChr->partsInfo.pos,			// �ߋ��̈ʒu
		NULL,							// �ړ��ʂ̃|�C���^
		&pChr->partsInfo.rot,			// ���݂̌����̃|�C���^
		pChr->partsInfo.rot,			// �ߋ��̌���
		&pChr->partsInfo,				// ���i�Ǘ����
		&setUp.partsSet,				// ���i�ݒ���
		&setUp.hitTestSet.aHitTest[0],	// �����蔻��̏��
		(COLLCHK_MODE)0,				// �Փ˃`�F�b�N�̃��[�h
	};
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================
//========================================
// GetChr_player�֐� - CHR:�v���C���[�̏��̃|�C���^���擾 -
//========================================
Chr_player *GetChr_player(void)
{
	return &g_chr_player;
}