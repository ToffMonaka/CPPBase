/**
 * @file
 * @brief Dateコードファイル
 */


#include "Date.h"
#include "../string/StringUtil.h"


/**
 * @brief コンストラクタ
 */
tml::Date::Date() :
	time_(0LL),
	year_(0),
	mon_(0),
	day_(0),
	hour_(0),
	min_(0),
	sec_(0),
	week_day_(tml::ConstantUtil::DATE::WEEK_DAY::SUNDAY)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Date::~Date()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::Date::Init(void)
{
	this->time_ = tml::TIME_SECONDS(0LL);
	this->year_ = 0;
	this->mon_ = 0;
	this->day_ = 0;
	this->hour_ = 0;
	this->min_ = 0;
	this->sec_ = 0;
	this->week_day_ = tml::ConstantUtil::DATE::WEEK_DAY::SUNDAY;

	return;
}


/**
 * @brief SetTime関数
 * @param time (time)
 */
void tml::Date::SetTime(const tml::TIME_SECONDS &time)
{
	if (time.count() > 0LL) {
		this->time_ = time;

		struct tm date;
		time_t date_time = this->time_.count();

		if (localtime_s(&date, &date_time) == 0) {
			this->year_ = date.tm_year + 1900;
			this->mon_ = date.tm_mon + 1;
			this->day_ = date.tm_mday;
			this->hour_ = date.tm_hour;
			this->min_ = date.tm_min;
			this->sec_ = date.tm_sec;
			this->week_day_ = static_cast<tml::ConstantUtil::DATE::WEEK_DAY>(date.tm_wday);
		} else {
			this->Init();
		}
	} else {
		this->Init();
	}

	return;
}


/**
 * @brief GetString関数
 * @param dst_str (string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
const CHAR *tml::Date::GetString(CHAR *dst_str, const size_t dst_str_size) const
{
	if ((dst_str == nullptr)
	|| (dst_str_size < sizeof(CHAR))) {
		return (dst_str);
	}

	dst_str[0] = 0;

	if (dst_str_size < (tml::ConstantUtil::DATE::STRING_LENGTH + 1U)) {
		return (dst_str);
	}

	return (this->GetStringSetStringPart(dst_str, dst_str_size));
}


/**
 * @brief GetString関数
 * @param dst_str (string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
const WCHAR *tml::Date::GetString(WCHAR *dst_str, const size_t dst_str_size) const
{
	if ((dst_str == nullptr)
	|| (dst_str_size < sizeof(WCHAR))) {
		return (dst_str);
	}

	dst_str[0] = 0;

	if (dst_str_size < ((tml::ConstantUtil::DATE::STRING_LENGTH + 1U) << 1)) {
		return (dst_str);
	}

	return (this->GetStringSetStringPart(dst_str, dst_str_size));
}


/**
 * @brief GetString関数
 * @param dst_str (string)
 * @return dst_str (dst_string)
 */
std::string &tml::Date::GetString(std::string &dst_str) const
{
	CHAR str[tml::ConstantUtil::DATE::STRING_LENGTH + 1U] = "";

	dst_str = this->GetStringSetStringPart(str, sizeof(str));

	return (dst_str);
}


/**
 * @brief GetString関数
 * @param dst_str (string)
 * @return dst_str (dst_string)
 */
std::wstring &tml::Date::GetString(std::wstring &dst_str) const
{
	WCHAR str[tml::ConstantUtil::DATE::STRING_LENGTH + 1U] = L"";

	dst_str = this->GetStringSetStringPart(str, sizeof(str));

	return (dst_str);
}


/**
 * @brief GetStringSetStringPart関数
 * @param dst_str (string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
const CHAR *tml::Date::GetStringSetStringPart(CHAR *dst_str, const size_t dst_str_size) const
{
	_snprintf_s(dst_str, dst_str_size, _TRUNCATE,
				"%04d-%02d-%02d %02d:%02d:%02d",
				this->year_, this->mon_, this->day_, this->hour_, this->min_, this->sec_);

	return (dst_str);
}


/**
 * @brief GetStringSetStringPart関数
 * @param dst_str (string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
const WCHAR *tml::Date::GetStringSetStringPart(WCHAR *dst_str, const size_t dst_str_size) const
{
	_snwprintf_s(dst_str, dst_str_size >> 1, _TRUNCATE,
				L"%04d-%02d-%02d %02d:%02d:%02d",
				this->year_, this->mon_, this->day_, this->hour_, this->min_, this->sec_);

	return (dst_str);
}


/**
 * @brief SetString関数
 * @param str (string)
 */
