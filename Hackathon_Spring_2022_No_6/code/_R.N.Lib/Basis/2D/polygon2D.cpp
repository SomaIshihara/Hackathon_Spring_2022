//========================================
// 
// �|���S��(2D)�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** polygon2D.cpp ***
//========================================
#include "assert.h"
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �O���[�o���ϐ��錾
//****************************************
// �|���S��(2D)�̒��_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffPolygon2D = NULL;
// �|���S��(2D)�̊Ǘ����
static Polygon2DControl g_polygon2DControl;

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================

//========================================
// InitPolygon2D�֐� - �|���S��(2D)�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitPolygon2D(void)
{
	// �f�o�C�X�̎擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(
		sizeof(VERTEX_2D) * 4 * POLYGON2D_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_2D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffPolygon2D,
		NULL);

	VERTEX_2D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPolygon2D->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntPoly = 0; nCntPoly < POLYGON2D_MAX; nCntPoly++, pVtx += 4)
	{
		// rhw�̐ݒ�
		SetRHW2D(pVtx);
	}

	// ���_�o�b�t�@���A�����b�N����
	g_pVtxBuffPolygon2D->Unlock();
}

//========================================
// UninitPolygon2D�֐� - �|���S��(2D)�̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitPolygon2D(void)
{
	// ���_�o�b�t�@�̔j��
	if (g_pVtxBuffPolygon2D != NULL)
	{
		g_pVtxBuffPolygon2D->Release();
		g_pVtxBuffPolygon2D = NULL;
	}
}

//========================================
// DrawPolygon2D�֐� - �|���S��2D�̕`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void DrawPolygon2D(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetD3DDevice();

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffPolygon2D, 0, sizeof(VERTEX_2D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_2D);

	// �|���S��(2D)�̊Ǘ����̃|�C���^
	Polygon2DControl *pPolyCtl = &g_polygon2DControl;
	// �|���S��(2D)�̐ݒ���̃|�C���^
	Polygon2DSet *pPolySet = pPolyCtl->aPolySet;

	for (int nCntPoly = 0; nCntPoly < pPolyCtl->nPolygonNum; nCntPoly++, pPolySet++)
	{
		// �e�N�X�`���̐ݒ�
		SetTexture(pDevice, pPolySet->nTex);

		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, nCntPoly * 4, 2);
	}
}

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================

