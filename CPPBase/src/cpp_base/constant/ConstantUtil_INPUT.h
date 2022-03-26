/**
 * @file
 * @brief ConstantUtil_INPUTヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"
#include "../../lib/tml/constant/ConstantUtil_INPUT.h"


namespace cpp_base {
namespace ConstantUtil {
namespace INPUT {
	namespace CLASS_NAME {
	}
	namespace RESOURCE_NAME {
	}
	enum class RESOURCE_TYPE : UINT {
		USER = static_cast<UINT>(tml::ConstantUtil::INPUT::RESOURCE_TYPE::USER),
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(cpp_base::ConstantUtil::INPUT::RESOURCE_TYPE::COUNT);
	enum class TASK_TYPE : UINT {
		USER = static_cast<UINT>(tml::ConstantUtil::INPUT::TASK_TYPE::USER),
		COUNT
	};
	const UINT TASK_TYPE_COUNT = static_cast<UINT>(cpp_base::ConstantUtil::INPUT::TASK_TYPE::COUNT);
	enum class EVENT_TYPE : UINT {
		USER = static_cast<UINT>(tml::ConstantUtil::INPUT::EVENT_TYPE::USER),
		COUNT
	};
	const UINT EVENT_TYPE_COUNT = static_cast<UINT>(cpp_base::ConstantUtil::INPUT::EVENT_TYPE::COUNT);
}
}
}


namespace cpp_base {
namespace input {
class Manager;
}
}
