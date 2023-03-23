//==========================================
//
//�v���C���[�v���O����[player.cpp]
//Author:�Ό��D�n  �i�e�֌W�F���V�����j
//
//==========================================
#include "main.h"
#include "boomerang.h"

//�}�N��
#define MAX_USE_BOOMERANG		(3)		//�u�[�������̎g�p���i�w�b�_�Ɉڂ��Ă������j
#define BOOMERANG_ONE_ROTATE	(15)	//�u�[��������1������̂ɂ�����t���[�����i2PI�Ŋ���j
#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//�p�x��-PI~PI�ɏC��

//�O���[�o��
Boomerang g_aBoomerang[MAX_USE_BOOMERANG] = {};

//========================
//����������
//========================
void InitBoomerang(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾

	//�ϐ�������
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_BOOMERANG; nCntBoomerang++)
	{
		//�ϐ�������
		g_aBoomerang[nCntBoomerang].pos = c_aPosRot[nCntBoomerang][0];
		g_aBoomerang[nCntBoomerang].posOld = g_aBoomerang[nCntBoomerang].pos;
		g_aBoomerang[nCntBoomerang].move = ZERO_SET;
		g_aBoomerang[nCntBoomerang].rot = c_aPosRot[nCntBoomerang][1];
		
		g_aBoomerang[nCntBoomerang].bUse = true;
	}
}

//========================
//�I������
//========================
void UninitBoomerang(void)
{
	
}

