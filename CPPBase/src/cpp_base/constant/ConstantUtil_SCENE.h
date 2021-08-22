/**
 * @file
 * @brief ConstantUtil_SCENEヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"
#include "../../lib/tml/constant/ConstantUtil_SCENE.h"


namespace cpp_base {
namespace ConstantUtil {
namespace SCENE {
	namespace CLASS_NAME {
		const WCHAR INIT_SCENE[] = L"InitScene";
		const WCHAR TITLE_SCENE[] = L"TitleScene";
		const WCHAR SELECT_SCENE[] = L"SelectScene";
		const WCHAR STAGE_SCENE[] = L"StageScene";
		const WCHAR TEST_2D_STAGE_NODE[] = L"Test2DStageNode";
		const WCHAR FIELD_2D_NODE[] = L"Field2DNode";
	}
	namespace RESOURCE_NAME {
		const WCHAR DEBUG_NODE[] = L"DebugNode";
	}
	enum class RESOURCE_TYPE : UINT {
		USER = static_cast<UINT>(tml::ConstantUtil::SCENE::RESOURCE_TYPE::USER),
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(cpp_base::ConstantUtil::SCENE::RESOURCE_TYPE::COUNT);
	enum class EVENT_TYPE : UINT {
		USER = static_cast<UINT>(tml::ConstantUtil::SCENE::EVENT_TYPE::USER),
		COUNT
	};
	const UINT EVENT_TYPE_COUNT = static_cast<UINT>(cpp_base::ConstantUtil::SCENE::EVENT_TYPE::COUNT);
}
}
}


namespace cpp_base {
namespace scene {
class Manager;
class Scene;
class InitScene;
class TitleScene;
class SelectScene;
class StageScene;
class Node;
class DebugNode;
class Test2DStageNode;
class Field2DNode;
}
}
