/**
 * @file
 * @brief Clockコードファイル
 */


#include "Clock.h"


/**
 * @brief コンストラクタ
 */
tml::Clock::Clock() :
	time_(0LL)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Clock::~Clock()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::Clock::Init(void)
{
	this->time_ = tml::TIME_MILLI(0LL);

	return;
}


/**
 * @brief SetTime関数
 * @param time (time)
 */
void tml::Clock::SetTime(const tml::TIME_MILLI &time)
{
	this->time_ = time;

	return;
}
