/**
 * @file
 * @brief ConstantUtil�w�b�_�[�t�@�C��
 */
#pragma once


#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <stdlib.h>
#include <iostream>


using DLONG = long long;
using UDLONG = unsigned long long;
using DOUBLE = double;
#define NULLP nullptr
using NULLP_TYPE = std::nullptr_t;


namespace tml {
/**
 * @brief ConstantUtil�N���X
 *
 * ���[�e�B���e�B�p�^�[��
 */
class ConstantUtil
{
private: ConstantUtil() {return;};
private: ConstantUtil(const ConstantUtil &) {return;};
private: ConstantUtil &operator =(const ConstantUtil &) {return ((*this));};

public:
};
}
