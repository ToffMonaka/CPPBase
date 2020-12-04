/**
 * @file
 * @brief RandomSeedヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <random>


namespace tml {
/**
 * @brief RandomSeedクラス
 */
class RandomSeed
{
public: RandomSeed(const tml::RandomSeed &) = delete;
public: tml::RandomSeed &operator =(const tml::RandomSeed &) = delete;

private:
	std::mt19937 seed_;

private:
	void Release(void);

public:
	RandomSeed();
	virtual ~RandomSeed();

	void Init(void);
	INT Create(void);

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
};
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
