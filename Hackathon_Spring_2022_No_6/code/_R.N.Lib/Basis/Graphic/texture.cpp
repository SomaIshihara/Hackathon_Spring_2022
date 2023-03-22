//========================================
// 
// �e�N�X�`���֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** texture.cpp ***
//========================================
#include "assert.h"
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
// �e�N�X�`���̍ő吔
#define TEXTURE_MAX (1024)

//****************************************
// �\���̂̒�`
//****************************************
// �e�N�X�`���̊Ǘ����
typedef struct
{
	//========== *** �ǂݍ��݊֘A ***
	// �ǂݍ��ݍς̃e�N�X�`���p�X
	char aLoadTexturePath[TEXTURE_MAX][TXT_MAX] = {};
	unsigned int nTextureNum = 0;	// �e�N�X�`���̎�ސ�
}TextureInfo;

//****************************************
// �O���[�o���ϐ��錾
//****************************************
// �e�N�X�`���֘A�̃e�N�X�`���ւ̃|�C���^
static LPDIRECT3DTEXTURE9 g_aTextureTexture[TEXTURE_MAX] = {};
// �e�N�X�`���̊Ǘ����
static TextureInfo g_textureSetUpInfo;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================

//========================================
// UninitTexture�֐� - �e�N�X�`���̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitTexture(void)
{
	// �e�N�X�`���̔j��
	for (int nCntTex = 0; nCntTex < TEXTURE_MAX; nCntTex++)
	{
		if (g_aTextureTexture[nCntTex] != NULL)
		{
			g_aTextureTexture[nCntTex]->Release();
			g_aTextureTexture[nCntTex] = NULL;
		}
	}
}

//============================================================
//--------------------| *** ���o�� *** |----------------------
//============================================================

//========================================
// LoadTexture�֐� - �e�N�X�`���̓ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
int LoadTexture(char *pTexturePath)
{
	if (!strcmp(pTexturePath, ""))
	{// �e�N�X�`���p�X�������Ȃ����A
		return -1;
	}

	// ���ɓǂݍ��܂�Ă���e�N�X�`�����m�F
	for (int nCntTex = 0; nCntTex < g_textureSetUpInfo.nTextureNum; nCntTex++) 
	{
		if (!strcmp(pTexturePath, g_textureSetUpInfo.aLoadTexturePath[nCntTex])) 
		{// ���ɓ����p�X�̃e�N�X�`����ǂݍ���ł������A
			return nCntTex;	// �e�N�X�`���ԍ���Ԃ�
		}
	}

	if (g_textureSetUpInfo.nTextureNum == TEXTURE_MAX) 
	{// ���Ƀe�N�X�`���̐����ő�ɒB���Ă������A
		assert(false);
		return 0;
	}

	// �e�N�X�`���̃p�X��ۑ�
	sprintf(g_textureSetUpInfo.aLoadTexturePath[g_textureSetUpInfo.nTextureNum], "%s", pTexturePath);

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// �e�N�X�`���̓ǂݍ���
	D3DXCreateTextureFromFile(pDevice, pTexturePath, &g_aTextureTexture[g_textureSetUpInfo.nTextureNum]);

	// �e�N�X�`���ԍ���Ԃ�
	return g_textureSetUpInfo.nTextureNum++;
}

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================

//========================================
// SetTexture�֐� - �e�N�X�`���̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetTexture(LPDIRECT3DDEVICE9 pDevice, int nTex) 
{
	if (nTex == -1) 
	{// �e�N�X�`���ԍ���-1�̎��A
		// �e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, NULL);
		return;	// �������I������
	}

	// �e�N�X�`���̐ݒ�
	pDevice->SetTexture(0, g_aTextureTexture[nTex]);
}