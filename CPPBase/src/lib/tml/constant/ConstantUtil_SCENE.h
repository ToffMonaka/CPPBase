/**
 * @file
 * @brief ConstantUtil_SCENEヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"


namespace tml {
namespace ConstantUtil {
namespace SCENE {
	namespace CLASS_NAME {
		const WCHAR SCENE[] = L"Scene";
		const WCHAR NODE[] = L"Node";
	}
	namespace RESOURCE_NAME {
	}
	enum class RESOURCE_TYPE : UINT {
		NONE = 0U,
		BASE,
		SCENE,
		NODE,
		USER,
		COUNT
	};
	const UINT RESOURCE_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SCENE::RESOURCE_TYPE::COUNT);
	enum class TASK_TYPE : UINT {
		NONE = 0U,
		BASE,
		SCENE,
		NODE,
		USER,
		COUNT
	};
	const UINT TASK_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SCENE::TASK_TYPE::COUNT);
	enum class EVENT_TYPE : UINT {
		NONE = 0U,
		BASE,
		USER,
		COUNT
	};
	const UINT EVENT_TYPE_COUNT = static_cast<UINT>(tml::ConstantUtil::SCENE::EVENT_TYPE::COUNT);
	enum class SCENE_TASK_RUN_TYPE : UINT {
		NONE = 0U,
		START_SCENE,
		END_SCENE
	};
	enum class NODE_TASK_RUN_TYPE : UINT {
		NONE = 0U,
		ADD_CHILD_NODE,
		REMOVE_CHILD_NODE
	};
}
}
}


namespace tml {
namespace scene {
class Manager;
class Scene;
class SceneDesc;
class Node;
class NodeDesc;
class SceneTask;
class SceneTaskDesc;
class NodeTask;
class NodeTaskDesc;
}
}
