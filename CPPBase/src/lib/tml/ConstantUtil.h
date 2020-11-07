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
#define NULLP nullptr
using NULLP_TYPE = std::nullptr_t;
using TIME_SECOND = std::chrono::seconds;
using TIME_MILLI = std::chrono::milliseconds;
using TIME_MICRO = std::chrono::microseconds;
using TIME_NANO = std::chrono::nanoseconds;
using TIME_REAL = std::chrono::duration<double>;


namespace tml {
namespace ConstantUtil {
}


/**
 * @brief TimeCast関数
 * @param time (time)
 * @return time (time)
 */
template <typename T1, typename T2>
T1 TimeCast(const T2 &time)
{
	return (std::chrono::duration_cast<T1>(time));
}
}
