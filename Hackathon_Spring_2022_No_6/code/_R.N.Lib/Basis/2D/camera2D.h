//========================================
// 
// �J����(2D)�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// *** camera2D.h ***
//========================================
#ifndef _CAMERA2D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _CAMERA2D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �񋓌^�̒�`
//****************************************
// �J�����̏��
typedef enum
{
	CAMERA2D_STATE_VIBRATION,	// �U��
	CAMERA2D_STATE_MAX,
}CAMERA2D_STATE;

//****************************************
// �\���̂̒�`
//****************************************
// �J����(2D)�̏��\����
typedef struct
{
	//========== *** �ʒu�֘A ***
	D3DXVECTOR3 pos;				// �ʒu
	D3DXVECTOR3 posOld;				// ���̈ʒu
	D3DXVECTOR3 vibrationPos;		// �U���ʒu
	D3DXVECTOR3 vibrationTargetPos;	// �U���̖ڕW�ʒu
	D3DXVECTOR3 *pTargetPos;		// �ڕW�ʒu�̃|�C���^
	D3DXVECTOR3 targetRelativePos;	// �ڕW�ʒu�̃|�C���^

	//========== *** ��Ԋ֘A ***
	// ��ԃt���O
	bool aState[CAMERA2D_STATE_MAX];
	// ��ԊǗ��J�E���^�[
	int aCounterState[CAMERA2D_STATE_MAX];
	float fVibration;	// �U���̋���
	bool bTemp;			// �t���O�ۑ�
	bool bMove;			// �ړ��t���O
	int nCounterMove;	// �ړ��J�E���^�[
}Camera2D;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �擾 ***
// �J����(2D)�̏����擾
Camera2D *GetCamera2D(void);
//========== *** ��{�ڑ� ***
// �J����(2D)�̏���������
void InitCamera2D(void);
// �J����(2D)�̏I������
void UninitCamera2D(void);
// �J����(2D)�̍X�V����
void UpdateCamera2D(void);
//========== *** ���̑� ***
// �`��ʒu���J����(2D)�̈ʒu�ɍ��킹��
void MatchCamera2DPosition(D3DXVECTOR3 *pDrawPos);
// �J����(2D)�̐U����ݒ�
void SetCamera2DVibration(float fVibration);

#endif