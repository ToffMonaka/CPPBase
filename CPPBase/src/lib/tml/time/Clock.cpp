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
 * @brief コンストラクタ
 * @param src (src)
 */
tml::Clock::Clock(const tml::Clock &src)
{
	this->time_ = src.time_;

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::Clock &tml::Clock::operator =(const tml::Clock &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->time_ = src.time_;

	return ((*this));
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::Clock::Clock(tml::Clock &&src) noexcept
{
	this->time_ = src.time_;

	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::Clock &tml::Clock::operator =(tml::Clock &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->time_ = src.time_;

	src.Init();

	return ((*this));
}


/**
 * @brief デストラクタ
 */
tml::Clock::~Clock()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Clock::Init(void)
{
	this->Release();

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
