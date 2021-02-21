/**
 * @file
 * @brief FrameRateコードファイル
 */


#include "FrameRate.h"
#include "TimeUtil.h"


/**
 * @brief コンストラクタ
 */
tml::FrameRate::FrameRate() :
	limit_(0U),
	cnt_(0U),
	fps_(0.0),
	elapsed_time_(0.0),
	work_elapsed_time_(0.0),
	total_elapsed_time_(0.0),
	one_time_(0.0),
	sleep_time_(0.0),
	average_sleep_time_(0.0),
	wait_time_(0.0),
	over_time_(0.0),
	started_flg_(false)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::FrameRate::FrameRate(const tml::FrameRate &src)
{
	this->limit_ = src.limit_;
	this->cnt_ = src.cnt_;
	this->fps_ = src.fps_;
	this->start_time_ = src.start_time_;
	this->work_start_time_ = src.work_start_time_;
	this->elapsed_time_ = src.elapsed_time_;
	this->work_elapsed_time_ = src.work_elapsed_time_;
	this->total_elapsed_time_ = src.total_elapsed_time_;
	this->one_time_ = src.one_time_;
	this->sleep_time_ = src.sleep_time_;
	this->average_sleep_time_ = src.average_sleep_time_;
	this->wait_time_ = src.wait_time_;
	this->over_time_ = src.over_time_;
	this->started_flg_ = src.started_flg_;

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::FrameRate &tml::FrameRate::operator =(const tml::FrameRate &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->limit_ = src.limit_;
	this->cnt_ = src.cnt_;
	this->fps_ = src.fps_;
	this->start_time_ = src.start_time_;
	this->work_start_time_ = src.work_start_time_;
	this->elapsed_time_ = src.elapsed_time_;
	this->work_elapsed_time_ = src.work_elapsed_time_;
	this->total_elapsed_time_ = src.total_elapsed_time_;
	this->one_time_ = src.one_time_;
	this->sleep_time_ = src.sleep_time_;
	this->average_sleep_time_ = src.average_sleep_time_;
	this->wait_time_ = src.wait_time_;
	this->over_time_ = src.over_time_;
	this->started_flg_ = src.started_flg_;

	return ((*this));
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::FrameRate::FrameRate(tml::FrameRate &&src) noexcept
{
	this->limit_ = src.limit_;
	this->cnt_ = src.cnt_;
	this->fps_ = src.fps_;
	this->start_time_ = src.start_time_;
	this->work_start_time_ = src.work_start_time_;
	this->elapsed_time_ = src.elapsed_time_;
	this->work_elapsed_time_ = src.work_elapsed_time_;
	this->total_elapsed_time_ = src.total_elapsed_time_;
	this->one_time_ = src.one_time_;
	this->sleep_time_ = src.sleep_time_;
	this->average_sleep_time_ = src.average_sleep_time_;
	this->wait_time_ = src.wait_time_;
	this->over_time_ = src.over_time_;
	this->started_flg_ = src.started_flg_;

	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::FrameRate &tml::FrameRate::operator =(tml::FrameRate &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->limit_ = src.limit_;
	this->cnt_ = src.cnt_;
	this->fps_ = src.fps_;
	this->start_time_ = src.start_time_;
	this->work_start_time_ = src.work_start_time_;
	this->elapsed_time_ = src.elapsed_time_;
	this->work_elapsed_time_ = src.work_elapsed_time_;
	this->total_elapsed_time_ = src.total_elapsed_time_;
	this->one_time_ = src.one_time_;
	this->sleep_time_ = src.sleep_time_;
	this->average_sleep_time_ = src.average_sleep_time_;
	this->wait_time_ = src.wait_time_;
	this->over_time_ = src.over_time_;
	this->started_flg_ = src.started_flg_;

	src.Init();

	return ((*this));
}


/**
 * @brief デストラクタ
 */
tml::FrameRate::~FrameRate()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::FrameRate::Init(void)
{
	this->Release();

	this->limit_ = 0U;
	this->cnt_ = 0U;
	this->fps_ = 0.0;
	this->start_time_ = std::chrono::steady_clock::time_point();
	this->work_start_time_ = std::chrono::steady_clock::time_point();
	this->elapsed_time_ = tml::TIME_REAL(0.0);
	this->work_elapsed_time_ = tml::TIME_REAL(0.0);
	this->total_elapsed_time_ = tml::TIME_REAL(0.0);
	this->one_time_ = tml::TIME_REAL(0.0);
	this->sleep_time_ = tml::TIME_REAL(0.0);
	this->average_sleep_time_ = tml::TIME_REAL(0.0);
	this->wait_time_ = tml::TIME_REAL(0.0);
	this->over_time_ = tml::TIME_REAL(0.0);
	this->started_flg_ = false;

	return;
}


/**
 * @brief Start関数
 * @param limit (limit)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::FrameRate::Start(const UINT limit)
{
	this->limit_ = limit;
	this->cnt_ = 0U;
	this->fps_ = static_cast<DOUBLE>(this->limit_);
	this->start_time_ = std::chrono::steady_clock::now();
	this->work_start_time_ = this->start_time_;
	this->elapsed_time_ = tml::TIME_REAL(0.0);
	this->work_elapsed_time_ = this->elapsed_time_;
	this->total_elapsed_time_ = tml::TIME_REAL(0.0);
	this->one_time_ = (this->limit_ > 0U) ? tml::TIME_REAL(1.0 / this->limit_) : tml::TIME_REAL(0.0);
	this->sleep_time_ = tml::TIME_REAL(0.001);
	this->average_sleep_time_ = this->sleep_time_;
	this->wait_time_ = tml::TIME_REAL(0.0);
	this->over_time_ = tml::TIME_REAL(0.0);

	this->started_flg_ = true;

	return (0);
}


/**
 * @brief Stop関数
 */
void tml::FrameRate::Stop(void)
{
	if (!this->started_flg_) {
		return;
	}

	this->started_flg_ = false;

	return;
}


/**
 * @brief Update関数
 */
void tml::FrameRate::Update(void)
{
	if (!this->started_flg_) {
		return;
	}

	this->work_elapsed_time_ = tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - this->start_time_);

	if (this->limit_ > 0U) {
		this->wait_time_ = tml::TIME_REAL(this->one_time_.count() - this->work_elapsed_time_.count() - this->over_time_.count());

		while (this->wait_time_.count() >= this->average_sleep_time_.count()) {
			this->sleep_time_ = tml::TimeUtil::Sleep(TIME_REAL(0.001));
			this->average_sleep_time_ = TIME_REAL((this->average_sleep_time_.count() + this->sleep_time_.count()) * 0.5);
			this->wait_time_ = TIME_REAL(this->wait_time_.count() - this->sleep_time_.count());
		}

		this->elapsed_time_ = tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - this->work_start_time_);

		this->over_time_ = TIME_REAL(this->over_time_.count() + (this->elapsed_time_.count() - this->one_time_.count()));
	} else {
		this->elapsed_time_ = this->work_elapsed_time_;
	}

	this->total_elapsed_time_ = tml::TIME_REAL(this->total_elapsed_time_.count() + this->elapsed_time_.count());

	this->start_time_ = std::chrono::steady_clock::now();
	this->work_start_time_ = this->start_time_;

	++this->cnt_;

	if (this->total_elapsed_time_.count() >= tml::TIME_REAL(1.0).count()) {
		this->fps_ = static_cast<DOUBLE>(this->cnt_) / this->total_elapsed_time_.count();
		this->cnt_ = 0U;
		this->total_elapsed_time_ = tml::TIME_REAL(0.0);

		this->sleep_time_ = tml::TIME_REAL(0.001);
		this->average_sleep_time_ = this->sleep_time_;
		this->wait_time_ = tml::TIME_REAL(0.0);
	}

	return;
}
