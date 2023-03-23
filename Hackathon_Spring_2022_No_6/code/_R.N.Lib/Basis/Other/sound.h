//========================================
// 
// �T�E���h�̃w�b�_�t�@�C��
// Author:AKIRA TANAKA
// Arrange:RIKU NISHIMURA
// 
//========================================
// *** sound.h ***
//========================================
#ifndef _SOUND_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _SOUND_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �񋓌^�̒�`
//****************************************
// �T�E���h�̎��
typedef enum
{
	SOUND_TYPE_BGM,	// ���y
	SOUND_TYPE_SE,	// ���ʉ�
	SOUND_TYPE_MAX,
}SOUND_TYPE;

//****************************************
// �\���̂̒�`
//****************************************
// �T�E���h���̍\���̒�`
typedef struct
{
	// �t�@�C����
	char aFileName[TXT_MAX];
	int nCntLoop;		// ���[�v�J�E���g
	float fVolume;		// ����
	SOUND_TYPE type;	// �T�E���h�̎��
} SOUNDINFO;

//*****************************************************************************
// �v���g�^�C�v�錾
//*****************************************************************************
//========== *** ��{�ڑ� ***
// �T�E���h�̏���������
HRESULT InitSound(HWND hWnd);
// �T�E���h�̏I������
void UninitSound(void);
//========== *** ���o�� ***
// �T�E���h�̓ǂݍ��ݏ���
void LoadSound(void);
//========== *** �擾 ***
// �T�E���h�̏����擾
SOUNDINFO *GetSoundInfo(void);
//========== *** ���� ***
// �Z�O�����g�Đ�(�Đ����Ȃ��~)
HRESULT PlaySound(int nSoundIdx);
// �Z�O�����g��~(���x���w��)
void StopSound(int nSoundIdx);
// �Z�O�����g��~(�S��)
void StopSound(void);
// �ݒ艹�ʂ�ݒ�
void SetSettingVolume(SOUND_TYPE type);
// ��ޖ��ɉ��ʕύX
void SoundTypeVolumeChange(SOUND_TYPE type, float fVolume);
// ��ޖ��ɍĐ���~
void StopSoundType(SOUND_TYPE type);

#endif
