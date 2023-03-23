//========================================
// 
// ���C������
// Author:RIKU NISHIMURA
// 
//========================================
// *** main.cpp ***
//========================================
#include "main.h"
#include "_R.N.Lib/RNmain.h"
// Mode
#include "Mode\md_title.h"
#include "Mode\md_game.h"
#include "Mode\md_result.h"

//****************************************
// �}�N����`
//****************************************
// �E�C���h�E�̖��O
#define WINDOW_NAME	"R.N.ModelViewer"
// �E�C���h�E�N���X
#define CLASS_NAME "WindowClass"
// �����̃��[�h
#define INIT_MODE (MODE_TITLE)
// �w�i�F
#define BGCOLOR Color{90,90,90,255}

//****************************************
// �v���g�^�C�v�錾
//****************************************
// ���[�h�ɉ���������������
void ModeInit(MODE mode);
// ���[�h�ɉ������I������
void ModeUninit(MODE mode);
// ���[�h�ɉ������X�V����
void ModeUpdate(MODE mode);
// ���[�h�ɉ������`�揈��
void ModeDraw(MODE mode);
// ����������
HRESULT Init(HINSTANCE hInstance);
// �I������
void Uninit(void);
// �X�V����
void Update(void);
// �`�揈��
void Draw(void);
// �ǂݍ��ݏ���
void Load(void);
// �������ݏ���
void Save(void);
// �E�C���h�E�v���V�[�W��
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

//****************************************
// �O���[�o���ϐ��錾
//****************************************
static Main g_main;								// ���C�������̏��\����

//============================================================
//--------------------| *** ���[�h�ɉ��������� *** |----------
//============================================================
#if 1
//========================================
// ModeInit�֐� - ���[�h�ɉ��������������� -
// Author:RIKU NISHIMURA
//========================================
void ModeInit(MODE mode) {
	switch (mode) {
	case MODE_TITLE:InitMd_title(); break;
	case MODE_GAME:InitMd_game(); break;
	case MODE_RESULT:InitMd_result(); break;
	}
}

//========================================
// ModeUninit�֐� - ���[�h�ɉ������I������ -
// Author:RIKU NISHIMURA
//========================================
void ModeUninit(MODE mode) {
	switch (mode) {
	case MODE_TITLE:UninitMd_title(); break;
	case MODE_GAME:UninitMd_game(); break;
	case MODE_RESULT:UninitMd_result(); break;
	}
}

//========================================
// ModeUpdate�֐� - ���[�h�ɉ������X�V���� -
// Author:RIKU NISHIMURA
//========================================
void ModeUpdate(MODE mode) {
	switch (mode) {
	case MODE_TITLE:UpdateMd_title(); break;
	case MODE_GAME:UpdateMd_game(); break;
	case MODE_RESULT:UpdateMd_result(); break;
	}
}

//========================================
// ModeDraw�֐� - ���[�h�ɉ������`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void ModeDraw(MODE mode) {
	switch (mode) {
	case MODE_TITLE:DrawMd_title(); break;
	case MODE_GAME:DrawMd_game(); break;
	case MODE_RESULT:DrawMd_result(); break;
	}
}
#endif
//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================
#if 1
//========================================
// Init�֐� - ���������� -
// Author:RIKU NISHIMURA
//========================================
HRESULT Init(HINSTANCE hInstance)
{
	// �ǂݍ��ݏ���
	Load();

	// R.N.Lib�̏���������
	RNInit(hInstance);
	
	// ���[�h��ݒ肷��
	SetMode(INIT_MODE);

	// �w�i�F��ݒ�
	SetBackgroundColor(BGCOLOR);

	return S_OK;
}

//========================================
// Uninit�֐� - �I������ -
// Author:RIKU NISHIMURA
//========================================
void Uninit(void)
{
	// �������ݏ���
	Save();

	// R.N.Lib�̏I������
	RNUninit();
	// ���[�h�ɉ������I������
	ModeUninit(g_main.mode);

	// �^�X�N�o�[��\��
	ShowTaskBar(true);
}

//========================================
// Update�֐� - �X�V���� - 
// Author:RIKU NISHIMURA
//========================================
void Update(void)
{
	// ���[�h�ɉ������X�V����
	ModeUpdate(g_main.mode);
	// R.N.Lib�̍X�V����
	RNUpdate();
}

//========================================
// Draw�֐� - �`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void Draw(void)
{
	// R.N.Lib�̕`�揈��
	RNDraw();
	// ���[�h�ɉ������`�揈��
	ModeDraw(g_main.mode);
}

//========================================
// Load�֐� - �ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void Load(void)
{
	// R.N.Lib�̓ǂݍ��ݏ���
	RNLoad();
}

