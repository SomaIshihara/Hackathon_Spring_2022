//========================================
// 
// 標的の処理
// Author:KEISUKE OOTONO
// 
//========================================
//  *** target.h ***
//========================================
#ifndef _TARGET_H_	// このマクロ定義がされていなかった時
#define _TARGET_H_	// 二重インクルード防止のマクロを定義する
#include "main.h"
//****************************************
// マクロ定義
//****************************************
#define MAX_TARGET		(64)						// 標的の最大数
#define MAX_SUMMON		(64)						// 出現位置の最大数
//****************************************
// 列挙型の定義
//****************************************
// Itemの種類
typedef enum
{
	TARGET_A = 0,	// 
	TARGET_B,		// 
	TARGET_C,		// 
	TARGET_MAX
}TARGET_ITEM;
//****************************************
// 構造体の定義
//****************************************
// targetの情報構造体
typedef struct
{
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rot;		// 向き
	D3DXVECTOR3 move;		// 移動量
	D3DXMATRIX mtxWorld;	// ワールドマトリックス
	TARGET_ITEM type;		// 種類

	int nSummon;			// 標的の配置場所

	float fSpeed;			// 移動速度

	bool bSet;				// 再配置するフラグ
	bool bUse;				// 使用フラグ
}Target;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
}Summon;
//****************************************
// プロトタイプ宣言
//****************************************
// アイテムの読み込み処理
void InitTarget(void);
void UninitTarget(void);
void UpdateTarget(void);
void DrawTarget(void);
void SetTarget(void);
Target *GetTarget(void);
#endif