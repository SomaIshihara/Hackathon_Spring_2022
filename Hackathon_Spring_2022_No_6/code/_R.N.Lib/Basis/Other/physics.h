//========================================
// 
// �����֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** physics.h ***
//========================================
#ifndef _PHYSICS_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _PHYSICS_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

// R.N.Lib
#include "../3D/parts3D.h"

//****************************************
// �}�N����`
//****************************************
// �����蔻��̍ő吔
#define HIT_TEST_MAX (4)
// �����蔻��̕��i�̍ő吔
#define HIT_TEST_PARTS_MAX (16)

//****************************************
// �񋓌^�̒�`
//****************************************
//========== *** �����蔻�� ***
// �Փ˃`�F�b�N�̃��[�h
typedef enum 
{
	COLLCHK_MODE_NORMAL,	// �ʏ�
	COLLCHK_MODE_LOOKDOWN,	// �����낵
}COLLCHK_MODE;

// �����蔻��̌`
typedef enum
{
	HIT_TEST_FORM_SPHERE,	// ��
	HIT_TEST_FORM_SQUARE,	// �l�p
	HIT_TEST_FORM_CYLINDER,	// �~��
	HIT_TEST_FORM_MAX,
}HIT_TEST_FORM;

//========== *** ���̑� ***
// �Փ˕���
typedef enum 
{
	HITDIRECTION_TOP,		// ��
	HITDIRECTION_BOTTOM,	// ��
	HITDIRECTION_LEFT,		// ��
	HITDIRECTION_RIGHT,		// �E
	HITDIRECTION_BACK,		// ��
	HITDIRECTION_FRONT,		// ��O
	HITDIRECTION_MAX,
}HITDIRECTION;

// ����
typedef enum
{
	DIRECTION_UP,			// ��
	DIRECTION_DOWN,			// ��
	DIRECTION_LEFT,			// ��
	DIRECTION_RIGHT,		// �E
	DIRECTION_BACK,			// ��
	DIRECTION_FRONT,		// ��O
	DIRECTION_LEFT_BACK,	// ����
	DIRECTION_LEFT_FRONT,	// ����O
	DIRECTION_RIGHT_BACK,	// �E��
	DIRECTION_RIGHT_FRONT,	// �E��O
	DIRECTION_MAX,
}DIRECTION;

// �x�N�g���̎��
typedef enum 
{
	VECTOR_X,		// X����
	VECTOR_Y,		// Y����
	VECTOR_Z,		// Z����
	VECTOR_NONE,	// ����
	VECTOR_MAX
}VECTOR;

// ���_
typedef enum 
{
	VERTEX_X0Y0,	// ����
	VERTEX_X1Y0,	// �E��
	VERTEX_X0Y1,	// ����
	VERTEX_X1Y1,	// �E��
	VERTEX_MAX,
}VERTEX;

//****************************************
// �\���̂̒�`
//****************************************
//========== *** �Փˏ�� ***
// �Փˏ��\����
typedef struct
{
	bool bHit;	// ������t���O
	bool bColl;	// �Փ˃t���O
	bool bOvl;	// �͈͓��t���O
}Collision;
// �����蔻��̕��i���\����
typedef struct
{
	HIT_TEST_FORM hitTestForm;		// �����蔻��̌`
	int nParent;					// �e�ԍ�
	float fWidth;					// ��
	float fHeight;					// ����
	float fDepth;					// ���s��
	D3DXVECTOR3 fixedRelativePos;	// ���Έʒu
	D3DXVECTOR3 fixedRelativeRot;	// ���Ό���
	bool aGhost[HITDIRECTION_MAX];	// ���蔲�����
}HitTestParts;
//========== *** �ݒ��� ***
// �����蔻��̏��\����
typedef struct 
{
	int nHitTestPartsNum;	// �����蔻��̕��i�̐�
	// �����蔻��̕��i�̏��
	HitTestParts aHitTestParts[HIT_TEST_PARTS_MAX];
}HitTest;
// �����蔻��̐ݒ���\����
typedef struct
{
	int nHitTestNum;				// �����蔻��̐�
	HitTest aHitTest[HIT_TEST_MAX];	// �����蔻��̏��
}HitTestSet;
//========== *** �Ǘ���� ***
// �����蔻��Ǘ��\����
typedef struct
{
	int	nHitTest;	// �����蔻��ԍ�
}HitTestInfo;
//========== *** ���n��� ***
// �Փ˔���ɕK�v�ȏ��\����
typedef struct
{
	D3DXVECTOR3 *pPos;			// ���݂̈ʒu�̃|�C���^
	D3DXVECTOR3 posOld;			// �ߋ��̈ʒu�̃|�C���^
	D3DXVECTOR3 *pMove;			// �ړ��ʂ̃|�C���^
	D3DXVECTOR3 *pRot;			// ���݂̌����̃|�C���^
	D3DXVECTOR3 rotOld;			// �ߋ��̌����̃|�C���^
	Parts3DInfo *pPartsInfo;	// ���i�Ǘ����
	Parts3DSet *pPartsSet;		// ���i�ݒ���
	HitTest *pHitTest;			// �����蔻��̏��
	COLLCHK_MODE mode;			// �Փ˃`�F�b�N�̃��[�h
}CollisionInfo;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// �����֘A�̏���������
void InitPhysics(void);
//========== *** ���o�� ***
// �����蔻��ݒ���̓ǂݍ��ݏ���
void LoadHitTestSet(FILE *pFile, HitTestSet *pHitTestSet);
//========== *** �����蔻�� ***
// �����蔻��o�^����
void HitTestSignUp(CollisionInfo myCollInfo);
// �����蔻��o�^��������
void HitTestSignOut(void);
// �Փ˃`�F�b�N
void CollisionCheck(VECTOR vector, Collision *pCollision, CollisionInfo myCollInfo, CollisionInfo pairCollInfo, COLLCHK_MODE mode);
// �Փˏ��̏㏑��
void CollisionOverwrite(Collision *pOvwCollision, Collision collision);
//========== *** �����蔻��`��֘A ***
// �����蔻��̕`�揀������
void DrawHitTestSetUp(void);
// �����蔻��̕`�揈��
void DrawHitTest(void);
// �����蔻��̐��̐���������
void InitHitTestLineNum(void);
// �����蔻��̕\���ݒ�
void ShowHitTest(bool bShow);

#endif