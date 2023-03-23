//========================================
// 
// �W�I�̏���
// Author:KEISUKE OOTONO
// 
//========================================
//  *** target.h ***
//========================================
#ifndef _TARGET_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _TARGET_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����
#include "_R.N.Lib\Basis\Other\window.h"
#include "_R.N.Lib\RNmain.h"
#include "main.h"
//****************************************
// �}�N����`
//****************************************
#define MAX_TARGET		(64)						// �W�I�̍ő吔
#define MAX_SUMMON		(64)						// �o���ʒu�̍ő吔
//****************************************
// �񋓌^�̒�`
//****************************************
// Item�̎��
typedef enum
{
	TARGET_A = 0,	// 
	TARGET_B,		// 
	TARGET_C,		// 
	TARGET_MAX
}TARGET_ITEM;
//****************************************
// �\���̂̒�`
//****************************************
// target�̏��\����
typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
	D3DXVECTOR3 rot;		// ����
	D3DXVECTOR3 move;		// �ړ���
	D3DXMATRIX mtxWorld;	// ���[���h�}�g���b�N�X
	TARGET_ITEM type;		// ���

	float fSpeed;			// �ړ����x

	bool bUse;				// �g�p�t���O

	// ���i�̏��
	Parts3DInfo partsInfo;
}Target;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
}Summon;
//****************************************
// �v���g�^�C�v�錾
//****************************************
// �A�C�e���̓ǂݍ��ݏ���
void InitTarget(void);
void UpdateTarget(void);
void LoadSummon(void);
void SetTarget(int nPos, TARGET_ITEM type);

Target *GetTarget(void);
#endif