//========================
//�X�V����
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
//�`�揈��
//========================
void DrawBoomerang(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();	//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;				//�}�e���A���f�[�^�ւ̃|�C���^

	//���݂̃}�e���A���擾
	pDevice->GetMaterial(&matDef);

	//�v���C���[�̐������J��Ԃ�
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_GAMEPAD; nCntBoomerang++)
	{
		if (g_aBoomerang[nCntBoomerang].bUseBoomerang == true)
		{
			//"�v���C���[��"���[���h�}�g���b�N�X������
			D3DXMatrixIdentity(&g_aBoomerang[nCntBoomerang].mtxWorld);

			//�����𔽉f
			D3DXMatrixRotationYawPitchRoll(&mtxRot, g_aBoomerang[nCntBoomerang].rot.y, g_aBoomerang[nCntBoomerang].rot.x, g_aBoomerang[nCntBoomerang].rot.z);
			D3DXMatrixMultiply(&g_aBoomerang[nCntBoomerang].mtxWorld, &g_aBoomerang[nCntBoomerang].mtxWorld, &mtxRot);

			//�ʒu���f
			D3DXMatrixTranslation(&mtxTrans, g_aBoomerang[nCntBoomerang].pos.x, g_aBoomerang[nCntBoomerang].pos.y, g_aBoomerang[nCntBoomerang].pos.z);
			D3DXMatrixMultiply(&g_aBoomerang[nCntBoomerang].mtxWorld, &g_aBoomerang[nCntBoomerang].mtxWorld, &mtxTrans);

			// ���f���̐ݒ���
			ModelSet modelSet;
			/* ���f���ԍ�	*/modelSet.nModelIdx = ;
			/* �}�g���b�N�X	*/modelSet.mtx = ;
			/* �F			*/modelSet.col = ;
			// ���f���̐ݒ�
			SetModel(modelSet);

			//"�v���C���[��"���[���h�}�g���b�N�X�ݒ�
			pDevice->SetTransform(D3DTS_WORLD, &g_aBoomerang[nCntBoomerang].mtxWorld);

#if 0
			for (int nCntParts = 0; nCntParts < MAX_PARTS; nCntParts++)
			{
				if (useAnimal.aParts[nCntParts].bUse == true)
				{
					D3DXMATRIX mtxRotModel, mtxTransModel;	//�v�Z�p
					D3DXMATRIX mtxParent;					//�e�̃}�g��

					//"���f����"���[���h�}�g���b�N�X������
					D3DXMatrixIdentity(&g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld);

					//�����𔽉f
					D3DXMatrixRotationYawPitchRoll(&mtxRotModel, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].rot.y, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].rot.x, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].rot.z);
					D3DXMatrixMultiply(&g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &mtxRotModel);

					//�ʒu���f
					D3DXMatrixTranslation(&mtxTransModel, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].pos.x, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].pos.y, g_aBoomerang[nCntBoomerang].animalInst[nCntParts].pos.z);
					D3DXMatrixMultiply(&g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &mtxTransModel);

					//�p�[�c�̐e�}�g���ݒ�
					if (useAnimal.aParts[nCntParts].mIdxModelParent != -1)
					{
						mtxParent = g_aBoomerang[nCntBoomerang].animalInst[useAnimal.aParts[nCntParts].mIdxModelParent].mtxWorld;
					}
					else
					{
						mtxParent = g_aBoomerang[nCntBoomerang].mtxWorld;
					}

					//�p�[�c�̃}�g���Ɛe�}�g�����������킹��
					D3DXMatrixMultiply(&g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &mtxParent);

					//"���f����"���[���h�}�g���b�N�X�ݒ�
					pDevice->SetTransform(D3DTS_WORLD, &g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld);

					//�}�e���A���f�[�^�ւ̃|�C���^�擾
					pMat = (D3DXMATERIAL*)useAnimal.aParts[nCntParts].pBuffMat->GetBufferPointer();

					for (int nCntMat = 0; nCntMat < (int)useAnimal.aParts[nCntParts].dwNumMatModel; nCntMat++)
					{
						//�S�[�X�g�p
						D3DMATERIAL9 matChange = pMat[nCntMat].MatD3D;

						//�S�[�X�g��ԂȂ����
						if (g_aBoomerang[nCntBoomerang].nGhostItemTime > 0)
						{
							//�A���t�@�e�X�g��L���ɂ���
							pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);
							pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
							pDevice->SetRenderState(D3DRS_ALPHAREF, 10);
							matChange.Diffuse.a = 0.0f;
						}
						else if (nCntParts == MAX_PARTS - 1)
						{//�[�b�P���̎��͐F�ύX
							matChange.Diffuse = c_aColBoomerang[nCntBoomerang];
						}

						//�}�e���A���ݒ�
						pDevice->SetMaterial(&matChange);

						//�e�N�X�`���ݒ�
						pDevice->SetTexture(0, useAnimal.aParts[nCntParts].apTexture[nCntMat]);

						//���f���`��
						useAnimal.aParts[nCntParts].pMesh->DrawSubset(nCntMat);
					}

					//�A���t�@�e�X�g�𖳌��ɂ���
					pDevice->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
					pDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
					pDevice->SetRenderState(D3DRS_ALPHAREF, 10);

					/*------------------------------------------------------------------
					�e�̕`��		Author:���V���� �Ό��D�n
					--------------------------------------------------------------------*/
					if (g_aBoomerang[nCntBoomerang].pos.y >= 0.0f)
					{
						D3DXMATRIX	mtxShadow;		//�V���h�E�}�g���b�N�X
						D3DLIGHT9	light;			//���C�g���
						D3DXVECTOR4	posLight;		//���C�g�̈ʒu
						D3DXVECTOR3	pos, normal;	//���ʏ�̔C�ӂ̓_�A�@���x�N�g��
						D3DXPLANE	plane;			//���ʏ��

													//���C�g�̈ʒu��ݒ�
						pDevice->GetLight(0, &light);
						posLight = D3DXVECTOR4(-light.Direction.x, -light.Direction.y, -light.Direction.z, 0.0f);

						//���ʏ��𐶐�
						pos = ZERO_SET;
						normal = D3DXVECTOR3(0.0f, 1.0f, 0.0f);
						D3DXPlaneFromPointNormal(&plane, &pos, &normal);

						//�V���h�E�}�g���b�N�X�̏�����
						D3DXMatrixIdentity(&mtxShadow);

						//�V���h�E�}�g���b�N�X�̍쐬
						D3DXMatrixShadow(&mtxShadow, &posLight, &plane);
						D3DXMatrixMultiply(&mtxShadow, &g_aBoomerang[nCntBoomerang].animalInst[nCntParts].mtxWorld, &mtxShadow);

						//�V���h�E�}�g���b�N�X�̐ݒ�
						pDevice->SetTransform(D3DTS_WORLD, &mtxShadow);

						//�}�e���A���f�[�^�ւ̃|�C���^���擾
						pMat = (D3DXMATERIAL *)useAnimal.aParts[nCntParts].pBuffMat->GetBufferPointer();

						for (int nCntMat = 0; nCntMat < (int)useAnimal.aParts[nCntParts].dwNumMatModel; nCntMat++)
						{
							D3DMATERIAL9 MatCopy = pMat[nCntMat].MatD3D;	//�}�e���A���f�[�^����

																			//���F�ɐݒ�						//���Ȕ����𖳂���
							MatCopy.Diffuse = XCOL_BLACKSHADOW;	MatCopy.Emissive = XCOL_BLACK;

							//�}�e���A���ݒ�
							pDevice->SetMaterial(&MatCopy);

							//�e�N�X�`���ݒ�
							pDevice->SetTexture(0, NULL);

							//���f���`��
							useAnimal.aParts[nCntParts].pMesh->DrawSubset(nCntMat);
						}
					}
				}
			}
#endif
		}
	}

	//�}�e���A����߂�
	pDevice->SetMaterial(&matDef);
}