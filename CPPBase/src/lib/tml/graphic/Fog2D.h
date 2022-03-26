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
	tml::XMFLOAT4EX color;
	tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE effect_type;

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
	const tml::graphic::Fog2DDesc *desc_;
	tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE effect_type_;

public:
	tml::Transform2D transform;
	tml::XMFLOAT4EX color;
	tml::graphic::DRAW_FOG_2D_DATA *draw_data;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Fog2D();
	virtual ~Fog2D();

	virtual void Init(void);

	const tml::graphic::Fog2DDesc *GetDesc(void) const;
	tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE GetEffectType(void) const;

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
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::Fog2DDesc *tml::graphic::Fog2D::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetEffectType関数
 * @return effect_type (effect_type)
 */
inline tml::ConstantUtil::GRAPHIC::FOG_2D_EFFECT_TYPE tml::graphic::Fog2D::GetEffectType(void) const
{
	return (this->effect_type_);
}
