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
	tml::XMPosition3D position;
	tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE effect_type;
	tml::XMFLOAT3EX color;

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

public:
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::FOG_TYPE::_3D);

private:
	tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE effect_type_;
	tml::XMFLOAT3EX col_;

public:
	tml::XMPosition3D position;
	tml::graphic::DRAW_FOG_3D_DATA *draw_data;

private:
	void Release(void);

public:
	Fog3D();
	virtual ~Fog3D();

	virtual void Init(void);
	INT Create(const tml::graphic::Fog3DDesc &);

	tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE GetEffectType(void) const;
	const tml::XMFLOAT3EX &GetColor(void) const;
	void SetColor(const tml::XMFLOAT3EX &);

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


/**
 * @brief GetColor関数
 * @return col (color)
 */
inline const tml::XMFLOAT3EX &tml::graphic::Fog3D::GetColor(void) const
{
	return (this->col_);
}


/**
 * @brief SetColor関数
 * @param col (color)
 */
inline void tml::graphic::Fog3D::SetColor(const tml::XMFLOAT3EX &col)
{
	this->col_ = col;

	return;
}
