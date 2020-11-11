/**
 * @file
 * @brief RandomUtilEngineコードファイル
 */


#include "RandomUtilEngine.h"
#include <array>


/**
 * @brief コンストラクタ
 */
tml::RandomUtilEngine::RandomUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::RandomUtilEngine::~RandomUtilEngine()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::RandomUtilEngine::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::RandomUtilEngine::Init(void)
{
	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::RandomUtilEngine::Create(void)
{
	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		std::random_device seed_device;

		std::array<std::random_device::result_type, 10U> seed_ary;

		std::generate(seed_ary.begin(), seed_ary.end(), std::ref(seed_device));

		std::seed_seq seed_seq(seed_ary.begin(), seed_ary.end());

		this->gen_.seed(seed_seq);
	}

	return (0);
}


/**
 * @brief GetINT関数
 * @return val (value)
 */
INT tml::RandomUtilEngine::GetINT(void)
{
	INT val = 0;
	std::uniform_int_distribution<INT> rng(std::numeric_limits<INT>::min(), std::numeric_limits<INT>::max());

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}


/**
 * @brief GetINT関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
INT tml::RandomUtilEngine::GetINT(const INT min_val, const INT max_val)
{
	INT val = 0;
	std::uniform_int_distribution<INT> rng(min_val, max_val);

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}


/**
 * @brief GetUINT関数
 * @return val (value)
 */
UINT tml::RandomUtilEngine::GetUINT(void)
{
	UINT val = 0U;
	std::uniform_int_distribution<UINT> rng(std::numeric_limits<UINT>::min(), std::numeric_limits<UINT>::max());

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}


/**
 * @brief GetUINT関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
UINT tml::RandomUtilEngine::GetUINT(const UINT min_val, const UINT max_val)
{
	UINT val = 0U;
	std::uniform_int_distribution<UINT> rng(min_val, max_val);

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}


/**
 * @brief GetLONGLONG関数
 * @return val (value)
 */
LONGLONG tml::RandomUtilEngine::GetLONGLONG(void)
{
	LONGLONG val = 0LL;
	std::uniform_int_distribution<LONGLONG> rng(std::numeric_limits<LONGLONG>::min(), std::numeric_limits<LONGLONG>::max());

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}


/**
 * @brief GetLONGLONG関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
LONGLONG tml::RandomUtilEngine::GetLONGLONG(const LONGLONG min_val, const LONGLONG max_val)
{
	LONGLONG val = 0LL;
	std::uniform_int_distribution<LONGLONG> rng(min_val, max_val);

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}


/**
 * @brief GetULONGLONG関数
 * @return val (value)
 */
ULONGLONG tml::RandomUtilEngine::GetULONGLONG(void)
{
	ULONGLONG val = 0ULL;
	std::uniform_int_distribution<ULONGLONG> rng(std::numeric_limits<ULONGLONG>::min(), std::numeric_limits<ULONGLONG>::max());

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}


/**
 * @brief GetULONGLONG関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
ULONGLONG tml::RandomUtilEngine::GetULONGLONG(const ULONGLONG min_val, const ULONGLONG max_val)
{
	ULONGLONG val = 0ULL;
	std::uniform_int_distribution<ULONGLONG> rng(min_val, max_val);

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}


/**
 * @brief GetFLOAT関数
 * @return val (value)
 */
FLOAT tml::RandomUtilEngine::GetFLOAT(void)
{
	FLOAT val = 0.0f;
	std::uniform_real_distribution<FLOAT> rng(std::numeric_limits<FLOAT>::min(), std::numeric_limits<FLOAT>::max());

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}


/**
 * @brief GetFLOAT関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
FLOAT tml::RandomUtilEngine::GetFLOAT(const FLOAT min_val, const FLOAT max_val)
{
	FLOAT val = 0.0f;
	std::uniform_real_distribution<FLOAT> rng(min_val, max_val);

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}


/**
 * @brief GetDOUBLE関数
 * @return val (value)
 */
DOUBLE tml::RandomUtilEngine::GetDOUBLE(void)
{
	DOUBLE val = 0.0;
	std::uniform_real_distribution<DOUBLE> rng(std::numeric_limits<DOUBLE>::min(), std::numeric_limits<DOUBLE>::max());

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}


/**
 * @brief GetDOUBLE関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
DOUBLE tml::RandomUtilEngine::GetDOUBLE(const DOUBLE min_val, const DOUBLE max_val)
{
	DOUBLE val = 0.0;
	std::uniform_real_distribution<DOUBLE> rng(min_val, max_val);

	{tml::ThreadLockBlock th_lock_block(this->gen_th_lock_);
		val = rng(this->gen_);
	}

	return (val);
}
