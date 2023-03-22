//========================================
// 
// モーション(3D)関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
//  *** motion3D.h ***
//========================================
#ifndef _MOTION3D_H_	// このマクロ定義がされていなかった時
#define _MOTION3D_H_	// 二重インクルード防止のマクロを定義する

#include "parts3D.h"

//****************************************
// マクロ定義
//****************************************
// モーション(3D)の最大数
#define MOTION3D_MAX (16)
// モーション(3D)のコマンドの最大数
#define MOTION3D_COMMAND_MAX (16)
// モーション(3D)のコマンドの引数の最大数
#define MOTION3D_COMMAND_DATA_MAX (4)

//****************************************
// 列挙型の定義
//****************************************
// モーション(3D)コマンド
typedef enum
{
	MOTION3D_COMMAND_LABEL_MOVE,	// 移動
	MOTION3D_COMMAND_LABEL_SPIN,	// 回転
	MOTION3D_COMMAND_LABEL_MAX,
}MOTION3D_COMMAND_LABEL;

//****************************************
// 構造体の定義
//****************************************
// モーションコマンド情報構造体
typedef struct
{
	unsigned int nTime;	// 時間
	MOTION3D_COMMAND_LABEL command;	// コマンドの種類
	// 引数
	float aData[MOTION3D_COMMAND_DATA_MAX];
}MotionCommand;

// 部品毎のモーション(3D)情報構造体
typedef struct
{
	unsigned int nCommandNum;	// コマンド数
	// コマンド情報
	MotionCommand aCommand[MOTION3D_COMMAND_MAX];
}PartsMotion3D;

// モーション(3D)情報構造体
typedef struct
{
	int nLoopTime;	// ループ時間
	bool bLoop;		// ループするかフラグ
	// 部品毎のモーション情報
	PartsMotion3D aPartsMotion[PARTS_3D_MAX];
}Motion3D;

// モーション(3D)設定情報構造体
typedef struct
{
	int nMotionNum = 1;	// モーション数
	Motion3D aMotion[MOTION3D_MAX];	// モーションの情報
}Motion3DSet;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** モーション(3D)関連 ***
// モーション(3D)設定情報の読み込み処理
void LoadMotion3DSet(FILE *pFile, Motion3DSet *pMotionSet);
// モーション(3D)の更新処理
bool UpdateMotion3D(Motion3DSet motionSet, Parts3DInfo *pPartsInfo, Parts3DSet partsSet);
// モーション(3D)の設定処理
void SetMotion3D(Parts3DInfo *pPartsInfo);

#endif