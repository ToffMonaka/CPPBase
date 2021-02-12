/**
 * @file
 * @brief Timerコードファイル
 */


#include "Timer.h"


/**
 * @brief コンストラクタ
 */
tml::Timer::Timer() :
	elapsed_time_(0.0),
	started_flg_(false)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::Timer::Timer(const tml::Timer &src)
{
	this->start_time_ = src.start_time_;
	this->elapsed_time_ = src.elapsed_time_;
	this->started_flg_ = src.started_flg_;

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::Timer &tml::Timer::operator =(const tml::Timer &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->start_time_ = src.start_time_;
	this->elapsed_time_ = src.elapsed_time_;
	this->started_flg_ = src.started_flg_;

	return ((*this));
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::Timer::Timer(tml::Timer &&src) noexcept
{
	this->start_time_ = src.start_time_;
	this->elapsed_time_ = src.elapsed_time_;
	this->started_flg_ = src.started_flg_;

	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::Timer &tml::Timer::operator =(tml::Timer &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->start_time_ = src.start_time_;
	this->elapsed_time_ = src.elapsed_time_;
	this->started_flg_ = src.started_flg_;

	src.Init();

	return ((*this));
}


/**
 * @brief デストラクタ
 */
tml::Timer::~Timer()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::Timer::Init(void)
{
	this->Release();

	this->start_time_ = std::chrono::steady_clock::time_point();
	this->elapsed_time_ = tml::TIME_REAL(0.0);
	this->started_flg_ = false;

	return;
}


/**
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Timer::Start(void)
{
	this->start_time_ = std::chrono::steady_clock::now();
	this->elapsed_time_ = tml::TIME_REAL(0.0);

	this->started_flg_ = true;

	return (0);
}


/**
 * @brief Stop関数
 */
void tml::Timer::Stop(void)
{
	if (!this->started_flg_) {
		return;
	}

	this->elapsed_time_ = tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - this->start_time_);

	this->started_flg_ = false;

	return;
}
