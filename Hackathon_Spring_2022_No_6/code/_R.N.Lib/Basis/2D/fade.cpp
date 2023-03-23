//========================================
// 
// フェードの処理
// Author:RIKU NISHIMURA
// 
//========================================
// *** fade.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// マクロ定義
//****************************************
// フェードの透明度の推移値
#define FADE_ALPHA_TRANSITIVE_VALUE (5)

//****************************************
// グローバル変数宣言
//****************************************
FADE g_fade;		// フェードの状態
FADE g_fadeTemp;	// フェードの状態を保存
Color g_colorFade;	// ポリゴン(フェード)の色

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 基本接続 *** |--------------------
//============================================================
//========================================
// InitFade関数 - フェードの初期化処理 -
// Author:RIKU NISHIMURA
//========================================
void InitFade(void)
{
	g_fade = FADE_IN;				// フェードイン状態に
	g_colorFade = { 0,0,0,255 };	// 黒いポリゴン(不透明)にする
}

//========================================
// UpdateFade関数 - フェードの更新処理 -
// Author:RIKU NISHIMURA
//========================================
void UpdateFade(void)
{
	// フェードの状態を保存
	g_fadeTemp = g_fade;

	if (g_fade != FADE_NONE)
	{
		if (g_fade == FADE_IN)
		{// フェードイン状態
			// ポリゴンを透明にしていく
			g_colorFade.a -= FADE_ALPHA_TRANSITIVE_VALUE;

			// BGMとSEの音量を変更する
			SoundTypeVolumeChange(SOUND_TYPE_BGM, 1.0f - ((float)g_colorFade.a / (float)255));
			SoundTypeVolumeChange(SOUND_TYPE_SE, 1.0f - ((float)g_colorFade.a / (float)255));

			if (g_colorFade.a <= 0) 
			{// 透明度が0以下の時、
				g_colorFade.a = 0;	// 透明度を0に設定
				g_fade = FADE_NONE;	// フェード無し状態にする
			}
		}
		else if (g_fade == FADE_OUT) 
		{// フェードアウト状態
			// ポリゴンを不透明にしていく
			g_colorFade.a += FADE_ALPHA_TRANSITIVE_VALUE;

			// BGMとSEの音量を変更する
			SoundTypeVolumeChange(SOUND_TYPE_BGM, 1.0f - ((float)g_colorFade.a / (float)255));
			SoundTypeVolumeChange(SOUND_TYPE_SE, 1.0f - ((float)g_colorFade.a / (float)255));

			if (g_colorFade.a > 255) 
			{// 透明度が最大値を上回った時、
				g_colorFade.a = 255;	// 透明度を最大値に設定
				g_fade = FADE_IN;		// フェードイン状態にする

				// BGMとSEを一括で停止
				StopSoundType(SOUND_TYPE_BGM);
				StopSoundType(SOUND_TYPE_SE);
			}
		}
	}

	// ウィンドウの情報
	WindowMemory windowInfo = *GetWindowMemory();

	// ポリゴン(2D)の設定情報
	Polygon2DSet polySet;
	/* テクスチャ番号	*/polySet.nTex = -1;
	/* パターン番号		*/polySet.nPtn = 0;
	/* パターン上限X	*/polySet.nPtnX = 1;
	/* パターン上限Y	*/polySet.nPtnY = 1;
	/* 幅				*/polySet.fWidth = windowInfo.fWindowWidth;
	/* 高さ				*/polySet.fHeight = windowInfo.fWindowHeight;
	/* 位置				*/polySet.pos = D3DXVECTOR3(windowInfo.fWindowWidth * 0.5f, windowInfo.fWindowHeight * 0.5f, 0.0f);
	/* 向き				*/polySet.rot = INITD3DXVECTOR3;
	/* 色				*/polySet.col = g_colorFade;
	/* カメラ合わせ		*/polySet.bMatchCamera = false;
	// ポリゴン(2D)を設定
	SetPolygon2D(polySet);
}

//============================================================
//--------------------| *** 取得 *** |------------------------
//============================================================
//========================================
// GetFade関数 - フェードの設定処理 -
// Author:RIKU NISHIMURA
//========================================
FADE GetFade(void)
{
	return g_fade;
}

//========================================
// GetFadeSwap関数 - フェードの切り替え取得 -
// Author:RIKU NISHIMURA
//========================================
bool GetFadeSwap(void)
{
	return (g_fadeTemp == FADE_OUT) && (g_fade == FADE_IN);
}

//========================================
// GetFadeInEnd関数 - フェードイン終了取得 -
// Author:RIKU NISHIMURA
//========================================
bool GetFadeInEnd(void)
{
	return (g_fadeTemp == FADE_IN) && (g_fade == FADE_NONE);
}

//========================================
// SetFade関数 - フェードの設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetFade(void)
{
	g_fade		= FADE_OUT;			// フェードアウト状態に
	g_colorFade = { 0, 0, 0, 0 };	// 黒いポリゴン(透明)にする
}