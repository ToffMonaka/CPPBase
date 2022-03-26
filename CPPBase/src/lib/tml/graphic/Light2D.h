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
	tml::Transform2D transform;
	tml::XMFLOAT4EX color;
	tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE effect_type;

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

private:
	const tml::graphic::Light2DDesc *desc_;
	tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE effect_type_;

public:
	tml::Transform2D transform;
	tml::XMFLOAT4EX color;
	tml::graphic::DRAW_LIGHT_2D_DATA *draw_data;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Light2D();
	virtual ~Light2D();

	virtual void Init(void);

	const tml::graphic::Light2DDesc *GetDesc(void) const;
	tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE GetEffectType(void) const;

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
 * @brief GetDesc関数
 * @return desc (desc)
 */
inline const tml::graphic::Light2DDesc *tml::graphic::Light2D::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetEffectType関数
 * @return effect_type (effect_type)
 */
inline tml::ConstantUtil::GRAPHIC::LIGHT_2D_EFFECT_TYPE tml::graphic::Light2D::GetEffectType(void) const
{
	return (this->effect_type_);
}
