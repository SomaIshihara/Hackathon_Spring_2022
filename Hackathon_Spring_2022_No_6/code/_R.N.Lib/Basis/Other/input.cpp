//========================================
// 
// ���͊֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** input.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
//========== *** �����p�����[�^�[ ***
// ���s�[�g�̊Ԋu
#define REPEATE_INTERVAL (160)
// �U���̌��Z��
#define VIBRATION_SUBTRACT (0.02f)

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �擾 ***
// �X�e�B�b�N�̓��͏��̃p�����[�^�[�����l��Ԃ�
StickInput InitParameterStickInput(void);
// ���͏��̃p�����[�^�[�����l��Ԃ�
InputInfo InitParameterInputInfo(void);
//========== *** �X�V ***
// �L�[�{�[�h�̍X�V����
void UpdateKeyboard(void);
// �}�E�X�̍X�V����
void UpdateMouse(void);
// �J�[�\���̍X�V����
void UpdateCursor(void);
// �{�^���̍X�V����
void UpdateButton(void);
// �X�e�B�b�N�̍X�V����
void UpdateStick(void);
// �R���g���[���[�̐U���̍X�V����
void UpdateVibration(void);

//****************************************
// �O���[�o���ϐ��錾
//****************************************
LPDIRECTINPUT8 g_pInput = NULL;				// DirectInput�I�u�W�F�N�g�ւ̃|�C���^
LPDIRECTINPUTDEVICE8 g_pDevKeyboard = NULL;	// ���̓f�o�C�X(�L�[�{�[�h)�ւ̃|�C���^
InputInfo g_inputInfo;						// ���͏��
ACTIVE_DEVICE_TYPE g_activeInputType;		// ���I�ȃf�o�C�X

//****************************************
// �O���[�o���萔�錾
//****************************************
// �}�E�X�̃}�X�N
const int g_aMouseMask[MOUSEBUTTON_MAX] = {
	VK_LBUTTON,
	VK_RBUTTON,
};
// �{�^���̃}�X�N
const int g_aButtonMask[BUTTON_MAX] = {
	XINPUT_GAMEPAD_DPAD_UP,
	XINPUT_GAMEPAD_DPAD_DOWN,
	XINPUT_GAMEPAD_DPAD_LEFT,
	XINPUT_GAMEPAD_DPAD_RIGHT,
	XINPUT_GAMEPAD_START,
	XINPUT_GAMEPAD_BACK,
	XINPUT_GAMEPAD_LEFT_THUMB,
	XINPUT_GAMEPAD_RIGHT_THUMB,
	XINPUT_GAMEPAD_LEFT_SHOULDER,
	XINPUT_GAMEPAD_RIGHT_SHOULDER,
	XINPUT_GAMEPAD_A,
	XINPUT_GAMEPAD_B,
	XINPUT_GAMEPAD_X,
	XINPUT_GAMEPAD_Y,
	-1,
	-1,
};

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================
//========================================
// InitParameterStickInput�֐� - �X�e�B�b�N�̓��͏��̃p�����[�^�[�����l��Ԃ� -
// Author:RIKU NISHIMURA
//========================================
StickInput InitParameterStickInput(void)
{
	return{
		{ 0.0f },
		{ 0.0f },
		{ { false } },
		{ { false } },
		{ { false } },
		{ { false } },
	};
}

