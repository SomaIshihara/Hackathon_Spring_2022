//==========================================
//
//プレイヤープログラム[player.cpp]
//Author:石原颯馬  （影関係：平澤詩苑）
//
//==========================================
#include "main.h"
#include "boomerang.h"

//マクロ
#define MAX_USE_BOOMERANG		(3)		//ブーメランの使用数（ヘッダに移してもいい）
#define BOOMERANG_ONE_ROTATE	(15)	//ブーメランが1周するのにかかるフレーム数（2PIで割る）
#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//角度を-PI~PIに修正

//グローバル
Boomerang g_aBoomerang[MAX_USE_BOOMERANG] = {};

//========================
//初期化処理
//========================
void InitBoomerang(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得

	//変数初期化
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_BOOMERANG; nCntBoomerang++)
	{
		//変数初期化
		g_aBoomerang[nCntBoomerang].pos = c_aPosRot[nCntBoomerang][0];
		g_aBoomerang[nCntBoomerang].posOld = g_aBoomerang[nCntBoomerang].pos;
		g_aBoomerang[nCntBoomerang].move = ZERO_SET;
		g_aBoomerang[nCntBoomerang].rot = c_aPosRot[nCntBoomerang][1];
		
		g_aBoomerang[nCntBoomerang].bUse = true;
	}
}

//========================
//終了処理
//========================
void UninitBoomerang(void)
{
	
}

//========================
//更新処理
//========================
void UpdateBoomerang(void)
{
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_BOOMERANG; nCntBoomerang++)
	{
		if (g_aBoomerang[nCntBoomerang].bUse == true)
		{
			g_aBoomerang[nCntBoomerang].rot.y = FIX_ROT(g_aBoomerang[nCntBoomerang].rot.y + ((2 * D3DX_PI) / BOOMERANG_ONE_ROTATE));
		}
	}
}

