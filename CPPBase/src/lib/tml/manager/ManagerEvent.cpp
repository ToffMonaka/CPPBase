/**
 * @file
 * @brief ManagerEvent�R�[�h�t�@�C��
 */


#include "ManagerEvent.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerEventDesc::ManagerEventDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerEventDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	return;
}


/**
 * @brief SetManager�֐�
 * @param mgr (manager)
 */
void tml::ManagerEventDesc::SetManager(tml::Manager *mgr)
{
	this->mgr_ = mgr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::ManagerEvent::ManagerEvent() :
	mgr_(nullptr),
	event_index_(0U)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ManagerEvent::~ManagerEvent()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::ManagerEvent::Init(void)
{
	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param event_index (event_index)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::ManagerEvent::Create(const tml::ManagerEventDesc &desc, const UINT event_index)
{
	if ((desc.GetManager() == nullptr)
	|| (!desc.GetManager()->CheckFriendEvent(this))) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->event_index_ = event_index;

	return (0);
}
