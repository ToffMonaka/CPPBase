/**
 * @file
 * @brief Dateヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_DATE.h"


namespace tml {
/**
 * @brief Dateクラス
 */
class Date
{
private:
	tml::TIME_SECONDS time_;
	USHORT year_;
	UCHAR mon_;
	UCHAR day_;
	UCHAR hour_;
	UCHAR min_;
	UCHAR sec_;
	tml::ConstantUtil::DATE::WEEK_DAY week_day_;

public:
	static tml::TIME_SECONDS GetNowTime(void);

private:
	CHAR *GetStringSetStringPart(CHAR *, const size_t) const;
	WCHAR *GetStringSetStringPart(WCHAR *, const size_t) const;
	void SetStringSetTimePart(void);

protected:
	void Release(void);

public:
	Date();
	Date(const tml::Date &);
	tml::Date &operator =(const tml::Date &);
	Date(tml::Date &&) noexcept;
	tml::Date &operator =(tml::Date &&) noexcept;
	virtual ~Date();

	virtual void Init(void);

	void SetNowTime(void);
	const tml::TIME_SECONDS &GetTime(void) const;
	void SetTime(const tml::TIME_SECONDS &);
	USHORT GetYear(void) const;
	UCHAR GetMonth(void) const;
	UCHAR GetDay(void) const;
	UCHAR GetHour(void) const;
	UCHAR GetMinutes(void) const;
	UCHAR GetSeconds(void) const;
	tml::ConstantUtil::DATE::WEEK_DAY GetWeekDay(void) const;
	CHAR *GetString(CHAR *, const size_t) const;
	WCHAR *GetString(WCHAR *, const size_t) const;
	std::string &GetString(std::string &) const;
	std::wstring &GetString(std::wstring &) const;
	void SetString(const CHAR *);
	void SetString(const WCHAR *);
};
}


/**
 * @brief Release関数
 */
inline void tml::Date::Release(void)
{
	return;
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
inline const tml::TIME_SECONDS &tml::Date::GetTime(void) const
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
inline tml::ConstantUtil::DATE::WEEK_DAY tml::Date::GetWeekDay(void) const
{
	return (this->week_day_);
}
