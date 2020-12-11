/**
 * @file
 * @brief RandomSeed�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <random>


namespace tml {
/**
 * @brief RandomSeed�N���X
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
};
}


/**
 * @brief GetINT�֐�
 * @return val (value)
 */
inline INT tml::RandomSeed::GetINT(void)
{
	std::uniform_int_distribution<INT> rng(std::numeric_limits<INT>::min(), std::numeric_limits<INT>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetINT�֐�
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
 * @brief GetUINT�֐�
 * @return val (value)
 */
inline UINT tml::RandomSeed::GetUINT(void)
{
	std::uniform_int_distribution<UINT> rng(std::numeric_limits<UINT>::min(), std::numeric_limits<UINT>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetUINT�֐�
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
 * @brief GetLONGLONG�֐�
 * @return val (value)
 */
inline LONGLONG tml::RandomSeed::GetLONGLONG(void)
{
	std::uniform_int_distribution<LONGLONG> rng(std::numeric_limits<LONGLONG>::min(), std::numeric_limits<LONGLONG>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetLONGLONG�֐�
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
 * @brief GetULONGLONG�֐�
 * @return val (value)
 */
inline ULONGLONG tml::RandomSeed::GetULONGLONG(void)
{
	std::uniform_int_distribution<ULONGLONG> rng(std::numeric_limits<ULONGLONG>::min(), std::numeric_limits<ULONGLONG>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetULONGLONG�֐�
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
 * @brief GetFLOAT�֐�
 * @return val (value)
 */
inline FLOAT tml::RandomSeed::GetFLOAT(void)
{
	std::uniform_real_distribution<FLOAT> rng(std::numeric_limits<FLOAT>::min(), std::numeric_limits<FLOAT>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetFLOAT�֐�
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
 * @brief GetDOUBLE�֐�
 * @return val (value)
 */
inline DOUBLE tml::RandomSeed::GetDOUBLE(void)
{
	std::uniform_real_distribution<DOUBLE> rng(std::numeric_limits<DOUBLE>::min(), std::numeric_limits<DOUBLE>::max());

	return (rng(this->seed_));
}


/**
 * @brief GetDOUBLE�֐�
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
 * @brief GetValue�֐�
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline INT &tml::RandomSeed::GetValue(INT &dst_val)
{
	dst_val = this->GetINT();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
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
 * @brief GetValue�֐�
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline UINT &tml::RandomSeed::GetValue(UINT &dst_val)
{
	dst_val = this->GetUINT();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
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
 * @brief GetValue�֐�
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline LONGLONG &tml::RandomSeed::GetValue(LONGLONG &dst_val)
{
	dst_val = this->GetLONGLONG();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
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
 * @brief GetValue�֐�
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline ULONGLONG &tml::RandomSeed::GetValue(ULONGLONG &dst_val)
{
	dst_val = this->GetULONGLONG();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
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
 * @brief GetValue�֐�
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline FLOAT &tml::RandomSeed::GetValue(FLOAT &dst_val)
{
	dst_val = this->GetFLOAT();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
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
 * @brief GetValue�֐�
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline DOUBLE &tml::RandomSeed::GetValue(DOUBLE &dst_val)
{
	dst_val = this->GetDOUBLE();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
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
