//==========================================
//
//ブーメランプログラムのヘッダ[player.h]
//Author:石原颯馬
//
//==========================================
#ifndef _BOOMERANG_H_
#define _BOOMERANG_H_

#include "main.h"

//マクロ
#define MAX_USE_BOOMERANG		(3)		//ブーメランの使用数
#define BOOMERANG_HIT_RADIUS	(4.0f)	//ブーメランの当たり判定の半径

//投げ方向列挙
typedef enum
{
	THROWTYPE_LEFT = 0,
	THROWTYPE_RIGHT,
	THROWTYPE_MAX
} THROWTYPE;

//プレイヤー構造体
struct Boomerang
{
	//位置類
	D3DXVECTOR3 pos;		//位置
	D3DXVECTOR3 posOld;		//前回の位置
	D3DXVECTOR3 rot;		//向き
	float fRotTotal;		//回転した量
	D3DXVECTOR3 move;		//移動量
	int nCounterStraight;	//直線移動時間カウンタ
	float fRotForce;		//回転力
	bool bEndRotate;		//回転力をかけるのを終了するか
	bool bReturn;			//跳ね返りフラグ
	THROWTYPE throwType;	//投げ方向

	//描画類
	D3DXMATRIX mtxWorld;	//ワールドマトリ
	bool bUse;				//ブーメラン使用の有無

	Parts3DInfo partsInfo;	// 部品(3D)の情報
	Collision coll;			// 当たり判定の結果
};

//プロトタイプ宣言
void InitBoomerang(void);
void UninitBoomerang(void);
void UpdateBoomerang(void);
void DrawBoomerang(void);
void SetBoomerang(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
Boomerang *GetBoomerang(void);

#endif // !_BOOMERANG_H_
