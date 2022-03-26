/**
 * @file
 * @brief Canvas�R�[�h�t�@�C��
 */


#include "Canvas.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::CanvasDesc::CanvasDesc() :
	draw_priority(0)
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
	desc_(nullptr),
	dimension_type_(tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::NONE),
	draw_priority_(0),
	draw_set_flg_(false)
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

	this->dimension_type_ = tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::NONE;
	this->draw_priority_ = 0;
	this->draw_set_flg_ = false;

	tml::graphic::ManagerResource::Init();

	return;
}


/**
 * @brief OnCreate�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Canvas::OnCreate(void)
{
	if (tml::graphic::ManagerResource::OnCreate() < 0) {
		return (-1);
	}

	this->draw_priority_ = this->desc_->draw_priority;

	return (0);
}


/**
 * @brief OnCreateDeferred�֐�
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::graphic::Canvas::OnCreateDeferred(void)
{
	if (tml::graphic::ManagerResource::OnCreateDeferred() < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief OnSetDesc�֐�
 * @param desc (desc)
 */
void tml::graphic::Canvas::OnSetDesc(const tml::ManagerResourceDesc *desc)
{
	this->desc_ = dynamic_cast<const tml::graphic::CanvasDesc *>(desc);

	tml::graphic::ManagerResource::OnSetDesc(this->desc_);

	return;
}


/**
 * @brief Draw�֐�
 */
void tml::graphic::Canvas::Draw(void)
{
	return;
}
