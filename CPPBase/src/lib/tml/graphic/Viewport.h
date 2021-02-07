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
protected:
	void Release(void);

public:
	Viewport();
	Viewport(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
	Viewport(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
	Viewport(const CD3D11_VIEWPORT &);
	tml::graphic::Viewport &operator =(const CD3D11_VIEWPORT &);
	virtual ~Viewport();

	virtual void Init(void);
	virtual void Init(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
	virtual void Init(const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &, const tml::XMFLOAT2EX &);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Viewport::Release(void)
{
	return;
}