//========================================
// InitParameterInputInfo�֐� - ���͏��̃p�����[�^�[�����l��Ԃ� -
// Author:RIKU NISHIMURA
//========================================
InputInfo InitParameterInputInfo(void) 
{
	return{
		{ 0 },						// �L�[�{�[�h�̃v���X���
		{ 0 },						// �L�[�{�[�h�̃g���K�[���
		{ 0 },						// �L�[�{�[�h�̃����[�X���
		{ 0 },						// �L�[�{�[�h�̃��s�[�g���
		{ 0 },						// �L�[�{�[�h�̌��݂̎���
		{ 0 },						// �L�[�{�[�h�̍Ō�ɐ^��Ԃ�������
		{ 0 },						// �}�E�X�̃v���X���
		{ 0 },						// �}�E�X�̃g���K�[���
		{ 0 },						// �}�E�X�̃����[�X���
		{ 0 },						// �}�E�X�̃��s�[�g���
		{ 0 },						// �}�E�X�̌��݂̎���
		{ 0 },						// �}�E�X�̍Ō�ɐ^��Ԃ�������
		GetCursorPosOnScreen(),		// �J�[�\���̈ʒu��ۑ�
		INITD3DXVECTOR3,			// �J�[�\���̈ړ���
		WHEELSPIN_NONE,				// �}�E�X�z�C�[���̉�]���
		{ false },					// �{�^���̃v���X���
		{ false },					// �{�^���̃g���K�[���
		{ false },					// �{�^���̃����[�X���
		{ false },					// �{�^���̃��s�[�g���
		{ 0 },						// �{�^���̌��݂̎���
		{ 0 },						// �{�^���̍Ō�ɐ^��Ԃ�������
		InitParameterStickInput(),	// �X�e�B�b�N�̓��͏��
		{ 0 },						// �X�e�B�b�N�̌��݂̎���
		{ 0 },						// �X�e�B�b�N�̍Ō�ɐ^��Ԃ�������
		0,							// �R���g���[���[�̐U���J�E���^�[
		0,							// �R���g���[���[�̐U���J�E���^�[�̍ő�l��ۑ�
		0.0f,						// �U���{��
		{},							// XInput�̏��
	};
}

//============================================================
//--------------------| *** �X�V *** |----------------------
//============================================================
//========================================
// UpdateKeyboard�֐� - �L�[�{�[�h�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateKeyboard(void)
{
	// �L�[�{�[�h�̓��͏��
	BYTE aKeyState[NUM_KEY_MAX];

	// ���̓f�o�C�X����f�[�^���擾
	if (SUCCEEDED(g_pDevKeyboard->GetDeviceState(sizeof(aKeyState), &aKeyState[0])))
	{
		for (int nCntKey = 0; nCntKey < NUM_KEY_MAX; nCntKey++)
		{
			// �L�[�{�[�h�̃g���K�[����ۑ�
			g_inputInfo.aKeyStateTrigger[nCntKey] = (g_inputInfo.aKeyStatePress[nCntKey] ^ aKeyState[nCntKey])&aKeyState[nCntKey];

			// �L�[�{�[�h�̃����[�X����ۑ�
			g_inputInfo.aKeyStateRelease[nCntKey] = (g_inputInfo.aKeyStatePress[nCntKey] ^ aKeyState[nCntKey])&~aKeyState[nCntKey];

			// ���݂̎��Ԃ��擾
			g_inputInfo.aKeyCurrentTime[nCntKey] = timeGetTime();

			if (aKeyState[nCntKey] && ((g_inputInfo.aKeyCurrentTime[nCntKey] - g_inputInfo.aKeyExecLastTime[nCntKey]) > REPEATE_INTERVAL))
			{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
				// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
				g_inputInfo.aKeyExecLastTime[nCntKey] = g_inputInfo.aKeyCurrentTime[nCntKey];

				// �L�[�{�[�h�̃��s�[�g����ۑ�
				g_inputInfo.aKeyStateRepeat[nCntKey] = aKeyState[nCntKey];
			}
			else
			{
				// �L�[�{�[�h�̃��s�[�g����ۑ�
				g_inputInfo.aKeyStateRepeat[nCntKey] = 0;
			}

			// �L�[�{�[�h�̃v���X����ۑ�
			g_inputInfo.aKeyStatePress[nCntKey] = aKeyState[nCntKey];

			if (aKeyState[nCntKey])
			{// ���͂��s��ꂽ���A
				// ���I�ȃf�o�C�X���L�[�{�[�h�ɂ���
				g_activeInputType = ACTIVE_DEVICE_KEYBOARD;
			}
		}
	}
	else
	{// ���̓f�o�C�X����f�[�^���擾�ł��Ȃ��������A
		// �L�[�{�[�h�ւ̃A�N�Z�X�����擾
		g_pDevKeyboard->Acquire();
	}
}

