/**
 * @file
 * @brief NodeEvent�R�[�h�t�@�C��
 */


#include "NodeEvent.h"
#include "Manager.h"
#include "Node.h"


/**
 * @brief �R���X�g���N�^
 */
tml::scene::NodeEventData::NodeEventData() :
	type(tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::NodeEventData::~NodeEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
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
 * @brief �R���X�g���N�^
 */
tml::scene::NodeEventDesc::NodeEventDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::NodeEventDesc::~NodeEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::NodeEventDesc::Init(void)
{
	this->Release();

	this->data.Init();

	tml::scene::ManagerEventDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::scene::NodeEvent::NodeEvent() :
	type_(tml::ConstantUtil::SCENE::NODE_EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::NodeEvent::~NodeEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
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
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
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
