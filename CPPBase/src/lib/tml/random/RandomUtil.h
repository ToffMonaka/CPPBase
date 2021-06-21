/**
 * @file
 * @brief RandomUtilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../util/Util.h"
#include "RandomUtilEngine.h"
#include "RandomSeed.h"


namespace tml {
/**
 * @brief RandomUtilクラス
 *
 * ユーティリティパターン<br>
 * エンジンパターン
 */
class RandomUtil
{
public: RandomUtil() = delete;
public: RandomUtil(const tml::RandomUtil &) = delete;
public: tml::RandomUtil &operator =(const tml::RandomUtil &) = delete;

private:
	static std::unique_ptr<tml::RandomUtilEngine> engine_;
	static tml::RandomSeed seed_;
	static tml::SpinThreadLock seed_th_lock_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::RandomUtilEngine> &);

	static bool CheckFixedThread(void);
	static std::vector<tml::RandomSeed::SEED_VALUE_TYPE> GetSeedValueContainer(void);
	static void SetSeedValueContainer(const std::vector<tml::RandomSeed::SEED_VALUE_TYPE> &);
	static INT GetInt(void);
	static INT GetInt(const INT, const INT);
	static UINT GetUInt(void);
	static UINT GetUInt(const UINT, const UINT);
	static LONGLONG GetLongLong(void);
	static LONGLONG GetLongLong(const LONGLONG, const LONGLONG);
	static ULONGLONG GetULongLong(void);
	static ULONGLONG GetULongLong(const ULONGLONG, const ULONGLONG);
	static FLOAT GetFloat(void);
	static FLOAT GetFloat(const FLOAT, const FLOAT);
	static DOUBLE GetDouble(void);
	static DOUBLE GetDouble(const DOUBLE, const DOUBLE);
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
 * @brief CheckFixedThread関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::RandomUtil::CheckFixedThread(void)
{
	return (tml::Util::CheckFixedThread());
}


/**
 * @brief GetSeedValueContainer関数
 *
 * Create関数不要
 *
 * @return seed_val_cont (seed_value_container)
 */
inline std::vector<tml::RandomSeed::SEED_VALUE_TYPE> tml::RandomUtil::GetSeedValueContainer(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetSeedValueContainer());
}


/**
 * @brief SetSeedValueContainer関数
 *
 * Create関数不要
 *
 * @param seed_val_cont (seed_value_container)
 */
inline void tml::RandomUtil::SetSeedValueContainer(const std::vector<tml::RandomSeed::SEED_VALUE_TYPE> &seed_val_cont)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	tml::RandomUtil::seed_.SetSeedValueContainer(seed_val_cont);

	return;
}


/**
 * @brief GetInt関数
 *
 * Create関数不要
 *
 * @return val (value)
 */
inline INT tml::RandomUtil::GetInt(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetInt());
}


/**
 * @brief GetInt関数
 *
 * Create関数不要
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline INT tml::RandomUtil::GetInt(const INT min_val, const INT max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetInt(min_val, max_val));
}


/**
 * @brief GetUInt関数
 *
 * Create関数不要
 *
 * @return val (value)
 */
inline UINT tml::RandomUtil::GetUInt(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetUInt());
}


/**
 * @brief GetUInt関数
 *
 * Create関数不要
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline UINT tml::RandomUtil::GetUInt(const UINT min_val, const UINT max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetUInt(min_val, max_val));
}


/**
 * @brief GetLongLong関数
 *
 * Create関数不要
 *
 * @return val (value)
 */
inline LONGLONG tml::RandomUtil::GetLongLong(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetLongLong());
}


/**
 * @brief GetLongLong関数
 *
 * Create関数不要
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline LONGLONG tml::RandomUtil::GetLongLong(const LONGLONG min_val, const LONGLONG max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetLongLong(min_val, max_val));
}


/**
 * @brief GetULongLong関数
 *
 * Create関数不要
 *
 * @return val (value)
 */
