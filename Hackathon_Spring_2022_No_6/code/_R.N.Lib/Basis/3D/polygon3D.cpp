//========================================
// 
// �|���S��(3D)�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** polygon3D.cpp ***
//========================================
#include "assert.h"
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �O���[�o���ϐ��錾
//****************************************
// �|���S��(3D)�̒��_�o�b�t�@�ւ̃|�C���^
LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffpolygon3D = NULL;
// �|���S��(3D)�̊Ǘ����
Polygon3DControl g_polygon3DControl;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================

//========================================
// InitPolygon3D�֐� - �|���S��(3D)�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitPolygon3D(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_3D) * 4 * POLYGON3D_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffpolygon3D,
		NULL);
}

//========================================
// UninitPolygon3D�֐� - �|���S��(3D)�̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitPolygon3D(void)
{
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffpolygon3D != NULL)
	{
		g_pVtxBuffpolygon3D->Release();
		g_pVtxBuffpolygon3D = NULL;
	}
}

//========================================
// DrawPolygon3D�֐� - �|���S��(3D)�̕`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void DrawPolygon3D(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxSelf;	// �{�̃}�g���b�N�X

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffpolygon3D, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntPoly = 0; nCntPoly < g_polygon3DControl.nPolygonNum; nCntPoly++)
	{
		// �|���S��(3D)�̐ݒ���
		Polygon3DSet polygon3DSet = g_polygon3DControl.aPolySet[nCntPoly];

		// ���[���h�}�g���b�N�X�̏�����
		D3DXMatrixIdentity(&mtxSelf);

		{
			// �ʒu�ƌ�����ݒ�
			D3DXVECTOR3 pos = polygon3DSet.pos;
			D3DXVECTOR3 rot = polygon3DSet.rot;
			
			// �����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
			D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);
			
			// �ʒu�𔽉f
			D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
			D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);
		}

		// ���[���h�}�g���b�N�X�̐ݒ�
		pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);

		// �e�N�X�`���̐ݒ�
		SetTexture(pDevice, polygon3DSet.nTex);

		// �|���S��(3D)�̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nCntPoly, 2);
	}
}

//========================================
// DrawSinglePolygon3D�֐� - �|���S��(3D)�̕`�揈��(�P��) -
// Author:RIKU NISHIMURA
//========================================
void DrawSinglePolygon3D(LPDIRECT3DDEVICE9 pDevice,int nIdx)
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtxSelf;	// �{�̃}�g���b�N�X

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffpolygon3D, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	// �|���S��(3D)�̐ݒ���
	Polygon3DSet polygon3DSet = g_polygon3DControl.aPolySet[nIdx];

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtxSelf);

	{
		// �ʒu�ƌ�����ݒ�
		D3DXVECTOR3 pos = polygon3DSet.pos;
		D3DXVECTOR3 rot = polygon3DSet.rot;

		// �����𔽉f
		D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
		D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxRot);

		// �ʒu�𔽉f
		D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
		D3DXMatrixMultiply(&mtxSelf, &mtxSelf, &mtxTrans);
	}

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtxSelf);

	// �e�N�X�`���̐ݒ�
	SetTexture(pDevice, polygon3DSet.nTex);

	// �|���S��(3D)�̕`��
	pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 4 * nIdx, 2);
}

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================

