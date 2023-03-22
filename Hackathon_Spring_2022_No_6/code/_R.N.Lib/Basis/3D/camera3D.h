//========================================
// 
// �J����(3D)�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// *** camera3D.h ***
//========================================
#ifndef _CAMERA3D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _CAMERA3D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

// R.N.Lib
#include "../Other/physics.h"

//****************************************
// �񋓌^�̒�`
//****************************************
// �J����(3D)�̏��
typedef enum
{
	CAMERA3D_STATE_VIBRATION,	// �U��
	CAMERA3D_STATE_MAX,
}CAMERA3D_STATE;

//****************************************
// �\���̂̒�`
//****************************************
// �J����(3D)�̏��\����
typedef struct 
{
	D3DXVECTOR3 posV;			// ���_
	D3DXVECTOR3 posR;			// �����_
	D3DXVECTOR3 posU;			// ������x�N�g��
	D3DXVECTOR3 move;			// �ړ���
	D3DXVECTOR3 rot;			// ����
	D3DXVECTOR3 spin;			// ��]��
	float fLength;				// ����
	float fHeight;				// ����
	float fVerticalMove;		// �c�����̈ړ���
	D3DXMATRIX mtxProjection;	// �v���W�F�N�V�����}�g���b�N�X
	D3DXMATRIX mtxView;			// �r���[�}�g���b�N�X
	float fVibration;			// �U���̋���
	int nCounterVib;			// �U���J�E���^�[
	D3DXVECTOR3 vibrationPos;	// �U���ʒu
}Camera3D;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// �J����(3D)�̏���������
void InitCamera3D(void);
// �J����(3D)�̏I������
void UninitCamera3D(void);
// �J����(3D)�̍X�V����
void UpdateCamera3D(void);
//========== *** �擾 ***
// �J����(3D)�̏����擾
Camera3D *GetCamera3D(void);
//========== *** ��� ***
// �J����(3D)�̃p�����[�^�[����������
void InitParameterCamera3D(void);
//========== *** �ݒ� ***
// �J����(3D)�̐ݒ菈��
void SetCamera3D(void);
// �J����(3D)�̎��_�̐ݒ菈��
void SetCamera3DPosV(D3DXVECTOR3 pos);
// �J����(3D)�̒����_�̐ݒ菈��
void SetCamera3DPosR(D3DXVECTOR3 pos);
// �J����(3D)�̐U����ݒ�
void SetCamera3DVibration(float fVibration);
//========== *** ���� ***
// �J����(3D)�̈ړ�����
void MoveCamera3D(DIRECTION drct, float fMove);
// �J����(3D)�̎���]����
void AxisRotationCamera3D(DIRECTION drct, float fRot);
// �J����(3D)�̉�]����
void RotationCamera3D(DIRECTION drct, float fRot);

#endif