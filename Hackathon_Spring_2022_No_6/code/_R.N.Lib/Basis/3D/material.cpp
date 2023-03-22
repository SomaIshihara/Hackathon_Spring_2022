//========================================
// 
// マテリアル関連の処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** material.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 設定 *** |------------------------
//============================================================

//========================================
// SetMaterial関数 - マテリアルの設定 -
// Author:RIKU NISHIMURA
//========================================
void SetMaterial(LPDIRECT3DDEVICE9 pDevice, D3DMATERIAL9 *pMat, Color col)
{
	// マテリアルの材質パラメーターを保存
	D3DXCOLOR DiffuseTemp = pMat->Diffuse;
	D3DXCOLOR EmissiveTemp = pMat->Emissive;

	// マテリアルの材質パラメーターを設定
	pMat->Diffuse.r = DiffuseTemp.r * ((float)col.r / (float)255);
	pMat->Diffuse.g = DiffuseTemp.g * ((float)col.g / (float)255);
	pMat->Diffuse.b = DiffuseTemp.b * ((float)col.b / (float)255);
	pMat->Diffuse.a = DiffuseTemp.a * ((float)col.a / (float)255);
	pMat->Emissive.r = EmissiveTemp.r * ((float)col.r / (float)255);
	pMat->Emissive.g = EmissiveTemp.g * ((float)col.g / (float)255);
	pMat->Emissive.b = EmissiveTemp.b * ((float)col.b / (float)255);
	pMat->Emissive.a = EmissiveTemp.a * ((float)col.a / (float)255);

	// マテリアルの設定
	pDevice->SetMaterial(pMat);

	// マテリアルの材質パラメーターを元に戻す
	pMat->Diffuse = DiffuseTemp;
	pMat->Emissive = EmissiveTemp;
}