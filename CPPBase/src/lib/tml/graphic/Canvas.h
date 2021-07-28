/**
 * @file
 * @brief Canvas�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
/**
 * @brief CanvasDesc�N���X
 */
class CanvasDesc : public tml::graphic::ManagerResourceDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	CanvasDesc();
	virtual ~CanvasDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::CanvasDesc::Release(void)
{
	tml::graphic::ManagerResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Canvas�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Canvas : public tml::graphic::ManagerResource
{
public: Canvas(const tml::graphic::Canvas &) = delete;
public: tml::graphic::Canvas &operator =(const tml::graphic::Canvas &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::CANVAS);

private:
	tml::ConstantUtil::GRAPHIC::CANVAS_TYPE type_;

protected:
	void Release(void);
	INT Create(const tml::graphic::CanvasDesc &, const tml::ConstantUtil::GRAPHIC::CANVAS_TYPE);

public:
	Canvas();
	virtual ~Canvas();

	virtual void Init(void);

	tml::ConstantUtil::GRAPHIC::CANVAS_TYPE GetType(void) const;

	virtual void Draw(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Canvas::Release(void)
{
	tml::graphic::ManagerResource::Release();

	return;
}


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::GRAPHIC::CANVAS_TYPE tml::graphic::Canvas::GetType(void) const
{
	return (this->type_);
}
