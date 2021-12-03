/**
 * @file
 * @brief NodeEventコードファイル
 */


#include "NodeEvent.h"
#include "Manager.h"
#include "Node.h"


/**
 * @brief コンストラクタ
 */
tml::scene::NodeEventData::NodeEventData() :
	type(tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::NodeEventData::~NodeEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::NodeEventData::Init(void)
{
	this->Release();

	this->type = tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::NONE;
	this->node.reset();
	this->child_node.reset();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::scene::NodeEventDesc::NodeEventDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::NodeEventDesc::~NodeEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::NodeEventDesc::Init(void)
{
	this->Release();

	this->data.Init();

	tml::scene::ManagerEventDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::NodeEventDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::scene::ManagerEventDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// NodeEvent Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"NODE_EVENT");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::scene::NodeEvent::NodeEvent() :
	type_(tml::ConstantUtil::SCENE::NODE_EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::NodeEvent::~NodeEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::NodeEvent::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::SCENE::NODE_EVENT_TYPE::NONE;
	this->data.Init();

	tml::scene::ManagerEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::NodeEvent::Create(const tml::scene::NodeEventDesc &desc)
{
	this->Init();

	if (tml::scene::ManagerEvent::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->type_ = static_cast<tml::ConstantUtil::SCENE::NODE_EVENT_TYPE>(this->GetEventSubIndex());
	this->data = desc.data;

	return (0);
}
