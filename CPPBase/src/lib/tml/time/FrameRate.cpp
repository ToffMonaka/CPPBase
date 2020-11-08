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
	sleep_time_(0.001),
	wait_time_(0.0),
	total_time_(0.0),
	over_time_(0.0),
	start_flg_(false)
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
	this->sleep_time_ = tml::TIME_REAL(0.001);
	this->wait_time_ = tml::TIME_REAL(0.0);
	this->total_time_ = tml::TIME_REAL(0.0);
	this->over_time_ = tml::TIME_REAL(0.0);
	this->start_flg_ = false;

	/*
	this->work_one_frame_timer.Init();
	this->one_frame_timer.Init();
	this->work_one_frame_timer_storage.Init();
	this->one_frame_timer_storage.Init();
	*/

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
	this->sleep_time_ = tml::TIME_REAL(0.001);
	this->wait_time_ = tml::TIME_REAL(0.0);
	this->total_time_ = tml::TIME_REAL(0.0);
	this->over_time_ = tml::TIME_REAL(0.0);
	this->start_flg_ = true;

	/*
	this->work_one_frame_timer_storage.Open();
	this->one_frame_timer_storage.Open();

	this->work_one_frame_timer.Start();
	this->one_frame_timer = this->work_one_frame_timer;
	*/

	return (0);
}


/**
 * @brief Stop関数
 */
void tml::FrameRate::Stop(void)
{
	this->start_flg_ = false;

	return;
}


/**
 * @brief Update関数
 */
void tml::FrameRate::Update(void)
{
	if (!this->start_flg_) {
		return;
	}

	if (this->limit_ > 0U) {
		tml::TimeUtil::Sleep(tml::TIME_REAL(0.001));
	} else {
	}

	++this->cnt_;

	if (this->total_time_ >= tml::TIME_REAL(1.0)) {
		this->fps_ = static_cast<DOUBLE>(this->cnt_) / this->total_time_.count();
		this->cnt_ = 0U;
		this->sleep_time_ = tml::TIME_REAL(0.001);
		this->wait_time_ = tml::TIME_REAL(0.0);
		this->total_time_ = tml::TIME_REAL(0.0);
	}

	/*
	if (this->frame_rate > 0U) { //フレームレート有りの時
		this->work_one_frame_timer.Stop();

		TIME_REAL wait_time(this->one_frame_timer_storage.GetTimeLimit().count() - this->work_one_frame_timer.GetTime().count() - this->over_time.count());

		while (wait_time.count() >= this->sleep_time.count()) {
			auto sleep_time = tm_l::sleep::Util::Sleep(TIME_REAL(0.001));

			this->sleep_time = TIME_REAL((this->sleep_time.count() + sleep_time.count()) * 0.5);

			wait_time = TIME_REAL(wait_time.count() - sleep_time.count());
		}

		tm_l::sleep::Util::Wait(wait_time);

		this->one_frame_timer.Stop();

		this->over_time = TIME_REAL(this->over_time.count() + (this->one_frame_timer.GetTime().count() - this->one_frame_timer_storage.GetTimeLimit().count()));

		this->work_one_frame_timer_storage.SetTime(this->work_one_frame_timer.GetTime());
		this->one_frame_timer_storage.SetTime(this->one_frame_timer.GetTime());
		this->total_frame_timer_storage.SetTime(TIME_REAL(this->total_frame_timer_storage.GetTime().count() + this->one_frame_timer.GetTime().count()));

		this->work_one_frame_timer.Start();
		this->one_frame_timer = this->work_one_frame_timer;

		++this->frame_cnt;

		if (this->total_frame_timer_storage.IsLimit()) { //上限の時
			this->fps = static_cast<DOUBLE>(this->frame_cnt) / this->total_frame_timer_storage.GetTime().count();
			this->frame_cnt = 0U;
			this->total_frame_timer_storage.SetTime(TIME_REAL(0.0));
			this->sleep_time = TIME_REAL(0.001);
		}
	} else { //フレームレート無しの時
		this->one_frame_timer.Stop();

		this->work_one_frame_timer_storage.SetTime(this->one_frame_timer.GetTime());
		this->one_frame_timer_storage.SetTime(this->one_frame_timer.GetTime());
		this->total_frame_timer_storage.SetTime(TIME_REAL(this->total_frame_timer_storage.GetTime().count() + this->one_frame_timer.GetTime().count()));

		this->one_frame_timer.Start();

		++this->frame_cnt;

		if (this->total_frame_timer_storage.IsLimit()) { //上限の時
			this->fps = static_cast<DOUBLE>(this->frame_cnt) / this->total_frame_timer_storage.GetTime().count();
			this->frame_cnt = 0U;
			this->total_frame_timer_storage.SetTime(TIME_REAL(0.0));
		}
	}
	*/

	return;
}
