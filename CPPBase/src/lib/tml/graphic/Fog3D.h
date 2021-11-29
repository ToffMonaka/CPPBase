/**
 * @file
 * @brief Fog3Dヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Fog.h"


namespace tml {
namespace graphic {
struct DRAW_FOG_3D_DATA_;
typedef DRAW_FOG_3D_DATA_ DRAW_FOG_3D_DATA;
}
}


namespace tml {
namespace graphic {
/**
 * @brief Fog3DDescクラス
 */
class Fog3DDesc : public tml::graphic::FogDesc
{
public:
	tml::Transform3D transform;
	tml::XMFLOAT4EX color;
	tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE effect_type;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	Fog3DDesc();
	virtual ~Fog3DDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Fog3DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Fog3Dクラス
 */
class Fog3D : public tml::graphic::Fog
{
public: Fog3D(const tml::graphic::Fog3D &) = delete;
public: tml::graphic::Fog3D &operator =(const tml::graphic::Fog3D &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE effect_type_;

public:
	tml::Transform3D transform;
	tml::XMFLOAT4EX color;
	tml::graphic::DRAW_FOG_3D_DATA *draw_data;

private:
	void Release(void);

public:
	Fog3D();
	virtual ~Fog3D();

	virtual void Init(void);
	INT Create(const tml::graphic::Fog3DDesc &);

	tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE GetEffectType(void) const;

	virtual void DrawStageInit(void);
};
}
}


/**
 * @brief Release関数
 */
inline void tml::graphic::Fog3D::Release(void)
{
	return;
}


/**
 * @brief GetEffectType関数
 * @return effect_type (effect_type)
 */
inline tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE tml::graphic::Fog3D::GetEffectType(void) const
{
	return (this->effect_type_);
}
