/**
 * @file
 * @brief Viewport�R�[�h�t�@�C��
 */


#include "Viewport.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Viewport::Viewport() :
	vp_(0.0f, 0.0f, 0.0f, 0.0f, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 * @param pos (position)
 * @param size (size)
 */
tml::graphic::Viewport::Viewport(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size) :
	vp_(pos.x, pos.y, size.x, size.y, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Viewport::~Viewport()
{
	return;
}


/**
 * @brief �������֐�
 */
void tml::graphic::Viewport::Init(void)
{
	this->vp_ = CD3D11_VIEWPORT(0.0f, 0.0f, 0.0f, 0.0f, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH);

	return;
}
