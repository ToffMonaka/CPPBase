/**
 * @file
 * @brief Canvas2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Canvas.h"


namespace tml {
namespace graphic {
/**
 * @brief Canvas2DDescクラス
 */
class Canvas2DDesc : public tml::graphic::CanvasDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	Canvas2DDesc();
	virtual ~Canvas2DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Canvas2DDesc::Release(void)
{
	tml::graphic::CanvasDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Canvas2Dクラス
 */
class Canvas2D : public tml::graphic::Canvas
{
public: Canvas2D(const tml::graphic::Canvas2D &) = delete;
public: tml::graphic::Canvas2D &operator =(const tml::graphic::Canvas2D &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	Canvas2D();
	virtual ~Canvas2D();

	virtual void Init(void);
	INT Create(const tml::graphic::Canvas2DDesc &);
};
}
}
