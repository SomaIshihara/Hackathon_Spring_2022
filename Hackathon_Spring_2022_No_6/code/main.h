//========================================
// 
// ���C���̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// *** main.h ***
//========================================
#ifndef _MAIN_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _MAIN_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

#include "d3dx9.h"
#include "_R.N.Lib/R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
// �E�C���h�E�̕�
#define SCREEN_WIDTH (1280)	// NORMAL=1280 4:3=960
// �E�C���h�E�̍���
#define SCREEN_HEIGHT (720)
// �E�C���h�E�̒��S���WX
#define SCREEN_CENTER_X (SCREEN_WIDTH*0.5f)
// �E�C���h�E�̒��S���WY
#define SCREEN_CENTER_Y (SCREEN_HEIGHT*0.5f)
// �����X�N���[���̍��[
#define INSIDE_SCREEN_LEFTMOST (960)
// �����X�N���[���̉E�[
#define INSIDE_SCREEN_RIGHTMOST (720)

//****************************************
// �񋓌^�̒�`
//****************************************
// ���[�h(���)�̎��
typedef enum
{
	MODENONE = -1,	// ����
	MODE_TITLE,		// �^�C�g��
	MODE_GAME,		// �Q�[��
	MODE_RESULT,	// ���U���g
	MODE_MAX,
}MODE;

//****************************************
// �\���̂̒�`
//****************************************
// ���C�������̏��\����
typedef struct 
{
	int nCountFPS = 0;		// FPS�̃J�E���^�[
	MODE mode = MODENONE;	// ���[�h
}Main;

//****************************************
// �v���g�^�C�v�錾
//****************************************
// ���C�������̏��̎擾
Main *GetMain(void);
// ���[�h�̎擾
MODE GetMode(void);
// ���[�h�̐ݒ菈��
void SetMode(MODE mode);

#endif