//========================================
// SetPolygon2D�֐� - �|���S��(2D)�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetPolygon2D(Polygon2DSet polygon2DSet)
{
	if (g_polygon2DControl.nPolygonNum == POLYGON2D_MAX)
	{// �|���S��(2D)�̐����ő吔�ɒB���Ă��鎞�A
		assert(false);
		return;	// �������I������
	}

	// �ݒ������
	g_polygon2DControl.aPolySet[g_polygon2DControl.nPolygonNum] = polygon2DSet;

	VERTEX_2D *pVtx;	//���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffPolygon2D->Lock(0, 0, (void**)&pVtx, 0);
	{
		// ���_���ւ̃|�C���^��i�߂�
		pVtx += g_polygon2DControl.nPolygonNum * 4;

		// ���_���W�̐ݒ�
		SetVertexPos2D(pVtx,
			polygon2DSet.pos,
			polygon2DSet.rot,
			polygon2DSet.bMatchCamera,
			polygon2DSet.fWidth,
			polygon2DSet.fHeight);

		// ���_�J���[�̐ݒ�
		SetVertexColor2D(pVtx, polygon2DSet.col);

		// �e�N�X�`�����W�̐ݒ�
		SetTexturePos2D(pVtx,
			polygon2DSet.nPtn,
			polygon2DSet.nPtnX,
			polygon2DSet.nPtnY,
			NULL);
	}
	// ���_���W���A�����b�N����
	g_pVtxBuffPolygon2D->Unlock();

	// �|���S��(2D)�̐������Z
	g_polygon2DControl.nPolygonNum++;
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================

//========================================
// GetPolygon2DControl�֐� - �|���S��(2D)�̊Ǘ������擾 -
// Author:RIKU NISHIMURA
//========================================
Polygon2DControl *GetPolygon2DControl(void)
{
	return &g_polygon2DControl;
}

//============================================================
//--------------------| *** ���_�ݒ� *** |--------------------
//============================================================
#if 1
//========================================
// SetVertexPos2D�֐� - ���_���W�̐ݒ菈��(2D) -
// Author:RIKU NISHIMURA
//========================================
void SetVertexPos2D(VERTEX_2D *pVtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bMatchCamera, float fWidth, float fHeight)
{
	if (bMatchCamera)
	{// �ʒu���J�����ɍ��킹��t���O���^�̎��A
		// �ʒu���J�����ɍ��킹��
		MatchCamera2DPosition(&pos);
	}

	// �Ίp���̒���
	float fLength = sqrtf((fWidth * fWidth) + (fHeight * fHeight)) * 0.5f;
	// �Ίp���̊p�x
	float fAngle = atan2f(fWidth, fHeight);

	// ���_���W��ݒ�
	pVtx[0].pos.x = pos.x + sinf((rot.z + D3DX_PI) - (D3DX_PI - fAngle)) * fLength;
	pVtx[0].pos.y = pos.y + cosf((rot.z + D3DX_PI) - (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.x = pos.x + sinf((rot.z + D3DX_PI) + (D3DX_PI - fAngle)) * fLength;
	pVtx[1].pos.y = pos.y + cosf((rot.z + D3DX_PI) + (D3DX_PI - fAngle)) * fLength;
	pVtx[2].pos.x = pos.x + sinf((rot.z + D3DX_PI) - fAngle) * fLength;
	pVtx[2].pos.y = pos.y + cosf((rot.z + D3DX_PI) - fAngle) * fLength;
	pVtx[3].pos.x = pos.x + sinf((rot.z + D3DX_PI) + fAngle) * fLength;
	pVtx[3].pos.y = pos.y + cosf((rot.z + D3DX_PI) + fAngle) * fLength;
}

//========================================
// SetRHW2D�֐� - rhw�̐ݒ菈��(2D) -
// Author:RIKU NISHIMURA
//========================================
void SetRHW2D(VERTEX_2D *pVtx) 
{
	// rhw�̐ݒ�
	pVtx[0].rhw = 1.0f;
	pVtx[1].rhw = 1.0f;
	pVtx[2].rhw = 1.0f;
	pVtx[3].rhw = 1.0f;
}

//========================================
// SetVertexColor2D�֐� - ���_�F�̐ݒ菈��(2D) -
// Author:RIKU NISHIMURA
//========================================
void SetVertexColor2D(VERTEX_2D *pVtx, Color col)
{
	// ���_�F�̐ݒ�
	pVtx[0].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
	pVtx[1].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
	pVtx[2].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
	pVtx[3].col = D3DCOLOR_RGBA(col.r, col.g, col.b, col.a);
}

//========================================
// SetTexturePos2D�֐� - �e�N�X�`�����W�̐ݒ菈��(2D) -
// Author:RIKU NISHIMURA
//========================================
void SetTexturePos2D(VERTEX_2D *pVtx, int nPtn, int nPtnMaxX, int nPtnMaxY, D3DXVECTOR3 *pPos)
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
	pVtx[0].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX)						+ pos.x, ((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY)							+ pos.y);
	pVtx[1].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX) + (1.0f / nPtnMaxX)	+ pos.x, ((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY)							+ pos.y);
	pVtx[2].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX)						+ pos.x, (((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY)) + (1.0f / nPtnMaxY)	+ pos.y);
	pVtx[3].tex = D3DXVECTOR2((nPtn % nPtnMaxX) * (1.0f / nPtnMaxX) + (1.0f / nPtnMaxX)	+ pos.x, (((nPtn / nPtnMaxX) % nPtnMaxY) * (1.0f / nPtnMaxY)) + (1.0f / nPtnMaxY)	+ pos.y);
}

//========================================
// SetTexturePos2DCut�֐� - �e�N�X�`�����W�̐ݒ菈��(2D)(�؂���ver) -
// Author:RIKU NISHIMURA
//========================================
void SetTexturePos2DCut(VERTEX_2D *pVtx, Scale cutScale, D3DXVECTOR3 pos)
{
	pos.x += 0.5f;
	pos.y += 0.5f;

	// �e�N�X�`�����W�̐ݒ�
	pVtx[0].tex = D3DXVECTOR2(pos.x - (cutScale.fWidth * 0.5f), pos.y - (cutScale.fHeight * 0.5f));
	pVtx[1].tex = D3DXVECTOR2(pos.x + (cutScale.fWidth * 0.5f), pos.y - (cutScale.fHeight * 0.5f));
	pVtx[2].tex = D3DXVECTOR2(pos.x - (cutScale.fWidth * 0.5f), pos.y + (cutScale.fHeight * 0.5f));
	pVtx[3].tex = D3DXVECTOR2(pos.x + (cutScale.fWidth * 0.5f), pos.y + (cutScale.fHeight * 0.5f));
}
#endif
//============================================================
//--------------------| *** ���̑� *** |----------------------
//============================================================

//========================================
// MatchPosition�֐� - �`��ʒu����ɍ��킹�� -
// Author:RIKU NISHIMURA
//========================================
void MatchPosition(D3DXVECTOR3 *pDrawPos, D3DXVECTOR3 basePos, float fScWidth, float fScHeight)
{
	// �ʒu����̈ʒu�ɍ��킹��
	pDrawPos->x = pDrawPos->x - basePos.x + (fScWidth * 0.5f);
	pDrawPos->y = pDrawPos->y - basePos.y + (fScHeight * 0.5f);
}