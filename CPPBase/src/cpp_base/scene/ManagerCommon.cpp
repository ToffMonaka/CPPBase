/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "../constant/ConstantUtil_FILE_PATH.h"
#include "Manager.h"
#include "Scene.h"
#include "InitScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "StageScene.h"
#include "Node.h"
#include "DebugNode.h"
#include "InitSceneMainNode.h"
#include "TitleSceneMainNode.h"
#include "SelectSceneMainNode.h"
#include "StageSceneMainNode.h"
#include "Test2DStageNode.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::ManagerCommon::ManagerCommon() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::ManagerCommon::~ManagerCommon()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::ManagerCommon::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	this->debug_node.reset();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::ManagerCommon::Create(cpp_base::scene::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	if (cpp_base::ConstantUtil::APPLICATION::DEBUG_FLAG) {
		{// DebugNode Create
			cpp_base::scene::DebugNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.resource_name = cpp_base::ConstantUtil::SCENE::RESOURCE_NAME::DEBUG_NODE;
			desc.name = L"debug";

			if (this->mgr_->GetResource<cpp_base::scene::DebugNode>(this->debug_node, desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}
	}

	return (0);
}
