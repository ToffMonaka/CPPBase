/**
 * @file
 * @brief ManagerFactoryコードファイル
 */


#include "ManagerFactory.h"
#include "Manager.h"
#include "BaseScene.h"
#include "InitScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "StageScene.h"
#include "BaseNode.h"
#include "DebugNode.h"
#include "InitSceneMainNode.h"
#include "TitleSceneMainNode.h"
#include "SelectSceneMainNode.h"
#include "StageSceneMainNode.h"
#include "Test2DStageNode.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::ManagerFactory::ManagerFactory() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::ManagerFactory::~ManagerFactory()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::ManagerFactory::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::ManagerFactory::Create(cpp_base::scene::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	this->mgr_->factory.scene_by_ini_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::BASE_SCENE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::BaseSceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::BaseScene>(scene, desc, dst_result) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->mgr_->factory.scene_by_ini_file.AddFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::INIT_SCENE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::InitSceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::InitScene>(scene, desc, dst_result) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->mgr_->factory.scene_by_ini_file.AddFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::TITLE_SCENE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::TitleSceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::TitleScene>(scene, desc, dst_result) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->mgr_->factory.scene_by_ini_file.AddFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::SELECT_SCENE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::SelectSceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::SelectScene>(scene, desc, dst_result) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->mgr_->factory.scene_by_ini_file.AddFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::STAGE_SCENE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::StageSceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::StageScene>(scene, desc, dst_result) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->mgr_->factory.node_by_ini_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::BASE_NODE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::BaseNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::BaseNode>(node, desc, dst_result) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	this->mgr_->factory.node_by_ini_file.AddFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::INIT_SCENE_MAIN_NODE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::InitSceneMainNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::InitSceneMainNode>(node, desc, dst_result) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	this->mgr_->factory.node_by_ini_file.AddFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::TITLE_SCENE_MAIN_NODE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::TitleSceneMainNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::TitleSceneMainNode>(node, desc, dst_result) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	this->mgr_->factory.node_by_ini_file.AddFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::SELECT_SCENE_MAIN_NODE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::SelectSceneMainNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::SelectSceneMainNode>(node, desc, dst_result) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	this->mgr_->factory.node_by_ini_file.AddFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::STAGE_SCENE_MAIN_NODE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::StageSceneMainNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::StageSceneMainNode>(node, desc, dst_result) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	this->mgr_->factory.node_by_ini_file.AddFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::TEST_2D_STAGE_NODE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::Test2DStageNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::Test2DStageNode>(node, desc, dst_result) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	return (0);
}
