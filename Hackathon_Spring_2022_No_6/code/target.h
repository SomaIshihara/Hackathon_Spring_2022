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
#define MAX_TARGET		(64)	// �W�I�̍ő吔
#define MAX_SUMMON		(640)	// �����̍ő吔
#define MAX_POINT		(64)	// �o���ʒu�̍ő吔
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

	int nCntFlame;			// �t���[����
	int nPtn;				// �p�^�[���ԍ�

	float fSpeed;			// �ړ����x
	float Tarpos;			// �ڕW�ʒu

	bool bRot;				// �����t���O
	bool bUse;				// �g�p�t���O

}Target;

typedef struct
{
	int nType; // ���
	int nPoint;// �o���ʒu
	int nTime; // �o������
	int nMTyoe;// �ړ�����

	bool bUse; // �g�p�t���O
}Summon;

typedef struct
{
	D3DXVECTOR3 pos;		// �ʒu
}Point;
//****************************************
// �v���g�^�C�v�錾
//****************************************
void InitTarget(void);
void UpdateTarget(void);
void LoadSummon(void);
void LoadTarget(void);
void SetTarget(int nPos, TARGET_ITEM type, int mType);

Target *GetTarget(void);
#endif