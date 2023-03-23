//==========================================
//
//�u�[�������v���O����[player.cpp]
//Author:�Ό��D�n  �i�e�֌W�F���V�����j
//
//==========================================
#include "main.h"
#include "_R.N.Lib\R.N.Lib.h"
#include "boomerang.h"
#include "target.h"
#include "chr_player.h"
#include "_R.N.Lib\Basis\Other\sound.h"

//�}�N��
#define BOOMERANG_SETUP_NUM			(2)					//�u�[�������Z�b�g�A�b�v�ԍ�
#define BOOMERANG_ONE_ROTATE		(15)				//�u�[���������̂�1������̂ɂ�����t���[�����i2PI�Ŋ���j
#define BOOMERANG_THROW_ROT			(0.10f * D3DX_PI)	//������p�x
#define BOOMERANG_ROTTOTAL_MAX		(1.15f * D3DX_PI)	//��]�����ʂ̍��v�̍ő�l
#define BOOMERANG_MOVE_SPEED		(4.5f)				//�u�[�������̈ړ����x
#define BOOMERANG_ADDROTFORCE		(0.001f)			//��]�͑����E������
#define BOOMERANG_ROTFORCE_MAX		(0.1f)				//�ő�
#define BOOMERANG_STRAIGHT_END		(30)				//�����ړ��I������
#define BOOMERANG_DESTROY_LINE		(300.0f)			//�u�[���������ǂ������ł����i�����j���C��

#define FIX_ROT(x)				(fmodf(x + (D3DX_PI * 3), D3DX_PI * 2) - D3DX_PI)	//�p�x��-PI~PI�ɏC��

//�v���g
void CollisionBoomerangEnemy(int nBoomerangNum);
void CollisionBoomerangPlayer(int nBoomerangNum);

//�O���[�o��
Boomerang g_aBoomerang[MAX_USE_BOOMERANG] = {};

//========================
//����������
//========================
void InitBoomerang(void)
{
	//�ϐ�������
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_BOOMERANG; nCntBoomerang++)
	{
		//�ϐ�������
		g_aBoomerang[nCntBoomerang].posOld = g_aBoomerang[nCntBoomerang].pos = INITD3DXVECTOR3;
		g_aBoomerang[nCntBoomerang].move = INITD3DXVECTOR3;
		g_aBoomerang[nCntBoomerang].rot = INITD3DXVECTOR3;
		g_aBoomerang[nCntBoomerang].fRotForce = 0.0f;
		g_aBoomerang[nCntBoomerang].bEndRotate = false;

		// ���i(3D)�̏���������
		InitParts3DInfo(&g_aBoomerang[nCntBoomerang].partsInfo, BOOMERANG_SETUP_NUM);

		//�g�p�L��������
		g_aBoomerang[nCntBoomerang].bUse = false;
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
			//[����]��]����
			g_aBoomerang[nCntBoomerang].nCounterStraight++;

			if (g_aBoomerang[nCntBoomerang].nCounterStraight > BOOMERANG_STRAIGHT_END)
			{
				if (g_aBoomerang[nCntBoomerang].throwType == THROWTYPE_LEFT)
				{
					g_aBoomerang[nCntBoomerang].fRotForce += BOOMERANG_ADDROTFORCE;

					//�ő�l���߂����猸�炷
					if (g_aBoomerang[nCntBoomerang].fRotForce > BOOMERANG_ROTFORCE_MAX)
					{
						g_aBoomerang[nCntBoomerang].bReturn = true;
					}

					if (!g_aBoomerang[nCntBoomerang].bEndRotate)
					{
						g_aBoomerang[nCntBoomerang].rot.y += g_aBoomerang[nCntBoomerang].fRotForce;
						g_aBoomerang[nCntBoomerang].fRotTotal += g_aBoomerang[nCntBoomerang].fRotForce;
						if (g_aBoomerang[nCntBoomerang].fRotTotal >= BOOMERANG_ROTTOTAL_MAX)
						{
							g_aBoomerang[nCntBoomerang].bEndRotate = true;
						}
					}
				}
				else
				{
					g_aBoomerang[nCntBoomerang].fRotForce += BOOMERANG_ADDROTFORCE;

					//�ő�l���߂����猸�炷
					if (g_aBoomerang[nCntBoomerang].fRotForce > BOOMERANG_ROTFORCE_MAX)
					{
						g_aBoomerang[nCntBoomerang].bReturn = true;
					}

					if (!g_aBoomerang[nCntBoomerang].bEndRotate)
					{
						g_aBoomerang[nCntBoomerang].rot.y -= g_aBoomerang[nCntBoomerang].fRotForce;
						g_aBoomerang[nCntBoomerang].fRotTotal += g_aBoomerang[nCntBoomerang].fRotForce;
						if (g_aBoomerang[nCntBoomerang].fRotTotal >= BOOMERANG_ROTTOTAL_MAX)
						{
							g_aBoomerang[nCntBoomerang].bEndRotate = true;
						}
					}
				}
				g_aBoomerang[nCntBoomerang].rot.y = FIX_ROT(g_aBoomerang[nCntBoomerang].rot.y);
			}

			//[����]�ړ�����
			g_aBoomerang[nCntBoomerang].move.x = -sinf(g_aBoomerang[nCntBoomerang].rot.y) * BOOMERANG_MOVE_SPEED;
			g_aBoomerang[nCntBoomerang].move.y = 0.0f;
			g_aBoomerang[nCntBoomerang].move.z = cosf(g_aBoomerang[nCntBoomerang].rot.y) * BOOMERANG_MOVE_SPEED;

			g_aBoomerang[nCntBoomerang].pos += g_aBoomerang[nCntBoomerang].move;

			//[����]�����蔻��
			CollisionBoomerangEnemy(nCntBoomerang);
			
			//�A���Ă��Ă��鎞��������������s��
			if (g_aBoomerang[nCntBoomerang].bReturn)
			{
				CollisionBoomerangPlayer(nCntBoomerang);
			}

			//[������]�u�[�������̉�]����
			g_aBoomerang[nCntBoomerang].partsInfo.pos = g_aBoomerang[nCntBoomerang].pos;
			g_aBoomerang[nCntBoomerang].partsInfo.rot.y = FIX_ROT(g_aBoomerang[nCntBoomerang].partsInfo.rot.y + ((2 * D3DX_PI) / BOOMERANG_ONE_ROTATE));

			//��ʊO�ɏo�������
			if (fabs(g_aBoomerang[nCntBoomerang].pos.x) > BOOMERANG_DESTROY_LINE || g_aBoomerang[nCntBoomerang].pos.z < -BOOMERANG_DESTROY_LINE)
			{
				g_aBoomerang[nCntBoomerang].bUse = false;
			}
			else
			{
				// ���i(3D)�̍X�V����
				UpdateParts3DInfo(&g_aBoomerang[nCntBoomerang].partsInfo);
			}
		}
	}
}

