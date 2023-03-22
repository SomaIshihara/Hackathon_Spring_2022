//========================================
// 
// �}�g���b�N�X�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** matrix.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// ConvPosRotToMatrix�֐� - �ʒu�ƌ������}�g���b�N�X�ɕϊ����ĕԂ� -
// Author:RIKU NISHIMURA
//========================================
D3DXMATRIX ConvPosRotToMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	// �v�Z�p�}�g���b�N�X
	D3DXMATRIX mtxRot, mtxTrans;
	D3DXMATRIX mtx;	// �{�̂̃}�g���b�N�X

	// ���[���h�}�g���b�N�X�̏�����
	D3DXMatrixIdentity(&mtx);

	// �����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, rot.y, rot.x, rot.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxRot);

	// �ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, pos.x, pos.y, pos.z);
	D3DXMatrixMultiply(&mtx, &mtx, &mtxTrans);

	return mtx;
}

//========================================
// MultiplyMatrix�֐� - �}�g���b�N�X���|�����킹�� -
// Author:RIKU NISHIMURA
//========================================
D3DXMATRIX MultiplyMatrix(D3DXMATRIX mtxParent, D3DXMATRIX mtxChild)
{
	// �Z�o�������i�̃��[���h�}�g���b�N�X�Ɛe�̃}�g���b�N�X���|�����킹��
	D3DXMatrixMultiply(
		&mtxChild,
		&mtxChild,
		&mtxParent);

	return mtxChild;
}

//========================================
// ConvMatrixToPos�֐� - �}�g���b�N�X�̈ʒu�����𕪉����ĕԂ� -
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 ConvMatrixToPos(D3DXMATRIX mtx)
{
	return D3DXVECTOR3(mtx._41, mtx._42, mtx._43);
}

//========================================
// ConvMatrixToRot�֐� - �}�g���b�N�X�̌��������𕪉����ĕԂ� -
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 ConvMatrixToRot(D3DXMATRIX mtx)
{
	return D3DXVECTOR3(mtx._31, mtx._32, mtx._33);
}