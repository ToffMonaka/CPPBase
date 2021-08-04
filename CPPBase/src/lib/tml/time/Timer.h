/**
 * @file
 * @brief Timerヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
/**
 * @brief Timerクラス
 */
class Timer
{
private:
	std::chrono::steady_clock::time_point start_time_;
	tml::TIME_REAL elapsed_time_;
	bool started_flg_;

private:
	void Release(void);

public:
	Timer();
	Timer(const tml::Timer &);
	tml::Timer &operator =(const tml::Timer &);
	Timer(tml::Timer &&) noexcept;
	tml::Timer &operator =(tml::Timer &&) noexcept;
	virtual ~Timer();

	virtual void Init(void);

	INT Start(void);
	void Stop(void);
	void Update(void);
	const tml::TIME_REAL &GetElapsedTime(void) const;
};
}


/**
 * @brief Release関数
 */
inline void tml::Timer::Release(void)
{
	return;
}


/**
 * @brief GetElapsedTime関数
 * @return elapsed_time (elapsed_time)
 */
inline const tml::TIME_REAL &tml::Timer::GetElapsedTime(void) const
{
	return (this->elapsed_time_);
}
