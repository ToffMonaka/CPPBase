/**
 * @file
 * @brief Fog3D�w�b�_�[�t�@�C��
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
 * @brief Fog3DDesc�N���X
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
 * @brief Release�֐�
 */
inline void tml::graphic::Fog3DDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Fog3D�N���X
 */
class Fog3D : public tml::graphic::Fog
{
public: Fog3D(const tml::graphic::Fog3D &) = delete;
public: tml::graphic::Fog3D &operator =(const tml::graphic::Fog3D &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	const tml::graphic::Fog3DDesc *desc_;
	tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE effect_type_;

public:
	tml::Transform3D transform;
	tml::XMFLOAT4EX color;
	tml::graphic::DRAW_FOG_3D_DATA *draw_data;

private:
	void Release(void);

protected:
	virtual INT OnCreate(void);
	virtual INT OnCreateDeferred(void);

	virtual void OnSetDesc(const tml::ManagerResourceDesc *);

public:
	Fog3D();
	virtual ~Fog3D();

	virtual void Init(void);

	const tml::graphic::Fog3DDesc *GetDesc(void) const;
	tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE GetEffectType(void) const;

	virtual void DrawStageInit(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Fog3D::Release(void)
{
	return;
}


/**
 * @brief GetDesc�֐�
 * @return desc (desc)
 */
inline const tml::graphic::Fog3DDesc *tml::graphic::Fog3D::GetDesc(void) const
{
	return (this->desc_);
}


/**
 * @brief GetEffectType�֐�
 * @return effect_type (effect_type)
 */
inline tml::ConstantUtil::GRAPHIC::FOG_3D_EFFECT_TYPE tml::graphic::Fog3D::GetEffectType(void) const
{
	return (this->effect_type_);
}
