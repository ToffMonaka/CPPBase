/**
 * @file
 * @brief ConstantUtilヘッダーファイル
 */
#pragma once


#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <stdlib.h>
#include <iostream>
#include <memory>
#include <string>
#include <chrono>


using DOUBLE = double;


namespace tml {
using TIME_SECONDS = std::chrono::seconds;
using TIME_MILLI = std::chrono::milliseconds;
using TIME_MICRO = std::chrono::microseconds;
using TIME_NANO = std::chrono::nanoseconds;
using TIME_REAL = std::chrono::duration<double>;

template <typename T1, typename T2>
T1 CastTime(const T2 &time);
bool CheckResult(const INT *);
void SetResult(INT *, const INT);
}


/**
 * @brief CastTime関数
 * @param time (time)
 * @return time (time)
 */
template <typename T1, typename T2>
inline T1 tml::CastTime(const T2 &time)
{
	return (std::chrono::duration_cast<T1>(time));
}


/**
 * @brief CheckResult関数
 * @param res (result)
 * @return error_flg (error_flag)<br>
 * false=エラー無し,true=エラー有り
 */
inline bool tml::CheckResult(const INT *res)
{
	return ((res != nullptr) && ((*res) < 0));
}


/**
 * @brief SetResult関数
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
