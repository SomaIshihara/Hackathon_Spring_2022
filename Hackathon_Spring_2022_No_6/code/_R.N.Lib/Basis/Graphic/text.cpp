//========================================
// 
// �e�L�X�g�̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** text.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �}�N����`
//****************************************
// �t�H���g�̃f�[�^�t�@�C���̑��΃p�X
#define FONT_DATA_FILE "data\\FONT_LIST.txt"
// �t�H���g�̍ő吔
#define FONT_MAX (16)

//****************************************
// �O���[�o���ϐ��錾
//****************************************
static Font g_aFont[FONT_MAX];	// �t�H���g���̏��

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ��{�ڑ� *** |--------------------
//============================================================

//========================================
// InitText�֐� - �e�L�X�g�̏��������� -
// Author:RIKU NISHIMURA
//========================================
void InitText(void)
{
	LPDIRECT3DDEVICE9 pDevice;	// �f�o�C�X�ւ̃|�C���^

	// �f�o�C�X�̎擾
	pDevice = GetD3DDevice();

	for (int nCntFont = 0; nCntFont < FONT_MAX; nCntFont++)
	{
		// �e�N�X�`���̓ǂݍ���
		g_aFont[nCntFont].nTex = LoadTexture(g_aFont[nCntFont].aTexPath);
	}
}

//============================================================
//--------------------| *** ���o�� *** |----------------------
//============================================================

//========================================
// LoadFont�֐� - �t�H���g�̓ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void LoadFont(void)
{
	FILE *pFile;				// �t�@�C���|�C���^
	char aDataSearch[TXT_MAX];	// �f�[�^�����p
	Font *pFont = g_aFont;		// �t�H���g���̏��̃|�C���^

	// ��ޖ��̏��̃f�[�^�t�@�C�����J��
	pFile = fopen(FONT_DATA_FILE, "r");

	if (pFile == NULL)
	{// ��ޖ��̏��̃f�[�^�t�@�C�����J���Ȃ������ꍇ�A
		//�������I������
		return;
	}

	// END��������܂œǂݍ��݂��J��Ԃ�
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch);	// ����

		if (!strcmp(aDataSearch, "END"))
		{// �ǂݍ��݂��I��
			fclose(pFile); break; 
		}
		else if (!strcmp(aDataSearch, "FONTSET"))
		{// ���i�̐ݒ���̓ǂݍ��݂��J�n
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch);	// ����

				if (!strcmp(aDataSearch, "FONTSET_END")) 
				{// �ǂݍ��݂��I��
					break;
				}
				else if (!strcmp(aDataSearch, "FONT"))
				{// ���i���̏��̓ǂݍ��݂��J�n
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch);	// ����

						if (!strcmp(aDataSearch, "FONT_END"))
						{// �|�C���^��i�߂�
							pFont++;
							break;
						}
						else if (!strcmp(aDataSearch, "TEXTURE_PATH:"))
						{// �t�@�C����
							fscanf(pFile, "%s", &pFont->aTexPath); 
						}
						else if (!strcmp(aDataSearch, "START_CHAR:"))
						{// �J�n����
							fscanf(pFile, "%s", &pFont->cStartChar);
						}
						else if (!strcmp(aDataSearch, "PTN_WIDTH:"))
						{// �p�^�[����
							fscanf(pFile, "%d", &pFont->nPtnWidth);
						}
						else if (!strcmp(aDataSearch, "PTN_HEIGHT:"))
						{// �p�^�[������
							fscanf(pFile, "%d", &pFont->nPtnHeight);
						}
						else if (!strcmp(aDataSearch, "SPACE_NUM:"))
						{// �Ԋu�䗦�̕��q 
							fscanf(pFile, "%d", &pFont->nSpaceNum);
						}
						else if (!strcmp(aDataSearch, "SPACE_DENOM:"))
						{// �Ԋu�䗦�̕��� 
							fscanf(pFile, "%d", &pFont->nSpaceDenom);
						}
					}
				}
			}
		}
	}
}

//========================================
// GetFont�֐� - �t�H���g���̏����擾 -
// Author:RIKU NISHIMURA
//========================================
Font GetFont(unsigned int nFont) 
{
	return g_aFont[nFont];
}