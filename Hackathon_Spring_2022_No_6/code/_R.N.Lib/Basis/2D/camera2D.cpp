//========================================
// 
// �J����(2D)�̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** camera2D.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
// �J����(2D)�̐U���ɂ����鎞��
#define CAMERA2D_VIBRATION_TIME (20)
// �J����(2D)��1�x�̐U���ɂ����鎞��
#define CAMERA2D_ONCE_VIBRATION_TIME (2)
// �J����(2D)�̐U���̌����{��
#define CAMERA2D_VIBRATION_DAMPING (0.75f)
// �J����(2D)�̐U�����R���g���[���[�̐U���̎��Ԃɕϊ�����ۂ̔{��
#define CONTROLLER_CAMERA2D_VIBRATION_TIME_DIAMETER (5)
// �J����(2D)�̐U�����R���g���[���[�̐U���̍ő�l�ɒB����l
#define CONTROLLER_CAMERA2D_VIBRATION_MAX_VIBRATION (16.0f)

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �擾 ***
// �J����(2D)�̃p�����[�^�[����������
void InitParameterCamera2D(void);
//========== *** �X�V ***
// �J����(2D)�̏�ԏ���
void StateProcessCamera2D(void);

//****************************************
// �O���[�o���ϐ�
//****************************************
static Camera2D g_camera2D;	// �J����(2D)�̏��

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================
//========================================
// InitParameterCamera2D�֐� - �J����(2D)�̃p�����[�^�[���������� -
// Author:RIKU NISHIMURA
//========================================
void InitParameterCamera2D(void)
{
	g_camera2D.bTemp = false;	// �t���O�ۑ�
	g_camera2D.bMove = false;	// �ړ��t���O
}

//============================================================
//--------------------| *** �X�V *** |------------------------
//============================================================
//========================================
// StateProcessCamera2D�֐� - �J����(2D)�̏�ԏ��� -
// Author:RIKU NISHIMURA
//========================================
void StateProcessCamera2D(void)
{
	for (int nCntState = 0; nCntState < CAMERA2D_STATE_MAX; nCntState++)
	{
		if (g_camera2D.aState[nCntState])
		{// ���̏�Ԃ��^�̎��A
			switch (nCntState)
			{
			case CAMERA2D_STATE_VIBRATION:

				if (g_camera2D.aCounterState[CAMERA2D_STATE_VIBRATION] < CAMERA2D_VIBRATION_TIME)
				{// �U���J�E���^�[���U���ɂ����鎞�Ԃ�������Ă��鎞�A
					// �U���J�E���^�[�����Z
					g_camera2D.aCounterState[CAMERA2D_STATE_VIBRATION]++;

					if ((g_camera2D.aCounterState[CAMERA2D_STATE_VIBRATION] % CAMERA2D_ONCE_VIBRATION_TIME) == 0)
					{// �U���J�E���^�[��1�x�̐U���ɂ����鎞�ԂɒB�������A
						float	fAngle	// �p�x�𗐐��Őݒ�
								= -D3DX_PI + fRand(D3DX_PI * 2);

						// �U���̖ڕW�ʒu��ݒ�
						g_camera2D.vibrationTargetPos.x = sinf(fAngle) * g_camera2D.fVibration;
						g_camera2D.vibrationTargetPos.y = cosf(fAngle) * g_camera2D.fVibration;

						// �U���̋���������������
						g_camera2D.fVibration *= CAMERA2D_VIBRATION_DAMPING;
					}
				}
				else
				{// �U���J�E���^�[���o���ɂ����鎞�ԂɒB�������A
					// �U���t���O���U�ɂ���
					g_camera2D.aState[CAMERA2D_STATE_VIBRATION] = false;
				}

				break;
			}
		}
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// GetCamera2Ds�֐� - �J����(2D)�̏����擾 -
// Author:RIKU NISHIMURA
//========================================
Camera2D *GetCamera2D(void)
{
	return &g_camera2D;
}

//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================
//========================================
// InitCamera2D�֐� - �J����(2D)�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitCamera2D(void)
{
	
}

//========================================
// UninitCamera2D�֐� - �J����(2D)�̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitCamera2D(void)
{
	
}

//========================================
// UpdateCamera2D�֐� - �J����(2D)�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateCamera2D(void)
{
	
}

//============================================================
//--------------------| *** ���̑� *** |----------------------
//============================================================
//========================================
// MatchCamera2DPosition�֐� - �`��ʒu���J����(2D)�ɍ��킹�� -
// Author:RIKU NISHIMURA
//========================================
void MatchCamera2DPosition(D3DXVECTOR3 *pDrawPos)
{
	// �`��ʒu���J�����ɍ��킹��
	MatchPosition(pDrawPos, g_camera2D.pos, 0, 0);

	// �`��ʒu�ɐU���ʒu���X�V����
	*pDrawPos += g_camera2D.vibrationPos;
}

//========================================
// SetCamera2DVibration�֐� - �J����(2D)�̐U����ݒ� -
// Author:RIKU NISHIMURA
//========================================
void SetCamera2DVibration(float fVibration)
{
	// �U����Ԃ�^�ɂ���
	g_camera2D.aState[CAMERA2D_STATE_VIBRATION] = true;
	g_camera2D.aCounterState[CAMERA2D_STATE_VIBRATION] = 0;

	// �U���̋�����ݒ�
	g_camera2D.fVibration += fVibration;

	// �R���g���[���[�̐U����ݒ�
	SetVibration(
		fVibration / CONTROLLER_CAMERA2D_VIBRATION_MAX_VIBRATION, 
		fVibration * CONTROLLER_CAMERA2D_VIBRATION_TIME_DIAMETER);
}
