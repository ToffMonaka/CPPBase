/**
 * @file
 * @brief FrameRateヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief FrameRateクラス
 */
class FrameRate
{
public: FrameRate(const FrameRate &) = delete;
public: FrameRate &operator =(const FrameRate &) = delete;

private:
	UINT limit_;
	UINT cnt_;
	DOUBLE fps_;
	tml::TIME_REAL sleep_time_;
	tml::TIME_REAL wait_time_;
	tml::TIME_REAL total_time_;
	tml::TIME_REAL over_time_;
	bool start_flg_;

	/*
	tm_l::time::Timer work_one_frame_timer;
	tm_l::time::Timer one_frame_timer;
	tm_l::time::TimerStorage work_one_frame_timer_storage;
	tm_l::time::LimitTimerStorage one_frame_timer_storage;
	*/

public:
	FrameRate();
	virtual ~FrameRate();

	void Init(void);

	INT Start(const UINT);
	void Stop(void);
	void Update(void);
	UINT GetLimit(void) const;
	UINT GetCount(void) const;
	DOUBLE GetFPS(void) const;
};
}


/**
 * @brief GetLimit関数
 * @return limit (limit)
 */
inline UINT tml::FrameRate::GetLimit(void) const
{
	return (this->limit_);
}


/**
 * @brief GetCount関数
 * @return cnt (count)
 */
inline UINT tml::FrameRate::GetCount(void) const
{
	return (this->cnt_);
}


/**
 * @brief GetFPS関数
 * @return fps (fps)
 */
inline DOUBLE tml::FrameRate::GetFPS(void) const
{
	return (this->fps_);
}