void tml::Date::SetString(const CHAR *str)
{
	if ((str == nullptr)
	|| (strlen(str) != tml::ConstantUtil::DATE::STRING_LENGTH)
	|| (strcmp(str, tml::ConstantUtil::DATE::ZERO_STRING_MB) == 0)) {
		this->Init();

		return;
	}

	size_t str_index = 0U;
	CHAR parts_str[10] = "";

	{// Year Set
		memcpy(parts_str, &str[str_index], 4U);
		parts_str[4] = 0;
		this->year_ = tml::StringUtil::GetUINT(parts_str);

		str_index += 5U;
	}

	{// Month Set
		memcpy(parts_str, &str[str_index], 2U);
		parts_str[2] = 0;
		this->mon_ = tml::StringUtil::GetUINT(parts_str);

		str_index += 3U;
	}

	{// Day Set
		memcpy(parts_str, &str[str_index], 2U);
		parts_str[2] = 0;
		this->day_ = tml::StringUtil::GetUINT(parts_str);

		str_index += 3U;
	}

	{// Hour Set
		memcpy(parts_str, &str[str_index], 2U);
		parts_str[2] = 0;
		this->hour_ = tml::StringUtil::GetUINT(parts_str);

		str_index += 3U;
	}

	{// Minutes Set
		memcpy(parts_str, &str[str_index], 2U);
		parts_str[2] = 0;
		this->min_ = tml::StringUtil::GetUINT(parts_str);

		str_index += 3U;
	}

	{// Seconds Set
		memcpy(parts_str, &str[str_index], 2U);
		parts_str[2] = 0;
		this->sec_ = tml::StringUtil::GetUINT(parts_str);
	}

	this->SetStringSetTimePart();

	return;
}


/**
 * @brief SetString関数
 * @param str (string)
 */
void tml::Date::SetString(const WCHAR *str)
{
	if ((str == nullptr)
	|| (wcslen(str) != tml::ConstantUtil::DATE::STRING_LENGTH)
	|| (wcscmp(str, tml::ConstantUtil::DATE::ZERO_STRING_W) == 0)) {
		this->Init();

		return;
	}

	size_t str_index = 0U;
	WCHAR parts_str[10] = L"";

	{// Year Set
		memcpy(parts_str, &str[str_index], 4U << 1);
		parts_str[4] = 0;
		this->year_ = tml::StringUtil::GetUINT(parts_str);

		str_index += 5U;
	}

	{// Month Set
		memcpy(parts_str, &str[str_index], 2U << 1);
		parts_str[2] = 0;
		this->mon_ = tml::StringUtil::GetUINT(parts_str);

		str_index += 3U;
	}

	{// Day Set
		memcpy(parts_str, &str[str_index], 2U << 1);
		parts_str[2] = 0;
		this->day_ = tml::StringUtil::GetUINT(parts_str);

		str_index += 3U;
	}

	{// Hour Set
		memcpy(parts_str, &str[str_index], 2U << 1);
		parts_str[2] = 0;
		this->hour_ = tml::StringUtil::GetUINT(parts_str);

		str_index += 3U;
	}

	{// Minutes Set
		memcpy(parts_str, &str[str_index], 2U << 1);
		parts_str[2] = 0;
		this->min_ = tml::StringUtil::GetUINT(parts_str);

		str_index += 3U;
	}

	{// Seconds Set
		memcpy(parts_str, &str[str_index], 2U << 1);
		parts_str[2] = 0;
		this->sec_ = tml::StringUtil::GetUINT(parts_str);
	}

	this->SetStringSetTimePart();

	return;
}


/**
 * @brief SetStringSetTimePart関数
 */
void tml::Date::SetStringSetTimePart(void)
{
	struct tm date = {};

	date.tm_year = this->year_ - 1900;
	date.tm_mon = this->mon_ - 1;
	date.tm_mday = this->day_;
	date.tm_hour = this->hour_;
	date.tm_min = this->min_;
	date.tm_sec = this->sec_;
	date.tm_isdst = -1;

	time_t date_time = mktime(&date);

	if (date_time < 0LL) {
		date_time = 0LL;
	}

	this->SetTime(tml::TIME_SECONDS(date_time));

	return;
}
