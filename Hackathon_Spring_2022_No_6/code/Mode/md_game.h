//========================================
// 
// MD:�Q�[���̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** md_game.h ***
//========================================
#ifndef _MD_GAME_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _MD_GAME_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "../main.h"

//****************************************
// �񋓌^�̒�`
//****************************************
// MD:�Q�[���̏��
typedef enum
{
	MD_GAME_STATE_NONE,		// ����
	MD_GAME_STATE_NORMAL,	// �ʏ�
	MD_GAME_STATE_RANKING,	// �����L���O
	MD_GAME_STATE_RESULT,	// ���U���g
	MD_GAME_STATE_MAX,
}MD_GAME_STATE;

//****************************************
// �\���̂̒�`
//****************************************
// MD:�Q�[���̏��\����
typedef struct
{
	// ��Ԋ֘A
	MD_GAME_STATE state;	// MD:�Q�[�����[00] �̏��
	MODE mode;	// �ړ���̃��[�h
}Md_game;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// MD:�Q�[���̏���������
void InitMd_game(void);
// MD:�Q�[���̏I������
void UninitMd_game(void);
// MD:�Q�[���̍X�V����
void UpdateMd_game(void);
// MD:�Q�[���̕`�揈��
void DrawMd_game(void);
//========== *** �擾 ***
// MD:�Q�[���̏����擾
Md_game *GetMd_game(void);
//========== *** �ݒ� ***
// MD:�Q�[���̏�Ԑݒ菈��
void SetStateMd_game(MD_GAME_STATE state);

#endif