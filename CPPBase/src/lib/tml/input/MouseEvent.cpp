/**
 * @file
 * @brief MouseEventコードファイル
 */


#include "MouseEvent.h"


/**
 * @brief コンストラクタ
 */
tml::input::MouseEventData::MouseEventData() :
	type_flag(tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::NONE),
	position(0),
	displacement(0),
	wheel(0.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::MouseEventData::~MouseEventData()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::MouseEventData::Init(void)
{
	this->Release();

	this->type_flag = tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::NONE;
	this->position = 0;
	this->displacement = 0;
	this->wheel = 0.0f;

	return;
}


/**
 * @brief SetRawInput関数
 * @param rm (raw_input)
 * @param pos (position)
 */
void tml::input::MouseEventData::SetRawInput(const RAWMOUSE &rm, const tml::XMINT2EX &pos)
{
	this->type_flag = static_cast<tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE>(rm.usButtonFlags);
	this->position = pos;

	if ((rm.lLastX != 0L) || (rm.lLastY != 0L)) {
		this->type_flag |= tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::DISPLACEMENT;
		this->displacement.x = rm.lLastX;
		this->displacement.y = rm.lLastY;
	} else {
		this->displacement = 0;
	}

	if (rm.usButtonFlags & (RI_MOUSE_HWHEEL | RI_MOUSE_WHEEL)) {
		this->type_flag |= tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::WHEEL;
		this->wheel.x = (rm.usButtonFlags & RI_MOUSE_HWHEEL) ? static_cast<FLOAT>(static_cast<SHORT>(rm.usButtonData)) / WHEEL_DELTA : 0.0f;
		this->wheel.y = (rm.usButtonFlags & RI_MOUSE_WHEEL) ? static_cast<FLOAT>(static_cast<SHORT>(rm.usButtonData)) / WHEEL_DELTA : 0.0f;
	} else {
		this->wheel = 0.0f;
	}

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::MouseEvent::MouseEvent()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::MouseEvent::~MouseEvent()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::MouseEvent::Init(void)
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
INT tml::input::MouseEvent::Create(tml::input::Manager *mgr)
{
	this->Init();

	if (tml::input::Event::Create(tml::input::MouseEvent::EVENT_TYPE, mgr) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
