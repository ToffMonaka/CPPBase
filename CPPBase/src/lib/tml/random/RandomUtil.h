/**
 * @file
 * @brief RandomUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "RandomUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief RandomUtil�N���X
 *
 * ���[�e�B���e�B�p�^�[��<br>
 * �G���W���p�^�[��
 */
class RandomUtil
{
public: RandomUtil() = delete;
public: RandomUtil(const RandomUtil &) = delete;
public: RandomUtil &operator =(const RandomUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::RandomUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::RandomUtilEngine> &);

	static CHAR GetCHAR(void);
	static CHAR GetCHAR(const CHAR, const CHAR);
	static SHORT GetSHORT(void);
	static SHORT GetSHORT(const SHORT, const SHORT);
	static INT GetINT(void);
	static INT GetINT(const INT, const INT);
	static LONGLONG GetLONGLONG(void);
	static LONGLONG GetLONGLONG(const LONGLONG, const LONGLONG);
	static FLOAT GetFLOAT(void);
	static FLOAT GetFLOAT(const FLOAT, const FLOAT);
	static DOUBLE GetDOUBLE(void);
	static DOUBLE GetDOUBLE(const DOUBLE, const DOUBLE);
};


/**
 * @brief GetCHAR�֐�
 * @return val (value)
 */
inline CHAR tml::RandomUtil::GetCHAR(void)
{
	return (tml::RandomUtil::engine_->GetCHAR());
}


/**
 * @brief GetCHAR�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
inline CHAR tml::RandomUtil::GetCHAR(const CHAR min, const CHAR max)
{
	return (tml::RandomUtil::engine_->GetCHAR(min, max));
}


/**
 * @brief GetSHORT�֐�
 * @return val (value)
 */
inline SHORT tml::RandomUtil::GetSHORT(void)
{
	return (tml::RandomUtil::engine_->GetSHORT());
}


/**
 * @brief GetSHORT�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
inline SHORT tml::RandomUtil::GetSHORT(const SHORT min, const SHORT max)
{
	return (tml::RandomUtil::engine_->GetSHORT(min, max));
}


/**
 * @brief GetINT�֐�
 * @return val (value)
 */
inline INT tml::RandomUtil::GetINT(void)
{
	return (tml::RandomUtil::engine_->GetINT());
}


/**
 * @brief GetINT�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
inline INT tml::RandomUtil::GetINT(const INT min, const INT max)
{
	return (tml::RandomUtil::engine_->GetINT(min, max));
}


/**
 * @brief GetLONGLONG�֐�
 * @return val (value)
 */
inline LONGLONG tml::RandomUtil::GetLONGLONG(void)
{
	return (tml::RandomUtil::engine_->GetLONGLONG());
}


/**
 * @brief GetLONGLONG�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
inline LONGLONG tml::RandomUtil::GetLONGLONG(const LONGLONG min, const LONGLONG max)
{
	return (tml::RandomUtil::engine_->GetLONGLONG(min, max));
}


/**
 * @brief GetFLOAT�֐�
 * @return val (value)
 */
inline FLOAT tml::RandomUtil::GetFLOAT(void)
{
	return (tml::RandomUtil::engine_->GetFLOAT());
}


/**
 * @brief GetFLOAT�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
inline FLOAT tml::RandomUtil::GetFLOAT(const FLOAT min, const FLOAT max)
{
	return (tml::RandomUtil::engine_->GetFLOAT(min, max));
}


/**
 * @brief GetDOUBLE�֐�
 * @return val (value)
 */
inline DOUBLE tml::RandomUtil::GetDOUBLE(void)
{
	return (tml::RandomUtil::engine_->GetDOUBLE());
}


/**
 * @brief GetDOUBLE�֐�
 * @param min (min)
 * @param max (max)
 * @return val (value)
 */
inline DOUBLE tml::RandomUtil::GetDOUBLE(const DOUBLE min, const DOUBLE max)
{
	return (tml::RandomUtil::engine_->GetDOUBLE(min, max));
}
}