//========================================
// Save�֐� - �������ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void Save(void)
{
	// ��������
	RNSave();		// R.N.Lib
	SaveSetting();	// �ݒ�
}
#endif
//============================================================
//--------------------| *** ���̑� *** |----------------------
//============================================================
#if 1
//========================================
// WinMain�֐�
// Author:RIKU NISHIMURA
//========================================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR IpCmdLine, int nCmdShow)
{
	MSG msg;				// ���b�Z�[�W���i�[����ϐ�
	DWORD dwCurrentTime;	// ���ݎ���
	DWORD dwExecLastTime;	// �Ō�ɏ�����������
	DWORD dwFrameCount;		// �t���[���J�E���g
	DWORD dwFPSLastTime;	// �Ō��FPS���v����������

	// �E�B���h�E�������
	CreateWindowInfo cwi =
	{
		WindowProc,		// �E�B���h�E�v���V�[�W��
		hInstance,		// �C���X�^���X�n���h��
		CLASS_NAME,		// �E�B���h�E�N���X�̖��O
		WINDOW_NAME,	// �E�B���h�E�̖��O
		SCREEN_WIDTH,	// �E�B���h�E�̕�
		SCREEN_HEIGHT,	// �E�B���h�E�̍���
		true,			// �E�B���h�E���[�h
	};
	CreateWindowRN(cwi);

	// ����������
	if (FAILED(Init(hInstance)))
	{// ���������������s�����ꍇ
		return -1;
	}

	// ����\��ݒ�
	timeBeginPeriod(1);

	dwCurrentTime = 0; // ���ݎ���������������
	dwExecLastTime = timeGetTime(); // ���ݎ������擾(�ۑ�)

	dwFrameCount = 0;	// �t���[���J�E���g������������
	dwFPSLastTime = timeGetTime();	// ���ݎ������擾(�ۑ�)

	// ���b�Z�[�W���[�v
	while (1){
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE) != 0)
		{// Windows�̏���
			if (msg.message == WM_QUIT)
			{// WM_QUIT���b�Z�[�W���󂯎�������A���b�Z�[�W���[�v�𔲂���
				break;
			}
			else {
				// ���b�Z�[�W�̐ݒ�
				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}
		}
		else
		{// DirectX�̏���
			dwCurrentTime = timeGetTime(); // ���ݎ������擾

			if ((dwCurrentTime - dwFPSLastTime) >= 500)
			{// 0.5�b�o��
				// FPS���v��
				g_main.nCountFPS = (dwFrameCount * 1000) / (dwCurrentTime - dwFPSLastTime);

				// FPS�𑪒肵��������ۑ�
				dwFPSLastTime = dwCurrentTime;

				// �t���[���J�E���g���N���A
				dwFrameCount = 0;
			}

			if ((dwCurrentTime - dwExecLastTime) >= (1000 / 60))
			{// 60/1�b�o��
				Update();	// �X�V����
				Draw();		// �`�揈��

				// �����J�n�̎���(���ݎ���)��ۑ�
				dwExecLastTime = dwCurrentTime;

				// �t���[���J�E���g�����Z
				dwFrameCount++;
			}
		}
	}

	// �I������
	Uninit();

	// ����\��߂�
	timeEndPeriod(1);

	return (int)msg.wParam;
}

//========================================
// WindowProc�֐�
// Author:RIKU NISHIMURA
//========================================
LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	int nID;	// �Ԃ�l���i�[

	// R.N.Lib
	RNWindowProc(hWnd, uMsg, wParam, lParam);

	switch (uMsg)
	{
	case WM_DESTROY: // �E�C���h�E�j���̃��b�Z�[�W

		PostQuitMessage(0); // WM_QUIT���b�Z�[�W�𑗂�

		break;
	case WM_KEYDOWN: // �L�[�����̃��b�Z�[�W

		switch (wParam)
		{
		case VK_ESCAPE: // [ESC]�L�[�������ꂽ

			nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO); // �E�C���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)

			if (nID == IDYES)
			{
				DestroyWindow(hWnd); // �E�C���h�E��j������
			}

			break;
		}

		break;
	case WM_CLOSE: // �I���{�^���������ꂽ��

		nID = MessageBox(hWnd, "�I�����܂����H", "�I�����b�Z�[�W", MB_YESNO); // �E�C���h�E��j������(WM_DESTROY���b�Z�[�W�𑗂�)

		if (nID == IDYES)
		{
			DestroyWindow(hWnd); // �E�C���h�E��j������
		}
		else
		{
			return 0; // (��0��Ԃ��Ȃ��ƏI�����Ă��܂�)
		}

		break;
	case WM_LBUTTONDOWN: // �}�E�X�N���b�N�̃��b�Z�[�W

		// �ΏۃE�C���h�E�Ƀt�H�[�J�X�����킹��
		SetFocus(hWnd); // �}�E�X�����N���b�N�����E�C���h�E���A�N�e�B�u�ɂ���

		break;
	case WM_CREATE: //�E�C���h�E�����̃��b�Z�[�W

		break;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam); // ����̏�����Ԃ�
}

//========================================
// GetMain�֐� - ���C�������̏��̎擾 -
// Author:RIKU NISHIMURA
//========================================
Main *GetMain(void)
{
	return &g_main;
}

//========================================
// GetMode�֐� - ���[�h�̎擾 -
// Author:RIKU NISHIMURA
//========================================
MODE GetMode(void)
{
	return g_main.mode;
}

//========================================
// SetMode�֐� - ���[�h�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetMode(MODE mode)
{
	// ���݂̃��[�h�̏I������
	ModeUninit(g_main.mode);

	// ���݂̃��[�h��؂�ւ���
	g_main.mode = mode;

	// �V�������[�h�̏���������
	ModeInit(mode);
}
#endif