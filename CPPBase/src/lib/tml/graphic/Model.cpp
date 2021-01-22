/**
 * @file
 * @brief Modelコードファイル
 */


#include "Model.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::graphic::ModelDesc::ModelDesc() :
	position_set_flag(true)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::ModelDesc::~ModelDesc()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::ModelDesc::Init(void)
{
	this->position.Init();
	this->position_set_flag = true;

	tml::graphic::ResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
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
 * @brief コンストラクタ
 */
tml::graphic::Model::Model() :
	type_(tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::graphic::Model::~Model()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::graphic::Model::Release(void)
{
	tml::graphic::Resource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::graphic::Model::Init(void)
{
	this->type_ = tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE;
	this->position.reset();

	tml::graphic::Resource::Init();

	return;
}


/**
 * @brief Create関数
 * @param type (type)
 * @param desc (desc)
 * @param pos (position)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::graphic::Model::Create(const tml::ConstantUtil::GRAPHIC::MODEL_TYPE type, const tml::graphic::ModelDesc &desc, tml::shared_ptr<tml::XMPosition> &pos)
{
	if (type == tml::ConstantUtil::GRAPHIC::MODEL_TYPE::NONE) {
		return (-1);
	}

	if (tml::graphic::Resource::Create(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::MODEL, desc) < 0) {
		return (-1);
	}

	this->type_ = type;
	tml::get_shared(this->position, pos, 1U);

	if (desc.position_set_flag) {
		(*this->position) = desc.position;
	}

	return (0);
}
