/**
 * @file
 * @brief Light2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Light.h"


namespace tml {
namespace graphic {
struct DRAW_LIGHT_2D_DATA_;
typedef DRAW_LIGHT_2D_DATA_ DRAW_LIGHT_2D_DATA;
}
}


namespace tml {
namespace graphic {
/**
 * @brief Light2DDescクラス
 */
class Light2DDesc : public tml::graphic::LightDesc
{
public:
	tml::XMPosition2D position;
	tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE effect_type;
	tml::XMFLOAT3EX color;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Light2DDesc();
	virtual ~Light2DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Light2DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Light2Dクラス
 */
class Light2D : public tml::graphic::Light
{
public: Light2D(const tml::graphic::Light2D &) = delete;
public: tml::graphic::Light2D &operator =(const tml::graphic::Light2D &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::_2D);

private:
	tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE effect_type_;
	tml::XMFLOAT3EX col_;

public:
	tml::XMPosition2D position;
	tml::graphic::DRAW_LIGHT_2D_DATA *draw_data;

private:
	void Release(void);

public:
	Light2D();
	virtual ~Light2D();

	virtual void Init(void);
	INT Create(const tml::graphic::Light2DDesc &);

	tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE GetEffectType(void) const;
	const tml::XMFLOAT3EX &GetColor(void) const;
	void SetColor(const tml::XMFLOAT3EX &);

	virtual void DrawStageInit(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Light2D::Release(void)
{
	return;
}


/**
 * @brief GetEffectType関数
 * @return effect_type (effect_type)
 */
inline tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE tml::graphic::Light2D::GetEffectType(void) const
{
	return (this->effect_type_);
}


/**
 * @brief GetColor関数
 * @return col (color)
 */
inline const tml::XMFLOAT3EX &tml::graphic::Light2D::GetColor(void) const
{
	return (this->col_);
}


/**
 * @brief SetColor関数
 * @param col (color)
 */
inline void tml::graphic::Light2D::SetColor(const tml::XMFLOAT3EX &col)
{
	this->col_ = col;

	return;
}
