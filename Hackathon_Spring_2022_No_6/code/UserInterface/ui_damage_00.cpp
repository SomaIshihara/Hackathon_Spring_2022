//========================================
// 
// UI:�_���[�W[00] �̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** ui_damage_00.cpp ***
//========================================
#include "main.h"
#include "camera.h"
#include "chunk.h"
#include "physics.h"
#include "polygon3D.h"
#include "sound.h"
#include "text.h"
#include "ui_damage_00.h"	// UI:�_���[�W	[00]
#include <stdio.h>

//****************************************
// �}�N����`
//****************************************
// UI:�_���[�W[00] �̍ő吔
#define UI_DAMAGE_00_MAX	(256)

// UI:�_���[�W[00] �̖@���x�N�g��
// UI:�_���[�W[00] �̑��Έʒu
#define UI_DAMAGE_00_NOR			(D3DXVECTOR3(0.0f, 1.0f, 0.0f))
#define UI_DAMAGE_00_RELATIVE_POS	(D3DXVECTOR3(0.0f, 0.0f, 0.0f))

// UI:�_���[�W[00] �̎���
#define UI_DAMAGE_00_LIFE	(30)

// UI:�_���[�W[00] �̈ړ���
// UI:�_���[�W[00] �̈ʒu�̂Ԃꕝ
#define UI_DAMAGE_00_MOVE_FORCE		D3DXVECTOR3(0.0f,0.5f,0.0f)
#define UI_DAMAGE_00_POS_AMPLITUDE	(5.0f)

//****************************************
// �\���̂̒�`
//****************************************
// UI:�_���[�W[00] �̏��\����
typedef struct
{
	// �ʒu�֘A
	D3DXVECTOR3 pos;	// �ʒu
	
	// ���ފ֘A
	UI_DAMAGE_00_COLOR_TYPE colType;	// �F�̎��

	// ��Ԋ֘A
	int		nDamage;	// �_���[�W
	bool	bUse;		// �g�p����Ă��邩�t���O
	int		nLife;		// ����
}Ui_damage_00;

//****************************************
// �v���g�^�C�v�錾
//****************************************
// UI:�_���[�W[00] �̃p�����[�^�[�̏���������
void InitParameterUi_damage_00(Ui_damage_00 *pUi);

//****************************************
// �O���[�o���錾
//****************************************
Ui_damage_00	g_aUi_damage_00	// UI:�_���[�W[00] �̏��
				[UI_DAMAGE_00_MAX];

// UI:�_���[�W[00] �̐F
const Color g_aUi_damage_00Color[UI_DAMAGE_00_COLOR_TYPE_MAX] =
{
	{219,43,0,255},
	{255,255,255,255},
};

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitParameterUi_damage_00�֐� - UI:�_���[�W[00] �̃p�����[�^�[�̏��������� -
//========================================
void InitParameterUi_damage_00(Ui_damage_00 *pUi)
{
	pUi->pos		= D3DXVECTOR3(0.0f, 0.0f, 0.0f);	// �ʒu
	pUi->colType	= (UI_DAMAGE_00_COLOR_TYPE)0;		// �F�̎��
	pUi->nDamage	= 0;								// �_���[�W
	pUi->bUse		= false;							// �g�p����Ă��邩�t���O
	pUi->nLife		= 0;								// ����
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// InitUi_damage_00�֐� - UI:�_���[�W[00] �̏��������� -
//========================================
void InitUi_damage_00(void)
{
	Ui_damage_00	*pUi	// UI:�_���[�W[00] �̏��̃|�C���^
					= g_aUi_damage_00;

	for (int nCntEff = 0; nCntEff < UI_DAMAGE_00_MAX; nCntEff++, pUi++)
	{
		// �p�����[�^�[�̏���������
		InitParameterUi_damage_00(&g_aUi_damage_00[nCntEff]);
	}
}

//========================================
// UninitUi_damage_00�֐� - UI:�_���[�W[00] �̏I������ -
//========================================
void UninitUi_damage_00(void)
{
	
}

//========================================
// UpdateUi_damage_00�֐� - UI:�_���[�W[00] �̍X�V���� -
//========================================
void UpdateUi_damage_00(void)
{
	Ui_damage_00	*pUi	// UI:�_���[�W[00] �̏��̃|�C���^
					= g_aUi_damage_00;
	
	for (int nCntEff = 0; nCntEff < UI_DAMAGE_00_MAX; nCntEff++, pUi++)
	{
		if (!pUi->bUse)
		{// �g�p����Ă����ԂłȂ����A
			// �J��Ԃ�������܂�Ԃ�
			continue;
		}
		else if (--pUi->nLife <= 0) 
		{// ���������Z��������0�ȉ��̎��A
			pUi->bUse = false;	// �g�p����Ă��Ȃ���Ԃɂ���
			continue;			// �J��Ԃ�������܂�Ԃ�
		}

		// �ʒu���X�V
 		pUi->pos += (UI_DAMAGE_00_MOVE_FORCE * ((float)pUi->nLife / (float)UI_DAMAGE_00_LIFE));

		// �e�L�X�g�̐ݒ菈��
		{
			char aString[TXT_MAX];
			sprintf(aString, "%d", pUi->nDamage);
			SetText3D(
				aString,
				FONT_002,
				DISPLAY_CENTER,
				pUi->pos,
				g_aUi_damage_00Color[pUi->colType],
				1.0f, 1.0f, false, false, true);
		}
	}
}

//========================================
// SetUi_damage_00�֐� - UI:�_���[�W[00] �̐ݒ菈�� -
//========================================
void SetUi_damage_00(D3DXVECTOR3 pos, int nDamage, UI_DAMAGE_00_COLOR_TYPE colType)
{
	Ui_damage_00	*pUi	// UI:�_���[�W[00] �̏��̃|�C���^
					= g_aUi_damage_00;

	for (int nCntEff = 0; nCntEff < UI_DAMAGE_00_MAX; nCntEff++, pUi++)
	{
		if (pUi->bUse)
		{// �g�p����Ă����Ԃ̎��A
			// ������܂�Ԃ�
			continue;
		}

		pUi->pos = pos;			// �ʒu����
		pUi->nDamage = nDamage;	// �_���[�W����
		pUi->colType = colType;	// �F�̎�ނ���
		pUi->bUse = true;		// �g�p����Ă����Ԃɂ���

		// �ʒu�ɗ�����K�p
		pUi->pos.x += -UI_DAMAGE_00_POS_AMPLITUDE + fRand(UI_DAMAGE_00_POS_AMPLITUDE * 2);
		pUi->pos.y += -UI_DAMAGE_00_POS_AMPLITUDE + fRand(UI_DAMAGE_00_POS_AMPLITUDE * 2);
		pUi->pos.z += -UI_DAMAGE_00_POS_AMPLITUDE + fRand(UI_DAMAGE_00_POS_AMPLITUDE * 2);

		// ������ݒ�
		pUi->nLife = UI_DAMAGE_00_LIFE;

		// �J��Ԃ������𔲂���
		break;
	}
}