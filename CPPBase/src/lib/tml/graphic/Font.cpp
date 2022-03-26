/**
 * @file
 * @brief Fontコードファイル
 */


#include "Font.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::FontBitmap::FontBitmap() :
	code_(0),
	gm_{}
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::FontBitmap::~FontBitmap()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::FontBitmap::Init(void)
{
	this->Release();

	this->code_ = 0;
	tml::Clear(&this->gm_, 1U);
	this->buf_.Init();

	return;
}


/**
 * @brief Create関数
 * @param dc_handle (device_context_handle)
 * @param code (code)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::FontBitmap::Create(const HDC dc_handle, const WCHAR code)
{
	if ((dc_handle == nullptr)
	|| (code == 0)) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->code_ = code;

	const MAT2 mat = {{0, 1}, {0, 0}, {0, 0}, {0, 1}};
	tml::DynamicBuffer buf;
	DWORD buf_size = GetGlyphOutline(dc_handle, this->code_, GGO_GRAY4_BITMAP, &this->gm_, 0UL, nullptr, &mat);

	if ((buf_size <= 0U)
	|| (buf_size == GDI_ERROR)) {
		this->Init();

		return (-1);
	}

	buf.SetSize(buf_size);
	buf.AddWriteIndex(buf.GetSize());

	GetGlyphOutline(dc_handle, this->code_, GGO_GRAY4_BITMAP, &this->gm_, buf.GetLength(), buf.Get(), &mat);

	this->buf_.SetSize(buf.GetLength() << 2);
	this->buf_.AddWriteIndex(this->buf_.GetSize());

	for (size_t buf_i = 0U, buf_end_i = buf.GetLength(); buf_i < buf_end_i; ++buf_i) {
		UINT a = (255U * static_cast<UINT>(buf.Get()[buf_i]) >> 4) & 0xFF;

		reinterpret_cast<UINT *>(this->buf_.Get())[buf_i] = 0x00FFFFFFU | (a << 24);
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::graphic::FontDesc::FontDesc() :
	font_desc{}
{
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

	tml::Clear(&this->font_desc, 1U);

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::FontDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Font Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"FONT");

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
void tml::graphic::FontDesc::SetFontDesc(const tml::XMUINT2EX &size, const WCHAR *family)
{
	tml::Clear(&this->font_desc, 1U);
	this->font_desc.lfHeight = -MulDiv(static_cast<LONG>(size.y), GetDeviceCaps(this->GetManager()->GetWindowDeviceContextHandle(), LOGPIXELSY), 72);
	this->font_desc.lfWidth = static_cast<LONG>(size.x);
	this->font_desc.lfEscapement = 0L;
	this->font_desc.lfOrientation = 0L;
	this->font_desc.lfWeight = FW_NORMAL;
	this->font_desc.lfItalic = 0;
	this->font_desc.lfUnderline = 0;
	this->font_desc.lfStrikeOut = 0;
	this->font_desc.lfCharSet = SHIFTJIS_CHARSET;
	this->font_desc.lfOutPrecision = OUT_TT_ONLY_PRECIS;
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
	desc_(nullptr),
	dc_handle_(nullptr),
	font_handle_(nullptr),
	font_desc_{},
	tm_{}
{
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

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Font::Init(void)
{
	this->Release();

	tml::Clear(&this->font_desc_, 1U);
	tml::Clear(&this->tm_, 1U);
	this->bm_cont_.clear();

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief OnCreate関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Font::OnCreate(void)
{
	if (tml::graphic::ManagerResource::OnCreate() < 0) {
		return (-1);
	}

	this->dc_handle_ = CreateCompatibleDC(this->GetManager()->GetWindowDeviceContextHandle());

	if (this->dc_handle_ == nullptr) {
		return (-1);
	}

	this->font_handle_ = CreateFontIndirect(&this->desc_->font_desc);

	if (this->font_handle_ == nullptr) {
		return (-1);
	}

	this->font_desc_ = this->desc_->font_desc;

	SelectObject(this->dc_handle_, this->font_handle_);

	GetTextMetrics(this->dc_handle_, &this->tm_);

	return (0);
}


/**
 * @brief OnCreateDeferred関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Font::OnCreateDeferred(void)
{
	if (tml::graphic::ManagerResource::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc関数
 * @param desc (desc)
 */
void tml::graphic::Font::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::FontDesc *>(desc);

	tml::graphic::ManagerResource::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief GetBitmap関数
 * @param code (code)
 * @return bm (bitmap)<br>
 * nullptr=失敗
 */
const tml::graphic::FontBitmap *tml::graphic::Font::GetBitmap(const WCHAR code)
{
	auto bm_itr = this->bm_cont_.find(code);

	if (bm_itr == this->bm_cont_.end()) {
		tml::graphic::FontBitmap bm;

		if (bm.Create(this->dc_handle_, code) < 0) {
			return (nullptr);
		}

		auto insert_result = this->bm_cont_.emplace(code, bm);

		return (&insert_result.first->second);
	}

	return (&bm_itr->second);
}
