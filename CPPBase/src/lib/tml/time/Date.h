/**
 * @file
 * @brief Date�w�b�_�[�t�@�C��
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
const WCHAR ZERO_STRING[] = L"0000-00-00 00:00:00";
}


/**
 * @brief Date�N���X
 */
class Date
{
public: Date(const Date &) = delete;
public: Date &operator =(const Date &) = delete;

private:
	tml::TIME_MILLI time_;
	USHORT year_;
	UCHAR mon_;
	UCHAR day_;
	UCHAR hour_;
	UCHAR min_;
	UCHAR sec_;
	tml::DateConstantUtil::WEEK_DAY week_day_;

public:
	static tml::TIME_MILLI GetNowTime(void);

public:
	Date();
	virtual ~Date();

	void Init(void);

	void SetNowTime(void);
	tml::TIME_MILLI GetTime(void) const;
	void SetTime(const tml::TIME_MILLI &);
	USHORT GetYear(void) const;
	UCHAR GetMonth(void) const;
	UCHAR GetDay(void) const;
	UCHAR GetHour(void) const;
	UCHAR GetMinutes(void) const;
	UCHAR GetSeconds(void) const;
	tml::DateConstantUtil::WEEK_DAY GetWeekDay(void) const;
	WCHAR *GetString(WCHAR *, const size_t) const;
	void SetString(const WCHAR *);
};
}


/**
 * @brief GetNowTime�֐�
 * @return now_time (now_time)
 */
inline tml::TIME_MILLI tml::Date::GetNowTime(void)
{
	auto now_time = std::chrono::system_clock::now();

	return (tml::CastTime<tml::TIME_MILLI>(now_time.time_since_epoch()));
}


/**
 * @brief SetNowTime�֐�
 */
inline void tml::Date::SetNowTime(void)
{
	auto now_time = std::chrono::system_clock::now();

	this->SetTime(tml::CastTime<tml::TIME_MILLI>(now_time.time_since_epoch()));

	return;
}


/**
 * @brief GetTime�֐�
 * @return time (time)
 */
inline tml::TIME_MILLI tml::Date::GetTime(void) const
{
	return (this->time_);
}


/**
 * @brief GetYear�֐�
 * @return year (year)
 */
inline USHORT tml::Date::GetYear(void) const
{
	return (this->year_);
}


/**
 * @brief GetMonth�֐�
 * @return mon (month)
 */
inline UCHAR tml::Date::GetMonth(void) const
{
	return (this->mon_);
}


/**
 * @brief GetDay�֐�
 * @return day (day)
 */
inline UCHAR tml::Date::GetDay(void) const
{
	return (this->day_);
}


/**
 * @brief GetHour�֐�
 * @return hour (hour)
 */
inline UCHAR tml::Date::GetHour(void) const
{
	return (this->hour_);
}


/**
 * @brief GetMinutes�֐�
 * @return min (minutes)
 */
inline UCHAR tml::Date::GetMinutes(void) const
{
	return (this->min_);
}


/**
 * @brief GetSeconds�֐�
 * @return sec (seconds)
 */
inline UCHAR tml::Date::GetSeconds(void) const
{
	return (this->sec_);
}


/**
 * @brief GetWeekDay�֐�
 * @return week_day (week_day)
 */
inline tml::DateConstantUtil::WEEK_DAY tml::Date::GetWeekDay(void) const
{
	return (this->week_day_);
}
