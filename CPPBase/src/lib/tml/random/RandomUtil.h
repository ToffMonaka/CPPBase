/**
 * @file
 * @brief RandomUtilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "RandomUtilEngine.h"
#include "../thread/ThreadFix.h"


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
};
}


/**
 * @brief CheckThreadFix関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::RandomUtil::CheckThreadFix(void)
{
	return (tml::RandomUtil::th_fix_.Check());
}


/**
 * @brief GetINT関数
 * @return val (value)
 */
inline INT tml::RandomUtil::GetINT(void)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (0);
	}

	return (tml::RandomUtil::engine_->GetINT());
}


/**
 * @brief GetINT関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline INT tml::RandomUtil::GetINT(const INT min_val, const INT max_val)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (min_val);
	}

	return (tml::RandomUtil::engine_->GetINT(min_val, max_val));
}


/**
 * @brief GetUINT関数
 * @return val (value)
 */
inline UINT tml::RandomUtil::GetUINT(void)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (0U);
	}

	return (tml::RandomUtil::engine_->GetUINT());
}


/**
 * @brief GetUINT関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline UINT tml::RandomUtil::GetUINT(const UINT min_val, const UINT max_val)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (min_val);
	}

	return (tml::RandomUtil::engine_->GetUINT(min_val, max_val));
}


/**
 * @brief GetLONGLONG関数
 * @return val (value)
 */
inline LONGLONG tml::RandomUtil::GetLONGLONG(void)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (0LL);
	}

	return (tml::RandomUtil::engine_->GetLONGLONG());
}


/**
 * @brief GetLONGLONG関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline LONGLONG tml::RandomUtil::GetLONGLONG(const LONGLONG min_val, const LONGLONG max_val)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (min_val);
	}

	return (tml::RandomUtil::engine_->GetLONGLONG(min_val, max_val));
}


/**
 * @brief GetULONGLONG関数
 * @return val (value)
 */
inline ULONGLONG tml::RandomUtil::GetULONGLONG(void)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (0ULL);
	}

	return (tml::RandomUtil::engine_->GetULONGLONG());
}


/**
 * @brief GetULONGLONG関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline ULONGLONG tml::RandomUtil::GetULONGLONG(const ULONGLONG min_val, const ULONGLONG max_val)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (min_val);
	}

	return (tml::RandomUtil::engine_->GetULONGLONG(min_val, max_val));
}


/**
 * @brief GetFLOAT関数
 * @return val (value)
 */
inline FLOAT tml::RandomUtil::GetFLOAT(void)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (0.0f);
	}

	return (tml::RandomUtil::engine_->GetFLOAT());
}


/**
 * @brief GetFLOAT関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline FLOAT tml::RandomUtil::GetFLOAT(const FLOAT min_val, const FLOAT max_val)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (min_val);
	}

	return (tml::RandomUtil::engine_->GetFLOAT(min_val, max_val));
}


/**
 * @brief GetDOUBLE関数
 * @return val (value)
 */
inline DOUBLE tml::RandomUtil::GetDOUBLE(void)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (0.0);
	}

	return (tml::RandomUtil::engine_->GetDOUBLE());
}


/**
 * @brief GetDOUBLE関数
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
inline DOUBLE tml::RandomUtil::GetDOUBLE(const DOUBLE min_val, const DOUBLE max_val)
{
	if (tml::RandomUtil::engine_ == nullptr) {
		return (min_val);
	}

	return (tml::RandomUtil::engine_->GetDOUBLE(min_val, max_val));
}


/**
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline INT &tml::RandomUtil::GetValue(INT &dst_val)
{
	dst_val = tml::RandomUtil::GetINT();

	return (dst_val);
}


/**
 * @brief GetValue関数
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
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline UINT &tml::RandomUtil::GetValue(UINT &dst_val)
{
	dst_val = tml::RandomUtil::GetUINT();

	return (dst_val);
}


/**
 * @brief GetValue関数
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
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline LONGLONG &tml::RandomUtil::GetValue(LONGLONG &dst_val)
{
	dst_val = tml::RandomUtil::GetLONGLONG();

	return (dst_val);
}


/**
 * @brief GetValue関数
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
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline ULONGLONG &tml::RandomUtil::GetValue(ULONGLONG &dst_val)
{
	dst_val = tml::RandomUtil::GetULONGLONG();

	return (dst_val);
}


/**
 * @brief GetValue関数
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
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline FLOAT &tml::RandomUtil::GetValue(FLOAT &dst_val)
{
	dst_val = tml::RandomUtil::GetFLOAT();

	return (dst_val);
}


/**
 * @brief GetValue関数
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
 * @brief GetValue関数
 * @param dst_val (dst_value)
 * @return dst_val (dst_value)
 */
inline DOUBLE &tml::RandomUtil::GetValue(DOUBLE &dst_val)
{
	dst_val = tml::RandomUtil::GetDOUBLE();

	return (dst_val);
}


/**
 * @brief GetValue関数
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
