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
		const WCHAR INIT_SCENE_MAIN_NODE[] = L"InitSceneMainNode";
		const WCHAR TITLE_SCENE_MAIN_NODE[] = L"TitleSceneMainNode";
		const WCHAR SELECT_SCENE_MAIN_NODE[] = L"SelectSceneMainNode";
		const WCHAR STAGE_SCENE_MAIN_NODE[] = L"StageSceneMainNode";
		const WCHAR TEST_2D_STAGE_NODE[] = L"Test2DStageNode";
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
class BaseScene;
class InitScene;
class TitleScene;
class SelectScene;
class StageScene;
class BaseNode;
class DebugNode;
class InitSceneMainNode;
class TitleSceneMainNode;
class SelectSceneMainNode;
class StageSceneMainNode;
class Test2DStageNode;
}
}
