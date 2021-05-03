/**
 * @file
 * @brief RandomUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/ThreadFix.h"
#include "RandomUtilEngine.h"
#include "RandomSeed.h"


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
	static tml::RandomSeed seed_;
	static tml::SpinThreadLock seed_th_lock_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::RandomUtilEngine> &);

	static bool CheckThreadFix(void);
	static std::vector<tml::RandomSeed::SEED_VALUE_TYPE> GetSeedValueContainer(void);
	static void SetSeedValueContainer(const std::vector<tml::RandomSeed::SEED_VALUE_TYPE> &);
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
	static bool GetBool(void);
	static INT &GetValue(INT &);
	static INT &GetValue(INT &, const INT, const INT);
	static UINT &GetValue(UINT &);
	static UINT &GetValue(UINT &, const UINT, const UINT);
	static LONGLONG &GetValue(LONGLONG &);
	static LONGLONG &GetValue(LONGLONG &, const LONGLONG, const LONGLONG);
	static ULONGLONG &GetValue(ULONGLONG &);
	static ULONGLONG &GetValue(ULONGLONG &, const ULONGLONG, const ULONGLONG);
	static FLOAT &GetValue(FLOAT &);
	static FLOAT &GetValue(FLOAT &, const FLOAT, const FLOAT);
	static DOUBLE &GetValue(DOUBLE &);
	static DOUBLE &GetValue(DOUBLE &, const DOUBLE, const DOUBLE);
	static bool &GetValue(bool &);
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
 * @brief GetSeedValueContainer�֐�
 *
 * Create�֐��s�v
 *
 * @return seed_val_cont (seed_value_container)
 */
inline std::vector<tml::RandomSeed::SEED_VALUE_TYPE> tml::RandomUtil::GetSeedValueContainer(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetSeedValueContainer());
}


/**
 * @brief SetSeedValueContainer�֐�
 *
 * Create�֐��s�v
 *
 * @param seed_val_cont (seed_value_container)
 */
inline void tml::RandomUtil::SetSeedValueContainer(const std::vector<tml::RandomSeed::SEED_VALUE_TYPE> &seed_val_cont)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	tml::RandomUtil::seed_.SetSeedValueContainer(seed_val_cont);

	return;
}


/**
 * @brief GetINT�֐�
 *
 * Create�֐��s�v
 *
 * @return val (value)
 */
inline INT tml::RandomUtil::GetINT(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetINT());
}


/**
 * @brief GetINT�֐�
 *
 * Create�֐��s�v
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline INT tml::RandomUtil::GetINT(const INT min_val, const INT max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetINT(min_val, max_val));
}


/**
 * @brief GetUINT�֐�
 *
 * Create�֐��s�v
 *
 * @return val (value)
 */
inline UINT tml::RandomUtil::GetUINT(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetUINT());
}


/**
 * @brief GetUINT�֐�
 *
 * Create�֐��s�v
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline UINT tml::RandomUtil::GetUINT(const UINT min_val, const UINT max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetUINT(min_val, max_val));
}


/**
 * @brief GetLONGLONG�֐�
 *
 * Create�֐��s�v
 *
 * @return val (value)
 */
inline LONGLONG tml::RandomUtil::GetLONGLONG(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetLONGLONG());
}


/**
 * @brief GetLONGLONG�֐�
 *
 * Create�֐��s�v
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline LONGLONG tml::RandomUtil::GetLONGLONG(const LONGLONG min_val, const LONGLONG max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetLONGLONG(min_val, max_val));
}


/**
 * @brief GetULONGLONG�֐�
 *
 * Create�֐��s�v
 *
 * @return val (value)
 */
inline ULONGLONG tml::RandomUtil::GetULONGLONG(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetULONGLONG());
}


/**
 * @brief GetULONGLONG�֐�
 *
 * Create�֐��s�v
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline ULONGLONG tml::RandomUtil::GetULONGLONG(const ULONGLONG min_val, const ULONGLONG max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetULONGLONG(min_val, max_val));
}


/**
 * @brief GetFLOAT�֐�
 *
 * Create�֐��s�v
 *
 * @return val (value)
 */
inline FLOAT tml::RandomUtil::GetFLOAT(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetFLOAT());
}


/**
 * @brief GetFLOAT�֐�
 *
 * Create�֐��s�v
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline FLOAT tml::RandomUtil::GetFLOAT(const FLOAT min_val, const FLOAT max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetFLOAT(min_val, max_val));
}


/**
 * @brief GetDOUBLE�֐�
 *
 * Create�֐��s�v
 *
 * @return val (value)
 */
inline DOUBLE tml::RandomUtil::GetDOUBLE(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetDOUBLE());
}


/**
 * @brief GetDOUBLE�֐�
 *
 * Create�֐��s�v
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline DOUBLE tml::RandomUtil::GetDOUBLE(const DOUBLE min_val, const DOUBLE max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetDOUBLE(min_val, max_val));
}


/**
 * @brief GetBool�֐�
 *
 * Create�֐��s�v
 *
 * @return val (value)
 */
inline bool tml::RandomUtil::GetBool(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetBool());
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline INT &tml::RandomUtil::GetValue(INT &dst_val)
{
	dst_val = tml::RandomUtil::GetINT();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline INT &tml::RandomUtil::GetValue(INT &dst_val, const INT min_val, const INT max_val)
{
	dst_val = tml::RandomUtil::GetINT(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline UINT &tml::RandomUtil::GetValue(UINT &dst_val)
{
	dst_val = tml::RandomUtil::GetUINT();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline UINT &tml::RandomUtil::GetValue(UINT &dst_val, const UINT min_val, const UINT max_val)
{
	dst_val = tml::RandomUtil::GetUINT(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline LONGLONG &tml::RandomUtil::GetValue(LONGLONG &dst_val)
{
	dst_val = tml::RandomUtil::GetLONGLONG();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline LONGLONG &tml::RandomUtil::GetValue(LONGLONG &dst_val, const LONGLONG min_val, const LONGLONG max_val)
{
	dst_val = tml::RandomUtil::GetLONGLONG(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline ULONGLONG &tml::RandomUtil::GetValue(ULONGLONG &dst_val)
{
	dst_val = tml::RandomUtil::GetULONGLONG();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline ULONGLONG &tml::RandomUtil::GetValue(ULONGLONG &dst_val, const ULONGLONG min_val, const ULONGLONG max_val)
{
	dst_val = tml::RandomUtil::GetULONGLONG(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline FLOAT &tml::RandomUtil::GetValue(FLOAT &dst_val)
{
	dst_val = tml::RandomUtil::GetFLOAT();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline FLOAT &tml::RandomUtil::GetValue(FLOAT &dst_val, const FLOAT min_val, const FLOAT max_val)
{
	dst_val = tml::RandomUtil::GetFLOAT(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline DOUBLE &tml::RandomUtil::GetValue(DOUBLE &dst_val)
{
	dst_val = tml::RandomUtil::GetDOUBLE();

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline DOUBLE &tml::RandomUtil::GetValue(DOUBLE &dst_val, const DOUBLE min_val, const DOUBLE max_val)
{
	dst_val = tml::RandomUtil::GetDOUBLE(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline bool &tml::RandomUtil::GetValue(bool &dst_val)
{
	dst_val = tml::RandomUtil::GetBool();

	return (dst_val);
}
