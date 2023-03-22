//========================================
// 
// �e�L�X�g(2D)�̏���
// Author:RIKU NISHIMURA
// 
//========================================
//  *** text2D.cpp ***
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
// SetText2D�֐� - �e�L�X�g(2D)�̐ݒ菈�� -
// Author:RIKU NISHIMURA
//========================================
void SetText2D(Text2DSet text2DSet)
{
	// ������̃|�C���^
	char *pString = text2DSet.pString;

	for (int nCntDigit = 0; nCntDigit < strlen(pString); nCntDigit++)
	{
		if (pString[nCntDigit] == ' ') 
		{// �J�E���g�̕������󔒂̎��A
			continue;	// �܂�Ԃ�
		}

		// �ݒ�ʒu
		D3DXVECTOR3 setPos = INITD3DXVECTOR3;
		// �t�H���g�̏��
		Font font = GetFont(text2DSet.nFont);
		// �Ԋu�䗦
		float fSpaceRate = (float)font.nSpaceNum / (float)font.nSpaceDenom;
		float fWidth = text2DSet.fWidth;	// ��
		float fHeight = text2DSet.fHeight;	// ����

		// �\���`���ɉ������ݒ�ʒu�̐ݒ�
		switch (text2DSet.disp)
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
		D3DXMATRIX baseMtx = ConvPosRotToMatrix(text2DSet.pos, text2DSet.rot);
		D3DXMATRIX txtMtx = ConvPosRotToMatrix(setPos, INITD3DXVECTOR3);

		// ��}�g���b�N�X�ƃe�L�X�g�}�g���b�N�X���|�����킹��
		D3DXMATRIX resultMtx = MultiplyMatrix(baseMtx, txtMtx);

		// �|���S��(2D)�̐ݒ���
		Polygon2DSet polySet;
		/* �e�N�X�`���ԍ�	*/polySet.nTex = font.nTex;
		/* �p�^�[���ԍ�		*/polySet.nPtn = (int)pString[nCntDigit] - (int)font.cStartChar;
		/* �p�^�[�����X	*/polySet.nPtnX = font.nPtnWidth;
		/* �p�^�[�����Y	*/polySet.nPtnY = font.nPtnHeight;
		/* ��				*/polySet.fWidth = fWidth;
		/* ����				*/polySet.fHeight = fHeight;
		/* �ʒu				*/polySet.pos = ConvMatrixToPos(resultMtx);
		/* ����				*/polySet.rot = ConvMatrixToPos(resultMtx) + D3DXVECTOR3(0.0f,0.0f,D3DX_PI);
		/* �F				*/polySet.col = text2DSet.col;
		/* �J�������킹		*/polySet.bMatchCamera = text2DSet.bMatchCamera;
		// �|���S��(2D)��ݒ�
		SetPolygon2D(polySet);
	}
}