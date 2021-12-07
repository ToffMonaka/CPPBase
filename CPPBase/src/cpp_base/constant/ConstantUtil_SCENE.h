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
		const WCHAR FIELD_2D_GROUND_NODE[] = L"Field2DGroundNode";
		const WCHAR FIELD_2D_PLAYER_NODE[] = L"Field2DPlayerNode";
		const WCHAR FIELD_2D_MOB_NODE[] = L"Field2DMobNode";
		const WCHAR FIELD_2D_BULLET_NODE[] = L"Field2DBulletNode";
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
class SceneDesc;
class InitScene;
class InitSceneDesc;
class TitleScene;
class TitleSceneDesc;
class SelectScene;
class SelectSceneDesc;
class StageScene;
class StageSceneDesc;
class Node;
class NodeDesc;
class DebugNode;
class DebugNodeDesc;
class Test2DStageNode;
class Test2DStageNodeDesc;
class Field2DNode;
class Field2DNodeDesc;
class Field2DGroundNode;
class Field2DGroundNodeDesc;
class Field2DPlayerNode;
class Field2DPlayerNodeDesc;
class Field2DMobNode;
class Field2DMobNodeDesc;
class Field2DBulletNode;
class Field2DBulletNodeDesc;
}
}
