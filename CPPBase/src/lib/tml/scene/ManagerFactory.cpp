/**
 * @file
 * @brief ManagerFactoryコードファイル
 */


#include "ManagerFactory.h"
#include "Manager.h"
#include "Scene.h"
#include "BaseScene.h"
#include "Node.h"
#include "BaseNode.h"


/**
 * @brief コンストラクタ
 */
tml::scene::ManagerFactory::ManagerFactory() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::ManagerFactory::~ManagerFactory()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::ManagerFactory::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	this->scene_by_ini_file.Init();
	this->scene_by_xml_file.Init();
	this->node_by_ini_file.Init();
	this->node_by_xml_file.Init();

	return;
}


/**
 * @brief Create関数
 * @param mgr (manager)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::ManagerFactory::Create(tml::scene::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	this->scene_by_ini_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::BASE_SCENE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			tml::scene::BaseSceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<tml::scene::BaseScene>(scene, desc, dst_get_res) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->scene_by_xml_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::SCENE,
		[this] (const tml::XMLFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			auto file_read_desc_dat = file_read_desc.GetDataByParent();

			tml::XMLFile xml_file;

			xml_file.read_desc.parent_data = file_read_desc_dat;

			if (xml_file.Read() < 0) {
				return (scene);
			}

			if (xml_file.data.GetRootNode()->GetChildNodeContainer().empty()) {
				return (scene);
			}

			auto &xml_file_node = xml_file.data.GetRootNode()->GetChildNodeContainer().front();

			if (xml_file_node->name != L"scene") {
				return (scene);
			}

			auto scene_class_name = xml_file_node->GetValue(L"class_name");
			auto scene_res_name = xml_file_node->GetValue(L"res_name");
			INT scene_get_res = -1;

			if (scene_class_name != nullptr) {
				tml::INIFileReadDesc scene_desc;

				scene_desc.data.string = xml_file_node->string;

				if (this->scene_by_ini_file.Get(scene, scene_class_name->c_str(), scene_desc, &scene_get_res) == nullptr) {
					return (scene);
				}
			} else if (scene_res_name != nullptr) {
				if (this->mgr_->GetResource<tml::scene::Scene>(scene, scene_res_name->c_str(), &scene_get_res) == nullptr) {
					return (scene);
				}
			} else {
				return (scene);
			}

			if (scene_get_res == 0) {
				for (auto &xml_file_child_node : xml_file_node->GetChildNodeContainer()) {
					this->SetNodeRecursivePart(scene->GetRootNode(), xml_file_child_node);
				}
			}

			tml::SetResult(dst_get_res, scene_get_res);

			return (scene);
		}
	);

	this->node_by_ini_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::BASE_NODE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			tml::scene::BaseNodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<tml::scene::BaseNode>(node, desc, dst_get_res) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	this->node_by_xml_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::NODE,
		[this] (const tml::XMLFileReadDesc &file_read_desc, INT *dst_get_res) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			auto file_read_desc_dat = file_read_desc.GetDataByParent();

			tml::XMLFile xml_file;

			xml_file.read_desc.parent_data = file_read_desc_dat;

			if (xml_file.Read() < 0) {
				return (node);
			}

			if (xml_file.data.GetRootNode()->GetChildNodeContainer().empty()) {
				return (node);
			}

			auto &xml_file_node = xml_file.data.GetRootNode()->GetChildNodeContainer().front();

			if (xml_file_node->name != L"node") {
				return (node);
			}

			auto node_class_name = xml_file_node->GetValue(L"class_name");
			auto node_res_name = xml_file_node->GetValue(L"res_name");
			INT node_get_res = -1;

			if (node_class_name != nullptr) {
				tml::INIFileReadDesc node_desc;

				node_desc.data.string = xml_file_node->string;

				if (this->node_by_ini_file.Get(node, node_class_name->c_str(), node_desc, &node_get_res) == nullptr) {
					return (node);
				}
			} else if (node_res_name != nullptr) {
				if (this->mgr_->GetResource<tml::scene::Node>(node, node_res_name->c_str(), &node_get_res) == nullptr) {
					return (node);
				}
			} else {
				return (node);
			}

			if (node_get_res == 0) {
				for (auto &xml_file_child_node : xml_file_node->GetChildNodeContainer()) {
					this->SetNodeRecursivePart(node, xml_file_child_node);
				}
			}

			tml::SetResult(dst_get_res, node_get_res);

			return (node);
		}
	);

	return (0);
}


/**
 * @brief SetNodeRecursivePart関数
 * @param parent_node (parent_node)
 * @param xml_file_node (xml_file_node)
 */
void tml::scene::ManagerFactory::SetNodeRecursivePart(const tml::shared_ptr<tml::scene::Node> &parent_node, const tml::shared_ptr<tml::XMLFileDataNode> &xml_file_node)
{
	tml::shared_ptr<tml::scene::Node> child_node;

	if (xml_file_node->name != L"node") {
		return;
	}

	auto child_node_class_name = xml_file_node->GetValue(L"class_name");
	auto child_node_res_name = xml_file_node->GetValue(L"res_name");
	INT child_node_get_res = -1;

	if (child_node_class_name != nullptr) {
		tml::INIFileReadDesc child_node_desc;

		child_node_desc.data.string = xml_file_node->string;

		if (this->node_by_ini_file.Get(child_node, child_node_class_name->c_str(), child_node_desc, &child_node_get_res) == nullptr) {
			return;
		}
	} else if (child_node_res_name != nullptr) {
		if (this->mgr_->GetResource<tml::scene::Node>(child_node, child_node_res_name->c_str(), &child_node_get_res) == nullptr) {
			return;
		}
	} else {
		return;
	}

	child_node->RemoveChildNodeFromParentNode();

	parent_node->AddChildNode(child_node);

	if (child_node_get_res == 0) {
		for (auto &xml_file_child_node : xml_file_node->GetChildNodeContainer()) {
			this->SetNodeRecursivePart(child_node, xml_file_child_node);
		}
	}

	return;
}