//========================================
// SetPolygon3D�֐� - �|���S��(3D)�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetPolygon3D(Polygon3DSet polygon3DSet)
{
	if (g_polygon3DControl.nPolygonNum == POLYGON3D_MAX) 
	{// �|���S��(3D)�̐����ő吔�ɒB���Ă��鎞�A
		assert(false);
		return;	// �������I������
	}

	// �|���S����
	int nPolyNum = g_polygon3DControl.nPolygonNum;

	// �ݒ������
	g_polygon3DControl.aPolySet[nPolyNum] = polygon3DSet;

	VERTEX_3D *pVtx;	//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffpolygon3D->Lock(0, 0, (void**)&pVtx, 0);
	{
		// ���_���ւ̃|�C���^��i�߂�
		pVtx += g_polygon3DControl.nPolygonNum * 4;

		// ���_���W�̐ݒ�
		SetVertexPos3D(pVtx, polygon3DSet.fWidth, polygon3DSet.fHeight);

		// �@���x�N�g���̐ݒ�
		SetNormalLine3D(pVtx, FindNormalVector(polygon3DSet.rot));

		// ���_�J���[�̐ݒ�
		SetVertexColor3D(pVtx, polygon3DSet.col);

		// �e�N�X�`�����W�̐ݒ�
		SetTexturePos3D(pVtx, polygon3DSet.nPtn, polygon3DSet.nPtnX, polygon3DSet.nPtnY, NULL);
	}
	// ���_���W���A�����b�N����
	g_pVtxBuffpolygon3D->Unlock();

	// �|���S��(3D)�̐������Z
	g_polygon3DControl.nPolygonNum++;
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================

//========================================
// GetPolygon3DControl�֐� - �|���S��(3D)�̊Ǘ������擾 -
// Author:RIKU NISHIMURA
//========================================
Polygon3DControl *GetPolygon3DControl(void) 
{
	return &g_polygon3DControl;
}

//============================================================
//--------------------| *** ���_�ݒ� *** |--------------------
//============================================================

//========================================
// SetVertexPos3D�֐� - ���_���W�̐ݒ菈��(3D) -
// Author:RIKU NISHIMURA
//========================================
void SetVertexPos3D(VERTEX_3D *pVtx, float fWidth, float fHeight)
{
	// ���_���W�̐ݒ�
	pVtx[0].pos = D3DXVECTOR3(-(fWidth * 0.5f), 0.0f,  (fHeight * 0.5f));
	pVtx[1].pos = D3DXVECTOR3( (fWidth * 0.5f), 0.0f,  (fHeight * 0.5f));
	pVtx[2].pos = D3DXVECTOR3(-(fWidth * 0.5f), 0.0f, -(fHeight * 0.5f));
	pVtx[3].pos = D3DXVECTOR3( (fWidth * 0.5f), 0.0f, -(fHeight * 0.5f));
}

//========================================
// SetNormalLine3D�֐� - �@���x�N�g���̐ݒ菈��(3D) -
// Author:RIKU NISHIMURA
//========================================
void SetNormalLine3D(VERTEX_3D *pVtx, D3DXVECTOR3 nor) 
{
	// �@���x�N�g���̐ݒ�
	pVtx[0].nor = nor;
	pVtx[1].nor = nor;
	pVtx[2].nor = nor;
	pVtx[3].nor = nor;
}

//========================================
// SetVertexColor3D�֐� - ���_�F�̐ݒ菈��(3D) -
// Author:RIKU NISHIMURA
//========================================
void SetVertexColor3D(VERTEX_3D *pVtx, Color col)
{
	// ���_�F�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
}

//========================================
// SetTexturePos3D�֐� - �e�N�X�`�����W�̐ݒ菈��(3D) -
// Author:RIKU NISHIMURA
//========================================
void SetTexturePos3D(VERTEX_3D *pVtx, int nPtn, int nPtnMaxX, int nPtnMaxY, D3DXVECTOR3 *pPos)
{
	if (nPtnMaxX * nPtnMaxY == 0)
	{// �p�^�[���̏����0�̎��A
		// �������I������
		return;
	}

	D3DXVECTOR3 pos;	// �ʒu

	if (pPos == NULL)
	{// �ʒu�̃|�C���^��NULL�̎��A
		// �ʒu��������
		pos = D3DXVECTOR3(0, 0, 0);
	}
	else
	{// �ʒu�̃|�C���^��NULL�Ŗ������A
		// �ʒu��-�␳���đ��
		pos = -*pPos;
	}

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX) + pos.x						, ((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY) + pos.y);
	pVtx[1].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX) + (1.0f / nPtnMaxX) + pos.x	, ((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY) + pos.y);
	pVtx[2].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX) + pos.x						, (((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY)) + (1.0f / nPtnMaxY) + pos.y);
	pVtx[3].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX) + (1.0f / nPtnMaxX) + pos.x	, (((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY)) + (1.0f / nPtnMaxY) + pos.y);
}