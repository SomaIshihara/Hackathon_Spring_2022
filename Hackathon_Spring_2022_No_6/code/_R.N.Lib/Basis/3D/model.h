//========================================
// 
// モデル関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
//  *** model.h ***
//========================================
#ifndef _MODEL_H_	// このマクロ定義がされていなかった時
#define _MODEL_H_	// 二重インクルード防止のマクロを定義する

//****************************************
// マクロ定義
//****************************************
// モデルの種類の最大数
#define MODELTYPE_MAX (1024)
// モデルの最大数
#define MODEL_MAX (1024)

//****************************************
// 構造体の定義
//****************************************
// モデルの読み込み情報構造体
typedef struct
{
	char *pModelPath;	// モデルのパス
}ModelLoad;

// モデルの設定情報構造体
typedef struct
{
	int nModelIdx = -1;	// 種類番号
	D3DXMATRIX mtx;		// マトリックス
	Color col;			// 色
#if /* 設定フォーマット */0
	// モデルの設定情報
	ModelSet modelSet;
	/* モデル番号	*/modelSet.nModelIdx = ;
	/* マトリックス	*/modelSet.mtx = ;
	/* 色			*/modelSet.col = ;
	// モデルの設定
	SetModel(modelSet);
#endif
}ModelSet;

// モデルの管理情報
typedef struct
{
	//========== *** 読み込み関連 ***
	// 読み込み済のモデルパス
	char aLoadModelPath[MODELTYPE_MAX][TXT_MAX] = {};
	unsigned int nModelTypeNum = 0;	// モデルの種類数

	//========== *** 設定関連 ***
	unsigned int nModelSetNum = 0;		// モデルの設定数
	ModelSet aModelSet[MODEL_MAX] = {};	// モデルの設定情報
}ModelInfo;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 基本接続 ***
// モデルの初期化処理
void InitModel(void);
// モデルの終了処理
void UninitModel(void);
// モデルの描画処理
void DrawModel(void);
// モデルの描画処理(単体)
void DrawSingleModel(LPDIRECT3DDEVICE9 pDevice, int nIdx);
//========== *** 入出力 ***
// モデルの読み込み処理
int LoadModel(ModelLoad modelLoad);
//========== *** 設定 ***
// モデルの設定処理
void SetModel(ModelSet modelSet);
//========== *** 取得 ***
// モデルの管理情報取得
ModelInfo *GetModelInfo(void);

#endif