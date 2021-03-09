/**
 * @file
 * @brief MouseEventコードファイル
 */


#include "MouseEvent.h"


/**
 * @brief コンストラクタ
 */
tml::input::MouseEventData::MouseEventData()
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
