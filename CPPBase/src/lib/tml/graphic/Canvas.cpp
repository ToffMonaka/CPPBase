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
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::CanvasDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::graphic::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Canvas Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"CANVAS");

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
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Canvas::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::NONE;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Canvas::Create(const tml::graphic::CanvasDesc &desc)
{
	if (tml::graphic::ManagerResource::Create(desc) < 0) {
		return (-1);
	}

	this->type_ = static_cast<tml::ConstantUtil::GRAPHIC::CANVAS_TYPE>(this->GetResourceSubIndex());

	return (0);
}


/**
 * @brief Draw�֐�
 */
void tml::graphic::Canvas::Draw(void)
{
	return;
}
