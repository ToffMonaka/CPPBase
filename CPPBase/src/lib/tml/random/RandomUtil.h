/**
 * @file
 * @brief RandomUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
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
public: RandomUtil(const tml::RandomUtil &) = delete;
public: tml::RandomUtil &operator =(const tml::RandomUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::RandomUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::RandomUtilEngine> &);

	static bool CheckThreadFix(void);
	static INT GetINT(void);
	static INT GetINT(const INT, const INT);
	static UINT GetUINT(void);
	static UINT GetUINT(const UINT, const UINT);
	static LONGLONG GetLONGLONG(void);
	static LONGLONG GetLONGLONG(const LONGLONG, const LONGLONG);
	static ULONGLONG GetULONGLONG(void);
	static ULONGLONG GetULONGLONG(const ULONGLONG, const ULONGLONG);
	static FLOAT GetFLOAT(void);
	static FLOAT GetFLOAT(const FLOAT, const FLOAT);
	static DOUBLE GetDOUBLE(void);
	static DOUBLE GetDOUBLE(const DOUBLE, const DOUBLE);
};
}


/**
 * @brief CheckThreadFix�֐�
 * @return res_flg (result_flag)<br>
 * false=���s,true=����
 */
inline bool tml::RandomUtil::CheckThreadFix(void)
{
	return (tml::RandomUtil::th_fix_.Check());
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
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline INT tml::RandomUtil::GetINT(const INT min_val, const INT max_val)
{
	return (tml::RandomUtil::engine_->GetINT(min_val, max_val));
}


/**
 * @brief GetUINT�֐�
 * @return val (value)
 */
inline UINT tml::RandomUtil::GetUINT(void)
{
	return (tml::RandomUtil::engine_->GetUINT());
}


/**
 * @brief GetUINT�֐�
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline UINT tml::RandomUtil::GetUINT(const UINT min_val, const UINT max_val)
{
	return (tml::RandomUtil::engine_->GetUINT(min_val, max_val));
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
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline LONGLONG tml::RandomUtil::GetLONGLONG(const LONGLONG min_val, const LONGLONG max_val)
{
	return (tml::RandomUtil::engine_->GetLONGLONG(min_val, max_val));
}


/**
 * @brief GetULONGLONG�֐�
 * @return val (value)
 */
inline ULONGLONG tml::RandomUtil::GetULONGLONG(void)
{
	return (tml::RandomUtil::engine_->GetULONGLONG());
}


/**
 * @brief GetULONGLONG�֐�
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline ULONGLONG tml::RandomUtil::GetULONGLONG(const ULONGLONG min_val, const ULONGLONG max_val)
{
	return (tml::RandomUtil::engine_->GetULONGLONG(min_val, max_val));
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
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline FLOAT tml::RandomUtil::GetFLOAT(const FLOAT min_val, const FLOAT max_val)
{
	return (tml::RandomUtil::engine_->GetFLOAT(min_val, max_val));
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
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline DOUBLE tml::RandomUtil::GetDOUBLE(const DOUBLE min_val, const DOUBLE max_val)
{
	return (tml::RandomUtil::engine_->GetDOUBLE(min_val, max_val));
}