inline ULONGLONG tml::RandomUtil::GetULongLong(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetULongLong());
}


/**
 * @brief GetULongLong関数
 *
 * Create関数不要
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline ULONGLONG tml::RandomUtil::GetULongLong(const ULONGLONG min_val, const ULONGLONG max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetULongLong(min_val, max_val));
}


/**
 * @brief GetFloat関数
 *
 * Create関数不要
 *
 * @return val (value)
 */
inline FLOAT tml::RandomUtil::GetFloat(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetFloat());
}


/**
 * @brief GetFloat関数
 *
 * Create関数不要
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline FLOAT tml::RandomUtil::GetFloat(const FLOAT min_val, const FLOAT max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetFloat(min_val, max_val));
}


/**
 * @brief GetDouble関数
 *
 * Create関数不要
 *
 * @return val (value)
 */
inline DOUBLE tml::RandomUtil::GetDouble(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetDouble());
}


/**
 * @brief GetDouble関数
 *
 * Create関数不要
 *
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline DOUBLE tml::RandomUtil::GetDouble(const DOUBLE min_val, const DOUBLE max_val)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetDouble(min_val, max_val));
}


/**
 * @brief GetBool関数
 *
 * Create関数不要
 *
 * @return val (value)
 */
inline bool tml::RandomUtil::GetBool(void)
{tml::ThreadLockBlock th_lock_block(tml::RandomUtil::seed_th_lock_);
	return (tml::RandomUtil::seed_.GetBool());
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline INT &tml::RandomUtil::GetValue(INT &dst_val)
{
	dst_val = tml::RandomUtil::GetInt();

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline INT &tml::RandomUtil::GetValue(INT &dst_val, const INT min_val, const INT max_val)
{
	dst_val = tml::RandomUtil::GetInt(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline UINT &tml::RandomUtil::GetValue(UINT &dst_val)
{
	dst_val = tml::RandomUtil::GetUInt();

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline UINT &tml::RandomUtil::GetValue(UINT &dst_val, const UINT min_val, const UINT max_val)
{
	dst_val = tml::RandomUtil::GetUInt(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline LONGLONG &tml::RandomUtil::GetValue(LONGLONG &dst_val)
{
	dst_val = tml::RandomUtil::GetLongLong();

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline LONGLONG &tml::RandomUtil::GetValue(LONGLONG &dst_val, const LONGLONG min_val, const LONGLONG max_val)
{
	dst_val = tml::RandomUtil::GetLongLong(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline ULONGLONG &tml::RandomUtil::GetValue(ULONGLONG &dst_val)
{
	dst_val = tml::RandomUtil::GetULongLong();

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline ULONGLONG &tml::RandomUtil::GetValue(ULONGLONG &dst_val, const ULONGLONG min_val, const ULONGLONG max_val)
{
	dst_val = tml::RandomUtil::GetULongLong(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline FLOAT &tml::RandomUtil::GetValue(FLOAT &dst_val)
{
	dst_val = tml::RandomUtil::GetFloat();

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline FLOAT &tml::RandomUtil::GetValue(FLOAT &dst_val, const FLOAT min_val, const FLOAT max_val)
{
	dst_val = tml::RandomUtil::GetFloat(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline DOUBLE &tml::RandomUtil::GetValue(DOUBLE &dst_val)
{
	dst_val = tml::RandomUtil::GetDouble();

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return dst_val (dst_value)
 */
inline DOUBLE &tml::RandomUtil::GetValue(DOUBLE &dst_val, const DOUBLE min_val, const DOUBLE max_val)
{
	dst_val = tml::RandomUtil::GetDouble(min_val, max_val);

	return (dst_val);
}


/**
 * @brief GetValue関数
 *
 * Create関数不要
 *
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline bool &tml::RandomUtil::GetValue(bool &dst_val)
{
	dst_val = tml::RandomUtil::GetBool();

	return (dst_val);
}
