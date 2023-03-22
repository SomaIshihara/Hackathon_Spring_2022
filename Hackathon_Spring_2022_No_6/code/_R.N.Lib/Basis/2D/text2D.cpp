//========================================
// 
// テキスト(2D)の処理
// Author:RIKU NISHIMURA
// 
//========================================
//  *** text2D.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| hファイルの共有関数
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** 設定 *** |------------------------
//============================================================
//========================================
// SetText2D関数 - テキスト(2D)の設定処理 -
// Author:RIKU NISHIMURA
//========================================
void SetText2D(Text2DSet text2DSet)
{
	// 文字列のポインタ
	char *pString = text2DSet.pString;

	for (int nCntDigit = 0; nCntDigit < strlen(pString); nCntDigit++)
	{
		if (pString[nCntDigit] == ' ') 
		{// カウントの文字が空白の時、
			continue;	// 折り返す
		}

		// 設定位置
		D3DXVECTOR3 setPos = INITD3DXVECTOR3;
		// フォントの情報
		Font font = GetFont(text2DSet.nFont);
		// 間隔比率
		float fSpaceRate = (float)font.nSpaceNum / (float)font.nSpaceDenom;
		float fWidth = text2DSet.fWidth;	// 幅
		float fHeight = text2DSet.fHeight;	// 高さ

		// 表示形式に応じた設定位置の設定
		switch (text2DSet.disp)
		{
		case TEXT_DISP_CENTER:
			// 設定位置に文字の最終的な長さの半分を減算
			setPos.x -= ((fWidth * fSpaceRate) * strlen(pString)) * 0.5f;
			// 設定位置に配置間隔Xを適用(加算)
			setPos.x += ((float)nCntDigit + 0.5f) * (fWidth * fSpaceRate);
			break;
		case TEXT_DISP_LEFT:
			// 設定位置に配置間隔Xを適用(加算)
			setPos.x += nCntDigit * (fWidth * fSpaceRate);
			break;
		case TEXT_DISP_RIGHT:
			// 設定位置に文字の最終的な長さを減算
			setPos.x -= (fWidth * fSpaceRate) * (strlen(pString) - 1);
			// 設定位置に配置間隔Xを適用(加算)
			setPos.x += nCntDigit * (fWidth * fSpaceRate);
			break;
		}

		// 位置と向きをマトリックス変換
		D3DXMATRIX baseMtx = ConvPosRotToMatrix(text2DSet.pos, text2DSet.rot);
		D3DXMATRIX txtMtx = ConvPosRotToMatrix(setPos, INITD3DXVECTOR3);

		// 基準マトリックスとテキストマトリックスを掛け合わせる
		D3DXMATRIX resultMtx = MultiplyMatrix(baseMtx, txtMtx);

		// ポリゴン(2D)の設定情報
		Polygon2DSet polySet;
		/* テクスチャ番号	*/polySet.nTex = font.nTex;
		/* パターン番号		*/polySet.nPtn = (int)pString[nCntDigit] - (int)font.cStartChar;
		/* パターン上限X	*/polySet.nPtnX = font.nPtnWidth;
		/* パターン上限Y	*/polySet.nPtnY = font.nPtnHeight;
		/* 幅				*/polySet.fWidth = fWidth;
		/* 高さ				*/polySet.fHeight = fHeight;
		/* 位置				*/polySet.pos = ConvMatrixToPos(resultMtx);
		/* 向き				*/polySet.rot = ConvMatrixToPos(resultMtx) + D3DXVECTOR3(0.0f,0.0f,D3DX_PI);
		/* 色				*/polySet.col = text2DSet.col;
		/* カメラ合わせ		*/polySet.bMatchCamera = text2DSet.bMatchCamera;
		// ポリゴン(2D)を設定
		SetPolygon2D(polySet);
	}
}