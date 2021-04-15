/**
 * @file
 * @brief ManagerEvent�R�[�h�t�@�C��
 */


#include "ManagerEvent.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::ManagerEventDesc::ManagerEventDesc() :
	manager(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::ManagerEventDesc::Init(void)
{
	this->Release();

	this->manager = nullptr;

	tml::ManagerEventDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::input::ManagerEvent::ManagerEvent() :
	mgr_(nullptr),
	event_type_(tml::ConstantUtil::INPUT::EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::ManagerEvent::~ManagerEvent()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::ManagerEvent::Init(void)
{
	this->mgr_ = nullptr;
	this->event_type_ = tml::ConstantUtil::INPUT::EVENT_TYPE::NONE;

	tml::ManagerEvent::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param event_type (event_type)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::input::ManagerEvent::Create(const tml::input::ManagerEventDesc &desc, const tml::ConstantUtil::INPUT::EVENT_TYPE event_type)
{
	if ((desc.manager == nullptr)
	|| (event_type == tml::ConstantUtil::INPUT::EVENT_TYPE::NONE)) {
		return (-1);
	}

	if (tml::ManagerEvent::Create(desc, static_cast<UINT>(event_type)) < 0) {
		return (-1);
	}

	this->mgr_ = desc.manager;
	this->event_type_ = event_type;

	return (0);
}
