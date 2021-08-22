/**
 * @file
 * @brief ManagerFactory�R�[�h�t�@�C��
 */


#include "ManagerFactory.h"
#include "Manager.h"
#include "Scene.h"
#include "InitScene.h"
#include "TitleScene.h"
#include "SelectScene.h"
#include "StageScene.h"
#include "Node.h"
#include "DebugNode.h"
#include "Test2DStageNode.h"
#include "Field2DNode.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::ManagerFactory::ManagerFactory() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::ManagerFactory::~ManagerFactory()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::ManagerFactory::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create�֐�
 * @param mgr (manager)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::ManagerFactory::Create(cpp_base::scene::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	this->mgr_->factory.scene_by_ini_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::SCENE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			cpp_base::scene::SceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::Scene>(scene, desc, dst_result) == nullptr) {
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

	this->mgr_->factory.node_by_ini_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::NODE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::NodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::Node>(node, desc, dst_result) == nullptr) {
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

	this->mgr_->factory.node_by_ini_file.AddFunction(cpp_base::ConstantUtil::SCENE::CLASS_NAME::FIELD_2D_NODE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			cpp_base::scene::Field2DNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<cpp_base::scene::Field2DNode>(node, desc, dst_result) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	return (0);
}
