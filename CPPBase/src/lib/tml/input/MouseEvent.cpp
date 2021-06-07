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
	move_value(0),
	wheel_value(0.0f)
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
	this->move_value = 0;
	this->wheel_value = 0.0f;

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
		this->type_flag |= tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::MOVE;
		this->move_value.x = rm.lLastX;
		this->move_value.y = rm.lLastY;
	} else {
		this->move_value = 0;
	}

	if (rm.usButtonFlags & (RI_MOUSE_HWHEEL | RI_MOUSE_WHEEL)) {
		this->type_flag |= tml::ConstantUtil::INPUT::MOUSE_EVENT_DATA_TYPE::WHEEL;
		this->wheel_value.x = (rm.usButtonFlags & RI_MOUSE_HWHEEL) ? static_cast<FLOAT>(static_cast<SHORT>(rm.usButtonData)) / WHEEL_DELTA : 0.0f;
		this->wheel_value.y = (rm.usButtonFlags & RI_MOUSE_WHEEL) ? static_cast<FLOAT>(static_cast<SHORT>(rm.usButtonData)) / WHEEL_DELTA : 0.0f;
	} else {
		this->wheel_value = 0.0f;
	}

	return;
}


/**
 * @brief コンストラクタ
 */
tml::input::MouseEventDesc::MouseEventDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::input::MouseEventDesc::~MouseEventDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::input::MouseEventDesc::Init(void)
{
	this->Release();

	this->data.Init();

	tml::input::ManagerEventDesc::Init();

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

	tml::input::ManagerEvent::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::input::MouseEvent::Create(const tml::input::MouseEventDesc &desc)
{
	this->Init();

	if (tml::input::ManagerEvent::Create(desc, tml::ConstantUtil::INPUT::EVENT_TYPE::DEVICE, static_cast<UINT>(tml::ConstantUtil::INPUT::DEVICE_EVENT_TYPE::MOUSE)) < 0) {
		this->Init();

		return (-1);
	}

	this->SetData(desc.data);

	return (0);
}
