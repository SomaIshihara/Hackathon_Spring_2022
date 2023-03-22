//========================================
// 
// ���͊֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** input.h ***
//========================================
#ifndef _INPUT_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _INPUT_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �}�N����`
//****************************************
//========== *** ��{��� ***
// �L�[�̍ő吔
#define NUM_KEY_MAX (256)

//****************************************
// �񋓌^�̒�`
//****************************************
// ���I�ȃf�o�C�X
typedef enum 
{
	ACTIVE_DEVICE_KEYBOARD,
	ACTIVE_DEVICE_CONTROLLER,
	ACTIVE_DEVICE_MAX,
}ACTIVE_DEVICE_TYPE;
// �}�E�X�ԍ�
typedef enum
{
	MOUSEBUTTON_LEFT,
	MOUSEBUTTON_RIGHT,
	MOUSEBUTTON_MAX,
}MOUSEBUTTON;
// �{�^���ԍ�
typedef enum 
{
	BUTTON_UP,				// ��L�[
	BUTTON_DOWN,			// ���L�[
	BUTTON_LEFT,			// ���L�[
	BUTTON_RIGHT,			// �E�L�[
	BUTTON_START,			// �X�^�[�g�L�[
	BUTTON_BACK,			// �o�b�N�L�[
	BUTTON_LEFT_THUMB,		// ���X�e�B�b�N
	BUTTON_RIGHT_THUMB,		// �E�X�e�B�b�N
	BUTTON_LEFT_SHOULDER,	// ���g���K�[
	BUTTON_RIGHT_SHOULDER,	// �E�g���K�[
	BUTTON_A,				// A�{�^��
	BUTTON_B,				// B�{�^��
	BUTTON_X,				// X�{�^��
	BUTTON_Y,				// Y�{�^��
	BUTTON_LEFT_TRIGGER,	// ���g���K�[
	BUTTON_RIGHT_TRIGGER,	// �E�g���K�[
	BUTTON_MAX,
}BUTTON;
// �X�e�B�b�N�ԍ�
typedef enum
{
	STICK_TYPE_LEFT,
	STICK_TYPE_RIGHT,
	STICK_TYPE_MAX
}STICK_TYPE;
// �X�e�B�b�N�̕���
typedef enum 
{
	STICK_ANGLE_UP,
	STICK_ANGLE_DOWN,
	STICK_ANGLE_LEFT,
	STICK_ANGLE_RIGHT,
	STICK_ANGLE_MAX,
}STICK_ANGLE;
// �}�E�X�z�C�[���̉�]���
typedef enum
{
	WHEELSPIN_NONE,		// ����
	WHEELSPIN_FRONT,	// �O��]
	WHEELSPIN_BACK,		// ���]
}WHEELSPIN;

