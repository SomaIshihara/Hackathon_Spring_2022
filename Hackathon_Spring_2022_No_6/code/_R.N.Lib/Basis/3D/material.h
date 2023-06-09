//========================================
// 
// マテリアル関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
//  *** material.h ***
//========================================
#ifndef _MATERIAL_H_	// このマクロ定義がされていなかった時
#define _MATERIAL_H_	// 二重インクルード防止のマクロを定義する

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 設定 ***
// マテリアルの設定
void SetMaterial(LPDIRECT3DDEVICE9 pDevice, D3DMATERIAL9 *pMat, Color col);

#endif