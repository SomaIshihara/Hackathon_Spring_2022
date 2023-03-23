//========================================
// 
// SYS:�����L���O[00] �̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** sys_ranking.cpp ***
//========================================
#include "../main.h"
#include "sys_ranking.h"
#include <stdio.h>

//****************************************
// �}�N����`
//****************************************
// �����L���O[00] �̏��̃f�[�^�t�@�C���̑��΃p�X
#define SYS_RANKING_RANKING_DATA_FILE_PATH	"data\\SAVEDATA\\ranking.bin"

//****************************************
// �v���g�^�C�v�錾
//****************************************
// �X�R�A�����L���O���~���Ƀ\�[�g����
void ScoreSortDesc(int *nScore, int *nUpdateRank);

//****************************************
// �O���[�o���錾
//****************************************
// �����L���O[00] �̏��
Sys_ranking	g_sys_ranking[RANKING_NUM] = 
{
	{ "AAA", 30000 },
	{ "BBB", 10000 },
	{ "CCC", 2500 },
	{ "---", 0 },
	{ "---", 0 },
	{ "---", 0 },
	{ "---", 0 },
	{ "---", 0 },
};

// ���ʂ̕\���`��
char g_aRankText[RANKING_NUM][TXT_MAX] =
{
	"1ST",
	"2ND",
	"3RD",
	"4TH",
	"5TH",
	"6TH",
	"7TH",
	"8TH",
};

//========== *** �V�X�e��:�����L���O[00] �̏����擾 ***
Sys_ranking *GetSys_ranking(void)
{
	return g_sys_ranking;
}

//========== *** ���ʂ̕\���`�����擾 ***
char *GetRankText(int nRank) 
{
	return g_aRankText[nRank];
}

//========================================
// InitSys_ranking�֐� - �V�X�e��:�����L���O[00] �̏��������� -
//========================================
void InitSys_ranking(void)
{
	
}

//========================================
// UninitSys_ranking�֐� - �V�X�e��:�����L���O[00] �̏I������ -
//========================================
void UninitSys_ranking(void) 
{
	
}

//========================================
// UpdateSys_ranking�֐� - �V�X�e��:�����L���O[00] �̍X�V���� -
//========================================
void UpdateSys_ranking(void) 
{
	
}

//========================================
// SetScore�֐� - �����L���O�ɃX�R�A��}������ -
//========================================
int SetScore(int nScore)
{
	int nUpdateRank = -1;	// �X�R�A���X�V��������

	// �X�R�A���~���Ƀ\�[�g����
	ScoreSortDesc(&nScore, &nUpdateRank);

	if (nScore > g_sys_ranking[RANKING_NUM - 1].nScore)
	{// �ł��������l���}������l���傫��������
		// �ł��������l�ɑ}������l��������
		g_sys_ranking[RANKING_NUM - 1].nScore = nScore;

		// �X�R�A���X�V�������ʂ�������
		nUpdateRank = RANKING_NUM - 1;
	}

	// �X�R�A���~���Ƀ\�[�g����
	ScoreSortDesc(&nScore, &nUpdateRank);

	// �X�R�A���X�V�������ʂ�Ԃ�
	return nUpdateRank;
}

//========================================
// ScoreSortDesc�֐� - �X�R�A�����L���O���~���Ƀ\�[�g���� -
//========================================
void ScoreSortDesc(int *nScore, int *nUpdateRank)
{
	int		nTemp;						// �ꎞ�I�ɒl���i�[
	char	aNameTemp					// 
			[RANKING_NAME_NUM + 1];		// ���O���ꎞ�I�Ɋi�[
	int		nCntCompare1, nCntCompare2;	// ��r�̃J�E���g
	bool	bUpdateRank					//
			= false;					// ���ʍX�V�t���O

	for (nCntCompare1 = 0; nCntCompare1 < RANKING_NUM - 1; nCntCompare1++)
	{
		for (nCntCompare2 = nCntCompare1 + 1; nCntCompare2 < RANKING_NUM; nCntCompare2++)
		{
			if (g_sys_ranking[nCntCompare2].nScore > g_sys_ranking[nCntCompare1].nScore)
			{// �v�f2���v�f1�̒l�������Ă������A
				// �l�����ւ���
				nTemp = g_sys_ranking[nCntCompare1].nScore;
				g_sys_ranking[nCntCompare1].nScore = g_sys_ranking[nCntCompare2].nScore;
				g_sys_ranking[nCntCompare2].nScore = nTemp;

				// ���O�����ւ���
				sprintf(aNameTemp, "%s",g_sys_ranking[nCntCompare1].aName);
				sprintf(g_sys_ranking[nCntCompare1].aName, "%s", g_sys_ranking[nCntCompare2].aName);
				sprintf(g_sys_ranking[nCntCompare2].aName, "%s", aNameTemp);

				if (bUpdateRank == false)
				{// ���ʍX�V�t���O���U�̎��A
					// ���ʍX�V�t���O��^�ɂ���
					bUpdateRank = true;

					// �X�R�A���X�V�������ʂ�������
					*nUpdateRank = nCntCompare1;
				}
			}
		}
	}
}

//========================================
// LoadSys_ranking�֐� - �V�X�e��:�����L���O[00] �̓ǂݍ��ݏ��� -
//========================================
void LoadSys_ranking(void)
{
	FILE *pFile;	//�t�@�C���̃|�C���^

	//�t�@�C�����J��
	pFile = fopen(SYS_RANKING_RANKING_DATA_FILE_PATH, "rb");

	if (pFile != NULL)
	{//�t�@�C�����J�������A
		//�t�@�C�����烉���L���O��ǂݍ���
		fread(g_sys_ranking, sizeof(Sys_ranking), RANKING_NUM, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
}

//========================================
// SaveSys_ranking�֐� - �V�X�e��:�����L���O[00] �̏������ݏ��� -
//========================================
void SaveSys_ranking(void)
{
	FILE *pFile;	//�t�@�C���̃|�C���^

	//�t�@�C�����J��
	pFile = fopen(SYS_RANKING_RANKING_DATA_FILE_PATH, "wb");

	if (pFile != NULL)
	{//�t�@�C�����J�������A
		//�t�@�C���Ƀ����L���O�������o��
		fwrite(g_sys_ranking, sizeof(Sys_ranking), RANKING_NUM, pFile);

		//�t�@�C�������
		fclose(pFile);
	}
}