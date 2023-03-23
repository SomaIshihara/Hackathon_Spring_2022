//========================================
// 
// R.N.Lib�̃��C�������̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** RNmain.h ***
//========================================
#ifndef _RNMAIN_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _RNMAIN_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include <windows.h>
#include <stdio.h>
#include "d3dx9.h"
#define DIRECTINPUT_VERSION	(0x0800)	// �r���h���̌x���Ώ��p�}�N��
#include "dinput.h"						// ���͏����ɕK�v
#include "Xinput.h"						// ���͏����ɕK�v
#include "xaudio2.h"					// �T�E���h�����ɕK�v

//****************************************
// ���C�u�����̃����N
//****************************************
#pragma comment(lib,"d3d9.lib")		// �`�揈���ɕK�v
#pragma comment(lib,"d3dx9.lib")	// [d3d9.lib]�̊g�����C�u����
#pragma comment(lib,"dxguid.lib")	// DirectX�R���|�[�l���g���g�p����̂ɕK�v
#pragma comment(lib,"dsound.lib")	// DirectSound���g�p����̂ɕK�v
#pragma comment(lib,"winmm.lib")	// �V�X�e�������擾�ɕK�v
#pragma comment(lib,"dinput8.lib")	// ���͏����ɕK�v
#pragma comment(lib,"xinput.lib")	// ���͏����ɕK�v
#pragma warning(disable:4091)		// �x��:C4091�𖳎�����
#pragma warning(disable:4244)		// �x��:C4244�𖳎�����

//****************************************
// �}�N����`
//****************************************
// ���_�t�H�[�}�b�g(2D)
#define FVF_VERTEX_2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)
// ���_�t�H�[�}�b�g(3D)
#define FVF_VERTEX_3D (D3DFVF_XYZ|D3DFVF_NORMAL|D3DFVF_DIFFUSE|D3DFVF_TEX1)

// D3DXVECTOR3�̏����l
#define INITD3DXVECTOR3 D3DXVECTOR3(0.0f,0.0f,0.0f)
// Color�̏����l
#define INITCOLOR Color{255,255,255,255}

// ������̍ő吔(�ėp)
#define TXT_MAX (1024)

// �s�N�Z���P�ʂ̑傫��
#define PIXEL (2.0f)

//****************************************
// �\���̂̒�`
//****************************************
// R.N.Lib�̃��C�������̏��\����
typedef struct 
{

}RNmain;

// ���_���(2D)�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	float rhw;			// ���W�ϊ��p�W��(1.0f�ŌŒ�)
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_2D;

// ���_���(3D)�̍\����
typedef struct
{
	D3DXVECTOR3 pos;	// ���_���W
	D3DXVECTOR3 nor;	// �@���x�N�g��
	D3DCOLOR col;		// ���_�J���[
	D3DXVECTOR2 tex;	// �e�N�X�`�����W
}VERTEX_3D;

// �g��{���\����
typedef struct
{
	float fWidth;	// ��
	float fHeight;	// ����
	float fDepth;	// ���s��
}Scale;

// �F�\����
typedef struct
{
	int r;
	int g;
	int b;
	int a;
}Color;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// ����������
void RNInit(HINSTANCE hInstance);
// �I������
void RNUninit(void);
// �X�V����
void RNUpdate(void);
// �`�揈��
void RNDraw(void);
// R.N.Lib�̃E�B���h�E�v���V�[�W���̉�����
void RNWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
//========== *** ���o�� ***
// �ǂݍ��ݏ���
void RNLoad(void);
// �������ݏ���
void RNSave(void);
//========== *** �擾 ***
// R.N.main�̏����擾
RNmain *GetRNmain(void);

#endif