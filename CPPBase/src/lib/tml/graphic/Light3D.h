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
	tml::XMPosition3D position;
	tml::ConstantUtil::GRAPHIC::LIGHT_3D_EFFECT_TYPE effect_type;
	tml::XMFLOAT3EX color;

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

public:
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::_3D);

private:
	tml::ConstantUtil::GRAPHIC::LIGHT_3D_EFFECT_TYPE effect_type_;
	tml::XMFLOAT3EX col_;

public:
	tml::XMPosition3D position;
	tml::graphic::DRAW_LIGHT_3D_DATA *draw_data;

private:
	void Release(void);

public:
	Light3D();
	virtual ~Light3D();

	virtual void Init(void);
	INT Create(const tml::graphic::Light3DDesc &);

	tml::ConstantUtil::GRAPHIC::LIGHT_3D_EFFECT_TYPE GetEffectType(void) const;
	const tml::XMFLOAT3EX &GetColor(void) const;
	void SetColor(const tml::XMFLOAT3EX &);

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


/**
 * @brief GetColor関数
 * @return col (color)
 */
inline const tml::XMFLOAT3EX &tml::graphic::Light3D::GetColor(void) const
{
	return (this->col_);
}


/**
 * @brief SetColor関数
 * @param col (color)
 */
inline void tml::graphic::Light3D::SetColor(const tml::XMFLOAT3EX &col)
{
	this->col_ = col;

	return;
}
