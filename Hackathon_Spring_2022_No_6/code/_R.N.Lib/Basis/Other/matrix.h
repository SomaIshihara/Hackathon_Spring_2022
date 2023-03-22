//========================================
// 
// マトリックス関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
//  *** matrix.h ***
//========================================
#ifndef _MATRIX_H_	// このマクロ定義がされていなかった時
#define _MATRIX_H_	// 二重インクルード防止のマクロを定義する

//****************************************
// プロトタイプ宣言
//****************************************
// 位置と向きをマトリックスに変換して返す
D3DXMATRIX ConvPosRotToMatrix(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
// マトリックスを掛け合わせる
D3DXMATRIX MultiplyMatrix(D3DXMATRIX mtxParent, D3DXMATRIX mtxChild);
// マトリックスの位置成分を分解して返す
D3DXVECTOR3 ConvMatrixToPos(D3DXMATRIX mtx);
// マトリックスの向き成分を分解して返す
D3DXVECTOR3 ConvMatrixToRot(D3DXMATRIX mtx);

#endif