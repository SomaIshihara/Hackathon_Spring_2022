//========================================
// 
// UI:���j���[ �̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
// *** ui_menu.h ***
//========================================
#ifndef UI_MENU_H_	// ���̃}�N����`������Ă��Ȃ�������
#define UI_MENU_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �񋓌^�̒�`
//****************************************
// UI:���j���[ �̓��̓��[�h
typedef enum
{
	UI_MENU_INPUT_MODE_UP_AND_DOWN,		// �㉺
	UI_MENU_INPUT_MODE_LEFT_AND_RIGHT,	// ���E
	UI_MENU_INPUT_MODE_MAX
}UI_MENU_INPUT_MODE;

// UI:���j���[ �̎��
typedef enum
{
	UI_MENU_TYPE_NORMAL,		// �ʏ�
	UI_MENU_TYPE_SELECTION,	// �I��
	UI_MENU_TYPE_MAX
}UI_MENU_TYPE;

// UI:���j���[ �̏��
typedef enum
{
	UI_MENU_STATE_NONE,
	UI_MENU_STATE_IN_POP,	// �o����
	UI_MENU_STATE_POP,		// �o��
	UI_MENU_STATE_IN_CLEAR,	// ������
	UI_MENU_STATE_MAX
}UI_MENU_STATE;

//****************************************
// �\���̂̒�`
//****************************************
// UI:���j���[ �̊Ǘ����\����
typedef struct
{
	UI_MENU_STATE	state;			// ���
	int					nCounterState;	// ��Ԃ̃J�E���^�[
	Scale				scale;			// �g�嗦
	int					nNum;			// ���݂̎g�p��
	int					nSelect;		// ���݂̑I��ԍ�
	D3DXVECTOR3			centerPos;		// ���S���W
}Ui_menuControl;

// UI:���j���[ �̏��\����
typedef struct
{
	// �ʒu�֘A
	D3DXVECTOR3	pos;	// �ʒu

	// ���ޏ��
	UI_MENU_TYPE	type;	// ���
	
	// ��Ԓl
	bool	bUse;		// �g�p����Ă��邩�t���O
	bool	bSelect;	// �I������Ă��邩�t���O
	char	aString
			[TXT_MAX];	// �\�����镶����
	int	 nSelectNum;	// ���݂̑I�����̔ԍ�
}Ui_menu;

// UI:���j���[ �̐ݒ���\����
typedef struct 
{
	UI_MENU_TYPE type;	// ���
	char *aString;		// �\�����镶����
	bool bDecisionSE;	// ����SE�t���O
}Ui_menuSet;

//****************************************
// �v���g�^�C�v�錾
//****************************************
// UI:���j���[ �̏����擾
Ui_menu *GetUi_menu(void);
// UI:���j���[ �̑S�̊Ǘ��̏����擾
Ui_menuControl *GetUi_menuControl(void);
// UI:���j���[ �̌��݂̑I��ԍ����擾
int *GetSelect(void);
// UI:���j���[ �̏���������
void InitUi_menu(void);
// UI:���j���[ �̏I������
void UninitUi_menu(void);
// UI:���j���[ �̍X�V����
void UpdateUi_menu(void);
// UI:���j���[ �̕`�揈��
void DrawUi_menu(void);
// UI:���j���[ �̓��͏���
int Ui_menuInput(UI_MENU_INPUT_MODE mode);
// UI:���j���[ �̒��S���W��ݒ�
void SetUi_menuPos(D3DXVECTOR3 pos);
// UI:���j���[ �̐ݒ菈��
void SetUi_menu(Ui_menuSet *pSet, int nNum);

#endif