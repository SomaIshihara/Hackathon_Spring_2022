//========================================
// 
// �J����(3D)�̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** camera3D.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
//========== *** �����p�����[�^�[ ***
// �J����(3D)��1�x�̐U���ɂ����鎞��
#define CAMERA3D_ONCE_VIBRATION_TIME (2)
// �J����(3D)�̐U���̌����{��
#define CAMERA3D_VIBRATION_DAMPING (0.75f)
// �J����(3D)�̐U���̋����̉���
#define CAMERA3D_VIBRATION_MIN (0.01f)
// �J����(3D)�̐U�����R���g���[���[�̐U���̎��Ԃɕϊ�����ۂ̔{��
#define CONTROLLER_CAMERA3D_VIBRATION_TIME_DIAMETER	(5)
// �J����(3D)�̐U�����R���g���[���[�̐U���̍ő�l�ɒB����l
#define CONTROLLER_CAMERA3D_VIBRATION_MAX_VIBRATION	(4.0f)
//========== *** �����p�����[�^�[ ***
// �J����(3D)�̏����̎��_
#define CAMERA3D_INIT_POS_V (D3DXVECTOR3(0.0f,0.0f,0.0f))
// �J����(3D)�̏����̒����_
#define CAMERA3D_INIT_POS_R (D3DXVECTOR3(0.0f,0.0f,0.0f))
// �J����(3D)�̏����̏�����x�N�g��
#define CAMERA3D_INIT_POS_U (D3DXVECTOR3(0.0f,1.0f,0.0f))
// �J����(3D)�̏����̌���
#define CAMERA3D_INIT_ROT (D3DXVECTOR3(0.0f,0.0f,0.0f))
// �J����(3D)�̏����̋���
#define CAMERA3D_INIT_LENGTH (80.0f)
// �J����(3D)�̏����̍���
#define CAMERA3D_INIT_HEIGHT (0.25f)

//****************************************
// �O���[�o���ϐ�
//****************************************
static Camera3D g_camera3D;	// �J����(3D)�̏��

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================
//========================================
// InitCamera3D�֐� - �J����(3D)�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitCamera3D(void)
{
	// �p�����[�^�[�̏���������
	InitParameterCamera3D();
}

//========================================
// UninitCamera3D�֐� - �J����(3D)�̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitCamera3D(void)
{
	
}

