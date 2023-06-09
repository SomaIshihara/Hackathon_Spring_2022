//========================================
// 
// 物理関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
//  *** physics.h ***
//========================================
#ifndef _PHYSICS_H_	// このマクロ定義がされていなかった時
#define _PHYSICS_H_	// 二重インクルード防止のマクロを定義する

// R.N.Lib
#include "../3D/parts3D.h"
#include "geometry.h"

//****************************************
// マクロ定義
//****************************************
// 当たり判定の最大数
#define HIT_TEST_MAX (4)
// 当たり判定の部品の最大数
#define HIT_TEST_PARTS_MAX (16)

//****************************************
// 列挙型の定義
//****************************************
//========== *** 当たり判定 ***
// 衝突チェックのモード
typedef enum 
{
	COLLCHK_MODE_NORMAL,	// 通常
	COLLCHK_MODE_LOOKDOWN,	// 見下ろし
}COLLCHK_MODE;

// 当たり判定の形
typedef enum
{
	HIT_TEST_FORM_SPHERE,	// 球
	HIT_TEST_FORM_SQUARE,	// 四角
	HIT_TEST_FORM_CYLINDER,	// 円筒
	HIT_TEST_FORM_MAX,
}HIT_TEST_FORM;

//========== *** その他 ***
// 衝突方向
typedef enum 
{
	HITDIRECTION_TOP,		// 上
	HITDIRECTION_BOTTOM,	// 下
	HITDIRECTION_LEFT,		// 左
	HITDIRECTION_RIGHT,		// 右
	HITDIRECTION_BACK,		// 奥
	HITDIRECTION_FRONT,		// 手前
	HITDIRECTION_MAX,
}HITDIRECTION;

// 方向
typedef enum
{
	DIRECTION_UP,			// 上
	DIRECTION_DOWN,			// 下
	DIRECTION_LEFT,			// 左
	DIRECTION_RIGHT,		// 右
	DIRECTION_BACK,			// 奥
	DIRECTION_FRONT,		// 手前
	DIRECTION_LEFT_BACK,	// 左奥
	DIRECTION_LEFT_FRONT,	// 左手前
	DIRECTION_RIGHT_BACK,	// 右奥
	DIRECTION_RIGHT_FRONT,	// 右手前
	DIRECTION_MAX,
}DIRECTION;

// ベクトルの種類
typedef enum 
{
	VECTOR_X,		// X方向
	VECTOR_Y,		// Y方向
	VECTOR_Z,		// Z方向
	VECTOR_NONE,	// 無し
	VECTOR_MAX
}VECTOR;

// 頂点
typedef enum 
{
	VERTEX_X0Y0,	// 左上
	VERTEX_X1Y0,	// 右上
	VERTEX_X0Y1,	// 左下
	VERTEX_X1Y1,	// 右下
	VERTEX_MAX,
}VERTEX;

//****************************************
// 構造体の定義
//****************************************
//========== *** 衝突情報 ***
// 衝突情報構造体
typedef struct
{
	bool bColl;						// 衝突フラグ
	bool aColl[HITDIRECTION_MAX];	// 方向毎の衝突フラグ
	bool bOvl;						// 範囲内フラグ
	bool aOvl[HITDIRECTION_MAX];	// 方向毎の範囲内フラグ
	bool bHit;						// 当たりフラグ※物理的に接触している
	bool aHit[HITDIRECTION_MAX];	// 方向毎の当たりフラグ
}Collision;
// 当たり判定の部品情報構造体
typedef struct
{
	HIT_TEST_FORM hitTestForm;		// 当たり判定の形
	int nParent;					// 親番号
	float fWidth;					// 幅
	float fHeight;					// 高さ
	float fDepth;					// 奥行き
	D3DXVECTOR3 fixedRelativePos;	// 相対位置
	D3DXVECTOR3 fixedRelativeRot;	// 相対向き
	bool aGhost[HITDIRECTION_MAX];	// すり抜け情報
}HitTestParts;
//========== *** 設定情報 ***
// 当たり判定の情報構造体
typedef struct 
{
	int nHitTestPartsNum;	// 当たり判定の部品の数
	// 当たり判定の部品の情報
	HitTestParts aHitTestParts[HIT_TEST_PARTS_MAX];
}HitTest;
// 当たり判定の設定情報構造体
typedef struct
{
	int nHitTestNum;				// 当たり判定の数
	HitTest aHitTest[HIT_TEST_MAX];	// 当たり判定の情報
}HitTestSet;
//========== *** 管理情報 ***
// 当たり判定管理構造体
typedef struct
{
	int	nHitTest;	// 当たり判定番号
}HitTestInfo;
//========== *** 引渡情報 ***
// 衝突判定に必要な情報構造体
typedef struct
{
	D3DXVECTOR3 *pPos;			// 現在の位置のポインタ
	D3DXVECTOR3 posOld;			// 過去の位置のポインタ
	D3DXVECTOR3 *pMove;			// 移動量のポインタ
	D3DXVECTOR3 *pRot;			// 現在の向きのポインタ
	D3DXVECTOR3 rotOld;			// 過去の向きのポインタ
	Parts3DInfo *pPartsInfo;	// 部品管理情報
	Parts3DSet *pPartsSet;		// 部品設定情報
	HitTest *pHitTest;			// 当たり判定の情報
	COLLCHK_MODE mode;			// 衝突チェックのモード
	float fScale;				// 拡大倍率
}CollisionInfo;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 基本接続 ***
// 物理関連の初期化処理
void InitPhysics(void);
//========== *** 入出力 ***
// 当たり判定設定情報の読み込み処理
void LoadHitTestSet(FILE *pFile, HitTestSet *pHitTestSet);
//========== *** 当たり判定 ***
// 当たり判定登録処理
void HitTestSignUp(CollisionInfo myCollInfo);
// 当たり判定登録解除処理
void HitTestSignOut(void);
// 衝突チェック
void CollisionCheck(VECTOR vector, Collision *pCollision, CollisionInfo myCollInfo, CollisionInfo pairCollInfo, COLLCHK_MODE mode);
// 衝突情報の上書き
void CollisionOverwrite(Collision *pOvwCollision, Collision collision);
//========== *** 当たり判定描画関連 ***
// 当たり判定の描画準備処理
void DrawHitTestSetUp(void);
// 当たり判定の描画処理
void DrawHitTest(void);
// 当たり判定の線の数を初期化
void InitHitTestLineNum(void);
// 当たり判定の表示設定
void ShowHitTest(bool bShow);

#endif