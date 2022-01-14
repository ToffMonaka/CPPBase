/**
 * @file
 * @brief RawStaticBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "StaticBuffer.h"


namespace tml {
template <size_t N>
using RawStaticBuffer = tml::BaseStaticBuffer<N>;
}
