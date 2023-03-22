//========================================
// 
// ���f���֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** model.h ***
//========================================
#ifndef _MODEL_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _MODEL_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �}�N����`
//****************************************
// ���f���̎�ނ̍ő吔
#define MODELTYPE_MAX (1024)
// ���f���̍ő吔
#define MODEL_MAX (1024)

//****************************************
// �\���̂̒�`
//****************************************
// ���f���̓ǂݍ��ݏ��\����
typedef struct
{
	char *pModelPath;	// ���f���̃p�X
}ModelLoad;

// ���f���̐ݒ���\����
typedef struct
{
	int nModelIdx = -1;	// ��ޔԍ�
	D3DXMATRIX mtx;		// �}�g���b�N�X
	Color col;			// �F
#if /* �ݒ�t�H�[�}�b�g */0
	// ���f���̐ݒ���
	ModelSet modelSet;
	/* ���f���ԍ�	*/modelSet.nModelIdx = ;
	/* �}�g���b�N�X	*/modelSet.mtx = ;
	/* �F			*/modelSet.col = ;
	// ���f���̐ݒ�
	SetModel(modelSet);
#endif
}ModelSet;

// ���f���̊Ǘ����
typedef struct
{
	//========== *** �ǂݍ��݊֘A ***
	// �ǂݍ��ݍς̃��f���p�X
	char aLoadModelPath[MODELTYPE_MAX][TXT_MAX] = {};
	unsigned int nModelTypeNum = 0;	// ���f���̎�ސ�

	//========== *** �ݒ�֘A ***
	unsigned int nModelSetNum = 0;		// ���f���̐ݒ萔
	ModelSet aModelSet[MODEL_MAX] = {};	// ���f���̐ݒ���
}ModelInfo;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// ���f���̏���������
void InitModel(void);
// ���f���̏I������
void UninitModel(void);
// ���f���̕`�揈��
void DrawModel(void);
// ���f���̕`�揈��(�P��)
void DrawSingleModel(LPDIRECT3DDEVICE9 pDevice, int nIdx);
//========== *** ���o�� ***
// ���f���̓ǂݍ��ݏ���
int LoadModel(ModelLoad modelLoad);
//========== *** �ݒ� ***
// ���f���̐ݒ菈��
void SetModel(ModelSet modelSet);
//========== *** �擾 ***
// ���f���̊Ǘ����擾
ModelInfo *GetModelInfo(void);

#endif