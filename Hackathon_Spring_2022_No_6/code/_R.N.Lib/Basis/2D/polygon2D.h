//========================================
// 
// �|���S��(2D)�֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** polygon2D.h ***
//========================================
#ifndef _POLYGON2D_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _POLYGON2D_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �}�N����`
//****************************************
// �|���S��(2D)�̍ő吔
#define POLYGON2D_MAX (1024)

//****************************************
// �\���̂̒�`
//****************************************
// �|���S��(2D)�̐ݒ���\����
typedef struct
{
	int nTex = -1;	// �e�N�X�`���ԍ�
	int nPtn = 0;	// �p�^�[���ԍ�
	int nPtnX = 1;	// �p�^�[�����X
	int nPtnY = 1;	// �p�^�[�����Y
	float fWidth = 0.0f;	// ��
	float fHeight = 0.0f;	// ����
	D3DXVECTOR3 pos = INITD3DXVECTOR3;	// �ʒu
	D3DXVECTOR3 rot = INITD3DXVECTOR3;	// ����
	Color col = INITCOLOR;	// �F
	bool bMatchCamera = false;	// �J�����Ɉʒu���킹�t���O
#if /* �ݒ�t�H�[�}�b�g */0 
	/* �e�N�X�`���ԍ�	*/polySet.nTex = ;
	/* �p�^�[���ԍ�		*/polySet.nPtn = ;
	/* �p�^�[�����X	*/polySet.nPtnX = ;
	/* �p�^�[�����Y	*/polySet.nPtnY = ;
	/* ��				*/polySet.fWidth = ;
	/* ����				*/polySet.fHeight = ;
	/* �ʒu				*/polySet.pos = ;
	/* ����				*/polySet.rot = ;
	/* �F				*/polySet.col = ;
	/* �J�������킹		*/polySet.bMatchCamera = ;
#endif
}Polygon2DSet;

// �|���S��(2D)�̊Ǘ����\����
typedef struct
{
	// �|���S��(2D)�̐ݒ���
	Polygon2DSet aPolySet[POLYGON2D_MAX];
	int nPolygonNum = 0;	// �|���S��(2D)�̐�
}Polygon2DControl;

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ��{�ڑ� ***
// �|���S��(2D)�̏���������
void InitPolygon2D(void);
// �|���S��(2D)�̏I������
void UninitPolygon2D(void);
// �|���S��(2D)�̕`�揈��
void DrawPolygon2D(void);
//========== *** �ݒ� ***
// �|���S��(2D)�̐ݒ菈��
void SetPolygon2D(Polygon2DSet polygon2DSet);
//========== *** �擾 ***
// �|���S��(2D)�̊Ǘ������擾
Polygon2DControl *GetPolygon2DControl(void);
//========== *** ���_�ݒ� ***
// ���_���W�̐ݒ菈��(2D)
void SetVertexPos2D(VERTEX_2D *pVtx, D3DXVECTOR3 pos, D3DXVECTOR3 rot, bool bMatchCamera, float fWidth, float fHeight);
// rhw�̐ݒ菈��(2D)
void SetRHW2D(VERTEX_2D *pVtx);
// ���_�F�̐ݒ菈��(2D)
void SetVertexColor2D(VERTEX_2D *pVtx, Color col);
// �e�N�X�`�����W�̐ݒ菈��(2D)
void SetTexturePos2D(VERTEX_2D *pVtx, int nPtn, int nPtnMaxX, int nPtnMaxY, D3DXVECTOR3 *pPos);
// �e�N�X�`�����W�̐ݒ菈��(2D)(�؂���ver)
void SetTexturePos2DCut(VERTEX_2D *pVtx, Scale cutScale, D3DXVECTOR3 pos);
//========== *** ���̑� ***
// �`��ʒu����ɍ��킹��
void MatchPosition(D3DXVECTOR3 *pDrawPos, D3DXVECTOR3 basePos, float fScWidth, float fScHeight);

#endif