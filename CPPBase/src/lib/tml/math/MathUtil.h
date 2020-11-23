/**
 * @file
 * @brief MathUtilヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "MathUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief MathUtilクラス
 *
 * ユーティリティパターン<br>
 * エンジンパターン
 */
class MathUtil
{
public: MathUtil() = delete;
public: MathUtil(const MathUtil &) = delete;
public: MathUtil &operator =(const MathUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::MathUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::MathUtilEngine> &);

	static bool CheckThreadFix(void);
	template <typename T>
	static T Div(const T &, const T &);
	template <typename T>
	static T Div(const T &, const T &, const T &);
	template <typename T>
	static T Mod(const T &, const T &);
	template <typename T>
	static T Mod(const T &, const T &, const T &);
	template <typename T>
	static T Min(const T &, const T &);
	template <typename T>
	static T Max(const T &, const T &);
	template <typename T>
	static T Clamp(const T &, const T &, const T &);
};
}


/**
 * @brief CheckThreadFix関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::MathUtil::CheckThreadFix(void)
{
	return (tml::MathUtil::th_fix_.Check());
}


/**
 * @brief Div関数
 *
 * Create関数不要
 *
 * @param val1 (value1)
 * @param val2 (value2)
 * @return val (value)
 */
template <typename T>
inline T tml::MathUtil::Div(const T &val1, const T &val2)
{
	return (val1 / val2);
}


/**
 * @brief Div関数
 *
 * Create関数不要
 *
 * @param val1 (value1)
 * @param val2 (value2)
 * @param zero_val (zero_value)
 * @return val (value)
 */
template <typename T>
inline T tml::MathUtil::Div(const T &val1, const T &val2, const T &zero_val)
{
	return ((val2 == static_cast<T>(0)) ? zero_val : (val1 / val2));
}


/**
 * @brief Mod関数
 *
 * Create関数不要
 *
 * @param val1 (value1)
 * @param val2 (value2)
 * @return val (value)
 */
template <typename T>
inline T tml::MathUtil::Mod(const T &val1, const T &val2)
{
	return (val1 % val2);
}


/**
 * @brief Mod関数
 *
 * Create関数不要
 *
 * @param val1 (value1)
 * @param val2 (value2)
 * @param zero_val (zero_value)
 * @return val (value)
 */
template <typename T>
inline T tml::MathUtil::Mod(const T &val1, const T &val2, const T &zero_val)
{
	return ((val2 == static_cast<T>(0)) ? zero_val : (val1 % val2));
}


/**
 * @brief Min関数
 *
 * Create関数不要
 *
 * @param val1 (value1)
 * @param val2 (value2)
 * @return val (value)
 */
template <typename T>
inline T tml::MathUtil::Min(const T &val1, const T &val2)
{
	return ((val1 > val2) ? val2 : val1);
}


/**
 * @brief Max関数
 *
 * Create関数不要
 *
 * @param val1 (value1)
 * @param val2 (value2)
 * @return val (value)
 */
template <typename T>
inline T tml::MathUtil::Max(const T &val1, const T &val2)
{
	return ((val1 < val2) ? val2 : val1);
}


/**
 * @brief Clamp関数
 *
 * Create関数不要
 *
 * @param val (value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
template <typename T>
inline T tml::MathUtil::Clamp(const T &val, const T &min_val, const T &max_val)
{
	return ((val < min_val) ? min_val : (val > max_val) ? max_val : val);
}