//========================
//�`�揈��
//========================
void DrawBoomerang(void)
{
	
}

//========================
//�u�[�������z�u����
//========================
void SetBoomerang(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	for (int nCntBoomerang = 0; nCntBoomerang < MAX_USE_BOOMERANG; nCntBoomerang++)
	{
		//�g�p����Ă��Ȃ����m�F
		if (g_aBoomerang[nCntBoomerang].bUse == false)
		{
			//�ϐ�������
			g_aBoomerang[nCntBoomerang].posOld = g_aBoomerang[nCntBoomerang].pos = pos;
			g_aBoomerang[nCntBoomerang].rot = rot;
			g_aBoomerang[nCntBoomerang].rot.y *= -1;
			g_aBoomerang[nCntBoomerang].rot.y -= BOOMERANG_THROW_ROT;
			g_aBoomerang[nCntBoomerang].move = INITD3DXVECTOR3;
			g_aBoomerang[nCntBoomerang].nCounterStraight = 0;
			g_aBoomerang[nCntBoomerang].fRotForce = 0.0f;
			g_aBoomerang[nCntBoomerang].fRotTotal = 0.0f;
			g_aBoomerang[nCntBoomerang].bEndRotate = false;
			g_aBoomerang[nCntBoomerang].bReturn = false;
			
			//�p�x�ɉ����ē��������ݒ�
			if (rot.y >= 0.0f)
			{
				g_aBoomerang[nCntBoomerang].throwType = THROWTYPE_LEFT;
			}
			else
			{
				g_aBoomerang[nCntBoomerang].throwType = THROWTYPE_RIGHT;
			}

			// ���i(3D)�̏���������
			InitParts3DInfo(&g_aBoomerang[nCntBoomerang].partsInfo, BOOMERANG_SETUP_NUM);

			//�g�p���Ă����Ԃɂ���
			g_aBoomerang[nCntBoomerang].bUse = true;

			//�z�u�I��
			break;
		}
	}
}

//========================
//�u�[���������擾����
//========================
Boomerang *GetBoomerang(void)
{
	return &g_aBoomerang[0];
}

//========================
//�u�[�������ƓG�̓����蔻��
//========================
void CollisionBoomerangEnemy(int nBoomerangNum)
{
	Target* pTarget = GetTarget();

	for (int nCntTarget = 0; nCntTarget < MAX_TARGET; nCntTarget++,pTarget++)
	{
		if (pTarget->bUse == true)
		{
			float fDistance = FindDistanceLookDown(pTarget->pos, g_aBoomerang[nBoomerangNum].pos);

			if (fDistance < BOOMERANG_HIT_RADIUS + GetTargetType()->fWidth * 0.5f)
			{//��������
				if (pTarget->type == TARGET_D)
				{
					g_aBoomerang[nCntTarget].bUse = false;
				}
				else
				{
					//�X�R�A����
					GetChr_player()->nScore += GetTargetType()->nScore;

					//�o���X
					pTarget->bUse = false;

					//�q�b�g�T�E���h�Đ�
					PlaySound(5);
				}
			}
		}
	}
}

//========================
//�u�[�������ƃv���C���[�̓����蔻��
//========================
void CollisionBoomerangPlayer(int nBoomerangNum)
{
	Chr_player *pPlayer = GetChr_player();

	float fDistance = FindDistanceLookDown(pPlayer->partsInfo.pos, g_aBoomerang[nBoomerangNum].pos);

	if (fDistance < BOOMERANG_HIT_RADIUS + PLAYER_HIT_RADIUS)
	{//��������
		//�u�[���������₷
		GetChr_player()->nBoomerang++;

		//�u�[�������L���b�`
		g_aBoomerang[nBoomerangNum].bUse = false;

		//�L���b�`�T�E���h�Đ�
		PlaySound(6);
	}
}