//========================================
// UpdateMouse�֐� - �}�E�X�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateMouse(void)
{
	// ��ʂɃt�H�[�J�X���������Ă��邩�ǂ������ׂ�
	bool bWindowFocused = IsWindowFocused(*GetWindowHandle());

	for (int nCntMouse = 0; nCntMouse < MOUSEBUTTON_MAX; nCntMouse++)
	{
		// �}�E�X�̓��͏��
		BYTE mouseState = GetKeyState(g_aMouseMask[nCntMouse]) & (0x80) ? true : false;
		
		if (!bWindowFocused) 
		{// ��ʂɃt�H�[�J�X���������Ă��Ȃ����A
			mouseState = false;	// ���͂��U�ɂ���
		}

		// �}�E�X�̃g���K�[����ۑ�
		g_inputInfo.aMouseStateTrigger[nCntMouse] = (g_inputInfo.aMouseState[nCntMouse] ^ mouseState)&mouseState;

		// �}�E�X�̃����[�X����ۑ�
		g_inputInfo.aMouseStateRelease[nCntMouse] = (g_inputInfo.aMouseState[nCntMouse] ^ mouseState)&~mouseState;

		// ���݂̎��Ԃ��擾
		g_inputInfo.aMouseCurrentTime[nCntMouse] = timeGetTime();

		if (mouseState && ((g_inputInfo.aMouseCurrentTime[nCntMouse] - g_inputInfo.aMouseExecLastTime[nCntMouse]) > REPEATE_INTERVAL))
		{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
			// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
			g_inputInfo.aMouseExecLastTime[nCntMouse] = g_inputInfo.aMouseCurrentTime[nCntMouse];

			// �}�E�X�̃��s�[�g����ۑ�
			g_inputInfo.aMouseStateRepeat[nCntMouse] = mouseState;
		}
		else
		{// �L�[�����͂���Ă��Ȃ��A�������͌��݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă��Ȃ����A
			// �}�E�X�̃��s�[�g����ۑ�
			g_inputInfo.aMouseStateRepeat[nCntMouse] = 0;
		}

		// �}�E�X�̃v���X����ۑ�
		g_inputInfo.aMouseState[nCntMouse] = mouseState;

		if (mouseState)
		{// ���͂��s��ꂽ���A
			// ���I�ȃf�o�C�X���L�[�{�[�h�ɂ���
			g_activeInputType = ACTIVE_DEVICE_KEYBOARD;
		}
	}
}

//========================================
// UpdateCursor�֐� - �J�[�\���̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateCursor(void)
{
	if (g_inputInfo.cursorPosTemp != GetCursorPosOnScreen()) 
	{// �J�[�\���̌��݈ʒu���ۑ��ʒu���قȂ鎞�A
		// ���I�ȃf�o�C�X���L�[�{�[�h�ɂ���
		g_activeInputType = ACTIVE_DEVICE_KEYBOARD;
	}

	// �J�[�\���̈ړ��ʂ�ݒ�
	g_inputInfo.cursorMove = GetCursorPosOnScreen() - g_inputInfo.cursorPosTemp;

	// �J�[�\���ʒu��ۑ�
	g_inputInfo.cursorPosTemp = GetCursorPosOnScreen();
}

//========================================
// UpdateButton�֐� - �{�^���̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateButton(void)
{
	// �{�^���̓��͏��
	bool aButton[BUTTON_MAX] = { false };

	for (int nCntButton = 0; nCntButton < BUTTON_MAX; nCntButton++)
	{
		if (nCntButton == BUTTON_LEFT_TRIGGER)
		{// �J�E���g�����g���K�[�̎��A
			if (GetXInputState()->Gamepad.bLeftTrigger > 0)
			{// �������܂�Ă���
				aButton[nCntButton] = true;
			}
		}
		else if (nCntButton == BUTTON_RIGHT_TRIGGER)
		{// �J�E���g���E�g���K�[�̎��A
			if (GetXInputState()->Gamepad.bRightTrigger > 0)
			{// �������܂�Ă���
				aButton[nCntButton] = true;
			}
		}
		else if (GetXInputState()->Gamepad.wButtons & g_aButtonMask[nCntButton])
		{// ���͏����X�V
			aButton[nCntButton] = true;
		}

		// �{�^���̃g���K�[����ۑ�
		g_inputInfo.aButtonTrigger[nCntButton] = (g_inputInfo.aButtonPress[nCntButton] ^ aButton[nCntButton])&aButton[nCntButton];

		// �{�^���̃����[�X����ۑ�
		g_inputInfo.aButtonRelease[nCntButton] = (g_inputInfo.aButtonPress[nCntButton] ^ aButton[nCntButton])&~aButton[nCntButton];

		// ���݂̎��Ԃ��擾
		g_inputInfo.aButtonCurrentTime[nCntButton] = timeGetTime();

		if (aButton[nCntButton] && ((g_inputInfo.aButtonCurrentTime[nCntButton] - g_inputInfo.aButtonExecLastTime[nCntButton]) > REPEATE_INTERVAL))
		{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
			// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
			g_inputInfo.aButtonExecLastTime[nCntButton] = g_inputInfo.aButtonCurrentTime[nCntButton];

			// �{�^���̃��s�[�g����ۑ�
			g_inputInfo.aButtonRepeat[nCntButton] = aButton[nCntButton];
		}
		else
		{
			// �{�^���̃��s�[�g����ۑ�
			g_inputInfo.aButtonRepeat[nCntButton] = 0;
		}

		// �{�^���̃v���X����ۑ�
		g_inputInfo.aButtonPress[nCntButton] = aButton[nCntButton];

		if (aButton[nCntButton])
		{// ���͂��s��ꂽ���A
			// ���I�ȃf�o�C�X���R���g���[���[�ɂ���
			g_activeInputType = ACTIVE_DEVICE_CONTROLLER;
		}
	}
}

