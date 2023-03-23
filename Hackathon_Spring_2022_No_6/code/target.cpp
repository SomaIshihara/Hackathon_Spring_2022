//========================================
// 
// �W�I�̏���
// Author:KEISUKE OOTONO
// 
//========================================
//  *** target.cpp ***
//========================================
#include "target.h"

//****************************************
// �}�N����`
//****************************************
#define MAXTEX_TARGET_TYPE	(TARGET_MAX)		// �W�I�̎�ނ̍ő吔
#define MAX_TEXTURE			(16)				// �e�N�X�`���̍ő吔
//****************************************
// �v���g�^�C�v�錾
//****************************************

//****************************************
// �O���[�o���ϐ��錾
//****************************************
static LPD3DXMESH g_pMeshTarget[MAXTEX_TARGET_TYPE] = {};							// ���b�V��(���_���)�ւ̃|�C���^
static LPD3DXBUFFER g_pBuffMatTarget[MAXTEX_TARGET_TYPE] = {};						// �}�e���A���ւ̃|�C���^
static LPDIRECT3DTEXTURE9 g_pTextureTarget[MAXTEX_TARGET_TYPE][MAX_TEXTURE] = {};	// �e�N�X�`���ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffTarget = NULL;								// ���_�o�b�t�@�̃|�C���^
static DWORD					g_dwNumMatTarget[MAXTEX_TARGET_TYPE] = {};			// �}�e���A���̐�

static Target g_aTarget[MAX_TARGET];		// �A�C�e���̏��
static Summon g_aSummon[MAX_SUMMON];		// �����̏��

//****************************************
// �O���[�o���萔�錾
//****************************************
// ���f���p�X
static char g_aModelPath[TARGET_MAX][TXT_MAX] = {
	"data//MODEL//Item//cheese.x"
};

// �ړ����x
static const float g_aItemSize[TARGET_MAX] = {
	1.0f,
	0.75f,
	0.5f,
};

//========== *** �W�I�̏����擾 ***
Target *GetTarget(void)
{
	return &g_aTarget[0];
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitTarget�֐� - �W�I�̏��������� -
// Author:KEISUKE OOTONO
//========================================
void InitTarget(void)
{

}
//========================================
// UninitTarget�֐� - �W�I�̏I������ -
// Author:KEISUKE OOTONO
//========================================
void UninitTarget(void)
{

}
//========================================
// UpdateTarget�֐� - �W�I�̍X�V���� -
// Author:KEISUKE OOTONO
//========================================
void UpdateTarget(void)
{

}
//========================================
// DrawTarget�֐� - �W�I�̕`�揈�� -
// Author:KEISUKE OOTONO
//========================================
void DrawTarget(void)
{

}
//========================================
// SetTarget�֐� - �W�I�̐ݒ菈�� -
// Author:KEISUKE OOTONO
//========================================
void SetTarget(void)
{

}