//========================================
// UpdateCamera3D�֐� - �J����(3D)�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateCamera3D(void)
{
	if (g_camera3D.fVibration >= CAMERA3D_VIBRATION_MIN)
	{// �U���̋������U���̋����̉����ȏ�̎��A
		if (--g_camera3D.nCounterVib <= 0)
		{// �U���J�E���^�[�����Z��������0�ȉ��̎��A
			g_camera3D.nCounterVib = CAMERA3D_ONCE_VIBRATION_TIME;	// �U���J�E���^�[��ݒ�
			float fAngle = -D3DX_PI + fRand(D3DX_PI * 2);			// �����𗐐��Őݒ�
			g_camera3D.vibrationPos.x = sinf(fAngle) * g_camera3D.fVibration;
			g_camera3D.vibrationPos.y = cosf(fAngle) * g_camera3D.fVibration;
			g_camera3D.fVibration *= CAMERA3D_VIBRATION_DAMPING;	// �U���̋���������
		}
	}
	else
	{// �U���̋������U���̋����̉��������̎��A�U���ʒu��������
		g_camera3D.vibrationPos = INITD3DXVECTOR3;
	}
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================
//========================================
// GetCamera3D�֐� - �J����3D�̏����擾 -
// Author:RIKU NISHIMURA
//========================================
Camera3D *GetCamera3D(void)
{
	return &g_camera3D;
}

//============================================================
//--------------------| *** ��� *** |------------------------
//============================================================
//========================================
// InitParameterCamera3D�֐� - �J����(3D)�̃p�����[�^�[���������� -
// Author:RIKU NISHIMURA
//========================================
void InitParameterCamera3D(void)
{
	g_camera3D.posV				= CAMERA3D_INIT_POS_V;	// ���_
	g_camera3D.posR				= CAMERA3D_INIT_POS_R;	// �����_
	g_camera3D.posU				= CAMERA3D_INIT_POS_U;	// ������x�N�g��
	g_camera3D.move				= INITD3DXVECTOR3;		// �ړ���
	g_camera3D.rot				= CAMERA3D_INIT_ROT;	// ����
	g_camera3D.spin				= INITD3DXVECTOR3;		// ��]��
	g_camera3D.fLength			= CAMERA3D_INIT_LENGTH;	// ����
	g_camera3D.fHeight			= CAMERA3D_INIT_HEIGHT;	// ����
	g_camera3D.fVerticalMove	= 0.0f;					// �c�����̈ړ���
	g_camera3D.fVibration		= 0.0f;					// �U���̋���
	g_camera3D.nCounterVib		= 0;					// �U���J�E���^�[
	g_camera3D.vibrationPos		= INITD3DXVECTOR3;		// �U���ʒu
}

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================
//========================================
// SetCamera3D�֐� - �J����(3D)�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetCamera3D(void) 
{
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();	// �f�o�C�X�擾

	// �v���W�F�N�V�����}�g���b�N�X�̏���������
	D3DXMatrixIdentity(&g_camera3D.mtxProjection);

	{
		// �E�B���h�E�̏��
		WindowMemory windowInfo = *GetWindowMemory();

		// �v���W�F�N�V�����}�g���b�N�X���쐬
		D3DXMatrixPerspectiveFovLH(&g_camera3D.mtxProjection, D3DXToRadian(45.0f), windowInfo.fWindowWidth / windowInfo.fWindowHeight, 10.0f, 4000.0f);
	}

	// �v���W�F�N�V�����}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_PROJECTION, &g_camera3D.mtxProjection);

	// �r���[�}�g���b�N�X�̐ݒ�
	D3DXMatrixIdentity(&g_camera3D.mtxView);

	{
		D3DXVECTOR3 posV = g_camera3D.posV;	// ���_
		D3DXVECTOR3 posR = g_camera3D.posR;	// �����_

		if (g_camera3D.vibrationPos != INITD3DXVECTOR3) 
		{// �U���ʒu�ɕϓ������鎞�A
			float fAngle = FindAngleLookDown(g_camera3D.posV, g_camera3D.posR) - (D3DX_PI * 0.5f);
			D3DXVECTOR3 addPos;	// ���Z�ʒu��U���ʒu�ɉ����Đݒ�
			addPos.x = sinf(fAngle) * g_camera3D.vibrationPos.x;
			addPos.z = cosf(fAngle) * g_camera3D.vibrationPos.x;
			addPos.y = g_camera3D.vibrationPos.y;

			// ���_/�����_�ɉ��Z�ʒu��K�p
			posV += addPos;
			posR += addPos;
		}
		
		// �r���[�}�g���b�N�X�̍쐬
		D3DXMatrixLookAtLH(&g_camera3D.mtxView, &posV, &posR, &g_camera3D.posU);
	}
	
	// �r���[�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_VIEW, &g_camera3D.mtxView);
}

//========================================
// SetCamera3DPosV�֐� - �J����(3D)�̎��_�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetCamera3DPosV(D3DXVECTOR3 pos) 
{
	// ���_�̈ʒu����
	g_camera3D.posV = pos;

	// �����_�̈ʒu��ݒ�
	g_camera3D.posR.x = g_camera3D.posV.x + (sinf(g_camera3D.rot.y) * (g_camera3D.fLength * (1.0f - fabsf(g_camera3D.fHeight))));
	g_camera3D.posR.y = g_camera3D.posV.y + (g_camera3D.fLength * g_camera3D.fHeight);
	g_camera3D.posR.z = g_camera3D.posV.z + (cosf(g_camera3D.rot.y) * (g_camera3D.fLength * (1.0f - fabsf(g_camera3D.fHeight))));
}

//========================================
// SetCamera3DPosR�֐� - �J����(3D)�̒����_�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetCamera3DPosR(D3DXVECTOR3 pos)
{
	// �����_�̈ʒu����
	g_camera3D.posR = pos;

	// ���_�̈ʒu��ݒ�
	g_camera3D.posV.x = g_camera3D.posR.x + (sinf(g_camera3D.rot.y + D3DX_PI) * (g_camera3D.fLength * (1.0f - fabsf(g_camera3D.fHeight))));
	g_camera3D.posV.y = g_camera3D.posR.y + (g_camera3D.fLength * g_camera3D.fHeight);
	g_camera3D.posV.z = g_camera3D.posR.z + (cosf(g_camera3D.rot.y + D3DX_PI) * (g_camera3D.fLength * (1.0f - fabsf(g_camera3D.fHeight))));
}

//========================================
// SetCamera3DVibration�֐� - �J����(3D)�̐U����ݒ� -
// Author:RIKU NISHIMURA
//========================================
void SetCamera3DVibration(float fVibration)
{
	// �U���̋�����ݒ�
	g_camera3D.fVibration += fVibration;

	// �U���J�E���^�[��������
	g_camera3D.nCounterVib = 0;

	// �R���g���[���[�̐U����ݒ�
	SetVibration(
		fVibration / CONTROLLER_CAMERA3D_VIBRATION_MAX_VIBRATION,
		fVibration * CONTROLLER_CAMERA3D_VIBRATION_TIME_DIAMETER);
}

//============================================================
//--------------------| *** ���� *** |------------------------
//============================================================
//========================================
// MoveCamera3D�֐� - �J����(3D)�̈ړ����� -
// Author:RIKU NISHIMURA
//========================================
void MoveCamera3D(DIRECTION drct, float fMove)
{
	// �����ɉ����Ď��_�ʒu���X�V
	switch (drct)
	{
	case DIRECTION_UP:g_camera3D.posV.z += fMove; break;	// ��
	case DIRECTION_DOWN:g_camera3D.posV.z -= fMove; break;	// ��
	case DIRECTION_LEFT:g_camera3D.posV.x += fMove; break;	// ��
	case DIRECTION_RIGHT:g_camera3D.posV.x -= fMove; break;	// �E
	}

	// �����_�̈ʒu��ݒ�
	g_camera3D.posR.x = g_camera3D.posV.x + (sinf(g_camera3D.rot.y) * (g_camera3D.fLength * (1.0f - fabsf(g_camera3D.fHeight))));
	g_camera3D.posR.y = g_camera3D.posV.y + (g_camera3D.fLength * g_camera3D.fHeight);
	g_camera3D.posR.z = g_camera3D.posV.z + (cosf(g_camera3D.rot.y) * (g_camera3D.fLength * (1.0f - fabsf(g_camera3D.fHeight))));
}

//========================================
// AxisRotationCamera3D�֐� - �J����(3D)�̎���]���� -
// Author:RIKU NISHIMURA
//========================================
void AxisRotationCamera3D(DIRECTION drct, float fRot)
{
	// �����ɉ����Č����̈ړ��ʂ��X�V
	switch (drct)
	{
	case DIRECTION_UP:g_camera3D.fVerticalMove += fRot; break;
	case DIRECTION_DOWN:g_camera3D.fVerticalMove -= fRot; break;
	case DIRECTION_LEFT:g_camera3D.spin.y -= fRot; break;
	case DIRECTION_RIGHT:g_camera3D.spin.y += fRot; break;
	}
}

//========================================
// RotationCamera3D�֐� - �J����(3D)�̉�]���� -
// Author:RIKU NISHIMURA
//========================================
void RotationCamera3D(DIRECTION drct, float fRot)
{
	// �����ɉ����Č������X�V
	switch (drct)
	{
	case DIRECTION_UP:g_camera3D.fHeight += fRot; break;
	case DIRECTION_DOWN:g_camera3D.fHeight -= fRot; break;
	case DIRECTION_LEFT:g_camera3D.rot.y -= fRot; break;
	case DIRECTION_RIGHT:g_camera3D.rot.y += fRot; break;
	}

	// �����𐧌�
	RotControl(&g_camera3D.rot);

	// �����_�̈ʒu��ݒ�
	g_camera3D.posR.x = g_camera3D.posV.x + (sinf(g_camera3D.rot.y) * (g_camera3D.fLength * (1.0f - fabsf(g_camera3D.fHeight))));
	g_camera3D.posR.y = g_camera3D.posV.y + (g_camera3D.fLength * g_camera3D.fHeight);
	g_camera3D.posR.z = g_camera3D.posV.z + (cosf(g_camera3D.rot.y) * (g_camera3D.fLength * (1.0f - fabsf(g_camera3D.fHeight))));
}
