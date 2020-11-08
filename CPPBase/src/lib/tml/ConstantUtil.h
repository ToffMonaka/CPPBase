/**
 * @file
 * @brief ConstantUtilヘッダーファイル
 */
#pragma once


#define WIN32_LEAN_AND_MEAN
#define NOMINMAX
#include <windows.h>
#include <stdlib.h>
#include <memory>
#include <string>
#include <chrono>


using DOUBLE = double;


namespace tml {
namespace ConstantUtil {
}

using TIME_SECOND = std::chrono::seconds;
using TIME_MILLI = std::chrono::milliseconds;
using TIME_MICRO = std::chrono::microseconds;
using TIME_NANO = std::chrono::nanoseconds;
using TIME_REAL = std::chrono::duration<double>;

template <typename T1, typename T2>
T1 CastTime(const T2 &time);
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
