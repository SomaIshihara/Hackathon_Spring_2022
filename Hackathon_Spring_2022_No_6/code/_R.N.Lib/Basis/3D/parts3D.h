//========================================
// 
// 部品(3D)関連のヘッダファイル
// Author:RIKU NISHIMURA
// 
//========================================
//  *** parts3D.h ***
//========================================
#ifndef _PARTS3D_H_	// このマクロ定義がされていなかった時
#define _PARTS3D_H_	// 二重インクルード防止のマクロを定義する

//****************************************
// マクロ定義
//****************************************
// マテリアル(3D)の上限
#define MATERIAL_3D_MAX (16)
// 部品(3D)の最大数
#define PARTS_3D_MAX (16)

//****************************************
// 構造体の定義
//****************************************
// 部品(3D)構造体
typedef struct
{
	// 位置関連
	D3DXVECTOR3 posResult;	// 位置(結果)
	D3DXVECTOR3 pos;		// 位置
	D3DXVECTOR3 rotResult;	// 向き(結果)
	D3DXVECTOR3 rot;		// 向き

	// モーション関連
	bool bPosAnim;			// 位置アニメーションフラグ
	int nCounterPosAnim;	// 位置アニメーションカウンター
	int nPosAnimTime;		// 位置アニメーションにかかる時間
	D3DXVECTOR3 posOld;		// 元の位置
	D3DXVECTOR3 targetPos;	// 目標位置
	bool bRotAnim;			// 角度アニメーションフラグ
	int nCounterRotAnim;	// 角度アニメーションカウンター
	int nRotAnimTime;		// 角度アニメーションにかかる時間
	D3DXVECTOR3 rotOld;		// 元の角度
	D3DXVECTOR3 targetRot;	// 目標角度
}Parts3D;

// 部品(3D)管理構造体
typedef struct
{
	D3DXVECTOR3 pos;	// 位置(本体)
	D3DXVECTOR3 rot;	// 向き(本体)
	bool bStop;			// 停止フラグ
	int nModelSetUp;	// モデルのセットアップ番号
	int nMotion;		// モーション番号
	int nMotionOld;		// モーション番号(過去)
	int nCounterMotion;	// モーションカウンター
	Color col;			// 色
	// 部品情報
	Parts3D aParts[PARTS_3D_MAX];
#if /* 設定フォーマット */0
	// 部品(3D)管理情報
	Parts3DInfo parts3DInfo;
	InitParts3DInfo(&parts3DInfo, );
	/* 位置 */parts3DInfo.pos = ;
	/* 向き */parts3DInfo.rot = ;
	/* 停止 */parts3DInfo.bStop = ;
	/* 色   */parts3DInfo.col = ;
	// 部品(3D)の更新処理
	UpdateParts3DInfo(&parts3DInfo);
#endif
}Parts3DInfo;

// 部品(3D)の種類毎の情報構造体
typedef struct
{
	// 読み込み情報
	int nModelIdx;	// モデルの番号
	int nParent;	// 親番号
	D3DXVECTOR3 fixedRelativePos;	// 固定の相対位置
	D3DXVECTOR3 fixedRelativeRot;	// 固定の相対角度
	D3DXVECTOR3 rotRelativePos;		// 回転軸の相対位置
}Parts3DType;

// 部品設定情報構造体
typedef struct
{
	float fScale;	// 拡大倍率
	int nPartsNum;	// 部品数
	// 部品の種類毎の情報
	Parts3DType aPartsType[PARTS_3D_MAX];
}Parts3DSet;

//****************************************
// プロトタイプ宣言
//****************************************
//========== *** 部品(3D)関連 ***
// 部品設定情報(3D)の読み込み処理
void LoadParts3DSet(FILE *pFile, Parts3DSet *pPartsSet);
// 部品(3D)の初期化処理
void InitParts3DInfo(Parts3DInfo *pPartsInfo, int nModelSetUp);
// 部品(3D)の更新処理
void UpdateParts3DInfo(Parts3DInfo *pPartsInfo);
// 部品(3D)のマトリックスを取得
D3DXMATRIX GetMatrixParts3D(int nParts, D3DXVECTOR3 pos, D3DXVECTOR3 rot, Parts3DInfo *pPartsInfo, Parts3DSet *pPartsSet);

#endif