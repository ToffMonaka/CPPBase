/**
 * @file
 * @brief Viewport�R�[�h�t�@�C��
 */


#include "Viewport.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Viewport::Viewport() :
	vp_(0.0f, 0.0f, 1.0f, 1.0f)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 * @param vp (viewport)
 */
tml::graphic::Viewport::Viewport(const CD3D11_VIEWPORT &vp)
{
	this->vp_ = vp;

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param x (x)
 * @param y (y)
 * @param w (width)
 * @param h (height)
 */
tml::graphic::Viewport::Viewport(const FLOAT x, const FLOAT y, const FLOAT w, const FLOAT h) :
	vp_(x, y, w, h)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 * @param x (x)
 * @param y (y)
 * @param w (width)
 * @param h (height)
 * @param min_depth (min_depth)
 * @param max_depth (max_depth)
 */
tml::graphic::Viewport::Viewport(const FLOAT x, const FLOAT y, const FLOAT w, const FLOAT h, const FLOAT min_depth, const FLOAT max_depth) :
	vp_(x, y, w, h, min_depth, max_depth)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 * @param src (src)
 */
tml::graphic::Viewport::Viewport(const tml::graphic::Viewport &src)
{
	this->vp_ = src.vp_;

	return;
}


/**
 * @brief operator =�֐�
 * @param src (src)
 * @return this (this)
 */
tml::graphic::Viewport &tml::graphic::Viewport::operator =(const tml::graphic::Viewport &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->vp_ = src.vp_;

	return ((*this));
}


/**
 * @brief �R���X�g���N�^
 * @param src (src)
 */
tml::graphic::Viewport::Viewport(tml::graphic::Viewport &&src) noexcept
{
	this->vp_ = src.vp_;

	src.Init();

	return;
}


/**
 * @brief operator =�֐�
 * @param src (src)
 * @return this (this)
 */
tml::graphic::Viewport &tml::graphic::Viewport::operator =(tml::graphic::Viewport &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->vp_ = src.vp_;

	src.Init();

	return ((*this));
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Viewport::~Viewport()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Viewport::Init(void)
{
	this->Release();

	this->vp_ = CD3D11_VIEWPORT(0.0f, 0.0f, 1.0f, 1.0f);

	return;
}


/**
 * @brief Init�֐�
 * @param vp (viewport)
 */
void tml::graphic::Viewport::Init(const CD3D11_VIEWPORT &vp)
{
	this->Release();

	this->vp_ = vp;

	return;
}


/**
 * @brief Init�֐�
 * @param x (x)
 * @param y (y)
 * @param w (width)
 * @param h (height)
 */
void tml::graphic::Viewport::Init(const FLOAT x, const FLOAT y, const FLOAT w, const FLOAT h)
{
	this->Release();

	this->vp_ = CD3D11_VIEWPORT(x, y, w, h);

	return;
}


/**
 * @brief Init�֐�
 * @param x (x)
 * @param y (y)
 * @param w (width)
 * @param h (height)
 * @param min_depth (min_depth)
 * @param max_depth (max_depth)
 */
void tml::graphic::Viewport::Init(const FLOAT x, const FLOAT y, const FLOAT w, const FLOAT h, const FLOAT min_depth, const FLOAT max_depth)
{
	this->Release();

	this->vp_ = CD3D11_VIEWPORT(x, y, w, h, min_depth, max_depth);

	return;
}
