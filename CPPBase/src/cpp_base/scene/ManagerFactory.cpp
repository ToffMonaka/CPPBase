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
#include "InitSceneNode.h"
#include "TitleSceneNode.h"
#include "SelectSceneNode.h"
#include "StageSceneNode.h"
#include "DebugNode.h"


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
 * @return res (result)<br>
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

	this->mgr_->factory.scene_by_ini_file.AddFunction(L"BaseScene",
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::BaseSceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::BaseScene>(scene, desc, dst_get_res) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->mgr_->factory.scene_by_ini_file.AddFunction(L"InitScene",
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::InitSceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::InitScene>(scene, desc, dst_get_res) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->mgr_->factory.scene_by_ini_file.AddFunction(L"TitleScene",
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::TitleSceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::TitleScene>(scene, desc, dst_get_res) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->mgr_->factory.scene_by_ini_file.AddFunction(L"SelectScene",
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::SelectSceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::SelectScene>(scene, desc, dst_get_res) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->mgr_->factory.scene_by_ini_file.AddFunction(L"StageScene",
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::StageSceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::StageScene>(scene, desc, dst_get_res) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->mgr_->factory.node_by_ini_file.AddFunction(L"BaseNode",
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::BaseNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::BaseNode>(node, desc, dst_get_res) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	this->mgr_->factory.node_by_ini_file.AddFunction(L"InitSceneNode",
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::InitSceneNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::InitSceneNode>(node, desc, dst_get_res) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	this->mgr_->factory.node_by_ini_file.AddFunction(L"TitleSceneNode",
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::TitleSceneNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::TitleSceneNode>(node, desc, dst_get_res) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	this->mgr_->factory.node_by_ini_file.AddFunction(L"SelectSceneNode",
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::SelectSceneNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::SelectSceneNode>(node, desc, dst_get_res) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	this->mgr_->factory.node_by_ini_file.AddFunction(L"StageSceneNode",
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::StageSceneNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::StageSceneNode>(node, desc, dst_get_res) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	return (0);
}
