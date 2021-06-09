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
	this->parent_node.reset();
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
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::NodeEvent::Create(const tml::scene::NodeEventDesc &desc)
{
	this->Init();

	if (tml::scene::ManagerEvent::Create(desc, tml::ConstantUtil::SCENE::EVENT_TYPE::NODE, static_cast<UINT>(tml::ConstantUtil::SCENE::NODE_EVENT_TYPE::ETC)) < 0) {
		this->Init();

		return (-1);
	}

	this->type_ = tml::ConstantUtil::SCENE::NODE_EVENT_TYPE::ETC;
	this->data = desc.data;

	return (0);
}