//****************************************
// �\���̂̒�`
//****************************************
// �X�e�B�b�N�̓��͏��\����
typedef struct 
{
	// �X�e�B�b�N�̓|���
	float aTplDiameter[STICK_TYPE_MAX];
	// �X�e�B�b�N�̊p�x
	float aAngle[STICK_TYPE_MAX];
	// �X�e�B�b�N�̕����v���X���
	bool aAnglePress[STICK_TYPE_MAX][STICK_ANGLE_MAX];
	// �X�e�B�b�N�̕����g���K�[���
	bool aAngleTrigger[STICK_TYPE_MAX][STICK_ANGLE_MAX];
	// �X�e�B�b�N�̕������s�[�g���
	bool aAngleRepeat[STICK_TYPE_MAX][STICK_ANGLE_MAX];
	// �X�e�B�b�N�̕��������[�X���
	bool aAngleRelease[STICK_TYPE_MAX][STICK_ANGLE_MAX];
}StickInput;
// ���͏��\����
typedef struct
{
	// �L�[�{�[�h�֘A
	BYTE aKeyStatePress[NUM_KEY_MAX];		// �L�[�{�[�h�̃v���X���
	BYTE aKeyStateTrigger[NUM_KEY_MAX];		// �L�[�{�[�h�̃g���K�[���
	BYTE aKeyStateRelease[NUM_KEY_MAX];		// �L�[�{�[�h�̃����[�X���
	BYTE aKeyStateRepeat[NUM_KEY_MAX];		// �L�[�{�[�h�̃��s�[�g���
	DWORD aKeyCurrentTime[NUM_KEY_MAX];		// �L�[�{�[�h�̌��݂̎���
	DWORD aKeyExecLastTime[NUM_KEY_MAX];	// �L�[�{�[�h�̍Ō�ɐ^��Ԃ�������

	// �}�E�X�֘A
	BYTE aMouseState[MOUSEBUTTON_MAX];			// �}�E�X�̃v���X���
	BYTE aMouseStateTrigger[MOUSEBUTTON_MAX];	// �}�E�X�̃g���K�[���
	BYTE aMouseStateRelease[MOUSEBUTTON_MAX];	// �}�E�X�̃����[�X���
	BYTE aMouseStateRepeat[MOUSEBUTTON_MAX];	// �}�E�X�̃��s�[�g���
	DWORD aMouseCurrentTime[MOUSEBUTTON_MAX];	// �}�E�X�̌��݂̎���
	DWORD aMouseExecLastTime[MOUSEBUTTON_MAX];	// �}�E�X�̍Ō�ɐ^��Ԃ�������
	D3DXVECTOR3 cursorPosTemp;					// �J�[�\���̈ʒu��ۑ�
	D3DXVECTOR3 cursorMove;						// �J�[�\���̈ړ���
	WHEELSPIN wheelSpin;						// �}�E�X�z�C�[���̉�]���

	// �R���g���[���[�֘A
	bool aButtonPress[BUTTON_MAX];			// �{�^���̃v���X���
	bool aButtonTrigger[BUTTON_MAX];		// �{�^���̃g���K�[���
	bool aButtonRelease[BUTTON_MAX];		// �{�^���̃����[�X���
	bool aButtonRepeat[BUTTON_MAX];			// �{�^���̃��s�[�g���
	DWORD aButtonCurrentTime[BUTTON_MAX];	// �{�^���̌��݂̎���
	DWORD aButtonExecLastTime[BUTTON_MAX];	// �{�^���̍Ō�ɐ^��Ԃ�������
	StickInput stick;						// �X�e�B�b�N�̓��͏��
	// �X�e�B�b�N�̌��݂̎���
	DWORD aStickCurrentTime[STICK_TYPE_MAX][STICK_ANGLE_MAX];
	// �X�e�B�b�N�̍Ō�ɐ^��Ԃ�������
	DWORD aStickExecLastTime[STICK_TYPE_MAX][STICK_ANGLE_MAX];
	int nCounterVibration;		// �R���g���[���[�̐U���J�E���^�[
	int nCounterVibrationMax;	// �R���g���[���[�̐U���J�E���^�[�̍ő�l��ۑ�
	float fVibration;			// �U���{��
	XINPUT_STATE xInputState;	// XInput�̏��
}InputInfo;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// ���͊֘A�̏���������
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd);
// ���͊֘A�̏I������
void UninitInput(void);
// ���͊֘A�̍X�V����
void UpdateInput(void);
//========== *** �擾 ***
// ���͏����擾
InputInfo *GetInputInfo(void);
// XInput�̏�Ԃ��擾
XINPUT_STATE *GetXInputState(void);
// ��ʏ�̃J�[�\���̈ʒu���擾
D3DXVECTOR3 GetCursorPosOnScreen(void);
// �J�[�\���̈ړ��ʂ��擾
D3DXVECTOR3 GetCursorMove(void);
// �X�e�B�b�N�̓��͏����擾
StickInput GetStick(void);
// ���I�ȃf�o�C�X���擾
ACTIVE_DEVICE_TYPE GetActiveInputType(void);
//========== *** �L�[�{�[�h ***
// �L�[�{�[�h�̃v���X�����擾
bool GetKeyboardPress(int nKey);
// �L�[�{�[�h�̃g���K�[�����擾
bool GetKeyboardTrigger(int nKey);
// �L�[�{�[�h�̃��s�[�g�����擾
bool GetKeyboardRepeat(int nKey);
// �L�[�{�[�h�̃����[�X�����擾
bool GetKeyboardRelease(int nKey);
//========== *** �}�E�X ***
// �}�E�X�̃v���X�����擾
bool GetMousePress(int nMouse);
// �}�E�X�̃g���K�[�����擾
bool GetMouseTrigger(int nMouse);
// �}�E�X�̃��s�[�g�����擾
bool GetMouseRepeat(int nMouse);
// �}�E�X�̃����[�X�����擾
bool GetMouseRelease(int nMouse);
// �}�E�X�z�C�[���̉�]��Ԃ��擾
WHEELSPIN GetWheelSpin(void);
//========== *** �{�^�� ***
// �{�^���̃v���X�����擾
bool GetButtonPress(int nButton);
// �{�^���̃g���K�[�����擾
bool GetButtonTrigger(int nButton);
// �{�^���̃��s�[�g�����擾
bool GetButtonRepeat(int nButton);
// �{�^���̃����[�X�����擾
bool GetButtonRelease(int nButton);
//========== *** �R���g���[���[ ***
// �R���g���[���[�̐U���ݒ菈��
void SetVibration(float fVibration, int nTime);
//========== *** ���̑� ***
// ���͏��̃N���A����
void ClearInputInfo(void);

#endif