//========================================
// 
// �e�L�X�g�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// *** text.h ***
//========================================
#ifndef _TEXT_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _TEXT_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �񋓌^�̒�`
//****************************************
// �\���`��
typedef enum
{
	TEXT_DISP_CENTER,	// ��������
	TEXT_DISP_LEFT,		// ������
	TEXT_DISP_RIGHT,	// �E����
	TEXT_DISP_MAX,
}TEXT_DISP;

//****************************************
// �\���̂̒�`
//****************************************
// �t�H���g���̏��\����
typedef struct
{
	char aTexPath[TXT_MAX];		// �e�N�X�`���t�@�C���̑��΃p�X
	char cStartChar;			// �J�n����
	unsigned int nPtnWidth;		// �p�^�[����
	unsigned int nPtnHeight;	// �p�^�[������
	unsigned int nSpaceNum;		// �Ԋu�䗦�̕��q
	unsigned int nSpaceDenom;	// �Ԋu�䗦�̕���
	int nTex;					// �e�N�X�`���ԍ�
}Font;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// �e�L�X�g�̏���������
void InitText(void);
//========== *** ���o�� ***
// �t�H���g�̓ǂݍ��ݏ���
void LoadFont(void);
//========== *** �擾 ***
// �t�H���g���̏����擾
Font GetFont(unsigned int nFont);

#endif