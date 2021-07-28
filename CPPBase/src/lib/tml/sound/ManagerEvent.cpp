/**
 * @file
 * @brief ManagerEvent�R�[�h�t�@�C��
 */


#include "ManagerEvent.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::sound::ManagerEventDesc::ManagerEventDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::ManagerEventDesc::~ManagerEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::ManagerEventDesc::Init(void)
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
void tml::sound::ManagerEventDesc::SetManager(tml::sound::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::ManagerEventDesc::SetManager(mgr);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::sound::ManagerEvent::ManagerEvent() :
	mgr_(nullptr),
	event_type_(tml::ConstantUtil::SOUND::EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::ManagerEvent::~ManagerEvent()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::ManagerEvent::Init(void)
{
	this->mgr_ = nullptr;
	this->event_type_ = tml::ConstantUtil::SOUND::EVENT_TYPE::NONE;

	tml::ManagerEvent::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param event_type (event_type)
 * @param event_sub_index (event_sub_index)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::sound::ManagerEvent::Create(const tml::sound::ManagerEventDesc &desc, const tml::ConstantUtil::SOUND::EVENT_TYPE event_type, const UINT event_sub_index)
{
	if ((desc.GetManager() == nullptr)
	|| (event_type == tml::ConstantUtil::SOUND::EVENT_TYPE::NONE)) {
		return (-1);
	}

	if (tml::ManagerEvent::Create(desc, static_cast<UINT>(event_type), event_sub_index) < 0) {
		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->event_type_ = event_type;

	return (0);
}
