/**
 * @file
 * @brief Clockヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief Clockクラス
 */
class Clock
{
public: Clock(const Clock &) = delete;
public: Clock &operator =(const Clock &) = delete;

private:
	tml::TIME_MILLI time_;

public:
	static tml::TIME_MILLI GetNowTime(void);

public:
	Clock();
	virtual ~Clock();

	void Init(void);

	void SetNowTime(void);
	tml::TIME_MILLI GetTime(void) const;
	void SetTime(const tml::TIME_MILLI &);
};
}


/**
 * @brief GetNowTime関数
 * @return now_time (now_time)
 */
inline tml::TIME_MILLI tml::Clock::GetNowTime(void)
{
	auto now_time = std::chrono::system_clock::now();

	return (tml::CastTime<tml::TIME_MILLI>(now_time.time_since_epoch()));
}


/**
 * @brief SetNowTime関数
 */
inline void tml::Clock::SetNowTime(void)
{
	auto now_time = std::chrono::system_clock::now();

	this->SetTime(tml::CastTime<tml::TIME_MILLI>(now_time.time_since_epoch()));

	return;
}


/**
 * @brief GetTime関数
 * @return time (time)
 */
inline tml::TIME_MILLI tml::Clock::GetTime(void) const
{
	return (this->time_);
}