//========================================
// UpdateStick�֐� - �X�e�B�b�N�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateStick(void)
{
	// �X�e�B�b�N�̓��͏��
	bool bAngle[STICK_TYPE_MAX][STICK_ANGLE_MAX];

	// XInput�̏�Ԃ��擾
	g_inputInfo.xInputState.dwPacketNumber = XInputGetState(g_inputInfo.xInputState.dwPacketNumber, &g_inputInfo.xInputState);

	for (int nCntStick = 0; nCntStick < STICK_TYPE_MAX; nCntStick++)
	{
		float X;	// �X�e�B�b�N��X��
		float Y;	// �X�e�B�b�N��Y��

		// ��ނɉ������X�e�B�b�N�̎��̒l���擾
		switch (nCntStick)
		{
		case STICK_TYPE_LEFT:
			X = GetXInputState()->Gamepad.sThumbLX;
			Y = GetXInputState()->Gamepad.sThumbLY;
			break;
		case STICK_TYPE_RIGHT:
			X = GetXInputState()->Gamepad.sThumbRX;
			Y = GetXInputState()->Gamepad.sThumbRY;
			break;
		}

		// �p�x���擾
		g_inputInfo.stick.aAngle[nCntStick] = FindAngle(D3DXVECTOR3(X, Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f)) * -1;

		// �X�e�B�b�N�̓|������擾
		g_inputInfo.stick.aTplDiameter[nCntStick] = fabsf(X);
		if (g_inputInfo.stick.aTplDiameter[nCntStick] < fabsf(Y))
		{
			g_inputInfo.stick.aTplDiameter[nCntStick] = fabsf(Y);
		}
		g_inputInfo.stick.aTplDiameter[nCntStick] /= 32768.0f;

		// �������̓t���O��������
		for (int nCntAngle = 0; nCntAngle < STICK_ANGLE_MAX; nCntAngle++)
		{
			bAngle[nCntStick][nCntAngle] = false;
		}

		if (g_inputInfo.stick.aTplDiameter[nCntStick] > 0)
		{// �X�e�B�b�N���|����Ă��鎞�A
			// ���I�ȃf�o�C�X���R���g���[���[�ɂ���
			g_activeInputType = ACTIVE_DEVICE_CONTROLLER;

			if (false) {}
			else if ((g_inputInfo.stick.aAngle[nCntStick] < D3DX_PI * -0.75)
				|| (g_inputInfo.stick.aAngle[nCntStick] > D3DX_PI * 0.75))
			{// �p�x���l�����ŏ�Ɉʒu���鎞�A��t���O��^�ɂ���
				bAngle[nCntStick][STICK_ANGLE_UP] = true;
			}
			else if ((g_inputInfo.stick.aAngle[nCntStick] > D3DX_PI * -0.25)
				&& (g_inputInfo.stick.aAngle[nCntStick] < D3DX_PI * 0.25))
			{// �p�x���l�����ŉ��Ɉʒu���鎞�A���t���O��^�ɂ���
				bAngle[nCntStick][STICK_ANGLE_DOWN] = true;
			}
			else if ((g_inputInfo.stick.aAngle[nCntStick] > D3DX_PI * -0.75)
				&& (g_inputInfo.stick.aAngle[nCntStick] < D3DX_PI * -0.25))
			{// �p�x���l�����ō��Ɉʒu���鎞�A���t���O��^�ɂ���
				bAngle[nCntStick][STICK_ANGLE_LEFT] = true;
			}
			else if ((g_inputInfo.stick.aAngle[nCntStick] > D3DX_PI * 0.25)
				&& (g_inputInfo.stick.aAngle[nCntStick] < D3DX_PI * 0.75))
			{// �p�x���l�����ŉE�Ɉʒu���鎞�A�E�t���O��^�ɂ���
				bAngle[nCntStick][STICK_ANGLE_RIGHT] = true;
			}
		}

		for (int nCntAngle = 0; nCntAngle < STICK_ANGLE_MAX; nCntAngle++)
		{
			// �X�e�B�b�N�̃g���K�[����ۑ�
			g_inputInfo.stick.aAngleTrigger[nCntStick][nCntAngle] = (g_inputInfo.stick.aAnglePress[nCntStick][nCntAngle] ^ bAngle[nCntStick][nCntAngle])&bAngle[nCntStick][nCntAngle];

			// �X�e�B�b�N�̃����[�X����ۑ�
			g_inputInfo.stick.aAngleRelease[nCntStick][nCntAngle] = (g_inputInfo.stick.aAnglePress[nCntStick][nCntAngle] ^ bAngle[nCntStick][nCntAngle])&~bAngle[nCntStick][nCntAngle];

			// ���݂̎��Ԃ��擾
			g_inputInfo.aStickCurrentTime[nCntStick][nCntAngle] = timeGetTime();

			if (bAngle[nCntStick][nCntAngle] && ((g_inputInfo.aStickCurrentTime[nCntStick][nCntAngle] - g_inputInfo.aStickExecLastTime[nCntStick][nCntAngle]) > REPEATE_INTERVAL))
			{// �L�[�����͂���Ă��āA�����݂̎��ԂƍŌ�ɐ^��Ԃ������Ԃ̍������s�[�g�̊Ԋu���z���Ă������A
				// �Ō�ɐ^��Ԃ������Ԃ�ۑ�
				g_inputInfo.aStickExecLastTime[nCntStick][nCntAngle] = g_inputInfo.aStickCurrentTime[nCntStick][nCntAngle];

				// �X�e�B�b�N�̃��s�[�g����ۑ�
				g_inputInfo.stick.aAngleRepeat[nCntStick][nCntAngle] = bAngle[nCntStick][nCntAngle];
			}
			else {
				// �X�e�B�b�N�̃��s�[�g����ۑ�
				g_inputInfo.stick.aAngleRepeat[nCntStick][nCntAngle] = 0;
			}

			// �X�e�B�b�N�̃v���X����ۑ�
			g_inputInfo.stick.aAnglePress[nCntStick][nCntAngle] = bAngle[nCntStick][nCntAngle];

			if (bAngle[nCntStick][nCntAngle])
			{// ���͂��s��ꂽ���A
				// ���I�ȃf�o�C�X���R���g���[���[�ɂ���
				g_activeInputType = ACTIVE_DEVICE_CONTROLLER;
			}
		}
	}
}

