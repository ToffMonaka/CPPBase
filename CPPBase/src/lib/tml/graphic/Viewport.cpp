/**
 * @file
 * @brief Viewport�R�[�h�t�@�C��
 */


#include "Viewport.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Viewport::Viewport() :
	CD3D11_VIEWPORT(0.0f, 0.0f, 0.0f, 0.0f, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 * @param pos (position)
 * @param size (size)
 */
tml::graphic::Viewport::Viewport(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size) :
	CD3D11_VIEWPORT(pos.x, pos.y, size.x, size.y, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 * @param pos (position)
 * @param size (size)
 * @param depth (depth)
 */
tml::graphic::Viewport::Viewport(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size, const tml::XMFLOAT2EX &depth) :
	CD3D11_VIEWPORT(pos.x, pos.y, size.x, size.y, depth.x, depth.y)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 * @param src (src)
 */
tml::graphic::Viewport::Viewport(const CD3D11_VIEWPORT &src)
{
	this->TopLeftX = src.TopLeftX;
	this->TopLeftY = src.TopLeftY;
	this->Width = src.Width;
	this->Height = src.Height;
	this->MinDepth = src.MinDepth;
	this->MaxDepth = src.MaxDepth;

	return;
}


/**
 * @brief operator =�֐�
 * @param src (src)
 * @return this (this)
 */
tml::graphic::Viewport &tml::graphic::Viewport::operator =(const CD3D11_VIEWPORT &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->TopLeftX = src.TopLeftX;
	this->TopLeftY = src.TopLeftY;
	this->Width = src.Width;
	this->Height = src.Height;
	this->MinDepth = src.MinDepth;
	this->MaxDepth = src.MaxDepth;

	return ((*this));
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
	this->TopLeftX = 0.0f;
	this->TopLeftY = 0.0f;
	this->Width = 0.0f;
	this->Height = 0.0f;
	this->MinDepth = D3D11_MIN_DEPTH;
	this->MaxDepth = D3D11_MAX_DEPTH;

	return;
}
