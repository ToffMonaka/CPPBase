/**
 * @file
 * @brief Fontコードファイル
 */


#include "Font.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::FontDesc::FontDesc()
{
	tml::MemoryUtil::Clear(&this->font_desc, 1U);

	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FontDesc::~FontDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::FontDesc::Init(void)
{
	this->Release();

	tml::MemoryUtil::Clear(&this->font_desc, 1U);

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::FontDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Font Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"FONT");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief SetFontDesc関数
 * @param size (size)
 * @param family (family)
 */
void tml::graphic::FontDesc::SetFontDesc(const XMUINT2EX &size, const WCHAR *family)
{
	tml::MemoryUtil::Clear(&this->font_desc, 1U);

	this->font_desc.lfHeight = -MulDiv(static_cast<LONG>(size.y), GetDeviceCaps(this->manager->GetWindowDeviceContextHandle(), LOGPIXELSY), 72);
	this->font_desc.lfWidth = static_cast<LONG>(size.x);
	this->font_desc.lfEscapement = 0L;
	this->font_desc.lfOrientation = 0L;
	this->font_desc.lfWeight = FW_NORMAL;
	this->font_desc.lfItalic = 0;
	this->font_desc.lfUnderline = 0;
	this->font_desc.lfStrikeOut = 0;
	this->font_desc.lfCharSet = SHIFTJIS_CHARSET;
	this->font_desc.lfOutPrecision = OUT_DEFAULT_PRECIS;
	this->font_desc.lfClipPrecision = CLIP_DEFAULT_PRECIS;
	this->font_desc.lfQuality = PROOF_QUALITY;
	this->font_desc.lfPitchAndFamily = DEFAULT_PITCH | FF_MODERN;
	_snwprintf_s(this->font_desc.lfFaceName, sizeof(this->font_desc.lfFaceName) >> 1, _TRUNCATE, L"%s", family);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::graphic::Font::Font() :
	dc_handle_(nullptr),
	font_handle_(nullptr)
{
	tml::MemoryUtil::Clear(&this->font_desc_, 1U);
	tml::MemoryUtil::Clear(&this->tm_, 1U);

	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Font::~Font()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Font::Release(void)
{
	if (this->font_handle_ != nullptr) {
		DeleteObject(this->font_handle_);

		this->font_handle_ = nullptr;
	}

	if (this->dc_handle_ != nullptr) {
		DeleteDC(this->dc_handle_);

		this->dc_handle_ = nullptr;
	}

	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Font::Init(void)
{
	this->Release();

	tml::MemoryUtil::Clear(&this->font_desc_, 1U);
	tml::MemoryUtil::Clear(&this->tm_, 1U);

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Font::Create(const tml::graphic::FontDesc &desc)
{
	this->Init();

	if (tml::graphic::Resource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::FONT) < 0) {
		this->Init();

		return (-1);
	}

	this->dc_handle_ = CreateCompatibleDC(this->GetManager()->GetWindowDeviceContextHandle());

	if (this->dc_handle_ == nullptr) {
		this->Init();

		return (-1);
	}

	this->font_handle_ = CreateFontIndirect(&desc.font_desc);

	if (this->font_handle_ == nullptr) {
		this->Init();

		return (-1);
	}

	tml::MemoryUtil::Copy(&this->font_desc_, &desc.font_desc, 1U);

	SelectObject(this->dc_handle_, this->font_handle_);

	GetTextMetrics(this->dc_handle_, &this->tm_);

	return (0);
}