//========================================
// UpdateVibration�֐� - �R���g���[���[�̐U���X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateVibration(void) 
{
	if (g_inputInfo.fVibration > 0)
	{// �U���{����0�������Ă��鎞�A
		// �U���{�������Z
		g_inputInfo.fVibration -= VIBRATION_SUBTRACT;

		// �U���{���𐧌�
		FloatControl(&g_inputInfo.fVibration, 1.0f, 0);

		{// �U���t���O���^�̎��A
			XINPUT_STATE state;			//XINPUT_STATE�^ state���쐬
			XInputGetState(0, &state);	//state�ɏK�������R���g���[���̏�Ԃ��i�[
			XINPUT_VIBRATION vibration;	//XINPUT_VIBRATION vibration���쐬

			//vibration�����o�[wLeftMotorSpeed�ɒl���� ���[�^�[�X�s�[�h100%
			vibration.wLeftMotorSpeed = 65535 * g_inputInfo.fVibration;

			//vibration�����o�[wRightMotorSpeed�ɒl���� ���[�^�[�X�s�[�h0%
			vibration.wRightMotorSpeed = 65535 * g_inputInfo.fVibration;

			//�W���C�X�e�B�b�N�Ƀo�C�u���[�^�[�f�[�^�𑗐M
			XInputSetState(0, &vibration);
		}
	}
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
// InitInput�֐� - ���͊֘A�̏��������� -
// Author:RIKU NISHIMURA
//========================================
HRESULT InitInput(HINSTANCE hInstance, HWND hWnd)
{
	// �}�E�X�J�[�\����\��
	ShowCursor(true);

	// ���͏����N���A
	ClearInputInfo();

	// DirectInput�I�u�W�F�N�g�̐���
	if (FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&g_pInput, NULL))) 
	{
		return E_FAIL;
	}
	// ���̓f�o�C�X(�L�[�{�[�h)�̐���
	if (FAILED(g_pInput->CreateDevice(GUID_SysKeyboard, &g_pDevKeyboard, NULL)))
	{
		return E_FAIL;
	}
	// �f�[�^�t�H�[�}�b�g��ݒ�
	if (FAILED(g_pDevKeyboard->SetDataFormat(&c_dfDIKeyboard)))
	{
		return E_FAIL;
	}
	// �����t�H�[�}�b�g
	if (FAILED(g_pDevKeyboard->SetCooperativeLevel(hWnd, (DISCL_FOREGROUND | DISCL_NONEXCLUSIVE))))
	{
		return E_FAIL;
	}

	// �L�[�{�[�h�ւ̃A�N�Z�X�����l��
	g_pDevKeyboard->Acquire();

	return S_OK;
}

