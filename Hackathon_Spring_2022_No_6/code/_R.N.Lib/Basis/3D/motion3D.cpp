//========================================
// 
// ���[�V����(3D)�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** motion3D.cpp ***
//========================================
#include <assert.h>
// R.N.Lib
#include "../../R.N.Lib.h"

//****************************************
// �v���g�^�C�v�錾
//****************************************
//========== *** ���[�V����(3D)�֘A ***
// ���[�V����(3D)�̃A�j���[�V�����ǂݍ��ݏ���
void LoadMotionAnim3D(Motion3DSet motionSet, Parts3DInfo *pPartsInfo, Parts3DSet partsSet);
// ���[�V����(3D)�̃A�j���[�V��������
void MotionAnim3D(Parts3DInfo *pPartsInfo, Parts3DSet partsSet);

//****************************************
// �\���̂̒�`
//****************************************
// ���[�V����(3D)�R�}���h���
typedef struct 
{
	char *pLabelName;	// ���x����
	int nDataNum;		// �����̐�
}Motion3DCommandInfo;

//****************************************
// 
//****************************************
// ���[�V�����R�}���h�̃��x����
const Motion3DCommandInfo g_aMotionCommandInfo[MOTION3D_COMMAND_LABEL_MAX] =
{
	{"MOVE",4},	// �ړ�
	{"SPIN",4},	// ��]
};

//================================================================================
//----------|---------------------------------------------------------------------
//==========| cpp�t�@�C���̐�L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ���[�V����(3D)�֘A *** |----------
//============================================================

//========================================
// LoadMotionAnim3D�֐� - ���[�V����(3D)�̃A�j���[�V�����ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void LoadMotionAnim3D(Motion3DSet motionSet, Parts3DInfo *pPartsInfo, Parts3DSet partsSet)
{
	// ���i���̃A�j���[�V�����̓ǂݍ���
	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++)
	{
		// ���i���̃��[�V����(3D)�̏��
		PartsMotion3D partsMotion3D = motionSet.aMotion[pPartsInfo->nMotion].aPartsMotion[nCntParts];

		for (int nCntCmd = 0; nCntCmd < partsMotion3D.nCommandNum; nCntCmd++)
		{
			MotionCommand cmd = partsMotion3D.aCommand[nCntCmd];	// �R�}���h���
			Parts3D *pParts = &pPartsInfo->aParts[nCntParts];		// ���i(3D)�̏��

			if (pPartsInfo->nCounterMotion != cmd.nTime)
			{// �J�E���^�[���^�C���ƈ�v�������A
				continue;
			}

			// �R�}���h���x���ɉ���������
			switch (cmd.command)
			{
			case MOTION3D_COMMAND_LABEL_MOVE:
			{
				// �ʒu
				D3DXVECTOR3 pos = D3DXVECTOR3(cmd.aData[0], cmd.aData[1], cmd.aData[2]);
				// �ړ��ɂ����鎞��
				int nMoveTime = (int)cmd.aData[3];

				if (nMoveTime == 0)
				{// �ړ��ɂ����鎞�Ԃ�0�̎��A
					pParts->pos = pos;	// �ʒu�𒼐ڑ��
				}
				else
				{// �ړ��ɂ����鎞�Ԃ�0�łȂ����A
					// ���̈ʒu��ݒ�
					pParts->posOld = pParts->pos;
					// �ڕW�ʒu����
					pParts->targetPos = pos;
					// �ʒu�A�j���[�V�����ɂ����鎞�Ԃ���
					pParts->nPosAnimTime = nMoveTime;
					// �ʒu�A�j���[�V�����J�E���^�[��������
					pParts->nCounterPosAnim = 0;
					// �ʒu�A�j���[�V�����t���O��^�ɂ���
					pParts->bPosAnim = true;
				}
			}
				break;
			case MOTION3D_COMMAND_LABEL_SPIN:
			{
				// ����
				D3DXVECTOR3 rot = D3DXVECTOR3(cmd.aData[0], cmd.aData[1], cmd.aData[2]);
				// ��]�ɂ����鎞��
				int nSpinTime = (int)cmd.aData[3];

				if (nSpinTime == 0)
				{// ��]�ɂ����鎞�Ԃ�0�̎��A
					pParts->rot = rot;	// �����𒼐ڑ��
				}
				else
				{// ��]�ɂ����鎞�Ԃ�0�łȂ����A
					// ���̌�����ݒ�
					pParts->rotOld = pParts->rot;
					// �ڕW��������
					pParts->targetRot = rot;
					// �����A�j���[�V�����ɂ����鎞�Ԃ���
					pParts->nRotAnimTime = nSpinTime;
					// �����A�j���[�V�����J�E���^�[��������
					pParts->nCounterRotAnim = 0;
					// �����A�j���[�V�����t���O��^�ɂ���
					pParts->bRotAnim = true;
				}
			}
				break;
			}
		}
	}
}

