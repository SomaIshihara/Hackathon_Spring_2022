//========================================
// 
// ��(3D)�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** line3D.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
// ��(3D)�̍ő吔
#define LINE3D_MAX (1024)

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �擾 ***
// ��(3D)�֘A�̊Ǘ����̃p�����[�^�[�����l��Ԃ�
void InitParameterLine3DControl(Line3DControl *pPoly);

//****************************************
// �O���[�o���ϐ��錾
//****************************************
// ��(3D)�̒��_�o�b�t�@�ւ̃|�C���^
static LPDIRECT3DVERTEXBUFFER9 g_pVtxBuffLine3D = NULL;
static Line3DControl g_line3DControl;	// ��(3D)�֘A�̊Ǘ����

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================

//========================================
// InitParameterLine3DControl�֐� - ��(3D)�֘A�̊Ǘ����̃p�����[�^�[�����l��Ԃ� -
// Author:RIKU NISHIMURA
//========================================
void InitParameterLine3DControl(Line3DControl *pPoly)
{
	pPoly->nLineNum = 0;	// ���̐�
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
// InitLine3D�֐� - ��(3D)�֘A�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitLine3D(void)
{
	// �����֘A�����̊Ǘ����̃|�C���^
	Line3DControl *pPoly = &g_line3DControl;

	// �p�����[�^�[�̏�����
	InitParameterLine3DControl(pPoly);

	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();

	// ���_�o�b�t�@�̐���
	pDevice->CreateVertexBuffer(sizeof(VERTEX_3D) * 2 * LINE3D_MAX,
		D3DUSAGE_WRITEONLY,
		FVF_VERTEX_3D,
		D3DPOOL_MANAGED,
		&g_pVtxBuffLine3D,
		NULL);

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLine3D->Lock(0, 0, (void**)&pVtx, 0);

	for (int nCntLine = 0; nCntLine < LINE3D_MAX; nCntLine++, pVtx += 2)
	{
		// ���_�J���[��ݒ�
		pVtx[0].col = ColorToD3DCOLOR(INITCOLOR);
		pVtx[1].col = ColorToD3DCOLOR(INITCOLOR);
	}

	// ���_���W���A�����b�N����
	g_pVtxBuffLine3D->Unlock();
}

//========================================
// DrawLine3D�֐� - ��(3D)�֘A�̕`�揈�� -
// Author:RIKU NISHIMURA
//========================================
void DrawLine3D(void)
{
	// �f�o�C�X�擾
	LPDIRECT3DDEVICE9 pDevice = GetD3DDevice();
	D3DXMATRIX mtx;
	D3DXMATRIX mtxRot, mtxTrans;	// �v�Z�p�}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtx);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, 0.0f, 0.0f, 0.0f);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	// ���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &mtx);

	// �����_�����O�X�e�[�g��ݒ�
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	// Z�e�X�g�𖳌��ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, FALSE);

	// ���_�o�b�t�@���f�[�^�X�g���[���ɐݒ�
	pDevice->SetStreamSource(0, g_pVtxBuffLine3D, 0, sizeof(VERTEX_3D));

	// ���_�t�H�[�}�b�g�̐ݒ�
	pDevice->SetFVF(FVF_VERTEX_3D);

	for (int nCntLine = 0; nCntLine < g_line3DControl.nLineNum; nCntLine++)
	{
		// �|���S���̕`��
		pDevice->DrawPrimitive(D3DPT_LINELIST, 2 * nCntLine, 1);
	}

	// �����_�����O�X�e�[�g�����ɖ߂�
	pDevice->SetRenderState(D3DRS_LIGHTING, TRUE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	// Z�e�X�g��L���ɂ���
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_LESSEQUAL);
	pDevice->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);
}

//========================================
// UninitLine3D�֐� - ��(3D)�֘A�̏I������ -
// Author:RIKU NISHIMURA
//========================================
void UninitLine3D(void)
{
	// ���̒��_�o�b�t�@�̔j��
	if (g_pVtxBuffLine3D != NULL)
	{
		g_pVtxBuffLine3D->Release();
		g_pVtxBuffLine3D = NULL;
	}
}

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================

//========================================
// GetLine3DControl�֐� - ��(3D)�̊Ǘ������擾 -
// Author:RIKU NISHIMURA
//========================================
Line3DControl *GetLine3DControl(void) 
{
	return &g_line3DControl;
}

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================

//========================================
// SetLine3D�֐� - ��(3D)�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetLine3D(Line3DSet lineSet)
{
	// �����֘A�����̊Ǘ����̃|�C���^
	Line3DControl *pPoly = &g_line3DControl;

	if (pPoly->nLineNum >= LINE3D_MAX)
	{// �����蔻��̐��̐����ő吔�ɒB���Ă��鎞�A
		return;	// �������I������
	}

	VERTEX_3D *pVtx;	// ���_���ւ̃|�C���^

	// ���_�o�b�t�@�����b�N���A���_���ւ̃|�C���^���擾
	g_pVtxBuffLine3D->Lock(0, 0, (void**)&pVtx, 0);

	// ���_���ւ̃|�C���^��i�߂�
	pVtx += pPoly->nLineNum * 2;

	// �ʒu����
	pVtx[0].pos = lineSet.pos1;
	pVtx[1].pos = lineSet.pos2;

	// �F����
	pVtx[0].col = ColorToD3DCOLOR(lineSet.col1);
	pVtx[1].col = ColorToD3DCOLOR(lineSet.col2);

	// ���_���W���A�����b�N����
	g_pVtxBuffLine3D->Unlock();

	// �����蔻��̐��̐������Z
	pPoly->nLineNum++;
}