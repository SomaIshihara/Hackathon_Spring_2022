//========================================
// 
// �e�L�X�g(3D)�̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** text3D.cpp ***
//========================================
// R.N.Lib
#include "../../R.N.Lib.h"

//================================================================================
//----------|---------------------------------------------------------------------
//==========| h�t�@�C���̋��L�֐�
//----------|---------------------------------------------------------------------
//================================================================================

//============================================================
//--------------------| *** �ݒ� *** |------------------------
//============================================================

//========================================
// SetText3D�֐� - �e�L�X�g(3D)�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetText3D(Text3DSet text3DSet)
{
	// ������̃|�C���^
	char *pString = text3DSet.pString;

	for (int nCntDigit = 0; nCntDigit < strlen(pString); nCntDigit++)
	{
		if (pString[nCntDigit] == ' ')
		{// �J�E���g�̕������󔒂̎��A
			continue;	// �܂�Ԃ�
		}

		// �ݒ�ʒu
		D3DXVECTOR3 setPos = INITD3DXVECTOR3;
		// �t�H���g�̏��
		Font font = GetFont(text3DSet.nFont);
		// �Ԋu�䗦
		float fSpaceRate = (float)font.nSpaceNum / (float)font.nSpaceDenom;
		float fWidth = text3DSet.fWidth;	// ��
		float fHeight = text3DSet.fHeight;	// ����

		// �\���`���ɉ������ݒ�ʒu�̐ݒ�
		switch (text3DSet.disp)
		{
		case TEXT_DISP_CENTER:
			// �ݒ�ʒu�ɕ����̍ŏI�I�Ȓ����̔��������Z
			setPos.x -= ((fWidth * fSpaceRate) * strlen(pString)) * 0.5f;
			// �ݒ�ʒu�ɔz�u�ԊuX��K�p(���Z)
			setPos.x += ((float)nCntDigit + 0.5f) * (fWidth * fSpaceRate);
			break;
		case TEXT_DISP_LEFT:
			// �ݒ�ʒu�ɔz�u�ԊuX��K�p(���Z)
			setPos.x += nCntDigit * (fWidth * fSpaceRate);
			break;
		case TEXT_DISP_RIGHT:
			// �ݒ�ʒu�ɕ����̍ŏI�I�Ȓ��������Z
			setPos.x -= (fWidth * fSpaceRate) * (strlen(pString) - 1);
			// �ݒ�ʒu�ɔz�u�ԊuX��K�p(���Z)
			setPos.x += nCntDigit * (fWidth * fSpaceRate);
			break;
		}

		// �ʒu�ƌ������}�g���b�N�X�ϊ�
		D3DXMATRIX baseMtx = ConvPosRotToMatrix(text3DSet.pos, text3DSet.rot);
		D3DXMATRIX txtMtx = ConvPosRotToMatrix(setPos, INITD3DXVECTOR3);

		// ��}�g���b�N�X�ƃe�L�X�g�}�g���b�N�X���|�����킹��
		D3DXMATRIX resultMtx = MultiplyMatrix(baseMtx, txtMtx);

		// �|���S��(3D)�̐ݒ���
		Polygon3DSet polySet;
		/* �e�N�X�`���ԍ�	*/polySet.nTex = font.nTex;
		/* �p�^�[���ԍ�		*/polySet.nPtn = (int)pString[nCntDigit] - (int)font.cStartChar;
		/* �p�^�[�����X	*/polySet.nPtnX = font.nPtnWidth;
		/* �p�^�[�����Y	*/polySet.nPtnY = font.nPtnHeight;
		/* ��				*/polySet.fWidth = fWidth;
		/* ����				*/polySet.fHeight = fHeight;
		/* �ʒu				*/polySet.pos = ConvMatrixToPos(resultMtx);
		/* ����				*/polySet.rot = text3DSet.rot;
		/* �F				*/polySet.col = text3DSet.col;
		// �|���S��(3D)��ݒ�
		SetPolygon3D(polySet);
	}
}