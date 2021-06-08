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
	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::DeviceEvent::Init(void)
{
	this->type_ = tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::NONE;

	tml::input::ManagerEvent::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::input::DeviceEvent::Create(const tml::input::DeviceEventDesc &desc, const tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE type)
{
	if (type == tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::NONE) {
		return (-1);
	}

	if (tml::input::ManagerEvent::Create(desc, tml::ConstantUtil::INPUT::EVENT_TYPE::DEVICE, static_cast<UINT>(type)) < 0) {
		return (-1);
	}

	this->type_ = type;

	return (0);
}
