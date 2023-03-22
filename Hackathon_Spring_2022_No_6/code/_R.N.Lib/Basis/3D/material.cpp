//========================================
// 
// �}�e���A���֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** material.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================

//========================================
// SetMaterial�֐� - �}�e���A���̐ݒ� -
// Author:RIKU NISHIMURA
//========================================
void SetMaterial(LPDIRECT3DDEVICE9 pDevice, D3DMATERIAL9 *pMat, Color col)
{
	// �}�e���A���̍ގ��p�����[�^�[��ۑ�
	D3DXCOLOR DiffuseTemp = pMat->Diffuse;
	D3DXCOLOR EmissiveTemp = pMat->Emissive;

	// �}�e���A���̍ގ��p�����[�^�[��ݒ�
	pMat->Diffuse.r = DiffuseTemp.r * ((float)col.r / (float)255);
	pMat->Diffuse.g = DiffuseTemp.g * ((float)col.g / (float)255);
	pMat->Diffuse.b = DiffuseTemp.b * ((float)col.b / (float)255);
	pMat->Diffuse.a = DiffuseTemp.a * ((float)col.a / (float)255);
	pMat->Emissive.r = EmissiveTemp.r * ((float)col.r / (float)255);
	pMat->Emissive.g = EmissiveTemp.g * ((float)col.g / (float)255);
	pMat->Emissive.b = EmissiveTemp.b * ((float)col.b / (float)255);
	pMat->Emissive.a = EmissiveTemp.a * ((float)col.a / (float)255);

	// �}�e���A���̐ݒ�
	pDevice->SetMaterial(pMat);

	// �}�e���A���̍ގ��p�����[�^�[�����ɖ߂�
	pMat->Diffuse = DiffuseTemp;
	pMat->Emissive = EmissiveTemp;
}