//========================================
// 
// �E�B���h�E�̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** window.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �\���̂̒�`
//****************************************
// �E�C���h�E�̊Ǘ����\����
typedef struct
{
	D3DXVECTOR2 pos;	// �ʒu
}WindowInfo;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �ݒ� ***
// Direct3D�f�o�C�X�̐���
int CreateDirect3DDevice(CreateWindowInfo cwi);

//****************************************
// �O���[�o���ϐ��̒�`
//****************************************
// �E�B���h�E�̊Ǘ����
static WindowInfo g_windowInfo;
// �E�B���h�E�̋L�����
static WindowMemory g_windowMemory;
// Direct3D�I�u�W�F�N�g�ւ̃|�C���^
static LPDIRECT3D9 g_pD3D;
// Direct3D�f�o�C�X�ւ̃|�C���^
static LPDIRECT3DDEVICE9 g_pD3DDevice = NULL;
static HWND g_hWnd;	// �E�C���h�E�n���h��(���ʎq)

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================

//========================================
// CreateWindowRN�֐� - Direct3D�f�o�C�X�̐��� -
// Author:RIKU NISHIMURA
//========================================
int CreateDirect3DDevice(CreateWindowInfo cwi)
{
	// �E�B���h�E�̏����L��
	g_windowMemory.hInstance = cwi.hInstance;	// �C���X�^���X�n���h��
	g_windowMemory.pClassName = cwi.pClassName;	// �E�B���h�E�N���X�̖��O
	g_windowMemory.fWindowWidth = cwi.fWindowWidth;		// �E�B���h�E�̕�
	g_windowMemory.fWindowHeight = cwi.fWindowHeight;	// �E�B���h�E�̍���

	// Direct3D�I�u�W�F�N�g�̐���
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (g_pD3D == NULL)
	{// Direct3D�I�u�W�F�N�g�̐����Ɏ��s
		return -1;
	}

	D3DDISPLAYMODE d3ddm;	// �f�B�X�v���C���[�h

	// ���݂̃f�B�X�v���C���[�h���擾
	if (FAILED(g_pD3D->GetAdapterDisplayMode(D3DADAPTER_DEFAULT, &d3ddm)))
	{
		return E_FAIL;
	}

	D3DPRESENT_PARAMETERS d3dpp;	// �v���[���e�[�V�����p�����[�^

	// �f�o�C�X�̃v���[���e�[�V�����p�����[�^��ݒ�
	ZeroMemory(&d3dpp, sizeof(d3dpp)); // �p�����[�^�̃[���N���A

	d3dpp.BackBufferWidth = cwi.fWindowWidth;					// �Q�[���̉�ʃT�C�Y(��)
	d3dpp.BackBufferHeight = cwi.fWindowHeight;					// �Q�[���̉�ʃT�C�Y(����)
	d3dpp.BackBufferFormat = d3ddm.Format;						// �o�b�N�o�b�t�@�̌`��
	d3dpp.BackBufferCount = 1;									// �o�b�N�o�b�t�@�̐�
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;					// �_�u���o�b�t�@�̐؂�ւ�
	d3dpp.EnableAutoDepthStencil = TRUE;						// �f�v�X�o�b�t�@�ƃX�e���V���o�b�t�@���쐬
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;					// �f�v�X�o�b�t�@�Ƃ���16bit���g��
	d3dpp.Windowed = cwi.bWindow;								// �E�C���h�E���[�h
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;	// ���t���b�V�����[�g
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_DEFAULT;	// �C���^�[�o��

	// Direct3D�f�o�C�X�̐���
	if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		g_hWnd,
		D3DCREATE_HARDWARE_VERTEXPROCESSING,
		&d3dpp,
		&g_pD3DDevice)))
	{
		if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			g_hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&d3dpp,
			&g_pD3DDevice)))
		{
			if (FAILED(g_pD3D->CreateDevice(D3DADAPTER_DEFAULT,
				D3DDEVTYPE_REF,
				g_hWnd,
				D3DCREATE_SOFTWARE_VERTEXPROCESSING,
				&d3dpp,
				&g_pD3DDevice)))
			{
				return -1;
			}
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
// UpdateWindow�֐� - �E�C���h�E�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void UpdateWindowRN(void)
{
	RECT rec;	// �傫�����󂯎��RECT�\����

	// �E�C���h�E�̏����擾
	GetWindowRect(g_hWnd, &rec);

	// �E�C���h�E�̈ʒu��ݒ�
	g_windowInfo.pos = D3DXVECTOR2(rec.left, rec.top);
}

//========================================
// UninitWindow�֐� - �E�C���h�E�̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitWindow(void)
{
	// Direct3D�f�o�C�X�̔j��
	if (g_pD3DDevice != NULL)
	{
		g_pD3DDevice->Release();
		g_pD3DDevice = NULL;
	}

	// Direct3D�I�u�W�F�N�g�̔j��
	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}

	// �E�C���h�E�N���X�̓o�^������
	UnregisterClass(g_windowMemory.pClassName, g_windowMemory.hInstance);
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================

//========================================
// GetWindowMemory�֐� - �E�B���h�E�̋L�������擾 -
//========================================
WindowMemory *GetWindowMemory(void)
{
	return &g_windowMemory;
}

//========================================
// GetD3DDevice�֐� - Direct3D�f�o�C�X���擾 -
// Author:RIKU NISHIMURA
//========================================
LPDIRECT3DDEVICE9 GetD3DDevice(void) 
{
	return g_pD3DDevice;
}

//========================================
// GetWindowHandle�֐� - �E�C���h�E�n���h�����擾 -
// Author:RIKU NISHIMURA
//========================================
HWND *GetWindowHandle(void) 
{
	return &g_hWnd;
}

//========================================
// GetWindowPos�֐� - �E�C���h�E�̈ʒu���擾 -
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR2 GetWindowPos(void)
{
	return g_windowInfo.pos;
}

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================

//========================================
// CreateWindowRN�֐� - �E�C���h�E�쐬 -
// Author:RIKU NISHIMURA
//========================================
int CreateWindowRN(CreateWindowInfo cwi)
{
	// �E�C���h�E�N���X�̍\����
	WNDCLASSEX wcex =
	{
		sizeof(WNDCLASSEX),				// WNDCLASSEX�̃������T�C�Y
		CS_CLASSDC,						// �E�C���h�E�̃X�^�C��
		cwi.lpfnWndProc,				// �E�C���h�E�v���V�[�W��
		0,								// 0�ɂ���
		0,								// 0�ɂ���
		cwi.hInstance,					// �C���X�^���X�n���h��
		LoadIcon(NULL,IDI_APPLICATION),	// �^�X�N�o�[�̃A�C�R��
		LoadCursor(NULL,IDC_ARROW),		// �}�E�X�J�[�\��
		(HBRUSH)(COLOR_WINDOW + 1),		// �N���C�A���g�̈�̔w�i�F
		NULL,							// ���j���[�o�[
		cwi.pClassName,					// �E�C���h�E�N���X�̖��O
		LoadIcon(NULL,IDI_APPLICATION)	// �t�@�C���̃A�C�R��
	};

	// �E�C���h�E�N���X�̓o�^
	RegisterClassEx(&wcex);

	// �E�C���h�E�𐶐�
	g_hWnd = CreateWindowEx(
		0,								// �g���E�C���h�E�X�^�C��
		cwi.pClassName,					// �E�C���h�E�N���X�̖��O
		cwi.pWindowName,				// �E�C���h�E�̖��O
		WS_SYSMENU | WS_MINIMIZEBOX,	// �E�C���h�E�X�^�C��
		CW_USEDEFAULT,					// �E�C���h�E�̍���X���W
		CW_USEDEFAULT,					// �E�C���h�E�̍���Y���W
		cwi.fWindowWidth,				// �E�C���h�E�̕�
		cwi.fWindowHeight,				// �E�C���h�E�̍���
		NULL,							// �e�E�C���h�E�̃n���h��
		NULL,							// ���j���[�n���h���܂���
		cwi.hInstance,					// �C���X�^���X�n���h��
		NULL);							// �E�C���h�E�쐬�f�[�^

	// Direct3D�f�o�C�X�̐���
	if (CreateDirect3DDevice(cwi) == -1) 
	{// �����Ɏ��s
		return -1;
	}

	// �E�B���h�E�̃��[�h��ݒ肷��
	WindowModeChange(cwi.bWindow ^ 1);

	return 0;
}

//============================================================
//--------------------| *** ��� *** |------------------------
//============================================================

//========================================
// ShowTaskBar�֐� - �^�X�N�o�[�̕\��/��\����؂�ւ��� -
// Author:RIKU NISHIMURA
// �Q�l: https://dixq.net/forum/viewtopic.php?t=12505
//========================================
void ShowTaskBar(bool bShow)
{
	HWND hTask;	// �^�X�N�o�[�̃n���h��

	// �^�X�N�o�[�̃n���h�����擾
	hTask = FindWindow((LPCSTR)"Shell_TrayWnd", NULL);

	if (bShow)
	{// �\��
		// �^�X�N�o�[��\��
		ShowWindow(hTask, SW_SHOW);

		// �E�C���h�E���A�N�e�B�u�ɂ���
		SetFocus(g_hWnd);
	}
	else
	{// ��\��
		// �^�X�N�o�[���\��
		ShowWindow(hTask, SW_HIDE);
	}
}

//========================================
// WindowModeChange�֐� - �E�C���h�E�̃��[�h��؂�ւ��� -
// Author:RIKU NISHIMURA
//========================================
void WindowModeChange(bool bFullScreen)
{
	HDC hDC = GetDC(GetDesktopWindow());			// �f�X�N�g�b�v�̃n���h��
	int nScrSizeX = GetDeviceCaps(hDC, HORZRES);	// �f�X�N�g�b�v�̉�ʃT�C�YX
	int nScrSizeY = GetDeviceCaps(hDC, VERTRES);	// �f�X�N�g�b�v�̉�ʃT�C�YY

	// �f�X�N�g�b�v�̃n���h���������
	ReleaseDC(GetDesktopWindow(), hDC);

	if (bFullScreen)
	{// �S��ʃt���O���^�̎��A
	 // �E�C���h�E�̈ʒu��ݒ�
		SetWindowPos(
			g_hWnd,
			HWND_TOP,
			0,
			0,
			nScrSizeX,
			nScrSizeY,
			SWP_SHOWWINDOW);

		// �E�C���h�E�X�^�C����ύX
		SetWindowLong(g_hWnd, GWL_STYLE, WS_POPUP);
	}
	else
	{// �S��ʃt���O���U�̎��A
		// �E�C���h�E�̈ʒu��ݒ�
		SetWindowPos(
			g_hWnd,
			HWND_TOP,
			(nScrSizeX * 0.5f) - (g_windowMemory.fWindowWidth * 0.5f),	// �ʒu�𒆉��ɍ��킹��
			(nScrSizeY * 0.5f) - (g_windowMemory.fWindowHeight * 0.5f),
			g_windowMemory.fWindowWidth,
			g_windowMemory.fWindowHeight,
			SWP_SHOWWINDOW);

		// �E�C���h�E�X�^�C����ύX
		SetWindowLong(g_hWnd, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX);
	}

	// �E�C���h�E�̕\����Ԃ�ݒ�
	ShowWindow(g_hWnd, SW_NORMAL);

	// �N���C�A���g�̈���X�V
	UpdateWindow(g_hWnd);

	// �^�X�N�o�[��\��/��\��
	ShowTaskBar(bFullScreen ^ 1);
}

//============================================================
//--------------------| *** ���̑� *** |----------------------
//============================================================

//========================================
// Message�֐� - ���b�Z�[�W���� -
// Author:RIKU NISHIMURA
//========================================
void Message(char *pText, char *pCaption)
{
	static bool bMessage = false;	// ���b�Z�[�W�\�������t���O(���[�v�h�~)

	if (bMessage)
	{// ���b�Z�[�W�\�������t���O
		bMessage = false;	// ���b�Z�[�W�\�������t���O���U�ɂ���
		return;				// �������I������
	}

	if (MessageBox(*GetWindowHandle(), pText, pCaption, MB_OK) == IDOK)
	{// ���b�Z�[�W�{�b�N�X�̕Ԃ�l��OK�̎��A
		// ���b�Z�[�W�\�������t���O��^�ɂ���
		bMessage = true;
	}
}

//========================================
// IsWindowFocused�֐� - �E�B���h�E�Ƀt�H�[�J�X���������Ă��邩���ׂ� -
// Author:RIKU NISHIMURA
//========================================
bool IsWindowFocused(HWND hwnd)
{
	HRESULT hr = g_pD3DDevice->TestCooperativeLevel();

	if (hr == D3DERR_DEVICELOST || hr == D3DERR_DEVICENOTRESET)
	{
		// �f�o�C�X�������Ă���ꍇ�̓t�H�[�J�X���������Ă��Ȃ��Ƃ݂Ȃ�
		return false;
	}

	HWND activeWindow = GetForegroundWindow();

	return (activeWindow == hwnd);
}