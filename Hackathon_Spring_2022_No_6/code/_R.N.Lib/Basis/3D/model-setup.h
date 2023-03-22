//========================================
// 
// モデルのセットアップ関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
//  *** model-setup.h ***
//========================================
#ifndef _MODELSETUP_H_	// このマクロ定義がされていなかった時
#define _MODELSETUP_H_	// 二重インクルード防止のマクロを定義する

#include "model.h"
#include "motion3D.h"
#include "../Other/physics.h"

//****************************************
// マクロ定義
//****************************************

//****************************************
// 構造体の定義
//****************************************
// モデルのセットアップの読み込み情報構造体
typedef struct
{
	char *pModelSetUpPath;	// モデルのセットアップのパス
	bool bReload = false;	// 再読み込みフラグ
#if /* 設定フォーマット   */0
	// モデルのセットアップの読み込み情報
	ModelSetUpLoad modelSetUpLoad;
	/* セットアップのパス */modelSetUpLoad.pModelSetUpPath = ;
	/* 再読み込みフラグ   */modelSetUpLoad.bReload = ;
	// モデルのセットアップを読み込み
	 = LoadModelSetUp(modelSetUpLoad);
#endif
}ModelSetUpLoad;

// モデルのセットアップ情報構造体
typedef struct 
{
	Parts3DSet partsSet;	// 部品設定情報(3D)
	HitTestSet hitTestSet;	// 当たり判定設定情報
	Motion3DSet motionSet;	// モーション設定情報
}ModelSetUp;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 入出力 ***
// モデルのセットアップの読み込み処理
int LoadModelSetUp(ModelSetUpLoad modelSetUpLoad);
// モデルのセットアップリストの読み込み処理
void LoadModelSetUpList(void);
//========== *** 取得 ***
// モデルのセットアップ情報を取得
ModelSetUp GetModelSetUp(int nSetUp);

#endif