//========================================
// 
// �􉽊w�֘A�̏���
// Author:RIKU NISHIMURA
// 
//========================================
// *** geometry.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//========================================
// FindDistance�֐� - 2�_�̋��������߂� -
// Author:RIKU NISHIMURA
//========================================
float FindDistance(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	float x = pos1.x - pos2.x;	// ��������X��
	float y = pos1.y - pos2.y;	// ��������Y��
	float z = pos1.z - pos2.z;	// ��������Z��

	// 2�_�̋�����Ԃ�
	return sqrtf((x * x) + (y * y) + (z * z));
}

//========================================
// FindDistanceLookDown�֐� - 2�_�̋��������߂�(�����낵�) -
// Author:RIKU NISHIMURA
//========================================
float FindDistanceLookDown(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2)
{
	float x = pos1.x - pos2.x;	// ��������X��
	float z = pos1.z - pos2.z;	// ��������Z��

	// 2�_�̋�����Ԃ�
	return sqrtf((x * x) + (z * z));
}

//========================================
// FindAngle�֐� - 2�_�̊p�x�����߂� -
// Author:RIKU NISHIMURA
//========================================
float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos)
{
	float fAngle;	// �p�x

	fAngle = atan2f(targetPos.y - pos.y, targetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1;

	return fAngle;
}

//========================================
// FindAngleLookDown�֐� - 2�_�̊p�x�����߂�(�����낵�) -
// Author:RIKU NISHIMURA
//========================================
float FindAngleLookDown(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos)
{
	float fAngle;	// �p�x

	fAngle = atan2f(targetPos.z - pos.z, targetPos.x - pos.x);

	fAngle -= (D3DX_PI * 0.5f);
	fAngle *= -1;

	return fAngle;
}

//========================================
// FindIntersectionPointLookDown�֐� - ��_�����߂�(�����낵) -
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 FindIntersectionPointLookDown(D3DXVECTOR3 posA1, D3DXVECTOR3 posA2, D3DXVECTOR3 posB1, D3DXVECTOR3 posB2)
{
	D3DXVECTOR3 vB1B2 = posB2 - posB1;	// �x�N�g��B1��B2
	D3DXVECTOR3 vA1A2 = posA2 - posA1;	// �x�N�g��A1��A2
	D3DXVECTOR3 vA2B1 = posB1 - posA2;	// �x�N�g��A2��B1
	D3DXVECTOR3 vB1A1 = posA1 - posB1;	// �x�N�g��B1��A1

										// �ʐ�S1
	float fAreaS1 = ((vB1B2.x * vB1A1.z) - (vB1B2.z * vB1A1.x)) * 0.5f;
	// �ʐ�S2
	float fAreaS2 = ((vB1B2.x * vA2B1.z) - (vB1B2.z * vA2B1.x)) * 0.5f;

	// �ʐ�S1�̊���
	float fRate = (fAreaS1 / (fAreaS1 + fAreaS2));

	// ��_�̍��W��Ԃ�
	return	D3DXVECTOR3(
		posA1.x + (vA1A2.x * fRate),
		0.0f,
		posA1.z + (vA1A2.z * fRate));
}

//========================================
// AngleDifference�֐� - �p�x�̍������߂� -
// Author:RIKU NISHIMURA
//========================================
float AngleDifference(float fAngle, float fTargetAngle)
{
	float fAngleDifference = 0.0f;	// �p�x�̍�

	// �p�x�𐧌䂷��
	ControlAngle(&fAngle);

	if ((fAngle >= 0.0f) && (fTargetAngle >= 0.0f))
	{// �ǂ���̊p�x���v���X�̎��A
		// �p�x�̍���ݒ�
		fAngleDifference = fTargetAngle - fAngle;

		return fAngleDifference;
	}
	else if ((fAngle <= 0.0f) && (fTargetAngle <= 0.0f))
	{// �ǂ���̊p�x���}�C�i�X�̎��A
		// �p�x�̍���ݒ�
		fAngleDifference = fTargetAngle - fAngle;

		return fAngleDifference;
	}

	if ((fAngle >= 0.0f) && (fTargetAngle <= 0.0f))
	{// �p�x���v���X�ŁA�ڕW�p�x���}�C�i�X�̎��A
		if (fAngle - D3DX_PI <= fTargetAngle)
		{// �ڕW�p�x�������ɋ߂����A
			// �p�x�̍���ݒ�
			fAngleDifference = fTargetAngle - fAngle;
		}
		else if (fAngle - D3DX_PI >= fTargetAngle)
		{// �ڕW�p�x���㑤�ɋ߂����A
			// �p�x�̍���ݒ�
			fAngleDifference = (D3DX_PI - fAngle) + (D3DX_PI + fTargetAngle);
		}
	}

	if ((fAngle <= 0.0f) && (fTargetAngle >= 0.0f))
	{// �p�x���}�C�i�X�ŁA�ڕW�p�x���v���X�̎��A
		if (fAngle + D3DX_PI >= fTargetAngle)
		{// �ڕW�p�x�������ɋ߂����A
			// �p�x�̍���ݒ�
			fAngleDifference = fTargetAngle - fAngle;
		}
		else if (fAngle + D3DX_PI <= fTargetAngle)
		{// �ڕW�p�x���㑤�ɋ߂����A
			// �p�x�̍���ݒ�
			fAngleDifference = -(D3DX_PI + fAngle) - (D3DX_PI - fTargetAngle);
		}
	}

	return fAngleDifference;
}

//========================================
// ControlAngle�֐� - �p�x�𐧌䂷�� -
// Author:RIKU NISHIMURA
//========================================
void ControlAngle(float *pAngle)
{
	if (*pAngle > D3DX_PI)
	{// �v���X�̉~�����������Ă��鎞�A
		*pAngle = (D3DX_PI - (*pAngle - D3DX_PI)) * -1;
	}
	else if (*pAngle < -D3DX_PI)
	{// �}�C�i�X�̉~������������Ă��鎞�A
		*pAngle = (D3DX_PI + (*pAngle + D3DX_PI));
	}
}

//========================================
// ConvertAngleToDirection�֐� - �p�x���w�肳�ꂽ�������̕����ɕϊ����� -
// Author:RIKU NISHIMURA
//========================================
float ConvertAngleToDirection(float fAngle, int nDiv)
{
	float fRange = ((D3DX_PI * 2) / nDiv);	// �������̊p�x��

	for (int nCntDirection = 0; nCntDirection < nDiv + 1; nCntDirection++)
	{
		if ((fAngle >= -D3DX_PI - (fRange * 0.5f) + (fRange * nCntDirection))
			&&
			(fAngle <= -D3DX_PI + (fRange * 0.5f) + (fRange * nCntDirection)))
		{// �J�E���g�̕����̊p�x���̓����̎��A�p�x��ݒ�
			fAngle = -D3DX_PI + (fRange * nCntDirection);
			break;	// �J��Ԃ������𔲂���
		}
	}

	return fAngle;
}

//========================================
// ConvPosLookDown�֐� - �ʒu�������낵��ɕϊ�����(Z��Y) -
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 ConvPosLookDown(D3DXVECTOR3 pos)
{
	float fYTemp = pos.y;
	pos.y = -pos.z;
	pos.z = fYTemp;

	return pos;
}

//========================================
// ConvRotLookDown�֐� - �����������낵��ɕϊ�����(Z��Y) -
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 ConvRotLookDown(D3DXVECTOR3 rot)
{
	float fYTemp = rot.y;
	rot.y = -rot.z;
	rot.y *= -1;
	rot.y -= D3DX_PI;
	rot.z = fYTemp;
	rot.z += D3DX_PI;
	rot.z *= -1;

	return rot;
}

//========================================
// RotControl�֐� - �����𐧌䂷�� -
// Author:RIKU NISHIMURA
//========================================
void RotControl(D3DXVECTOR3 *pRot)
{
	FloatLoopControl(&pRot->x, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->y, D3DX_PI, -D3DX_PI);
	FloatLoopControl(&pRot->z, D3DX_PI, -D3DX_PI);
}

//========================================
// FindNormalVector�֐� - ���������ɖ@���x�N�g�������߂� -
// Author:RIKU NISHIMURA
//========================================
D3DXVECTOR3 FindNormalVector(D3DXVECTOR3 rot)
{
	// �e������̉�]���s����]�s����쐬
	float sx = sinf(rot.x);
	float cx = cosf(rot.x);
	float sy = sinf(rot.y);
	float cy = cosf(rot.y);
	float sz = sinf(rot.z);
	float cz = cosf(rot.z);

	// �e������̉�]�s��������āA�@���x�N�g�������߂�
	return D3DXVECTOR3(
		cy * cz,
		(-cx * sz) + (sx * sy * cz),
		(sx * sz) + (cx * sy * cz));
}