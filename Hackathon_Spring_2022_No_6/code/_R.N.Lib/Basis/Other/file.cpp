//========================================
// 
// �t�@�C���֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** file.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** �擾 *** |------------------------
//============================================================
//========================================
// OpenFile�֐� - �J���t�@�C����I�����擾 -
// (pFileName:�ǂݍ��܂ꂽ�t�@�C�������i�[���� pInitDir:�����\������f�B���N�g�� pFileType:�I���ł���t�@�C���̎��)
// Author:RIKU NISHIMURA
//========================================
bool OpenFile(char *pFileName, char *pInitDir, char *pFileType)
{
	TCHAR fileName[MAX_PATH];	// �t�@�C�����i�[

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);		// �\���̂̃T�C�Y�w��
	ofn.lpstrFile = fileName;			// �I�����ꂽ�t�@�C�������i�[�����z��w��
	ofn.lpstrFile[0] = '\0';			// �t�@�C����������
	ofn.nMaxFile = sizeof(fileName);	// lpstrFile �z��̍ő�T�C�Y���t�@�C�����i�[�p������̃T�C�Y�Ŏw��
	ofn.lpstrFilter = pFileType;		// �I���ł���t�@�C���̎�ނ��w��
	ofn.nFilterIndex = 1;				// �����I������Ă���t�B���^�̃C���f�b�N�X���w��
	ofn.lpstrFileTitle = NULL;			// �I�����ꂽ�t�@�C���̃^�C�g�����w��(�g�p����Ȃ��ꍇ��NULL)
	ofn.nMaxFileTitle = 0;				// lpstrFileTitle �̍ő�T�C�Y(�g�p����Ȃ��ꍇ��0)
	ofn.lpstrInitialDir = pInitDir;		// �����\������f�B���N�g��(�g�p����Ȃ��ꍇ��NULL)
	// �_�C�A���O�̃I�v�V�������w��
	// OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST �́A�I�����ꂽ�p�X�����݂��邱�ƂƁA�I�����ꂽ�t�@�C�������݂��邱�Ƃ��m�F�������
	// OFN_NOCHANGEDIR �́A�f�B���N�g����ύX���Ȃ��悤�ɂ������
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;

	if (GetOpenFileName(&ofn))
	{// �J�����t�@�C�������擾�o�������A
		// �t�@�C�����̃|�C���^�ɓǂݍ��񂾃t�@�C��������
		sprintf(pFileName, fileName);
		// ���͏��̃N���A����
		ClearInputInfo();
		return true;
	}
	else {
		// ���͏��̃N���A����
		ClearInputInfo();
		return false;
	}
}

//========================================
// SaveFile�֐� - �ۑ�����t�@�C����I�����擾 -
// �ipFileName:�ǂݍ��܂ꂽ�t�@�C�������i�[���� pInitDir:�����\������f�B���N�g�� pFileType:�I���ł���t�@�C���̊g���q�j
// Author:RIKU NISHIMURA
//========================================
bool SaveFile(char *pFileName, char *pInitDir, char *pExt)
{
	TCHAR fileName[MAX_PATH];	// �t�@�C�����i�[

	OPENFILENAME ofn;
	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(ofn);		// �\���̂̃T�C�Y�w��
	ofn.lpstrFile = fileName;			// �I�����ꂽ�t�@�C�������i�[�����z��w��
	ofn.lpstrFile[0] = '\0';			// �t�@�C����������
	ofn.nMaxFile = sizeof(fileName);	// lpstrFile �z��̍ő�T�C�Y���t�@�C�����i�[�p������̃T�C�Y�Ŏw��
	ofn.lpstrFilter = pExt;				// �I���ł���t�@�C���̊g���q���w��
	ofn.nFilterIndex = 1;				// �����I������Ă���t�B���^�̃C���f�b�N�X���w��
	ofn.lpstrFileTitle = NULL;			// �I�����ꂽ�t�@�C���̃^�C�g�����w��(�g�p����Ȃ��ꍇ��NULL)
	ofn.nMaxFileTitle = 0;				// lpstrFileTitle �̍ő�T�C�Y(�g�p����Ȃ��ꍇ��0)
	ofn.lpstrInitialDir = pInitDir;		// �����\������f�B���N�g��(�g�p����Ȃ��ꍇ��NULL)
	// �_�C�A���O�̃I�v�V�������w��
	// OFN_NOCHANGEDIR �́A�f�B���N�g����ύX���Ȃ��悤�ɂ������
	ofn.Flags = OFN_NOCHANGEDIR;

	if (GetSaveFileName(&ofn))
	{// �J�����t�@�C�������擾�o�������A
		// �t�@�C�����̃|�C���^�ɓǂݍ��񂾃t�@�C�����������邪�A
		// �������g���q�ŏI����Ă��Ȃ����A����ɉ����Ċg���q��A��������
		int len = strlen(fileName);
		int extlen = strlen(pExt);
		if (len < extlen || strcmp(fileName + len - extlen, pExt) != 0)
		{
			sprintf(pFileName, "%s%s", fileName, pExt);
		}
		else {
			strcpy(pFileName, fileName);
		}

		// ���͏��̃N���A����
		ClearInputInfo();
		return true;
	}
	else {
		// ���͏��̃N���A����
		ClearInputInfo();
		return false;
	}
}