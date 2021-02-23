/**
 * @file
 * @brief Font�R�[�h�t�@�C��
 */


#include "Font.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::FontDesc::FontDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::FontDesc::~FontDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::FontDesc::Init(void)
{
	this->Release();

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
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
 * @brief �R���X�g���N�^
 */
tml::graphic::Font::Font()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Font::~Font()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Font::Init(void)
{
	this->Release();

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
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
