/**
 * @file
 * @brief ManagerFactoryコードファイル
 */


#include "ManagerFactory.h"
#include "Manager.h"
#include "Scene.h"
#include "Node.h"


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
 * @return result (result)<br>
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

	this->scene_by_ini_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::SCENE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			tml::scene::SceneDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<tml::scene::Scene>(scene, desc, dst_result) == nullptr) {
				return (scene);
			}

			return (scene);
		}
	);

	this->scene_by_xml_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::SCENE,
		[this] (const tml::XMLFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Scene> {
			tml::shared_ptr<tml::scene::Scene> scene;

			auto file_read_desc_dat = file_read_desc.GetDataByParent();

			tml::XMLFile xml_file;

			xml_file.read_desc.parent_data = file_read_desc_dat;

			if (xml_file.Read() < 0) {
				tml::SetResult(dst_result, -1);

				return (scene);
			}

			if (xml_file.data.GetRootNode()->GetChildNodeContainer().empty()) {
				tml::SetResult(dst_result, -1);

				return (scene);
			}

			auto &xml_file_node = xml_file.data.GetRootNode()->GetChildNodeContainer().front();

			if (xml_file_node->name != L"scene") {
				tml::SetResult(dst_result, -1);

				return (scene);
			}

			INT get_result = 0;

			if (this->GetScenePart(scene, xml_file_node, &get_result) == nullptr) {
				tml::SetResult(dst_result, -1);

				return (scene);
			}

			if (get_result == 0) {
				for (auto &xml_file_child_node : xml_file_node->GetChildNodeContainer()) {
					this->GetNodeRecursivePart(scene->GetRootNode(), xml_file_child_node);
				}
			}

			tml::SetResult(dst_result, get_result);

			return (scene);
		}
	);

	this->node_by_ini_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::NODE,
		[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			tml::scene::NodeDesc desc;

			desc.SetManager(this->mgr_);
			desc.Read(file_read_desc);

			if (this->mgr_->GetResource<tml::scene::Node>(node, desc, dst_result) == nullptr) {
				return (node);
			}

			return (node);
		}
	);

	this->node_by_xml_file.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::NODE,
		[this] (const tml::XMLFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::scene::Node> {
			tml::shared_ptr<tml::scene::Node> node;

			auto file_read_desc_dat = file_read_desc.GetDataByParent();

			tml::XMLFile xml_file;

			xml_file.read_desc.parent_data = file_read_desc_dat;

			if (xml_file.Read() < 0) {
				tml::SetResult(dst_result, -1);

				return (node);
			}

			if (xml_file.data.GetRootNode()->GetChildNodeContainer().empty()) {
				tml::SetResult(dst_result, -1);

				return (node);
			}

			auto &xml_file_node = xml_file.data.GetRootNode()->GetChildNodeContainer().front();

			if (xml_file_node->name != L"node") {
				tml::SetResult(dst_result, -1);

				return (node);
			}

			INT get_result = 0;

			if (this->GetNodePart(node, xml_file_node, &get_result) == nullptr) {
				tml::SetResult(dst_result, -1);

				return (node);
			}

			if (get_result == 0) {
				for (auto &xml_file_child_node : xml_file_node->GetChildNodeContainer()) {
					this->GetNodeRecursivePart(node, xml_file_child_node);
				}
			}

			tml::SetResult(dst_result, get_result);

			return (node);
		}
	);

	return (0);
}


/**
 * @brief GetScenePart関数
 * @param dst_scene (dst_scene)
 * @param xml_file_node (xml_file_node)
 * @param dst_result (dst_result)
 */
