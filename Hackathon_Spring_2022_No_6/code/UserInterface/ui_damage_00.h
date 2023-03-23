//========================================
// 
// UI:�_���[�W[00] �̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// *** ui_damage_00.h ***
//========================================
#ifndef _UI_DAMAGE_00_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _UI_DAMAGE_00_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �񋓌^�̒�`
//****************************************
// UI:�_���[�W[00] �̐F�̎��
typedef enum 
{
	UI_DAMAGE_00_COLOR_TYPE_PLAYER,	// �v���C���[
	UI_DAMAGE_00_COLOR_TYPE_ENEMY,	// �G
	UI_DAMAGE_00_COLOR_TYPE_MAX,
}UI_DAMAGE_00_COLOR_TYPE;

//****************************************
// �v���g�^�C�v�錾
//****************************************
// UI:�_���[�W[00] �̏���������
// UI:�_���[�W[00] �̏I������
// UI:�_���[�W[00] �̍X�V����
void InitUi_damage_00(void);
void UninitUi_damage_00(void);
void UpdateUi_damage_00(void);

// UI:�_���[�W[00] �̐ݒ菈��
void SetUi_damage_00(D3DXVECTOR3 pos, int nDamage, UI_DAMAGE_00_COLOR_TYPE colType);

#endif