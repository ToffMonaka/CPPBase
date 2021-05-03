/**
 * @file
 * @brief Nodeコードファイル
 */


#include "Node.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::scene::NodeDesc::NodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::NodeDesc::~NodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::NodeDesc::Init(void)
{
	this->Release();

	tml::scene::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
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
 * @brief コンストラクタ
 */
tml::scene::Node::Node() :
	type_(tml::ConstantUtil::SCENE::NODE_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::Node::~Node()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::scene::Node::Release(void)
{
	tml::scene::ManagerResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::Node::Init(void)
{
	this->type_ = tml::ConstantUtil::SCENE::NODE_TYPE::NONE;

	tml::scene::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0未満=失敗
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
