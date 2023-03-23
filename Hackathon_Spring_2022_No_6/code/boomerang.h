//==========================================
//
//プレイヤープログラムのヘッダ[player.h]
//Author:石原颯馬
//
//==========================================
#ifndef _BOOMERANG_H_
#define _BOOMERANG_H_

#include "main.h"

//マクロ
#define MAX_USE_BOOMERANG		(3)		//ブーメランの使用数（ヘッダに移してもいい）

//プレイヤー構造体
struct Boomerang
{
	//位置類
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//向き
	D3DXVECTOR3 move;		//移動量

	//描画類
	D3DXMATRIX mtxWorld;	//ワールドマトリ
	bool bUse;		//プレイヤー使用の有無

	Parts3DInfo partsInfo;	// 部品(3D)の情報
};

//プロトタイプ宣言
void InitBoomerang(void);
void UninitBoomerang(void);
void UpdateBoomerang(void);
void DrawBoomerang(void);
void SetBoomerang(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Boomerang *GetBoomerang(void);

#endif // !_BOOMERANG_H_