//========================================
// MotionAnim3D�֐� - ���[�V����(3D)�̃A�j���[�V�������� -
// Author:RIKU NISHIMURA
//========================================
void MotionAnim3D(Parts3DInfo *pPartsInfo, Parts3DSet partsSet)
{
	for (int nCntParts = 0; nCntParts < partsSet.nPartsNum; nCntParts++)
	{
		// ���i�̏��̃|�C���^
		Parts3D *pParts = &pPartsInfo->aParts[nCntParts];

		if (pParts->bPosAnim)
		{// �ʒu�A�j���[�V�����t���O���^�̎��A
			if (++pParts->nCounterPosAnim >= pParts->nPosAnimTime)
			{// �ʒu�A�j���[�V�����J�E���^�[�����Z�������ʈʒu�A�j���[�V�����ɂ����鎞�Ԃ����������A
				// �ʒu�A�j���[�V�����t���O���U�ɂ���
				pParts->bPosAnim = false;

				// �ʒu�ɖڕW�ʒu����
				pParts->pos = pParts->targetPos;
			}
		}

		if (pParts->bRotAnim)
		{// �p�x�A�j���[�V�����t���O���^�̎��A
			if (++pParts->nCounterRotAnim >= pParts->nRotAnimTime)
			{// �����A�j���[�V�����J�E���^�[�����Z�������ʌ����A�j���[�V�����ɂ����鎞�Ԃ����������A
				// �����A�j���[�V�����t���O���U�ɂ���
				pParts->bRotAnim = false;
				
				// �����ɖڕW��������
				pParts->rot = pParts->targetRot;
			}
		}
	}
}

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** ���[�V����(3D)�֘A *** |----------
//============================================================

//========================================
// LoadMotion3DSet�֐� - ���[�V����(3D)�ݒ���̓ǂݍ��ݏ��� -
// Author:RIKU NISHIMURA
//========================================
void LoadMotion3DSet(FILE *pFile, Motion3DSet *pMotionSet)
{
	char aDataSearch[TXT_MAX];	// �f�[�^�����p

	// ���[�V��������������
	pMotionSet->nMotionNum = 0;

	// ���[�V�����ݒ���̓ǂݍ��݂��J�n
	while (1)
	{
		fscanf(pFile, "%s", aDataSearch); // ����

		if (!strcmp(aDataSearch, "MOTIONSET_END"))
		{// �ǂݍ��݂��I��
			break;
		}
		else if (!strcmp(aDataSearch, "MOTION"))
		{
			// ���[�V�����̏��̃|�C���^
			Motion3D *pMotion = &pMotionSet->aMotion[pMotionSet->nMotionNum];
			int nCntParts = 0;	// ���i�̃J�E���g

			// ���[�V�������̓ǂݍ��݂��J�n
			while (1)
			{
				fscanf(pFile, "%s", aDataSearch); // ����
				
				if (!strcmp(aDataSearch, "MOTION_END"))
				{// ���[�V�����������Z���A�ǂݍ��݂��I��
					pMotionSet->nMotionNum++;
					break; 
				}
				else if (!strcmp(aDataSearch, "LOOP_TIME:"))
				{// ���[�v���� 
					fscanf(pFile, "%d", &pMotion->nLoopTime);
				}
				else if (!strcmp(aDataSearch, "LOOP:"))
				{// ���[�v���邩�t���O
					int nTemp;
					fscanf(pFile, "%d", &nTemp);
					pMotion->bLoop = (nTemp != 0);
				}
				else if (!strcmp(aDataSearch, "PARTS"))
				{
					// ���i���̃��[�V�����̏��̃|�C���^
					PartsMotion3D *pPartsMotion = &pMotion->aPartsMotion[nCntParts];

					// �R�}���h����������
					pPartsMotion->nCommandNum = 0;

					// ���i���̃��[�V�����̏��̓ǂݍ��݂��J�n
					while (1)
					{
						fscanf(pFile, "%s", aDataSearch); // ����

						if (!strcmp(aDataSearch, "PARTS_END"))
						{// ���i�̃J�E���g�����Z���A�ǂݍ��݂��I��
							nCntParts++;
							break;
						}
						else if (!strcmp(aDataSearch, "TIME"))
						{
							// �R�}���h��
							int nCmdNum = pPartsMotion->nCommandNum;
							// �R�}���h�J�n����
							fscanf(pFile, "%d", &pPartsMotion->aCommand[nCmdNum].nTime);

							// �R�}���h�ԍ�
							int nCmd = 0;
							// �R�}���h���x����ǂݎ��
							fscanf(pFile, "%s", aDataSearch);

							// ��������Ń��x���̔�����s��
							for (int nCntLabel = 0; nCntLabel < MOTION3D_COMMAND_LABEL_MAX; nCntLabel++) 
							{
								if (!strcmp(aDataSearch, g_aMotionCommandInfo[nCntLabel].pLabelName))
								{// �����񂪃��x�����ƈ�v���Ă��鎞�A
									// ���x����ݒ�
									pPartsMotion->aCommand[nCmdNum].command = (MOTION3D_COMMAND_LABEL)nCntLabel;
									// �R�}���h�ԍ����w��
									nCmd = nCntLabel;
									break;
								}
							}

							// �����̓ǂݍ��݂������̐����s��
							for (int nCntData = 0; nCntData < g_aMotionCommandInfo[nCmd].nDataNum; nCntData++)
							{
								fscanf(pFile, "%f", &pPartsMotion->aCommand[nCmdNum].aData[nCntData]);
							}

							// �R�}���h�������Z
							pPartsMotion->nCommandNum++;
						}
					}
				}
			}
		}
	}
}

//========================================
// UpdateMotion3D�֐� - ���[�V����(3D)�̍X�V���� -
// Author:RIKU NISHIMURA
//========================================
bool UpdateMotion3D(Motion3DSet motionSet, Parts3DInfo *pPartsInfo, Parts3DSet partsSet)
{
	// ���[�V�����ԍ�
	int nMotion = pPartsInfo->nMotion;

	if (motionSet.aMotion[nMotion].nLoopTime == -1)
	{// ���[�V�����̃��[�v���Ԃ�-1�̎��A
		// �������I������
		return false;
	}

	// ���[�V�����̃A�j���[�V����(3D)�ǂݍ��ݏ���
	LoadMotionAnim3D(motionSet, pPartsInfo, partsSet);

	// ���[�V�����̃A�j���[�V��������
	MotionAnim3D(pPartsInfo, partsSet);

	// ���[�V���������[�v�������t���O
	bool bMotionLoop = false;

	if (++pPartsInfo->nCounterMotion > motionSet.aMotion[nMotion].nLoopTime)
	{// ���[�V�����J�E���^�[�����Z�������ʃ��[�v���ԂɒB�������A
		bMotionLoop = true;	// ���[�V���������[�v�������t���O��^�ɂ���

		if (motionSet.aMotion[nMotion].bLoop)
		{// ���[�v���邩�t���O���^�̎��A
			// ���[�V�����J�E���^�[�����[�v����
			IntLoopControl(&pPartsInfo->nCounterMotion, motionSet.aMotion[nMotion].nLoopTime, 0);
		}
		else
		{// ���[�v���邩�t���O���U�̎��A
			// ���[�V�����J�E���^�[�𐧌�
			IntControl(&pPartsInfo->nCounterMotion, motionSet.aMotion[nMotion].nLoopTime, 0);
		}
	}

	// ���[�V���������[�v�������t���O��Ԃ�
	return bMotionLoop;
}

//========================================
// SetMotion3D�֐� - ���[�V����(3D)�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetMotion3D(Parts3DInfo *pPartsInfo)
{
	if (pPartsInfo->nMotion == pPartsInfo->nMotionOld)
	{// ���ɂ��̃��[�V�����ԍ��ɐݒ肳��Ă��鎞�A
		return;	// �������I������
	}

	// �ߋ��̃��[�V�����ԍ��Ƃ��ĕۑ�
	pPartsInfo->nMotionOld = pPartsInfo->nMotion;
	// ���[�V�����J�E���^�[��������
	pPartsInfo->nCounterMotion = 0;
}