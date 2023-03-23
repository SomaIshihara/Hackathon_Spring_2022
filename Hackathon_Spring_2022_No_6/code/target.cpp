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
	"data//MODEL//Item//cheese.x",
	"data//MODEL//Item//cheese.x",
	"data//MODEL//Item//cheese.x",
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
		// �f�o�C�X�擾
		LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

		D3DXMATERIAL *pMat;	// �}�e���A���ւ̃|�C���^

		for (int nCntType = 0; nCntType < MAXTEX_TARGET_TYPE; nCntType++)
		{
			// X�t�@�C���̓ǂݍ���
			D3DXLoadMeshFromX(
				g_aModelPath[nCntType],
				D3DXMESH_SYSTEMMEM,
				pDevice,
				NULL,
				&g_pBuffMatTarget[nCntType],
				NULL,
				&g_dwNumMatTarget[nCntType],
				&g_pMeshTarget[nCntType]);

			// �}�e���A�����ɑ΂���|�C���^���擾
			pMat = (D3DXMATERIAL*)g_pBuffMatTarget[nCntType]->GetBufferPointer();

			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatTarget[nCntType]; nCntMat++)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{
					// �e�N�X�`���̓ǂݍ���
					D3DXCreateTextureFromFile(pDevice, pMat[nCntMat].pTextureFilename, &g_pTextureTarget[nCntType][nCntMat]);
				}
			}
		}

		// �W�I�̏���������
		for (int nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++)
		{
			g_aTarget[nCntTarget].pos = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].rot = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].move = INITD3DXVECTOR3;
			g_aTarget[nCntTarget].type = TARGET_A;
			g_aTarget[nCntTarget].bUse = false;
		}
}
//========================================
// UninitTarget�֐� - �W�I�̏I������ -
// Author:KEISUKE OOTONO
//========================================
void UninitTarget(void)
{
	//���b�V���̔j��
	for (int nCntType = 0; nCntType < MAXTEX_TARGET_TYPE; nCntType++)
	{
		if (g_pMeshTarget[nCntType] != NULL)
		{
			g_pMeshTarget[nCntType]->Release();
			g_pMeshTarget[nCntType] = NULL;

		}
	}

	//���_�o�b�t�@�̔j��
	if (g_pVtxBuffTarget != NULL)
	{
		g_pVtxBuffTarget->Release();
		g_pVtxBuffTarget = NULL;

	}

	//�e�N�X�`���̔j��
	for (int nCntType = 0; nCntType < MAXTEX_TARGET_TYPE; nCntType++)
	{
		for (int nCntMat = 0; nCntMat < 16; nCntMat++)
		{
			if (g_pTextureTarget[nCntType][nCntMat] != NULL)
			{
				g_pTextureTarget[nCntType][nCntMat]->Release();
				g_pTextureTarget[nCntType][nCntMat] = NULL;
			}
		}
	}
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
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			// ���݂̃}�e���A���̕ۑ��p
	D3DXMATERIAL *pMat;				// �}�e���A���f�[�^�ւ̃|�C���^
	D3DXMATRIX mtxSelf;				// �{�̂̃}�g���b�N�X

	for (int nCntPlayer = 0; nCntPlayer < MAXTEX_TARGET_TYPE; nCntPlayer++)
	{
		// ���݂̃}�e���A�����擾
		pDevice->GetMaterial(&matDef);

		// �{�̂̃��[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxSelf);

		// �{�̂̌����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aTarget[nCntPlayer].rot.y, g_aTarget[nCntPlayer].rot.x, g_aTarget[nCntPlayer].rot.z);
		D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);

		// �{�̂̈ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, g_aTarget[nCntPlayer].pos.x, g_aTarget[nCntPlayer].pos.y, g_aTarget[nCntPlayer].pos.z);
		D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);

		// �{�̂̃��[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);
		D3DXMATRIX	mtxParent;	// �e�}�g���b�N�X

		// �}�e���A���f�[�^�ւ̃|�C���^���擾
		pMat = (D3DXMATERIAL*)g_pBuffMatTarget[g_aTarget[nCntPlayer].type]->GetBufferPointer();

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &g_aTarget[nCntPlayer].mtxWorld);

		if (g_aTarget[nCntPlayer].bUse == true)
		{
			for (int nCntMat = 0; nCntMat < (int)g_dwNumMatTarget[g_aTarget[nCntPlayer].type]; nCntMat++)
			{
				// �}�e���A���̐ݒ�
				pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

				// �e�N�X�`���̐ݒ�
				pDevice->SetTexture(0, g_pTextureTarget[g_aTarget[nCntPlayer].type][nCntMat]);

				// �|���S��(�p�[�c)�̕`��
				g_pMeshTarget[g_aTarget[nCntPlayer].type]->DrawSubset(nCntMat);

			}
		}
	}
}
//========================================
// SetTarget�֐� - �W�I�̐ݒ菈�� -
// Author:KEISUKE OOTONO
//========================================
void SetTarget(int nPos, TARGET_ITEM type)
{
	for (int nCntItem = 0; nCntItem < MAX_TARGET; nCntItem++)
	{
		if (g_aTarget[nCntItem].bUse == false)
		{//�g�p����Ă��Ȃ��Ƃ�
			g_aTarget[nCntItem].pos = g_aSummon[nPos].pos;					// �ʒu
			g_aTarget[nCntItem].type = type;								// ��ނ̐ݒ�
			g_aTarget[nCntItem].bUse = true;								// �g�p�t���O
			break;
		}
	}
}