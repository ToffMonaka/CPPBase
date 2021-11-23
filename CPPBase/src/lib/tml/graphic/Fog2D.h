/**
 * @file
 * @brief Fog2Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Fog.h"


namespace tml {
namespace graphic {
struct DRAW_FOG_2D_DATA_;
typedef DRAW_FOG_2D_DATA_ DRAW_FOG_2D_DATA;
}
}


namespace tml {
namespace graphic {
/**
 * @brief Fog2DDescクラス
 */
class Fog2DDesc : public tml::graphic::FogDesc
{
public:
	tml::Transform2D transform;
	tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE effect_type;
	tml::XMFLOAT3EX color;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Fog2DDesc();
	virtual ~Fog2DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Fog2DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Fog2Dクラス
 */
class Fog2D : public tml::graphic::Fog
{
public: Fog2D(const tml::graphic::Fog2D &) = delete;
public: tml::graphic::Fog2D &operator =(const tml::graphic::Fog2D &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE effect_type_;
	tml::XMFLOAT3EX col_;

public:
	tml::Transform2D transform;
	tml::graphic::DRAW_FOG_2D_DATA *draw_data;

private:
	void Release(void);

public:
	Fog2D();
	virtual ~Fog2D();

	virtual void Init(void);
	INT Create(const tml::graphic::Fog2DDesc &);

	tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE GetEffectType(void) const;
	const tml::XMFLOAT3EX &GetColor(void) const;
	void SetColor(const tml::XMFLOAT3EX &);

	virtual void DrawStageInit(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Fog2D::Release(void)
{
	return;
}


/**
 * @brief GetEffectType関数
 * @return effect_type (effect_type)
 */
inline tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE tml::graphic::Fog2D::GetEffectType(void) const
{
	return (this->effect_type_);
}


/**
 * @brief GetColor関数
 * @return col (color)
 */
inline const tml::XMFLOAT3EX &tml::graphic::Fog2D::GetColor(void) const
{
	return (this->col_);
}


/**
 * @brief SetColor関数
 * @param col (color)
 */
inline void tml::graphic::Fog2D::SetColor(const tml::XMFLOAT3EX &col)
{
	this->col_ = col;

	return;
}
