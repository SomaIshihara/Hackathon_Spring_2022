//========================================
// 
// R.N.Lib�̃��C���̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** RNmain.cpp ***
//========================================
#include <time.h>
#include "R.N.Lib.h"

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �擾 ***
// R.N.Lib�̃��C�������̏��̃p�����[�^�[�����l���擾
RNmain InitParameterRNmain(void);
//========== *** �ݒ� ***
// �����_�[�X�e�[�g�̐ݒ菈��
void SetRenderStateRN(void);

//****************************************
// �O���[�o���ϐ��錾
//****************************************
RNmain g_RNmain;	// R.N.Lib�̃��C�������̏��
static int g_nGroundTex;	// �n�ʂ̃e�N�X�`���ԍ�

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================

//========================================
// InitParameterRNmain�֐� - R.N.Lib�̃��C�������̏��̃p�����[�^�[�����l���擾 -
// Author:RIKU NISHIMURA
//========================================
RNmain InitParameterRNmain(void) 
{
	return{

	};
}

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================

//========================================
// SetRenderStateRN�֐� - �����_�[�X�e�[�g�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetRenderStateRN(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// �����_�[�X�e�[�g�̐ݒ�
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	// �T���v���[�X�e�[�g�ݒ�
	pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_POINT);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);

	// �e�N�X�`���X�e�[�W�X�e�[�g�̐ݒ�
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_TEXTURE);
	pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_CURRENT);

	// �A���t�@�u�����h�̐ݒ�
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
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
// RNInit�֐� - R.N.Lib�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void RNInit(HINSTANCE hInstance)
{
	// �p�����[�^�[������
	g_RNmain = InitParameterRNmain();

	// �����_�[�X�e�[�g�̐ݒ菈��
	SetRenderStateRN();

	// �����̎���擾
	srand((unsigned int)time(0));

	// 3D
	InitCamera3D();	// �J����(3D)
	InitLight();	// ��
	InitLine3D();	// ��(3D)
	InitModel();	// ���f��
	InitMapChip3D();// �}�b�v�`�b�v(3D)
	InitPolygon3D();// �|���S��(3D)
	// 2D
	InitCamera2D();	// �J����(2D)
	InitFade();		// �t�F�[�h
	InitPolygon2D();// �|���S��(2D)
	// Graphic
	InitText();		// �e�L�X�g
	// Other
	InitInput(		// ���͊֘A�̏���������
		hInstance,
		*GetWindowHandle());
	InitPhysics();	// �����֘A
	InitSound(		// �T�E���h
		*GetWindowHandle());
	InitSetting();	// �ݒ�

	// �n�ʃe�N�X�`����ǂݍ���
	g_nGroundTex = LoadTexture("data\\TEXTURE\\BG\\ground.png");
}

//========================================
// RNUninit�֐� - R.N.Lib�̏I������ -
// Author:RIKU NISHIMURA
//========================================
void RNUninit(void)
{
	// 3D
	UninitCamera3D();	// �J����(3D)
	UninitLight();		// ��
	UninitLine3D();		// ��(3D)
	UninitModel();		// ���f��
	UninitMapChip3D();	// �}�b�v�`�b�v(3D)
	UninitPolygon3D();	// �|���S��(3D)
	// 2D
	UninitCamera2D();	// �J����(2D)
	UninitPolygon2D();	// �|���S��(2D)
	// Other
	UninitInput();		// ���͊֘A
	UninitSetting();	// �ݒ�
	UninitSound();		// �T�E���h
	UninitWindow();		// �E�B���h�E
}

