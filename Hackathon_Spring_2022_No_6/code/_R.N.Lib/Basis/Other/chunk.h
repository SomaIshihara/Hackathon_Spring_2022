//========================================
// 
// �����̂܂Ƃ܂�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** chunk.h ***
//========================================
#ifndef _CHUNK_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _CHUNK_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �񋓌^�̒�`
//****************************************
// �J�E���g�̎��
typedef enum
{
	COUNTTYPE_NORMAL,	// �ʏ�
	COUNTTYPE_TURN,		// �܂�Ԃ�
	COUNTTYPE_MAX,
}COUNTTYPE;

//****************************************
// �v���g�^�C�v�錾
//****************************************
// �J�E���g����
int Counter(int *pData, int nMin, int nMax, int *pCounter, int nCountTime, COUNTTYPE countType);
// �����^�̏����
bool IntConsumption(int *pData, int nSubtract);
// ���������^�̒l�̐��䏈��
void FloatControl(float *pData, float fMax, float fMin);
// ���������^�̒l�̃��[�v���䏈��
void FloatLoopControl(float *pData, float fMax, float fMin);
// �����^�̒l�̐��䏈��
void IntControl(int *pData, int nMax, int nMin);
// �����^�̒l�̃��[�v���䏈��
void IntLoopControl(int *pData, int nMax, int nMin);
// �����^�̒l�̐��䏈���������ʂ�Ԃ�
int IntControlReturn(int nData, int nMax, int nMin);
// �����^�̒l�̃��[�v���䏈���������ʂ�Ԃ�
int IntLoopControlReturn(int nData, int nMax, int nMin);
// ���I����
bool Lottery(float fProb);
// ���������^�̗�����Ԃ�
float fRand(float fMax);
// �����^������Ԃ�
int Rand(int nMin, int nMax);
// �l���Ԋu���݂ŕԂ�
float Tick(float fData, float fSpace);
// �^����ꂽ�l�ɉ�����1��-1��Ԃ�
int Sign(float fData);
// �^����ꂽ�l��0�ȉ��̎���0���A0�ȏ�̎��͒l�����̂܂ܕԂ�
float MaxOfZero(float fData);

#endif