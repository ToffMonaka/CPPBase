/**
 * @file
 * @brief Eventコードファイル
 */


#include "Event.h"


/**
 * @brief コンストラクタ
 */
tml::sound::Event::Event() :
	event_type_(tml::ConstantUtil::SOUND::EVENT_TYPE::NONE),
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::sound::Event::~Event()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::sound::Event::Init(void)
{
	this->event_type_ = tml::ConstantUtil::SOUND::EVENT_TYPE::NONE;
	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create関数
 * @param event_type (event_type)
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::sound::Event::Create(const tml::ConstantUtil::SOUND::EVENT_TYPE event_type, tml::sound::Manager *mgr)
{
	if ((event_type == tml::ConstantUtil::SOUND::EVENT_TYPE::NONE)
	|| (mgr == nullptr)) {
		return (-1);
	}

	this->event_type_ = event_type;
	this->mgr_ = mgr;

	return (0);
}
