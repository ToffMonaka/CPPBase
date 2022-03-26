/**
 * @file
 * @brief ConstantUtil_GRAPHICヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"
#include "../../lib/tml/constant/ConstantUtil_GRAPHIC.h"


namespace cpp_base {
namespace ConstantUtil {
namespace GRAPHIC {
	namespace CLASS_NAME {
	}
	namespace RESOURCE_NAME {
	}
	enum class RESOURCE_TYPE : UINT {
		USER = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::RESOURCE_TYPE::USER),
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(cpp_base::ConstantUtil::GRAPHIC::RESOURCE_TYPE::COUNT);
	enum class TASK_TYPE : UINT {
		USER = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::TASK_TYPE::USER),
		COUNT
	};
	const UINT TASK_TYPE_COUNT = static_cast<UINT>(cpp_base::ConstantUtil::GRAPHIC::TASK_TYPE::COUNT);
	enum class EVENT_TYPE : UINT {
		USER = static_cast<UINT>(tml::ConstantUtil::GRAPHIC::EVENT_TYPE::USER),
		COUNT
	};
	const UINT EVENT_TYPE_COUNT = static_cast<UINT>(cpp_base::ConstantUtil::GRAPHIC::EVENT_TYPE::COUNT);
}
}
}


namespace cpp_base {
namespace graphic {
class Manager;
}
}
