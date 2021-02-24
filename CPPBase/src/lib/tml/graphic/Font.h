/**
 * @file
 * @brief Font�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMath.h"
#include "Resource.h"


namespace tml {
namespace graphic {
/**
 * @brief FontDesc�N���X
 */
class FontDesc : public tml::graphic::ResourceDesc
{
public:
	LOGFONT font_desc;

protected:
	void Release(void);

	virtual INT ReadValue(const tml::INIFile &);

public:
	FontDesc();
	virtual ~FontDesc();

	virtual void Init(void);

	void SetFontDesc(const XMUINT2EX &, const WCHAR *);
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
	HDC dc_handle_;
	HFONT font_handle_;
	LOGFONT font_desc_;
	TEXTMETRIC tm_;

protected:
	void Release(void);

public:
	Font();
	virtual ~Font();

	virtual void Init(void);
	INT Create(const tml::graphic::FontDesc &);

	HDC GetDeviceContextHandle(void) const;
	HFONT GetFontHandle(void) const;
	const LOGFONT &GetFontDesc(void) const;
	const TEXTMETRIC &GetTextMetric(void) const;
};
}
}


/**
 * @brief GetDeviceContextHandle�֐�
 * @return dc_handle (device_context_handle)
 */
inline HDC tml::graphic::Font::GetDeviceContextHandle(void) const
{
	return (this->dc_handle_);
}


/**
 * @brief GetFontHandle�֐�
 * @return font_handle (font_handle)
 */
inline HFONT tml::graphic::Font::GetFontHandle(void) const
{
	return (this->font_handle_);
}


/**
 * @brief GetFontDesc�֐�
 * @return font_desc (font_desc)
 */
inline const LOGFONT &tml::graphic::Font::GetFontDesc(void) const
{
	return (this->font_desc_);
}


/**
 * @brief GetTextMetric�֐�
 * @return txt_metric (text_metric)
 */
inline const TEXTMETRIC &tml::graphic::Font::GetTextMetric(void) const
{
	return (this->tm_);
}
