//========================================
// 
// UI:�^�C�g�����S �̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** ui_title-logo.cpp ***
//========================================
#include "../_R.N.Lib/R.N.Lib.h"
#include "../main.h"

#include "ui_title-logo.h"	// UI :�^�C�g�����S	

//****************************************
// �}�N����`
//****************************************
// UI:�^�C�g�����S �̈ʒu
#define UI_TITLELOGO_POS	(D3DXVECTOR3((SCREEN_WIDTH*0.5f)+PIXEL*64,(SCREEN_HEIGHT*0.5f)+PIXEL*-64,0.0f))
// UI:�^�C�g�����S �̃e�L�X�g�̑��Έʒu
#define UI_TITLELOGO_TEXT_RELATIVE_POS	(D3DXVECTOR3(0,PIXEL*-13,0.0f))

//****************************************
// �񋓌^�̒�`
//****************************************
// UI:�^�C�g�����S �̕��i�ԍ�
typedef enum
{
	UI_TITLELOGO_PARTS_TITLELOGO,	// �^�C�g�����S
	UI_TITLELOGO_PARTS_MAX,
}UI_TITLELOGO_PARTS;

// UI:�^�C�g�����S �̃e�N�X�`���ԍ�
typedef enum 
{
	UI_TITLELOGO_TEXTURE_TITLELOGO,	// �^�C�g�����S
	UI_TITLELOGO_TEXTURE_MAX,
}UI_TITLELOGO_TEXTURE;

//****************************************
// �\���̂̒�`
//****************************************
// UI:�^�C�g�����S �̕��i���̏��\����
typedef struct
{
	UI_TITLELOGO_TEXTURE	tex;		// �e�N�X�`��
	float					fWidth;		// ��
	float					fHeight;	// ����
}Ui_titleLogoParts;

// UI:�^�C�g�����S �̃e�N�X�`�����̏��\����
typedef struct
{
	char	aTexturePath[TXT_MAX];	// �e�N�X�`���t�@�C���̑��΃p�X
	int		nPtnWidth;				// �p�^�[����
	int		nPtnHeight;				// �p�^�[������
}Ui_titleLogoTexture;

//****************************************
// �O���[�o���錾
//****************************************
static int g_nTex;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitUi_titleLogo�֐� - UI:�^�C�g�����S �̏��������� -
//========================================
void InitUi_titleLogo(void)
{
	g_nTex = LoadTexture("data\\TEXTURE\\UserInterface\\title.png");
}

//========================================
// UninitUi_titleLogo�֐� - UI:�^�C�g�����S �̏I������ -
//========================================
void UninitUi_titleLogo(void)
{
	
}

//========================================
// UpdateUi_titleLogo�֐� - UI:�^�C�g�����S �̍X�V���� -
//========================================
void UpdateUi_titleLogo(void) 
{
	// �|���S��(2D)�̐ݒ���
	Polygon2DSet polySet;
	/* �e�N�X�`���ԍ�	*/polySet.nTex = g_nTex;
	/* �p�^�[���ԍ�		*/polySet.nPtn = 0;
	/* �p�^�[�����X	*/polySet.nPtnX = 1;
	/* �p�^�[�����Y	*/polySet.nPtnY = 1;
	/* ��				*/polySet.fWidth = PIXEL * 256;
	/* ����				*/polySet.fHeight = PIXEL * 128;
	/* �ʒu				*/polySet.pos = UI_TITLELOGO_POS;
	/* ����				*/polySet.rot = D3DXVECTOR3(0.0f, 0.0f, D3DX_PI);
	/* �F				*/polySet.col = INITCOLOR;
	/* �J�������킹		*/polySet.bMatchCamera = false;
	// �|���S��(2D)�̐ݒ菈��
	SetPolygon2D(polySet);
}

//========================================
// DrawUi_titleLogo�֐� - UI:�^�C�g�����S �̕`�揈�� -
//========================================
void DrawUi_titleLogo(void)
{
	
}