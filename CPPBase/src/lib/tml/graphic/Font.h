/**
 * @file
 * @brief Font�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../math/XNAMathVector.h"
#include "ManagerResource.h"


namespace tml {
namespace graphic {
class Font;
}
}


namespace tml {
namespace graphic {
/**
 * @brief FontBitmap�N���X
 */
class FontBitmap
{
friend class tml::graphic::Font;

private:
	WCHAR code_;
	GLYPHMETRICS gm_;
	tml::DynamicBuffer buf_;

private:
	void Release(void);

public:
	FontBitmap();
	virtual ~FontBitmap();

	virtual void Init(void);
	INT Create(const HDC, const WCHAR);

	WCHAR GetCode(void) const;
	const GLYPHMETRICS &GetGlyphMetrics(void) const;
	const tml::DynamicBuffer &GetBuffer(void) const;
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::FontBitmap::Release(void)
{
	return;
}


/**
 * @brief GetCode�֐�
 * @return code (code)
 */
inline WCHAR tml::graphic::FontBitmap::GetCode(void) const
{
	return (this->code_);
}


/**
 * @brief GetGlyphMetrics�֐�
 * @return gm (glyph_metrics)
 */
inline const GLYPHMETRICS &tml::graphic::FontBitmap::GetGlyphMetrics(void) const
{
	return (this->gm_);
}


/**
 * @brief GetBuffer�֐�
 * @return buf (buffer)
 */
inline const tml::DynamicBuffer &tml::graphic::FontBitmap::GetBuffer(void) const
{
	return (this->buf_);
}


namespace tml {
namespace graphic {
/**
 * @brief FontDesc�N���X
 */
class FontDesc : public tml::graphic::ManagerResourceDesc
{
public:
	LOGFONT font_desc;

private:
	void Release(void);

protected:
	virtual INT ReadValue(const tml::INIFile &);

public:
	FontDesc();
	virtual ~FontDesc();

	virtual void Init(void);

	void SetFontDesc(const tml::XMUINT2EX &, const WCHAR *);
};
}
}


/**
 * @brief Release�֐�
 */
inline void tml::graphic::FontDesc::Release(void)
{
	return;
}


namespace tml {
namespace graphic {
/**
 * @brief Font�N���X
 */
class Font : public tml::graphic::ManagerResource
{
public: Font(const tml::graphic::Font &) = delete;
public: tml::graphic::Font &operator =(const tml::graphic::Font &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	static const UINT RESOURCE_MAIN_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::FONT);
	static const UINT RESOURCE_SUB_INDEX = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::FONT_TYPE::BASE);

private:
	HDC dc_handle_;
	HFONT font_handle_;
	LOGFONT font_desc_;
	TEXTMETRIC tm_;
	std::map<WCHAR, tml::graphic::FontBitmap> bm_cont_;

private:
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
	const tml::graphic::FontBitmap *GetBitmap(const WCHAR);
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
