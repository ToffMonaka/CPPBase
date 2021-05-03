/**
 * @file
 * @brief Node�R�[�h�t�@�C��
 */


#include "Node.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::scene::NodeDesc::NodeDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::NodeDesc::~NodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::NodeDesc::Init(void)
{
	this->Release();

	tml::scene::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::scene::NodeDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Node Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"NODE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::scene::Node::Node() :
	type_(tml::ConstantUtil::SCENE::NODE_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::Node::~Node()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::scene::Node::Release(void)
{
	tml::scene::ManagerResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::Node::Init(void)
{
	this->type_ = tml::ConstantUtil::SCENE::NODE_TYPE::NONE;

	tml::scene::ManagerResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::scene::Node::Create(const tml::scene::NodeDesc &desc, const tml::ConstantUtil::SCENE::NODE_TYPE type)
{
	if (type == tml::ConstantUtil::SCENE::NODE_TYPE::NONE) {
		return (-1);
	}

	if (tml::scene::ManagerResource::Create(desc, tml::ConstantUtil::SCENE::RESOURCE_TYPE::NODE, static_cast<UINT>(type)) < 0) {
		return (-1);
	}

	this->type_ = type;

	return (0);
}