//========================
//描画処理
//========================
void DrawBoomerang(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用
	D3DMATERIAL9 matDef;			//現在のマテリアル保存用
	D3DXMATERIAL *pMat;				//マテリアルデータへのポインタ

	//現在のマテリアル取得
	pDevice->GetMaterial(&matDef);

	//プレイヤーの数だけ繰り返す
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_GAMEPAD; nCntBoomerang++)
	{
		if (g_aBoomerang[nCntBoomerang].bUseBoomerang == true)
		{
			//"プレイヤーの"ワールドマトリックス初期化
			D3DXMatrixIdentity(&g_aBoomerang[nCntBoomerang].mtxWorld);

			//向きを反映
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBoomerang[nCntBoomerang].rot.y, g_aBoomerang[nCntBoomerang].rot.x, g_aBoomerang[nCntBoomerang].rot.z);
			D3DXMatrixMultiply(&g_aBoomerang[nCntBoomerang].mtxWorld, &g_aBoomerang[nCntBoomerang].mtxWorld, &mtxRot);

			//位置反映
			D3DXMatrixTranslation(&mtxTrans, g_aBoomerang[nCntBoomerang].pos.x, g_aBoomerang[nCntBoomerang].pos.y, g_aBoomerang[nCntBoomerang].pos.z);
			D3DXMatrixMultiply(&g_aBoomerang[nCntBoomerang].mtxWorld, &g_aBoomerang[nCntBoomerang].mtxWorld, &mtxTrans);

			// モデルの設定情報
			ModelSet modelSet;
			/* モデル番号	*/modelSet.nModelIdx = ;
			/* マトリックス	*/modelSet.mtx = ;
			/* 色			*/modelSet.col = ;
			// モデルの設定
			SetModel(modelSet);

			//"プレイヤーの"ワールドマトリックス設定
			pDevice->SetTransform(D3DTS_WORLD, &g_aBoomerang[nCntBoomerang].mtxWorld);

#if 0
			for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
			{
				if (useAnimal.aParts[nCntParts].bUse == true)
				{
					D3DXMATRIX mtxRotModel, mtxTransModel;	//計算用
					D3DXMATRIX mtxParent;					//親のマトリ

					//"モデルの"ワールドマトリックス初期化
					D3DXMatrixIdentity(&g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld);

					//向きを反映
					D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].rot.y, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].rot.x, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].rot.z);
					D3DXMatrixMultiply(&g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &mtxRotModel);

					//位置反映
					D3DXMatrixTranslation(&mtxTransModel, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].pos.x, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].pos.y, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].pos.z);
					D3DXMatrixMultiply(&g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &mtxTransModel);

					//パーツの親マトリ設定
					if (useAnimal.aParts[nCntParts].mIdxModelParent != -1)
					{
						mtxParent = g_aBoomerang[nCntBoomerang].animalInst[useAnimal.aParts[nCntParts].mIdxModelParent].mtxWorld;
					}
					else
					{
						mtxParent = g_aBoomerang[nCntBoomerang].mtxWorld;
					}

					//パーツのマトリと親マトリをかけ合わせる
					D3DXMatrixMultiply(&g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &mtxParent);

					//"モデルの"ワールドマトリックス設定
					pDevice->SetTransform(D3DTS_WORLD, &g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld);

					//マテリアルデータへのポインタ取得
					pMat = (D3DXMATERIAL*)useAnimal.aParts[nCntParts].pBuffMat->GetBufferPointer();

					for (int nCntMat = 0; nCntMat < (int)useAnimal.aParts[nCntParts].dwNumMatModel; nCntMat++)
					{
						//ゴースト用
						D3DMATERIAL9 matChange = pMat[nCntMat].MatD3D;

						//ゴースト状態なら消す
						if (g_aBoomerang[nCntBoomerang].nGhostItemTime > 0)
						{
							//アルファテストを有効にする
							pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
							pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
							pDevice->SetRenderState(D3DRS_ALPHAREF, 10);
							matChange.Diffuse.a = 0.0f;
						}
						else if (nCntParts == MAX_PARTS - 1)
						{//ゼッケンの時は色変更
							matChange.Diffuse = c_aColBoomerang[nCntBoomerang];
						}

						//マテリアル設定
						pDevice->SetMaterial(&matChange);

						//テクスチャ設定
						pDevice->SetTexture(0, useAnimal.aParts[nCntParts].apTexture[nCntMat]);

						//モデル描画
						useAnimal.aParts[nCntParts].pMesh->DrawSubset(nCntMat);
					}

					//アルファテストを無効にする
					pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
					pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
					pDevice->SetRenderState(D3DRS_ALPHAREF, 10);

					/*------------------------------------------------------------------
					影の描画		Author:平澤詩苑 石原颯馬
					--------------------------------------------------------------------*/
					if (g_aBoomerang[nCntBoomerang].pos.y >= 0.0f)
					{
						D3DXMATRIX	mtxShadow;		//シャドウマトリックス
						D3DLIGHT9	light;			//ライト情報
						D3DXVECTOR4	posLight;		//ライトの位置
						D3DXVECTOR3	pos, normal;	//平面上の任意の点、法線ベクトル
						D3DXPLANE	plane;			//平面情報

													//ライトの位置を設定
						pDevice->GetLight(0, &light);
						posLight = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);

						//平面情報を生成
						pos = ZERO_SET;
						normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
						D3DXPlaneFromPointNormal(&plane, &pos, &normal);

						//シャドウマトリックスの初期化
						D3DXMatrixIdentity(&mtxShadow);

						//シャドウマトリックスの作成
						D3DXMatrixShadow(&mtxShadow, &posLight, &plane);
						D3DXMatrixMultiply(&mtxShadow, &g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &mtxShadow);

						//シャドウマトリックスの設定
						pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

						//マテリアルデータへのポインタを取得
						pMat = (D3DXMATERIAL *)useAnimal.aParts[nCntParts].pBuffMat->GetBufferPointer();

						for (int nCntMat = 0; nCntMat < (int)useAnimal.aParts[nCntParts].dwNumMatModel; nCntMat++)
						{
							D3DMATERIAL9 MatCopy = pMat[nCntMat].MatD3D;	//マテリアルデータ複製

																			//黒色に設定						//自己発光を無くす
							MatCopy.Diffuse = XCOL_BLACKSHADOW;	MatCopy.Emissive = XCOL_BLACK;

							//マテリアル設定
							pDevice->SetMaterial(&MatCopy);

							//テクスチャ設定
							pDevice->SetTexture(0, NULL);

							//モデル描画
							useAnimal.aParts[nCntParts].pMesh->DrawSubset(nCntMat);
						}
					}
				}
			}
#endif
		}
	}

	//マテリアルを戻す
	pDevice->SetMaterial(&matDef);
}