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
 * @brief コンストラクタ
 */
tml::graphic::Font::Font()
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
 * @brief Init関数
 */
void tml::graphic::Font::Init(void)
{
	this->Release();

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

	return (0);
}
