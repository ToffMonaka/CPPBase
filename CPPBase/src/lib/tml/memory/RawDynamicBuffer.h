/**
 * @file
 * @brief RawDynamicBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "DynamicBuffer.h"


namespace tml {
using RawDynamicBuffer = tml::BaseDynamicBuffer<tml::raw_memory_get<BYTE>, tml::raw_memory_release<BYTE>>;
}
