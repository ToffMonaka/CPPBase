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
	one_elapsed_time_(0.0),
	work_one_elapsed_time_(0.0),
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
 * @brief デストラクタ
 */
tml::FrameRate::~FrameRate()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::FrameRate::Init(void)
{
	this->limit_ = 0U;
	this->cnt_ = 0U;
	this->fps_ = 0.0;
	this->one_start_time_ = std::chrono::steady_clock::time_point();
	this->one_elapsed_time_ = tml::TIME_REAL(0.0);
	this->work_one_start_time_ = std::chrono::steady_clock::time_point();
	this->work_one_elapsed_time_ = tml::TIME_REAL(0.0);
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
	this->one_start_time_ = std::chrono::steady_clock::now();
	this->one_elapsed_time_ = tml::TIME_REAL(0.0);
	this->work_one_start_time_ = this->one_start_time_;
	this->work_one_elapsed_time_ = this->one_elapsed_time_;
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

	this->one_elapsed_time_ = tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - this->one_start_time_);

	if (this->limit_ > 0U) {
		this->wait_time_ = tml::TIME_REAL(this->one_time_.count() - this->one_elapsed_time_.count() - this->over_time_.count());

		while (this->wait_time_.count() >= this->average_sleep_time_.count()) {
			this->sleep_time_ = tml::TimeUtil::Sleep(TIME_REAL(0.001));
			this->average_sleep_time_ = TIME_REAL((this->average_sleep_time_.count() + this->sleep_time_.count()) * 0.5);
			this->wait_time_ = TIME_REAL(this->wait_time_.count() - this->sleep_time_.count());
		}

		this->work_one_elapsed_time_ = tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - this->work_one_start_time_);

		this->over_time_ = TIME_REAL(this->over_time_.count() + (this->work_one_elapsed_time_.count() - this->one_time_.count()));
	} else {
		this->work_one_elapsed_time_ = this->one_elapsed_time_;
	}

	this->total_elapsed_time_ = tml::TIME_REAL(this->total_elapsed_time_.count() + this->work_one_elapsed_time_.count());

	this->one_start_time_ = std::chrono::steady_clock::now();
	this->work_one_start_time_ = this->one_start_time_;

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