//========================================
// RNUpdate�֐� - R.N.Lib�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
void RNUpdate(void)
{
	// �����蔻��̐��̐���������
	InitHitTestLineNum();

	UpdateSetting();	// �ݒ�
	UpdateInput();		// ���͊֘A
	UpdateMapChip3D();	// �}�b�v�`�b�v(3D)
	UpdateCamera2D();	// �J����(2D)
	UpdateCamera3D();	// �J����(3D)
	UpdateLight();		// ��
	UpdateFade();		// �t�F�[�h
	UpdateWindowRN();	// �E�B���h�E
	DrawHitTestSetUp();	// �����蔻��̕`�揀������
	HitTestSignOut();	// �����蔻��̓o�^��������

	float fSize = 680.0f;
	// �|���S��(3D)�̐ݒ���
	Polygon3DSet polygon3DSet;
	polygon3DSet.nTex = g_nGroundTex;
	polygon3DSet.nPtn = 0;
	polygon3DSet.nPtnX = 1;
	polygon3DSet.nPtnY = 1;
	polygon3DSet.fWidth = fSize;
	polygon3DSet.fHeight = fSize;
	polygon3DSet.pos = D3DXVECTOR3(0.0f,-80.0f,320.0f);
	polygon3DSet.rot = D3DXVECTOR3(-0.25f,0.0f,0.0f);
	polygon3DSet.col = INITCOLOR;
	// �|���S��(3D)�̐ݒ菈��
	SetPolygon3D(polygon3DSet);
	polygon3DSet.pos = D3DXVECTOR3(-fSize, -80.0f, 320.0f);
	// �|���S��(3D)�̐ݒ菈��
	SetPolygon3D(polygon3DSet);
	polygon3DSet.pos = D3DXVECTOR3(fSize, -80.0f, 320.0f);
	// �|���S��(3D)�̐ݒ菈��
	SetPolygon3D(polygon3DSet);
}

//========================================
// RNDraw�֐� - R.N.Lib�̕`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void RNDraw(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ��ʃN���A
	pDevice->Clear(0, NULL, (D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER), ColorToD3DXCOLOR(GetColorInfo()->bgCol), 1.0f, 0);

	// �`�悷��3D�I�u�W�F�N�g���\�[�g
	SortDraw3D();

	// �`��J�n
	if (SUCCEEDED(pDevice->BeginScene()))
	{// �`��J�n�����������ꍇ�A
		// 3D
		SetCamera3D();		// �J����(3D)�̐ݒ菈��
		DrawMapChip3D();	// �}�b�v�`�b�v(3D)
		Draw3D();			// 3D�I�u�W�F�N�g�S��

		// 2D
		DrawPolygon2D();	// �|���S��(2D)
		DrawLine3D();		// ��(3D)
		DrawHitTest();		// �����蔻��

		// �`��I��
		pDevice->EndScene();
	}

	// �|���S��(2D & 3D)�̐ݒ萔��������
	GetPolygon2DControl()->nPolygonNum = 0;
	GetPolygon3DControl()->nPolygonNum = 0;
	// ��(3D)�̐���������
	GetLine3DControl()->nLineNum = 0;
	// ���f���̐ݒ萔��������
	GetModelInfo()->nModelSetNum = 0;

	// �o�b�N�o�b�t�@���t�����g�o�b�t�@�̓���ւ�
	pDevice->Present(NULL, NULL, NULL, NULL);
}

//========================================
// RNWindowProc�֐� - R.N.Lib�̃E�B���h�E�v���V�[�W���̉����� -
// Author:RIKU NISHIMURA
//========================================
void RNWindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_MOUSEWHEEL: // �}�E�X�z�C�[�����񂳂ꂽ���̃��b�Z�[�W
		if (HIWORD(wParam) == WHEEL_DELTA)
		{// �}�E�X�z�C�[���̉�]��Ԃ�O��]�ɐݒ�
			GetInputInfo()->wheelSpin = WHEELSPIN_FRONT;
		}
		else
		{// �}�E�X�z�C�[���̉�]��Ԃ����]�ɐݒ�
			GetInputInfo()->wheelSpin = WHEELSPIN_BACK;
		}

		break;
	}
}

//============================================================
//--------------------| *** ���o�� *** |----------------------
//============================================================

//========================================
// RNLoad�֐� - R.N.Lib�̓ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void RNLoad(void)
{
	LoadFont();				// �t�H���g
	LoadMapChip3DList();		// �}�b�v�`�b�v(3D)���X�g
	LoadModelSetUpList();	// ���f���̃Z�b�g�A�b�v���X�g
}

//========================================
// RNSave�֐� - R.N.Lib�̏������ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void RNSave(void)
{
	
}

//========================================
// GetRNmain�֐� - R.N.main�̏����擾 -
// Author:RIKU NISHIMURA
//========================================
RNmain *GetRNmain(void) 
{
	return &g_RNmain;
}