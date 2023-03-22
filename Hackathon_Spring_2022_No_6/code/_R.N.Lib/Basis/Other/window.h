//========================================
// 
// �E�B���h�E�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// *** window.h ***
//========================================
#ifndef _WINDOW_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _WINDOW_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �}�N����`
//****************************************
// �E�B���h�E�쐬���\����
typedef struct 
{
	WNDPROC lpfnWndProc;	// �E�B���h�E�v���V�[�W��
	HINSTANCE hInstance;	// �C���X�^���X�n���h��
	char *pClassName;		// �E�B���h�E�N���X�̖��O
	char *pWindowName;		// �E�B���h�E�̖��O
	float fWindowWidth;		// �E�B���h�E�̕�
	float fWindowHeight;	// �E�B���h�E�̍���
	bool bWindow;			// �E�B���h�E���[�h
	// (��TRUE�Ȃ�E�B���h�E���[�h�AFALSE�Ȃ�t���X�N���[�����[�h�ŏ�����)
}CreateWindowInfo;

// �E�B���h�E�̋L�����\����
typedef struct
{
	HINSTANCE hInstance;	// �C���X�^���X�n���h��
	char *pClassName;		// �E�B���h�E�N���X�̖��O
	float fWindowWidth;		// �E�B���h�E�̕�
	float fWindowHeight;	// �E�B���h�E�̍���
}WindowMemory;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// �E�B���h�E�̍X�V����
void UpdateWindowRN(void);
// �E�B���h�E�̏I������
void UninitWindow(void);
//========== *** �擾 ***
// �E�B���h�E�̋L�������擾
WindowMemory *GetWindowMemory(void);
// Direct3D�f�o�C�X���擾
LPDIRECT3DDEVICE9 GetD3DDevice(void);
// �E�C���h�E�n���h�����擾
HWND *GetWindowHandle(void);
// �E�C���h�E�̈ʒu���擾
D3DXVECTOR2 GetWindowPos(void);
//========== *** �ݒ� ***
// �E�C���h�E�쐬
int CreateWindowRN(CreateWindowInfo cwi);
//========== *** ��� ***
// �^�X�N�o�[�̕\��/��\����؂�ւ���
void ShowTaskBar(bool bShow);
// �E�C���h�E�̃��[�h��؂�ւ���(true:Full false:Normal)
void WindowModeChange(bool bFullScreen);
// ���b�Z�[�W����
void Message(char *pText, char *pCaption);
// �E�B���h�E�Ƀt�H�[�J�X���������Ă��邩���ׂ�
bool IsWindowFocused(HWND hwnd);

#endif