//========================================
// UninitInput�֐� - ���͊֘A�̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitInput(void)
{
	// XInput�����
	XInputEnable(false);

	// ���̓f�o�C�X(�L�[�{�[�h)�̔j��
	if (g_pDevKeyboard != NULL) 
	{
		g_pDevKeyboard->Unacquire();	// �L�[�{�[�h�ւ̃A�N�Z�X�������
		g_pDevKeyboard->Release();
		g_pDevKeyboard = NULL;
	}

	// DirectInput�I�u�W�F�N�g�̔j��
	if (g_pInput != NULL) 
	{
		g_pInput->Release();
		g_pInput = NULL;
	}
}

//========================================
// UpdateInput�֐� - ���͊֘A�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateInput(void)
{
	UpdateKeyboard();	// �L�[�{�[�h
	UpdateButton();		// �{�^��
	UpdateCursor();		// �J�[�\��
	UpdateMouse();		// �}�E�X
	UpdateStick();		// �X�e�B�b�N
	UpdateVibration();	// �R���g���[���[�̐U��

	// �}�E�X�z�C�[���̉�]��Ԃ𖳂��ɐݒ�
	g_inputInfo.wheelSpin = WHEELSPIN_NONE;
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================
//=======================================
// GetInputInfo�֐� - ���͏����擾 -
//=======================================
InputInfo *GetInputInfo(void) 
{
	return &g_inputInfo;
}

//========================================
// GetXInputState�֐� - XInput�̏�Ԃ��擾 -
// Author:RIKU NISHIMURA
//=======================================
XINPUT_STATE *GetXInputState(void)
{
	return &g_inputInfo.xInputState;
}

//========================================
// GetCursorPosOnScreen�֐� - ��ʏ�̃J�[�\���̈ʒu���擾 -
// Author:RIKU NISHIMURA
//=======================================
D3DXVECTOR3 GetCursorPosOnScreen(void)
{
	// �J�[�\���̌��݈ʒu���擾
	POINT cursorPos;
	GetCursorPos(&cursorPos);

	// �N���C�A���g�̈�̃T�C�Y���擾
	RECT rc;
	GetClientRect(*GetWindowHandle(), &rc);

	D3DXVECTOR3 windowPos = GetWindowPos();	// �E�B���h�E�̈ʒu
	WindowMemory windowInfo = *GetWindowMemory();	// �E�B���h�E�̏��

	return D3DXVECTOR3(
		(cursorPos.x - windowPos.x) * (windowInfo.fWindowWidth / (float)rc.right),
		(cursorPos.y - windowPos.y) * (windowInfo.fWindowHeight / (float)rc.bottom),
		0.0f);
}

//========================================
// GetCursorMove�֐� - �J�[�\���̈ړ��ʂ��擾 -
// Author:RIKU NISHIMURA
//=======================================
D3DXVECTOR3 GetCursorMove(void)
{
	return g_inputInfo.cursorMove;
}

//========================================
// GetStick�֐� - �X�e�B�b�N�̓��͏����擾 -
// Author:RIKU NISHIMURA
//=======================================
StickInput GetStick(void)
{
	return g_inputInfo.stick;
}

//========================================
// GetActiveInputType�֐� - ���I�ȃf�o�C�X���擾 -
// Author:RIKU NISHIMURA
//========================================
ACTIVE_DEVICE_TYPE GetActiveInputType()
{
	return g_activeInputType;
}

//============================================================
//--------------------| *** �L�[�{�[�h *** |------------------
//============================================================
//========================================
// GetKeyboardPress�֐� - �L�[�{�[�h�̃v���X�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetKeyboardPress(int nKey)
{
	return g_inputInfo.aKeyStatePress[nKey] != 0;
}

//========================================
// GetKeyboardTrigger�֐� - �L�[�{�[�h�̃g���K�[�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetKeyboardTrigger(int nKey)
{
	return g_inputInfo.aKeyStateTrigger[nKey] != 0;
}

//========================================
// GetKeyboardRepeat�֐� - �L�[�{�[�h�̃��s�[�g�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetKeyboardRepeat(int nKey)
{
	return g_inputInfo.aKeyStateRepeat[nKey] != 0;
}

//========================================
// GetKeyboardRelease�֐� - �L�[�{�[�h�̃����[�X�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetKeyboardRelease(int nKey)
{
	return g_inputInfo.aKeyStateRelease[nKey] != 0;
}

//============================================================
//--------------------| *** �}�E�X *** |----------------------
//============================================================
//========================================
// GetMouse�֐� - �}�E�X�̃v���X�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetMousePress(int nMouse)
{
	return g_inputInfo.aMouseState[nMouse];
}

//========================================
// GetMouseTrigger�֐� - �}�E�X�̃g���K�[�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetMouseTrigger(int nMouse)
{
	return g_inputInfo.aMouseStateTrigger[nMouse];
}

//========================================
// GetMouseRepeat�֐� - �}�E�X�̃��s�[�g�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetMouseRepeat(int nMouse)
{
	return g_inputInfo.aMouseStateRepeat[nMouse];
}

//========================================
// GetMouseRelease�֐� - �}�E�X�̃����[�X�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetMouseRelease(int nMouse)
{
	return g_inputInfo.aMouseStateRelease[nMouse];
}

//========================================
// GetWheelSpin�֐� - �}�E�X�z�C�[���̉�]��Ԃ��擾 -
// Author:RIKU NISHIMURA
//========================================
WHEELSPIN GetWheelSpin(void) 
{
	return g_inputInfo.wheelSpin;
}

//============================================================
//--------------------| *** �{�^�� *** |----------------------
//============================================================
//========================================
// GetButtonPress�֐� - �{�^���̃v���X�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetButtonPress(int nButton)
{
	return g_inputInfo.aButtonPress[nButton];
}

//========================================
// GetButtonTrigger�֐� - �{�^���̃g���K�[�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetButtonTrigger(int nButton)
{
	return g_inputInfo.aButtonTrigger[nButton];
}

//========================================
// GetButtonRepeat�֐� - �{�^���̃��s�[�g�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetButtonRepeat(int nButton)
{
	return g_inputInfo.aButtonRepeat[nButton];
}

//========================================
// GetButtonRelease�֐� - �{�^���̃����[�X�����擾 -
// Author:RIKU NISHIMURA
//========================================
bool GetButtonRelease(int nButton)
{
	return g_inputInfo.aButtonRelease[nButton];
}

//============================================================
//--------------------| *** �R���g���[���[ *** |--------------
//============================================================
//========================================
// SetVibration�֐� - �R���g���[���[�̐U���ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetVibration(float fVibration, int nTime)
{
	if (g_activeInputType != ACTIVE_DEVICE_CONTROLLER) 
	{// ���I�ȃf�o�C�X���R���g���[���[�Ŗ������A
		// �������I��
		return;
	}

	if (fVibration > g_inputInfo.fVibration)
	{// �U���{�������̐U���{���������Ă��鎞�A
		// �U���{������
		g_inputInfo.fVibration = fVibration;
	}

	// �U���{���𐧌�
	FloatControl(&g_inputInfo.fVibration, 1.0f, 0);
}

//========================================
// ClearInputInfo�֐� - ���͏��̃N���A���� -
// Author:RIKU NISHIMURA
//========================================
void ClearInputInfo(void)
{
	// ���͏���������
	g_inputInfo = InitParameterInputInfo();
}