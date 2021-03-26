/**
 * @file
 * @brief ConstantUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "ConstantInclude_ConstantUtilBase.h"


#define TML_ENUM_CLASS_FLAG_OPERATOR(e, t) \
inline e operator &(const e &f1, const e &f2) {return (static_cast<e>(static_cast<t>(f1) & static_cast<t>(f2)));} \
inline e &operator &=(e &f1, const e &f2) {f1 = static_cast<e>(static_cast<t>(f1) & static_cast<t>(f2)); return (f1);} \
inline e operator |(const e &f1, const e &f2) {return (static_cast<e>(static_cast<t>(f1) | static_cast<t>(f2)));} \
inline e &operator |=(e &f1, const e &f2) {f1 = static_cast<e>(static_cast<t>(f1) | static_cast<t>(f2)); return (f1);} \
inline e operator ^(const e &f1, const e &f2) {return (static_cast<e>(static_cast<t>(f1) ^ static_cast<t>(f2)));} \
inline e &operator ^=(e &f1, const e &f2) {f1 = static_cast<e>(static_cast<t>(f1) ^ static_cast<t>(f2)); return (f1);} \
inline e operator ~(const e &f) {return (static_cast<e>(~static_cast<t>(f)));}


namespace tml {
using TIME_SECONDS = std::chrono::seconds;
using TIME_MILLI = std::chrono::milliseconds;
using TIME_MICRO = std::chrono::microseconds;
using TIME_NANO = std::chrono::nanoseconds;
using TIME_REAL = std::chrono::duration<double>;

template <typename T, size_t N>
size_t GetCount(const T (&)[N]);
template <typename T>
void Clear(T *, const size_t);
template <typename T>
void Copy(T *, const T *, const size_t);
template <typename T>
void CopySelf(T *, const T *, const size_t);
template <typename T>
T Div(const T &, const T &);
template <typename T>
T Div(const T &, const T &, const T &);
template <typename T>
T Mod(const T &, const T &);
template <typename T>
T Mod(const T &, const T &, const T &);
template <typename T>
const T &Min(const T &, const T &);
template <typename T>
const T &Max(const T &, const T &);
template <typename T>
const T &Clamp(const T &, const T &, const T &);
template <typename T1, typename T2>
T1 CastTime(const T2 &time);
bool CheckResult(const INT *);
void SetResult(INT *, const INT);
}


/**
 * @brief GetCount�֐�
 *
 * 1st unnamed param ary (array)
 *
 * @return cnt (count)
 */
template <typename T, size_t N>
inline size_t tml::GetCount(const T (&)[N])
{
	return (N);
}


/**
 * @brief Clear�֐�
 * @param p (pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::Clear(T *p, const size_t cnt)
{
	if ((p == nullptr)
	|| (cnt <= 0U)) {
		return;
	}

	memset(p, 0, sizeof(T) * cnt);

	return;
}


/**
 * @brief Copy�֐�
 * @param dst_p (dst_pointer)
 * @param src_p (src_pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::Copy(T *dst_p, const T *src_p, const size_t cnt)
{
	if ((dst_p == nullptr) || (src_p == nullptr) || (dst_p == src_p)
	|| (cnt <= 0U)) {
		return;
	}

	memcpy(dst_p, src_p, sizeof(T) * cnt);

	return;
}


/**
 * @brief CopySelf�֐�
 * @param dst_p (dst_pointer)
 * @param src_p (src_pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::CopySelf(T *dst_p, const T *src_p, const size_t cnt)
{
	if ((dst_p == nullptr) || (src_p == nullptr) || (dst_p == src_p)
	|| (cnt <= 0U)) {
		return;
	}

	memmove(dst_p, src_p, sizeof(T) * cnt);

	return;
}


/**
 * @brief Div�֐�
 * @param val1 (value1)
 * @param val2 (value2)
 * @return val (value)
 */
template <typename T>
inline T tml::Div(const T &val1, const T &val2)
{
	return (val1 / val2);
}


/**
 * @brief Div�֐�
 * @param val1 (value1)
 * @param val2 (value2)
 * @param zero_val (zero_value)
 * @return val (value)
 */
template <typename T>
inline T tml::Div(const T &val1, const T &val2, const T &zero_val)
{
	return ((val2 == static_cast<T>(0)) ? zero_val : (val1 / val2));
}


/**
 * @brief Mod�֐�
 * @param val1 (value1)
 * @param val2 (value2)
 * @return val (value)
 */
template <typename T>
inline T tml::Mod(const T &val1, const T &val2)
{
	return (val1 % val2);
}


/**
 * @brief Mod�֐�
 * @param val1 (value1)
 * @param val2 (value2)
 * @param zero_val (zero_value)
 * @return val (value)
 */
template <typename T>
inline T tml::Mod(const T &val1, const T &val2, const T &zero_val)
{
	return ((val2 == static_cast<T>(0)) ? zero_val : (val1 % val2));
}


/**
 * @brief Min�֐�
 * @param val1 (value1)
 * @param val2 (value2)
 * @return val (value)
 */
template <typename T>
inline const T &tml::Min(const T &val1, const T &val2)
{
	return ((val1 > val2) ? val2 : val1);
}


/**
 * @brief Max�֐�
 * @param val1 (value1)
 * @param val2 (value2)
 * @return val (value)
 */
template <typename T>
inline const T &tml::Max(const T &val1, const T &val2)
{
	return ((val1 < val2) ? val2 : val1);
}


/**
 * @brief Clamp�֐�
 * @param val (value)
 * @param min_val (min_value)
 * @param max_val (max_value)
 * @return val (value)
 */
template <typename T>
inline const T &tml::Clamp(const T &val, const T &min_val, const T &max_val)
{
	return ((val < min_val) ? min_val : (val > max_val) ? max_val : val);
}


/**
 * @brief CastTime�֐�
 * @param time (time)
 * @return time (time)
 */
template <typename T1, typename T2>
inline T1 tml::CastTime(const T2 &time)
{
	return (std::chrono::duration_cast<T1>(time));
}


/**
 * @brief CheckResult�֐�
 * @param res (result)
 * @return error_flg (error_flag)<br>
 * false=�G���[����,true=�G���[�L��
 */
inline bool tml::CheckResult(const INT *res)
{
	return ((res != nullptr) && ((*res) < 0));
}


/**
 * @brief SetResult�֐�
 * @param dst_res (dst_result)
 * @param res (result)
 */
inline void tml::SetResult(INT *dst_res, const INT res)
{
	if (dst_res != nullptr) {
		(*dst_res) = res;
	}

	return;
}


namespace tml {
namespace ConstantUtil {
namespace LIBRARY {
#if defined(DEBUG) || defined(_DEBUG)
	const bool DEBUG_FLAG = true;
#else
	const bool DEBUG_FLAG = false;
#endif
	const WCHAR NAME[] = L"Toff Monaka Library";
	const WCHAR COMPANY_NAME[] = L"Toff Monaka Project";
	const WCHAR VERSION_NAME[] = L"1.0.0";
}
}
}
