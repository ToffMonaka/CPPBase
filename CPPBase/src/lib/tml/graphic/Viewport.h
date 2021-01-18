/**
 * @file
 * @brief Viewportヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#pragma warning(push)
#pragma warning(disable: 4005)
#include <d3d11.h>
#include <d3dx11.h>
#pragma warning(pop)
#include "../math/XNAMath.h"


namespace tml {
namespace graphic {
/**
 * @brief Viewportクラス
 */
class Viewport : public CD3D11_VIEWPORT
{
public:
	Viewport();
	Viewport(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
	Viewport(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
	Viewport(const CD3D11_VIEWPORT &);
	tml::graphic::Viewport &operator =(const CD3D11_VIEWPORT &);
	virtual ~Viewport();

	virtual void Init(void);

	void Set(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
	void Set(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
};
}
}


/**
 * @brief Set関数
 * @param pos (position)
 * @param size (size)
 */
inline void tml::graphic::Viewport::Set(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size)
{
	this->TopLeftX = pos.x;
	this->TopLeftY = pos.y;
	this->Width = size.x;
	this->Height = size.y;
	this->MinDepth = D3D11_MIN_DEPTH;
	this->MaxDepth = D3D11_MAX_DEPTH;

	return;
}


/**
 * @brief Set関数
 * @param pos (position)
 * @param size (size)
 * @param depth (depth)
 */
inline void tml::graphic::Viewport::Set(const tml::XMFLOAT2EX &pos, const tml::XMFLOAT2EX &size, const tml::XMFLOAT2EX &depth)
{
	this->TopLeftX = pos.x;
	this->TopLeftY = pos.y;
	this->Width = size.x;
	this->Height = size.y;
	this->MinDepth = depth.x;
	this->MaxDepth = depth.y;

	return;
}
