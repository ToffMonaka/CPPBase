/**
 * @file
 * @brief KeyboardEvent�R�[�h�t�@�C��
 */


#include "KeyboardEvent.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::KeyboardEventData::KeyboardEventData() :
	type_flag(tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE::NONE),
	code(tml::ConstantUtil::INPUT::KEYBOARD_CODE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::KeyboardEventData::~KeyboardEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::KeyboardEventData::Init(void)
{
	this->Release();

	this->type_flag = tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE::NONE;
	this->code = tml::ConstantUtil::INPUT::KEYBOARD_CODE::NONE;

	return;
}


/**
 * @brief SetRawInput�֐�
 * @param rk (raw_keyboard)
 */
void tml::input::KeyboardEventData::SetRawInput(const RAWKEYBOARD &rk)
{
	this->type_flag = static_cast<tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE>((rk.Flags & 1) + 1);
	this->code = static_cast<tml::ConstantUtil::INPUT::KEYBOARD_CODE>(rk.VKey);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::input::KeyboardEventDesc::KeyboardEventDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::KeyboardEventDesc::~KeyboardEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::KeyboardEventDesc::Init(void)
{
	this->Release();

	this->data.Init();

	tml::input::ManagerEventDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::input::KeyboardEvent::KeyboardEvent()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::KeyboardEvent::~KeyboardEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::KeyboardEvent::Init(void)
{
	this->Release();

	this->dat_.Init();

	tml::input::ManagerEvent::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::input::KeyboardEvent::Create(const tml::input::KeyboardEventDesc &desc)
{
	this->Init();

	if (tml::input::ManagerEvent::Create(desc, tml::ConstantUtil::INPUT::EVENT_TYPE::DEVICE, static_cast<UINT>(tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::KEYBOARD)) < 0) {
		this->Init();

		return (-1);
	}

	this->SetData(desc.data);

	return (0);
}
