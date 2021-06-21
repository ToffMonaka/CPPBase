/**
 * @file
 * @brief RandomSeedヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <vector>
#include <random>


namespace tml {
/**
 * @brief RandomSeedクラス
 */
class RandomSeed
{
public: RandomSeed(const tml::RandomSeed &) = delete;
public: tml::RandomSeed &operator =(const tml::RandomSeed &) = delete;

public:
	using SEED_VALUE_TYPE = std::random_device::result_type;

private:
	std::mt19937 seed_;
	std::vector<tml::RandomSeed::SEED_VALUE_TYPE> seed_val_cont_;

public:
	RandomSeed();
	virtual ~RandomSeed();

	std::vector<tml::RandomSeed::SEED_VALUE_TYPE> GetSeedValueContainer(void) const;
	void SetSeedValueContainer(const std::vector<tml::RandomSeed::SEED_VALUE_TYPE> &);
	INT GetInt(void);
	INT GetInt(const INT, const INT);
	UINT GetUInt(void);
	UINT GetUInt(const UINT, const UINT);
	LONGLONG GetLongLong(void);
	LONGLONG GetLongLong(const LONGLONG, const LONGLONG);
	ULONGLONG GetULongLong(void);
	ULONGLONG GetULongLong(const ULONGLONG, const ULONGLONG);
	FLOAT GetFloat(void);
	FLOAT GetFloat(const FLOAT, const FLOAT);
	DOUBLE GetDouble(void);
	DOUBLE GetDouble(const DOUBLE, const DOUBLE);
	bool GetBool(void);
	INT &GetValue(INT &);
	INT &GetValue(INT &, const INT, const INT);
	UINT &GetValue(UINT &);
	UINT &GetValue(UINT &, const UINT, const UINT);
	LONGLONG &GetValue(LONGLONG &);
	LONGLONG &GetValue(LONGLONG &, const LONGLONG, const LONGLONG);
	ULONGLONG &GetValue(ULONGLONG &);
	ULONGLONG &GetValue(ULONGLONG &, const ULONGLONG, const ULONGLONG);
	FLOAT &GetValue(FLOAT &);
	FLOAT &GetValue(FLOAT &, const FLOAT, const FLOAT);
	DOUBLE &GetValue(DOUBLE &);
	DOUBLE &GetValue(DOUBLE &, const DOUBLE, const DOUBLE);
	bool &GetValue(bool &);
};
}


/**
 * @brief GetSeedValueContainer関数
 * @return seed_val_cont (seed_value_container)
 */
inline std::vector<tml::RandomSeed::SEED_VALUE_TYPE> tml::RandomSeed::GetSeedValueContainer(void) const
{
	return (this->seed_val_cont_);
}


/**
 * @brief SetSeedValueContainer関数
 * @param seed_val_cont (seed_value_container)
 */
inline void tml::RandomSeed::SetSeedValueContainer(const std::vector<tml::RandomSeed::SEED_VALUE_TYPE> &seed_val_cont)
{
	this->seed_val_cont_ = seed_val_cont;

	std::seed_seq seed_seq(this->seed_val_cont_.begin(), this->seed_val_cont_.end());

	this->seed_.seed(seed_seq);

	return;
}


/**
 * @brief GetInt関数
 * @return val (value)
 */
