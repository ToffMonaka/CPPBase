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
	virtual_key_code(tml::ConstantUtil::INPUT::VIRTUAL_KEY_CODE::NONE)
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
	this->virtual_key_code = tml::ConstantUtil::INPUT::VIRTUAL_KEY_CODE::NONE;

	return;
}


/**
 * @brief SetRawInput関数
 * @param rm (raw_input)
 */
void tml::input::KeyboardEventData::SetRawInput(const RAWKEYBOARD &rk)
{
	this->type_flag = static_cast<tml::ConstantUtil::INPUT::KEYBOARD_EVENT_DATA_TYPE>((rk.Flags & 1) + 1);
	this->virtual_key_code = static_cast<tml::ConstantUtil::INPUT::VIRTUAL_KEY_CODE>(rk.VKey);

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

	tml::input::Event::Init();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::KeyboardEvent::Create(tml::input::Manager *mgr)
{
	this->Init();

	if (tml::input::Event::Create(tml::input::KeyboardEvent::EVENT_TYPE, mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
