/**
 * @file
 * @brief DeviceEvent�R�[�h�t�@�C��
 */


#include "DeviceEvent.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::DeviceEventDesc::DeviceEventDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::DeviceEventDesc::~DeviceEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::DeviceEventDesc::Init(void)
{
	this->Release();

	tml::input::ManagerEventDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::input::DeviceEvent::DeviceEvent() :
	type_(tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::DeviceEvent::~DeviceEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::DeviceEvent::Init(void)
{
	this->Release();

	this->type_ = tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::NONE;

	tml::input::ManagerEvent::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::input::DeviceEvent::Create(const tml::input::DeviceEventDesc &desc)
{
	if (tml::input::ManagerEvent::Create(desc) < 0) {
		return (-1);
	}

	this->type_ = static_cast<tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE>(this->GetEventSubIndex());

	return (0);
}
