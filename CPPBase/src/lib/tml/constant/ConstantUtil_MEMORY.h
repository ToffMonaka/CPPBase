/**
 * @file
 * @brief ConstantUtil_MEMORY�w�b�_�[�t�@�C��
 */
#pragma once


#include "ConstantUtil.h"


namespace tml {
namespace ConstantUtil {
namespace MEMORY {
	enum class ALLOCATOR_TYPE : UINT {
		NONE = 0U,
		NEW,
		DLMALLOC
	};
}
}
}
