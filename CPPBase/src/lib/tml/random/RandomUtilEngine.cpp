/**
 * @file
 * @brief RandomUtilEngine�R�[�h�t�@�C��
 */


#include "RandomUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::RandomUtilEngine::RandomUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::RandomUtilEngine::~RandomUtilEngine()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::RandomUtilEngine::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::RandomUtilEngine::Init(void)
{
	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::RandomUtilEngine::Create(void)
{
	this->gen_th_lock_.Lock();

	std::random_device seed_device;

	std::array<std::random_device::result_type, 10U> seed_ary;

	std::generate(seed_ary.begin(), seed_ary.end(), std::ref(seed_device));

	std::seed_seq seed_seq(seed_ary.begin(), seed_ary.end());

	this->gen_.seed(seed_seq);

	this->gen_th_lock_.Unlock();

	return (0);
}


/**
 * @brief GetCHAR�֐�
 * @return val (value)
 */
CHAR tml::RandomUtilEngine::GetCHAR(void)
{
	CHAR val = 0;
	std::uniform_int_distribution<INT> rng(std::numeric_limits<CHAR>::min(), std::numeric_limits<CHAR>::max());

	this->gen_th_lock_.Lock();

	val = static_cast<CHAR>(rng(this->gen_));

	this->gen_th_lock_.Unlock();

	return (val);
}


/**
 * @brief GetCHAR�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
CHAR tml::RandomUtilEngine::GetCHAR(const CHAR min, const CHAR max)
{
	CHAR val = 0;
	std::uniform_int_distribution<INT> rng(min, max);

	this->gen_th_lock_.Lock();

	val = static_cast<CHAR>(rng(this->gen_));

	this->gen_th_lock_.Unlock();

	return (val);
}


/**
 * @brief GetSHORT�֐�
 * @return val (value)
 */
SHORT tml::RandomUtilEngine::GetSHORT(void)
{
	SHORT val = 0;
	std::uniform_int_distribution<INT> rng(std::numeric_limits<SHORT>::min(), std::numeric_limits<SHORT>::max());

	this->gen_th_lock_.Lock();

	val = static_cast<SHORT>(rng(this->gen_));

	this->gen_th_lock_.Unlock();

	return (val);
}


/**
 * @brief GetSHORT�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
SHORT tml::RandomUtilEngine::GetSHORT(const SHORT min, const SHORT max)
{
	SHORT val = 0;
	std::uniform_int_distribution<INT> rng(min, max);

	this->gen_th_lock_.Lock();

	val = static_cast<SHORT>(rng(this->gen_));

	this->gen_th_lock_.Unlock();

	return (val);
}


/**
 * @brief GetINT�֐�
 * @return val (value)
 */
INT tml::RandomUtilEngine::GetINT(void)
{
	INT val = 0;
	std::uniform_int_distribution<INT> rng(std::numeric_limits<INT>::min(), std::numeric_limits<INT>::max());

	this->gen_th_lock_.Lock();

	val = rng(this->gen_);

	this->gen_th_lock_.Unlock();

	return (val);
}


/**
 * @brief GetINT�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
INT tml::RandomUtilEngine::GetINT(const INT min, const INT max)
{
	INT val = 0;
	std::uniform_int_distribution<INT> rng(min, max);

	this->gen_th_lock_.Lock();

	val = rng(this->gen_);

	this->gen_th_lock_.Unlock();

	return (val);
}


/**
 * @brief GetLONGLONG�֐�
 * @return val (value)
 */
LONGLONG tml::RandomUtilEngine::GetLONGLONG(void)
{
	LONGLONG val = 0LL;
	std::uniform_int_distribution<LONGLONG> rng(std::numeric_limits<LONGLONG>::min(), std::numeric_limits<LONGLONG>::max());

	this->gen_th_lock_.Lock();

	val = rng(this->gen_);

	this->gen_th_lock_.Unlock();

	return (val);
}


/**
 * @brief GetLONGLONG�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
LONGLONG tml::RandomUtilEngine::GetLONGLONG(const LONGLONG min, const LONGLONG max)
{
	LONGLONG val = 0LL;
	std::uniform_int_distribution<LONGLONG> rng(min, max);

	this->gen_th_lock_.Lock();

	val = rng(this->gen_);

	this->gen_th_lock_.Unlock();

	return (val);
}


/**
 * @brief GetFLOAT�֐�
 * @return val (value)
 */
FLOAT tml::RandomUtilEngine::GetFLOAT(void)
{
	FLOAT val = 0.0f;
	std::uniform_real_distribution<FLOAT> rng(std::numeric_limits<FLOAT>::min(), std::numeric_limits<FLOAT>::max());

	this->gen_th_lock_.Lock();

	val = rng(this->gen_);

	this->gen_th_lock_.Unlock();

	return (val);
}


/**
 * @brief GetFLOAT�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
FLOAT tml::RandomUtilEngine::GetFLOAT(const FLOAT min, const FLOAT max)
{
	FLOAT val = 0.0f;
	std::uniform_real_distribution<FLOAT> rng(min, max);

	this->gen_th_lock_.Lock();

	val = rng(this->gen_);

	this->gen_th_lock_.Unlock();

	return (val);
}


/**
 * @brief GetDOUBLE�֐�
 * @return val (value)
 */
DOUBLE tml::RandomUtilEngine::GetDOUBLE(void)
{
	DOUBLE val = 0.0;
	std::uniform_real_distribution<DOUBLE> rng(std::numeric_limits<DOUBLE>::min(), std::numeric_limits<DOUBLE>::max());

	this->gen_th_lock_.Lock();

	val = rng(this->gen_);

	this->gen_th_lock_.Unlock();

	return (val);
}


/**
 * @brief GetDOUBLE�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
DOUBLE tml::RandomUtilEngine::GetDOUBLE(const DOUBLE min, const DOUBLE max)
{
	DOUBLE val = 0.0;
	std::uniform_real_distribution<DOUBLE> rng(min, max);

	this->gen_th_lock_.Lock();

	val = rng(this->gen_);

	this->gen_th_lock_.Unlock();

	return (val);
}
