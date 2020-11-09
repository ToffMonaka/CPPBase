/**
 * @file
 * @brief Timerヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief Timerクラス
 */
class Timer
{
public: Timer(const Timer &) = delete;
public: Timer &operator =(const Timer &) = delete;

private:
	std::chrono::steady_clock::time_point start_time_;
	tml::TIME_REAL elapsed_time_;
	bool started_flg_;

public:
	Timer();
	virtual ~Timer();

	void Init(void);

	INT Start(void);
	void Stop(void);
	tml::TIME_REAL GetElapsedTime(void) const;
};
}


/**
 * @brief GetElapsedTime関数
 * @return elapsed_time (elapsed_time)
 */
inline tml::TIME_REAL tml::Timer::GetElapsedTime(void) const
{
	return ((this->started_flg_) ? tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - this->start_time_) : this->elapsed_time_);
}
