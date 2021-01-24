/**
 * @file
 * @brief Model�R�[�h�t�@�C��
 */


#include "Model.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::ModelDesc::ModelDesc() :
	position_set_flag(true)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::ModelDesc::~ModelDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::ModelDesc::Init(void)
{
	this->position.Init();
	this->position_set_flag = true;

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::ModelDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::graphic::ResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Model Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"MODEL");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::graphic::Model::Model() :
	type_(tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::graphic::Model::~Model()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::graphic::Model::Release(void)
{
	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::graphic::Model::Init(void)
{
	this->type_ = tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE;
	this->position.reset();

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param type (type)
 * @param pos (position)<br>
 * nullptr=�w�薳��
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::graphic::Model::Create(const tml::graphic::ModelDesc &desc, const tml::ConstantUtil::GRAPHIC::MODEL_TYPE type, tml::shared_ptr<tml::XMPosition> *pos)
{
	if (type == tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE) {
		return (-1);
	}

	if (tml::graphic::Resource::Create(desc, tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::MODEL) < 0) {
		return (-1);
	}

	this->type_ = type;

	if (pos != nullptr) {
		tml::get_shared(this->position, (*pos), 1U);
	} else {
		tml::get_shared(this->position, 1U);
	}

	if (desc.position_set_flag) {
		(*this->position) = desc.position;
	}

	return (0);
}
