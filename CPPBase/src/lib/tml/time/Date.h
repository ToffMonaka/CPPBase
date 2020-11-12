/**
 * @file
 * @brief Dateヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
namespace DateConstantUtil {
enum class WEEK_DAY : UCHAR {
	SUNDAY = 0,
	MONDAY,
	TUESDAY,
	WEDNESDAY,
	THURSDAY,
	FRIDAY,
	SATURDAY
};
const size_t STRING_LENGTH = 19U;
const CHAR ZERO_STRING[] = "0000-00-00 00:00:00";
const WCHAR ZERO_STRING_W[] = L"0000-00-00 00:00:00";
}


/**
 * @brief Dateクラス
 */
class Date
{
public: Date(const Date &) = delete;
public: Date &operator =(const Date &) = delete;

private:
	tml::TIME_SECONDS time_;
	USHORT year_;
	UCHAR mon_;
	UCHAR day_;
	UCHAR hour_;
	UCHAR min_;
	UCHAR sec_;
	tml::DateConstantUtil::WEEK_DAY week_day_;

public:
	static tml::TIME_SECONDS GetNowTime(void);

private:
	void SetTime(void);

public:
	Date();
	virtual ~Date();

	void Init(void);

	void SetNowTime(void);
	tml::TIME_SECONDS GetTime(void) const;
	void SetTime(const tml::TIME_SECONDS &);
	USHORT GetYear(void) const;
	UCHAR GetMonth(void) const;
	UCHAR GetDay(void) const;
	UCHAR GetHour(void) const;
	UCHAR GetMinutes(void) const;
	UCHAR GetSeconds(void) const;
	tml::DateConstantUtil::WEEK_DAY GetWeekDay(void) const;
	CHAR *GetString(CHAR *, const size_t) const;
	WCHAR *GetStringW(WCHAR *, const size_t) const;
	std::string GetString(void) const;
	std::wstring GetStringW(void) const;
	void SetString(const CHAR *);
	void SetString(const WCHAR *);
};
}


/**
 * @brief GetNowTime関数
 * @return now_time (now_time)
 */
inline tml::TIME_SECONDS tml::Date::GetNowTime(void)
{
	auto now_time = std::chrono::system_clock::now();

	return (tml::CastTime<tml::TIME_SECONDS>(now_time.time_since_epoch()));
}


/**
 * @brief SetNowTime関数
 */
inline void tml::Date::SetNowTime(void)
{
	auto now_time = std::chrono::system_clock::now();

	this->SetTime(tml::CastTime<tml::TIME_SECONDS>(now_time.time_since_epoch()));

	return;
}


/**
 * @brief GetTime関数
 * @return time (time)
 */
inline tml::TIME_SECONDS tml::Date::GetTime(void) const
{
	return (this->time_);
}


/**
 * @brief GetYear関数
 * @return year (year)
 */
inline USHORT tml::Date::GetYear(void) const
{
	return (this->year_);
}


/**
 * @brief GetMonth関数
 * @return mon (month)
 */
inline UCHAR tml::Date::GetMonth(void) const
{
	return (this->mon_);
}


/**
 * @brief GetDay関数
 * @return day (day)
 */
inline UCHAR tml::Date::GetDay(void) const
{
	return (this->day_);
}


/**
 * @brief GetHour関数
 * @return hour (hour)
 */
inline UCHAR tml::Date::GetHour(void) const
{
	return (this->hour_);
}


/**
 * @brief GetMinutes関数
 * @return min (minutes)
 */
inline UCHAR tml::Date::GetMinutes(void) const
{
	return (this->min_);
}


/**
 * @brief GetSeconds関数
 * @return sec (seconds)
 */
inline UCHAR tml::Date::GetSeconds(void) const
{
	return (this->sec_);
}


/**
 * @brief GetWeekDay関数
 * @return week_day (week_day)
 */
inline tml::DateConstantUtil::WEEK_DAY tml::Date::GetWeekDay(void) const
{
	return (this->week_day_);
}
