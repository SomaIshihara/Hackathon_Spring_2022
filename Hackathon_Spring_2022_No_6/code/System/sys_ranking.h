//========================================
// 
// SYS:�����L���O[00] �̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// *** sys_ranking.h ***
//========================================
#ifndef _SYS_RANKING_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _SYS_RANKING_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �}�N����`
//****************************************
// �����L���O�̏��ʐ�
// �����L���O���̕�����
// �����L���O���̕�������
// �����L���O���̕������
// �����L���O���̊J�n����
#define RANKING_NUM				(8)
#define RANKING_NAME_NUM		(3)
#define RANKING_NAME_MIN_CHAR	('0')
#define RANKING_NAME_MAX_CHAR	('Z' + 1)
#define RANKING_NAME_START_CHAR	('A')

//****************************************
// �\���̂̒�`
//****************************************
// �����L���O�\����
typedef struct
{
	char	aName	// ���O
			[RANKING_NAME_NUM + 1];
	int		nScore;	// �X�R�A
}Sys_ranking;

//****************************************
// �v���g�^�C�v�錾
//****************************************
// ���ʂ̕\���`�����擾
char *GetRankText(int nRank);

// SYS:�����L���O[00] �̏����擾
Sys_ranking *GetSys_ranking(void);

// SYS:�����L���O[00] �̏���������
// SYS:�����L���O[00] �̏I������
// SYS:�����L���O[00] �̍X�V����
void InitSys_ranking(void);
void UninitSys_ranking(void);
void UpdateSys_ranking(void);

// SYS:�����L���O[00] �̓ǂݍ��ݏ���
// SYS:�����L���O[00] �̏������ݏ���
void LoadSys_ranking(void);
void SaveSys_ranking(void);

// �����L���O�ɃX�R�A��}������
int SetScore(int nScore);

#endif