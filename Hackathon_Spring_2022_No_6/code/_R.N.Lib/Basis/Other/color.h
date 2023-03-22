//========================================
// 
// �F�̏����̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** color.h ***
//========================================
#ifndef _COLOR_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _COLOR_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �}�N����`
//****************************************
// �w�i�F�̏����l
#define INITBGCOLOR Color{0,0,0,255}

//****************************************
// �\���̂̒�`
//****************************************
// �F�Ǘ����\����
typedef struct 
{
	// �w�i�F
	Color bgCol = INITBGCOLOR;
}ColorInfo;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** �擾 ***
// �F�Ǘ����̎擾
ColorInfo *GetColorInfo(void);
//========== *** �ݒ� ***
// �w�i�F��ݒ�
void SetBackgroundColor(Color bgCol);
//========== *** ���o�� ***
// �F�̓ǂݍ��ݏ���
void LoadColor(FILE *pFile, Color *pCol);
//========== *** �ϊ� ***
// Color�`���̐F��D3DXCOLOR�`���ɕϊ�
D3DXCOLOR ColorToD3DXCOLOR(Color col);
// Color�`���̐F��D3DCOLOR�`���ɕϊ�
D3DCOLOR ColorToD3DCOLOR(Color col);
//========== *** ���̑� ***
// �F�ɖ��邳�𔽉f
Color BrightnessToColor(Color col, float fBrightness);
// Color�`���̐F�̒l�������ŕԂ�
Color ColorRate(Color col, float fRate);
// Color�`���̐F�����Z
Color ColorAdd(Color col1, Color col2);
// Color�`���̐F��������
Color ColorMix(Color col1, Color col2);

#endif