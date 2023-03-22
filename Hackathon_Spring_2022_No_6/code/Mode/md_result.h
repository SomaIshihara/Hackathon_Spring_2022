//========================================
// 
// MD:���U���g�̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** md_result.h ***
//========================================
#ifndef _MD_RESULT_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _MD_RESULT_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �񋓌^�̒�`
//****************************************
// MD:���U���g�̏��
typedef enum
{
	MD_RESULT_STATE_NONE,	// ����
	MD_RESULT_STATE_NORMAL,	// �ʏ�
	MD_RESULT_STATE_MAX,
}MD_RESULT_STATE;

//****************************************
// �\���̂̒�`
//****************************************
// MD:���U���g�̏��\����
typedef struct
{
	// ��Ԋ֘A
	MD_RESULT_STATE state;	// MD:���U���g���[00] �̏��
}Md_result;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// MD:���U���g�̏���������
void InitMd_result(void);
// MD:���U���g�̏I������
void UninitMd_result(void);
// MD:���U���g�̍X�V����
void UpdateMd_result(void);
// MD:���U���g�̕`�揈��
void DrawMd_result(void);
//========== *** �擾 ***
// MD:���U���g�̏����擾
Md_result *GetMd_result(void);
//========== *** �ݒ� ***
// MD:���U���g�̏�Ԑݒ菈��
void SetStateMd_result(MD_RESULT_STATE state);

#endif