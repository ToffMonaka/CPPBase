/**
 * @file
 * @brief ManagerEvent�R�[�h�t�@�C��
 */


#include "ManagerEvent.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::ManagerEventDesc::ManagerEventDesc() :
	mgr_(nullptr)
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

	this->mgr_ = nullptr;

	tml::ManagerEventDesc::Init();

	return;
}


/**
 * @brief SetManager�֐�
 * @param mgr (manager)
 */
void tml::input::ManagerEventDesc::SetManager(tml::input::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::ManagerEventDesc::SetManager(mgr);

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
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::ManagerEvent::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->event_type_ = tml::ConstantUtil::INPUT::EVENT_TYPE::NONE;

	tml::ManagerEvent::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::input::ManagerEvent::Create(const tml::input::ManagerEventDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		return (-1);
	}

	if (tml::ManagerEvent::Create(desc) < 0) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->event_type_ = static_cast<tml::ConstantUtil::INPUT::EVENT_TYPE>(this->GetEventMainIndex());

	return (0);
}
