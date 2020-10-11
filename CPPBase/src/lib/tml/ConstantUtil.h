/**
 * @file
 * @brief ConstantUtil�w�b�_�[�t�@�C��
 */
#pragma once


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <chrono>


using DLONG = long long;
using UDLONG = unsigned long long;
using DOUBLE = double;
#define NULLP nullptr
using NULLP_TYPE = std::nullptr_t;
using TIME_SECOND = std::chrono::seconds;
using TIME_MILLI = std::chrono::milliseconds;
using TIME_MICRO = std::chrono::microseconds;
using TIME_NANO = std::chrono::nanoseconds;
using TIME_REAL = std::chrono::duration<double>;


namespace tml {
/**
 * @brief ConstantUtil�N���X
 *
 * ���[�e�B���e�B�p�^�[��
 */
class ConstantUtil
{
public: ConstantUtil() = delete;
public: ConstantUtil(const ConstantUtil &) = delete;
public: ConstantUtil &operator =(const ConstantUtil &) = delete;

public:
};
}
