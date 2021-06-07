/**
 * @file
 * @brief KeyboardEventコードファイル
 */


#include "KeyboardEvent.h"


/**
 * @brief コンストラクタ
 */
tml::input::KeyboardEventData::KeyboardEventData() :
	type_flag(tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE::NONE),
	code(tml::ConstantUtil::INPUT::KEYBOARD_CODE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::KeyboardEventData::~KeyboardEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::KeyboardEventData::Init(void)
{
	this->Release();

	this->type_flag = tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE::NONE;
	this->code = tml::ConstantUtil::INPUT::KEYBOARD_CODE::NONE;

	return;
}


/**
 * @brief SetRawInput関数
 * @param rk (raw_keyboard)
 */
void tml::input::KeyboardEventData::SetRawInput(const RAWKEYBOARD &rk)
{
	this->type_flag = static_cast<tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE>((rk.Flags & 1) + 1);
	this->code = static_cast<tml::ConstantUtil::INPUT::KEYBOARD_CODE>(rk.VKey);

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::KeyboardEventDesc::KeyboardEventDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::KeyboardEventDesc::~KeyboardEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::KeyboardEventDesc::Init(void)
{
	this->Release();

	this->data.Init();

	tml::input::ManagerEventDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::KeyboardEvent::KeyboardEvent()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::KeyboardEvent::~KeyboardEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::KeyboardEvent::Init(void)
{
	this->Release();

	this->dat_.Init();

	tml::input::ManagerEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
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
