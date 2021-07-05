/**
 * @file
 * @brief Canvas�R�[�h�t�@�C��
 */


#include "Canvas.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::CanvasDesc::CanvasDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::CanvasDesc::~CanvasDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::CanvasDesc::Init(void)
{
	this->Release();

	tml::graphic::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::CanvasDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Canvas Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"CANVAS");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Canvas::Canvas() :
	type_(tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Canvas::~Canvas()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::Canvas::Release(void)
{
	tml::graphic::ManagerResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Canvas::Init(void)
{
	this->type_ = tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::NONE;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::Canvas::Create(const tml::graphic::CanvasDesc &desc, const tml::ConstantUtil::GRAPHIC::CANVAS_TYPE type)
{
	if (type == tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::NONE) {
		return (-1);
	}

	if (tml::graphic::ManagerResource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::CANVAS, static_cast<UINT>(type)) < 0) {
		return (-1);
	}

	this->type_ = type;

	return (0);
}
