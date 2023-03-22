//========================================
// 
// �􉽊w�֘A�̃w�b�_�t�@�C��
// Author:RIKU NISHIMURA
// 
//========================================
//  *** geometry.h ***
//========================================
#ifndef _GEOMETRY_H_	// ���̃}�N����`������Ă��Ȃ�������
#define _GEOMETRY_H_	// ��d�C���N���[�h�h�~�̃}�N�����`����

//****************************************
// �v���g�^�C�v�錾
//****************************************
// 2�_�̋��������߂�
float FindDistance(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
// 2�_�̋��������߂�(�����낵�)
float FindDistanceLookDown(D3DXVECTOR3 pos1, D3DXVECTOR3 pos2);
// 2�_�̊p�x�����߂�
float FindAngle(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);
// 2�_�̊p�x�����߂�(�����낵�)
float FindAngleLookDown(D3DXVECTOR3 pos, D3DXVECTOR3 targetPos);
// ��_�̍��W�����߂�(�����낵�)
D3DXVECTOR3 FindIntersectionPointLookDown(D3DXVECTOR3 posA1, D3DXVECTOR3 posA2, D3DXVECTOR3 posB1, D3DXVECTOR3 posB2);
// �p�x�̍������߂�
float AngleDifference(float fAngle, float fTargetAngle);
// �p�x�𐧌䂷��
void ControlAngle(float *pAngle);
// �p�x���w�肳�ꂽ�������̕����ɕϊ�����
float ConvertAngleToDirection(float fAngle, int nDiv);
// �ʒu�������낵��ɕϊ�����(Z��Y)
D3DXVECTOR3 ConvPosLookDown(D3DXVECTOR3 pos);
// �����������낵��ɕϊ�����(Z��Y)
D3DXVECTOR3 ConvRotLookDown(D3DXVECTOR3 rot);
// �����𐧌�
void RotControl(D3DXVECTOR3 *pRot);
// ���������ɖ@���x�N�g�������߂�
D3DXVECTOR3 FindNormalVector(D3DXVECTOR3 rot);

#endif