/**
 * @file
 * @brief Font�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief FontDesc�N���X
 */
class FontDesc : public tml::graphic::ResourceDesc
{
public:

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	FontDesc();
	virtual ~FontDesc();

	virtual void Init(void);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::FontDesc::Release(void)
{
	tml::graphic::ResourceDesc::Release();

	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Font�N���X
 */
class Font : public tml::graphic::Resource
{
public: Font(const tml::graphic::Font &) = delete;
public: tml::graphic::Font &operator =(const tml::graphic::Font &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

protected:
	void Release(void);

public:
	Font();
	virtual ~Font();

	virtual void Init(void);
	INT Create(const tml::graphic::FontDesc &);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::Font::Release(void)
{
	tml::graphic::Resource::Release();

	return;
}
