/**
 * @file
 * @brief Viewportコードファイル
 */


#include "Viewport.h"


/**
 * @brief コンストラクタ
 */
tml::Viewport::Viewport() :
	vp_(0.0f, 0.0f, 0.0f, 0.0f, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param pos (position)
 * @param size (size)
 */
tml::Viewport::Viewport(const XMFLOAT2 &pos, const XMFLOAT2 &size) :
	vp_(pos.x, pos.y, size.x, size.y, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Viewport::~Viewport()
{
	return;
}


/**
 * @brief 初期化関数
 */
void tml::Viewport::Init(void)
{
	this->vp_ = CD3D11_VIEWPORT(0.0f, 0.0f, 0.0f, 0.0f, D3D11_MIN_DEPTH, D3D11_MAX_DEPTH);

	return;
}