inline INT tml::RandomSeed::GetInt(void)
{
	std::uniform_int_distribution<INT> rng(std::numeric_limits<INT>::min(), std::numeric_limits<INT>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetInt関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline INT tml::RandomSeed::GetInt(const INT min_val, const INT max_val)
{
	std::uniform_int_distribution<INT> rng(min_val, max_val);

	return (rng(this->seed_));
}


/**
 * @brief GetUInt関数
 * @return val (value)
 */
inline UINT tml::RandomSeed::GetUInt(void)
{
	std::uniform_int_distribution<UINT> rng(std::numeric_limits<UINT>::min(), std::numeric_limits<UINT>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetUInt関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline UINT tml::RandomSeed::GetUInt(const UINT min_val, const UINT max_val)
{
	std::uniform_int_distribution<UINT> rng(min_val, max_val);

	return (rng(this->seed_));
}


/**
 * @brief GetLongLong関数
 * @return val (value)
 */
inline LONGLONG tml::RandomSeed::GetLongLong(void)
{
	std::uniform_int_distribution<LONGLONG> rng(std::numeric_limits<LONGLONG>::min(), std::numeric_limits<LONGLONG>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetLongLong関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline LONGLONG tml::RandomSeed::GetLongLong(const LONGLONG min_val, const LONGLONG max_val)
{
	std::uniform_int_distribution<LONGLONG> rng(min_val, max_val);

	return (rng(this->seed_));
}


/**
 * @brief GetULongLong関数
 * @return val (value)
 */
inline ULONGLONG tml::RandomSeed::GetULongLong(void)
{
	std::uniform_int_distribution<ULONGLONG> rng(std::numeric_limits<ULONGLONG>::min(), std::numeric_limits<ULONGLONG>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetULongLong関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline ULONGLONG tml::RandomSeed::GetULongLong(const ULONGLONG min_val, const ULONGLONG max_val)
{
	std::uniform_int_distribution<ULONGLONG> rng(min_val, max_val);

	return (rng(this->seed_));
}


/**
 * @brief GetFloat関数
 * @return val (value)
 */
inline FLOAT tml::RandomSeed::GetFloat(void)
{
	std::uniform_real_distribution<FLOAT> rng(std::numeric_limits<FLOAT>::min(), std::numeric_limits<FLOAT>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetFloat関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline FLOAT tml::RandomSeed::GetFloat(const FLOAT min_val, const FLOAT max_val)
{
	std::uniform_real_distribution<FLOAT> rng(min_val, max_val);

	return (rng(this->seed_));
}


/**
 * @brief GetDouble関数
 * @return val (value)
 */
inline DOUBLE tml::RandomSeed::GetDouble(void)
{
	std::uniform_real_distribution<DOUBLE> rng(std::numeric_limits<DOUBLE>::min(), std::numeric_limits<DOUBLE>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetDouble関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline DOUBLE tml::RandomSeed::GetDouble(const DOUBLE min_val, const DOUBLE max_val)
{
	std::uniform_real_distribution<DOUBLE> rng(min_val, max_val);

	return (rng(this->seed_));
}


/**
 * @brief GetBool関数
 * @return val (value)
 */
inline bool tml::RandomSeed::GetBool(void)
{
	return (this->GetInt() & 1);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline INT &tml::RandomSeed::GetValue(INT &dst_val)
{
	dst_val = this->GetInt();

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline INT &tml::RandomSeed::GetValue(INT &dst_val, const INT min_val, const INT max_val)
{
	dst_val = this->GetInt(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline UINT &tml::RandomSeed::GetValue(UINT &dst_val)
{
	dst_val = this->GetUInt();

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline UINT &tml::RandomSeed::GetValue(UINT &dst_val, const UINT min_val, const UINT max_val)
{
	dst_val = this->GetUInt(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline LONGLONG &tml::RandomSeed::GetValue(LONGLONG &dst_val)
{
	dst_val = this->GetLongLong();

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline LONGLONG &tml::RandomSeed::GetValue(LONGLONG &dst_val, const LONGLONG min_val, const LONGLONG max_val)
{
	dst_val = this->GetLongLong(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline ULONGLONG &tml::RandomSeed::GetValue(ULONGLONG &dst_val)
{
	dst_val = this->GetULongLong();

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline ULONGLONG &tml::RandomSeed::GetValue(ULONGLONG &dst_val, const ULONGLONG min_val, const ULONGLONG max_val)
{
	dst_val = this->GetULongLong(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline FLOAT &tml::RandomSeed::GetValue(FLOAT &dst_val)
{
	dst_val = this->GetFloat();

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline FLOAT &tml::RandomSeed::GetValue(FLOAT &dst_val, const FLOAT min_val, const FLOAT max_val)
{
	dst_val = this->GetFloat(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline DOUBLE &tml::RandomSeed::GetValue(DOUBLE &dst_val)
{
	dst_val = this->GetDouble();

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline DOUBLE &tml::RandomSeed::GetValue(DOUBLE &dst_val, const DOUBLE min_val, const DOUBLE max_val)
{
	dst_val = this->GetDouble(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline bool &tml::RandomSeed::GetValue(bool &dst_val)
{
	dst_val = this->GetBool();

	return (dst_val);
}
