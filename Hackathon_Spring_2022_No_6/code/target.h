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
#include "_R.N.Lib\Basis\Other\window.h"
#include "_R.N.Lib\RNmain.h"
#include "main.h"
//****************************************
// マクロ定義
//****************************************
#define MAX_TARGET		(64)	// 標的の最大数
#define MAX_SUMMON		(640)	// 召喚の最大数
#define MAX_POINT		(64)	// 出現位置の最大数
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

	int nCntFlame;			// フレーム数
	int nPtn;				// パターン番号

	float fSpeed;			// 移動速度
	float Tarpos;			// 目標位置

	bool bRot;				// 方向フラグ
	bool bUse;				// 使用フラグ

}Target;

typedef struct
{
	int nType; // 種類
	int nPoint;// 出現位置
	int nTime; // 出現時間
	int nMTyoe;// 移動方向

	bool bUse; // 使用フラグ
}Summon;

typedef struct
{
	D3DXVECTOR3 pos;		// 位置
}Point;
//****************************************
// プロトタイプ宣言
//****************************************
void InitTarget(void);
void UpdateTarget(void);
void LoadSummon(void);
void LoadTarget(void);
void SetTarget(int nPos, TARGET_ITEM type, int mType);

Target *GetTarget(void);
#endif