/**
 * @file
 * @brief RawStaticBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "StaticBuffer.h"


namespace tml {
template <size_t N>
using RawStaticBuffer = tml::BaseStaticBuffer<N>;
}
