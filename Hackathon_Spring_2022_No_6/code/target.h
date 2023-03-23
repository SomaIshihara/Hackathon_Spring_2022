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
	TARGET_A = 0,	// ポチ
	TARGET_B,		// クー
	TARGET_C,		// 鷹
	TARGET_D,		// 棘 
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

	int nCntMFLame;			// 移動用のフレーム数
	int nCntMove;			// 移動時間
	int nCntSwit;			// 切り替え回数

	float fSpeed;			// 移動速度
	float Tarpos;			// 目標位置

	bool bMove;				// 移動フラグ
	bool bRot;				// 方向フラグ
	bool bUse;				// 使用フラグ

	bool bDown;			// ダウン
	int nDownCounter;	// ダウンカウンター

	bool bPop;			// 出現
	int nPopCounter;	// 出現カウンター

	bool bHide;			// 出現
	int nHideCounter;	// 出現カウンター
}Target;

// targetの情報構造体
typedef struct
{
	int nLife;		// 寿命
	int nScore;		// スコア

	float fWidth;	// 幅
	float fHeight;	// 高さ
}TargetType;

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
void LoadTargetType(void);
void SetTarget(int nPos, TARGET_ITEM type, int mType);

Target *GetTarget(void);
TargetType *GetTargetType(void);
#endif