tml::shared_ptr<tml::scene::Scene> &tml::scene::ManagerFactory::GetScenePart(tml::shared_ptr<tml::scene::Scene> &dst_scene, const tml::shared_ptr<tml::XMLFileDataNode> &xml_file_node, INT *dst_result)
{
	auto class_name = xml_file_node->GetValue(L"class_name");
	auto ini_file_path = xml_file_node->GetValue(L"ini_file_path");
	auto xml_file_path = xml_file_node->GetValue(L"xml_file_path");
	auto res_name = xml_file_node->GetValue(L"res_name");

	if (class_name != nullptr) {
		if (ini_file_path != nullptr) {
			if (this->scene_by_ini_file.Get(dst_scene, class_name->c_str(), tml::INIFileReadDesc(ini_file_path->c_str()), dst_result) == nullptr) {
				return (dst_scene);
			}
		} else if (xml_file_path != nullptr) {
			if (this->scene_by_xml_file.Get(dst_scene, class_name->c_str(), tml::XMLFileReadDesc(xml_file_path->c_str()), dst_result) == nullptr) {
				return (dst_scene);
			}
		} else {
			tml::INIFileReadDesc desc;

			desc.data.string = xml_file_node->string;

			if (this->scene_by_ini_file.Get(dst_scene, class_name->c_str(), desc, dst_result) == nullptr) {
				return (dst_scene);
			}
		}
	} else if (res_name != nullptr) {
		if (this->mgr_->GetResource<tml::scene::Scene>(dst_scene, res_name->c_str(), dst_result) == nullptr) {
			return (dst_scene);
		}
	} else {
		tml::SetResult(dst_result, -1);

		return (dst_scene);
	}

	return (dst_scene);
}


/**
 * @brief GetNodePart関数
 * @param dst_node (dst_node)
 * @param xml_file_node (xml_file_node)
 * @param dst_result (dst_result)
 */
tml::shared_ptr<tml::scene::Node> &tml::scene::ManagerFactory::GetNodePart(tml::shared_ptr<tml::scene::Node> &dst_node, const tml::shared_ptr<tml::XMLFileDataNode> &xml_file_node, INT *dst_result)
{
	auto class_name = xml_file_node->GetValue(L"class_name");
	auto ini_file_path = xml_file_node->GetValue(L"ini_file_path");
	auto xml_file_path = xml_file_node->GetValue(L"xml_file_path");
	auto res_name = xml_file_node->GetValue(L"res_name");

	if (class_name != nullptr) {
		if (ini_file_path != nullptr) {
			if (this->node_by_ini_file.Get(dst_node, class_name->c_str(), tml::INIFileReadDesc(ini_file_path->c_str()), dst_result) == nullptr) {
				return (dst_node);
			}
		} else if (xml_file_path != nullptr) {
			if (this->node_by_xml_file.Get(dst_node, class_name->c_str(), tml::XMLFileReadDesc(xml_file_path->c_str()), dst_result) == nullptr) {
				return (dst_node);
			}
		} else {
			tml::INIFileReadDesc desc;

			desc.data.string = xml_file_node->string;

			if (this->node_by_ini_file.Get(dst_node, class_name->c_str(), desc, dst_result) == nullptr) {
				return (dst_node);
			}
		}
	} else if (res_name != nullptr) {
		if (this->mgr_->GetResource<tml::scene::Node>(dst_node, res_name->c_str(), dst_result) == nullptr) {
			return (dst_node);
		}
	} else {
		tml::SetResult(dst_result, -1);

		return (dst_node);
	}

	return (dst_node);
}


/**
 * @brief GetNodeRecursivePart関数
 * @param parent_node (parent_node)
 * @param xml_file_node (xml_file_node)
 */
void tml::scene::ManagerFactory::GetNodeRecursivePart(const tml::shared_ptr<tml::scene::Node> &parent_node, const tml::shared_ptr<tml::XMLFileDataNode> &xml_file_node)
{
	tml::shared_ptr<tml::scene::Node> child_node;

	if (xml_file_node->name != L"node") {
		if (xml_file_node->name == L"if") {
			bool result_flg = true;

			for (auto &val : xml_file_node->value_container) {
				auto factory_val = this->mgr_->GetFactoryValue(val.first.c_str());

				if (factory_val == nullptr) {
					result_flg = false;

					break;
				}

				if ((*factory_val) != val.second) {
					result_flg = false;

					break;
				}
			}

			if (result_flg) {
				for (auto &xml_file_child_node : xml_file_node->GetChildNodeContainer()) {
					this->GetNodeRecursivePart(parent_node, xml_file_child_node);
				}
			}
		}

		return;
	}

	INT get_result = 0;

	if (this->GetNodePart(child_node, xml_file_node, &get_result) == nullptr) {
		return;
	}

	child_node->RemoveChildNodeFromParentNode();

	parent_node->AddChildNode(child_node);

	if (get_result == 0) {
		for (auto &xml_file_child_node : xml_file_node->GetChildNodeContainer()) {
			this->GetNodeRecursivePart(child_node, xml_file_child_node);
		}
	}

	return;
}
