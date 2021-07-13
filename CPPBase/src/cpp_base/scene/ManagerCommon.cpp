/**
 * @file
 * @brief ManagerCommonコードファイル
 */


#include "ManagerCommon.h"
#include "Manager.h"
#include "BaseScene.h"
#include "InitScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "StageScene.h"
#include "BaseNode.h"
#include "InitSceneNode.h"
#include "TitleSceneNode.h"
#include "SelectSceneNode.h"
#include "StageSceneNode.h"
#include "DebugNode.h"


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
 * @return res (result)<br>
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

	if (tml::ConstantUtil::LIBRARY::DEBUG_FLAG) {
		{// DebugNode Create
			cpp_base::scene::DebugNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.resource_name = L"debug_node";

			if (this->mgr_->GetResource<cpp_base::scene::DebugNode>(this->debug_node, desc) == nullptr) {
				this->Init();

				return (-1);
			}
		}
	}

	return (0);
}
