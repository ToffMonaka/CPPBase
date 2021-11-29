/**
 * @file
 * @brief Light3Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Light.h"


namespace tml {
namespace graphic {
struct DRAW_LIGHT_3D_DATA_;
typedef DRAW_LIGHT_3D_DATA_ DRAW_LIGHT_3D_DATA;
}
}


namespace tml {
namespace graphic {
/**
 * @brief Light3DDescクラス
 */
class Light3DDesc : public tml::graphic::LightDesc
{
public:
	tml::Transform3D transform;
	tml::XMFLOAT4EX color;
	tml::ConstantUtil::GRAPHIC::LIGHT_3D_EFFECT_TYPE effect_type;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Light3DDesc();
	virtual ~Light3DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Light3DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Light3Dクラス
 */
class Light3D : public tml::graphic::Light
{
public: Light3D(const tml::graphic::Light3D &) = delete;
public: tml::graphic::Light3D &operator =(const tml::graphic::Light3D &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::ConstantUtil::GRAPHIC::LIGHT_3D_EFFECT_TYPE effect_type_;

public:
	tml::Transform3D transform;
	tml::XMFLOAT4EX color;
	tml::graphic::DRAW_LIGHT_3D_DATA *draw_data;

private:
	void Release(void);

public:
	Light3D();
	virtual ~Light3D();

	virtual void Init(void);
	INT Create(const tml::graphic::Light3DDesc &);

	tml::ConstantUtil::GRAPHIC::LIGHT_3D_EFFECT_TYPE GetEffectType(void) const;

	virtual void DrawStageInit(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Light3D::Release(void)
{
	return;
}


/**
 * @brief GetEffectType関数
 * @return effect_type (effect_type)
 */
inline tml::ConstantUtil::GRAPHIC::LIGHT_3D_EFFECT_TYPE tml::graphic::Light3D::GetEffectType(void) const
{
	return (this->effect_type_);
}
