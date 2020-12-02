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

template <typename T>
void SetValue(T *, const T);
template <typename T1, typename T2>
T1 CastTime(const T2 &time);
}


/**
 * @brief SetValue関数
 * @param dst_val (dst_value)
 * @param val (value)
 */
template <typename T>
inline void tml::SetValue(T *dst_val, const T val)
{
	if (dst_val != nullptr) {
		(*dst_val) = val;
	}

	return;
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


namespace tml {
namespace ConstantUtil {
}
}
