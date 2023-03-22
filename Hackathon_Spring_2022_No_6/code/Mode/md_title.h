//========================================
// 
// MD:�^�C�g���̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** md_title.h ***
//========================================
#ifndef _MD_TITLE_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _MD_TITLE_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �񋓌^�̒�`
//****************************************
// MD:�^�C�g���̏��
typedef enum
{
	MD_TITLE_STATE_NONE,	// ����
	MD_TITLE_STATE_NORMAL,	// �ʏ�
	MD_TITLE_STATE_MAX,
}MD_TITLE_STATE;

//****************************************
// �\���̂̒�`
//****************************************
// MD:�^�C�g���̏��\����
typedef struct
{
	// ��Ԋ֘A
	MD_TITLE_STATE state;	// MD:�^�C�g�����[00] �̏��
}Md_title;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// MD:�^�C�g���̏���������
void InitMd_title(void);
// MD:�^�C�g���̏I������
void UninitMd_title(void);
// MD:�^�C�g���̍X�V����
void UpdateMd_title(void);
// MD:�^�C�g���̕`�揈��
void DrawMd_title(void);
//========== *** �擾 ***
// MD:�^�C�g���̏����擾
Md_title *GetMd_title(void);
//========== *** �ݒ� ***
// MD:�^�C�g���̏�Ԑݒ菈��
void SetStateMd_title(MD_TITLE_STATE state);

#endif