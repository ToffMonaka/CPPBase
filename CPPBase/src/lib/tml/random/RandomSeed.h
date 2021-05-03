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
	INT GetINT(void);
	INT GetINT(const INT, const INT);
	UINT GetUINT(void);
	UINT GetUINT(const UINT, const UINT);
	LONGLONG GetLONGLONG(void);
	LONGLONG GetLONGLONG(const LONGLONG, const LONGLONG);
	ULONGLONG GetULONGLONG(void);
	ULONGLONG GetULONGLONG(const ULONGLONG, const ULONGLONG);
	FLOAT GetFLOAT(void);
	FLOAT GetFLOAT(const FLOAT, const FLOAT);
	DOUBLE GetDOUBLE(void);
	DOUBLE GetDOUBLE(const DOUBLE, const DOUBLE);
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
 * @brief GetINT関数
 * @return val (value)
 */
inline INT tml::RandomSeed::GetINT(void)
{
	std::uniform_int_distribution<INT> rng(std::numeric_limits<INT>::min(), std::numeric_limits<INT>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetINT関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline INT tml::RandomSeed::GetINT(const INT min_val, const INT max_val)
{
	std::uniform_int_distribution<INT> rng(min_val, max_val);

	return (rng(this->seed_));
}


/**
 * @brief GetUINT関数
 * @return val (value)
 */
inline UINT tml::RandomSeed::GetUINT(void)
{
	std::uniform_int_distribution<UINT> rng(std::numeric_limits<UINT>::min(), std::numeric_limits<UINT>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetUINT関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline UINT tml::RandomSeed::GetUINT(const UINT min_val, const UINT max_val)
{
	std::uniform_int_distribution<UINT> rng(min_val, max_val);

	return (rng(this->seed_));
}


/**
 * @brief GetLONGLONG関数
 * @return val (value)
 */
inline LONGLONG tml::RandomSeed::GetLONGLONG(void)
{
	std::uniform_int_distribution<LONGLONG> rng(std::numeric_limits<LONGLONG>::min(), std::numeric_limits<LONGLONG>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetLONGLONG関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline LONGLONG tml::RandomSeed::GetLONGLONG(const LONGLONG min_val, const LONGLONG max_val)
{
	std::uniform_int_distribution<LONGLONG> rng(min_val, max_val);

	return (rng(this->seed_));
}


/**
 * @brief GetULONGLONG関数
 * @return val (value)
 */
inline ULONGLONG tml::RandomSeed::GetULONGLONG(void)
{
	std::uniform_int_distribution<ULONGLONG> rng(std::numeric_limits<ULONGLONG>::min(), std::numeric_limits<ULONGLONG>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetULONGLONG関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline ULONGLONG tml::RandomSeed::GetULONGLONG(const ULONGLONG min_val, const ULONGLONG max_val)
{
	std::uniform_int_distribution<ULONGLONG> rng(min_val, max_val);

	return (rng(this->seed_));
}


/**
 * @brief GetFLOAT関数
 * @return val (value)
 */
inline FLOAT tml::RandomSeed::GetFLOAT(void)
{
	std::uniform_real_distribution<FLOAT> rng(std::numeric_limits<FLOAT>::min(), std::numeric_limits<FLOAT>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetFLOAT関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline FLOAT tml::RandomSeed::GetFLOAT(const FLOAT min_val, const FLOAT max_val)
{
	std::uniform_real_distribution<FLOAT> rng(min_val, max_val);

	return (rng(this->seed_));
}


/**
 * @brief GetDOUBLE関数
 * @return val (value)
 */
inline DOUBLE tml::RandomSeed::GetDOUBLE(void)
{
	std::uniform_real_distribution<DOUBLE> rng(std::numeric_limits<DOUBLE>::min(), std::numeric_limits<DOUBLE>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetDOUBLE関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline DOUBLE tml::RandomSeed::GetDOUBLE(const DOUBLE min_val, const DOUBLE max_val)
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
	return (this->GetINT() & 1);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline INT &tml::RandomSeed::GetValue(INT &dst_val)
{
	dst_val = this->GetINT();

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
	dst_val = this->GetINT(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline UINT &tml::RandomSeed::GetValue(UINT &dst_val)
{
	dst_val = this->GetUINT();

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
	dst_val = this->GetUINT(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline LONGLONG &tml::RandomSeed::GetValue(LONGLONG &dst_val)
{
	dst_val = this->GetLONGLONG();

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
	dst_val = this->GetLONGLONG(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline ULONGLONG &tml::RandomSeed::GetValue(ULONGLONG &dst_val)
{
	dst_val = this->GetULONGLONG();

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
	dst_val = this->GetULONGLONG(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline FLOAT &tml::RandomSeed::GetValue(FLOAT &dst_val)
{
	dst_val = this->GetFLOAT();

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
	dst_val = this->GetFLOAT(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline DOUBLE &tml::RandomSeed::GetValue(DOUBLE &dst_val)
{
	dst_val = this->GetDOUBLE();

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
	dst_val = this->GetDOUBLE(min_val, max_val);

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
