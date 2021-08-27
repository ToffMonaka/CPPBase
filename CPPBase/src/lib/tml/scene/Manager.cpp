/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "Scene.h"
#include "Node.h"
#include "SceneEvent.h"
#include "NodeEvent.h"


/**
 * @brief コンストラクタ
 */
tml::scene::ManagerDesc::ManagerDesc() :
	input_mgr_(nullptr),
	graphic_mgr_(nullptr),
	sound_mgr_(nullptr)

{
	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::ManagerDesc::Init(void)
{
	this->Release();

	this->input_mgr_ = nullptr;
	this->graphic_mgr_ = nullptr;
	this->sound_mgr_ = nullptr;

	tml::ManagerDesc::Init();

	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount関数
 */
void tml::scene::ManagerDesc::InitResourceCount(void)
{
	tml::ManagerDesc::InitResourceCount();

	this->resource_count_container.resize(tml::ConstantUtil::SCENE::RESOURCE_TYPE_COUNT);
	this->resource_count_container[static_cast<UINT>(tml::ConstantUtil::SCENE::RESOURCE_TYPE::SCENE)] = tml::ConstantUtil::SCENE::SCENE_TYPE_COUNT;
	this->resource_count_container[static_cast<UINT>(tml::ConstantUtil::SCENE::RESOURCE_TYPE::NODE)] = tml::ConstantUtil::SCENE::NODE_TYPE_COUNT;

	return;
}


/**
 * @brief InitEventCount関数
 */
void tml::scene::ManagerDesc::InitEventCount(void)
{
	tml::ManagerDesc::InitEventCount();

	this->event_count_container.resize(tml::ConstantUtil::SCENE::EVENT_TYPE_COUNT);
	this->event_count_container[static_cast<UINT>(tml::ConstantUtil::SCENE::EVENT_TYPE::SCENE)] = tml::ConstantUtil::SCENE::SCENE_EVENT_TYPE_COUNT;
	this->event_count_container[static_cast<UINT>(tml::ConstantUtil::SCENE::EVENT_TYPE::NODE)] = tml::ConstantUtil::SCENE::NODE_EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief SetInputManager関数
 * @param input_mgr (input_manager)
 */
void tml::scene::ManagerDesc::SetInputManager(tml::input::Manager *input_mgr)
{
	this->input_mgr_ = input_mgr;

	return;
}


/**
 * @brief SetGraphicManager関数
 * @param graphic_mgr (graphic_manager)
 */
void tml::scene::ManagerDesc::SetGraphicManager(tml::graphic::Manager *graphic_mgr)
{
	this->graphic_mgr_ = graphic_mgr;

	return;
}


/**
 * @brief SetSoundManager関数
 * @param sound_mgr (sound_manager)
 */
void tml::scene::ManagerDesc::SetSoundManager(tml::sound::Manager *sound_mgr)
{
	this->sound_mgr_ = sound_mgr;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::scene::Manager::Manager() :
	input_mgr_(nullptr),
	graphic_mgr_(nullptr),
	sound_mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::scene::Manager::Release(void)
{
	if (this->scene_ != nullptr) {
		this->scene_->End();
		this->scene_->SetRunFlag(false);

		this->scene_.reset();
	}

	this->common.Init();

	this->DeleteResourceContainer();
	this->DeleteEventContainer();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::Manager::Init(void)
{
	this->Release();

	this->input_mgr_ = nullptr;
	this->graphic_mgr_ = nullptr;
	this->sound_mgr_ = nullptr;
	this->frame_rate_.Init();

	tml::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Manager::Create(const tml::scene::ManagerDesc &desc)
{
	if ((desc.GetInputManager() == nullptr)
	|| (desc.GetGraphicManager() == nullptr)
	|| (desc.GetSoundManager() == nullptr)) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->input_mgr_ = desc.GetInputManager();
	this->graphic_mgr_ = desc.GetGraphicManager();
	this->sound_mgr_ = desc.GetSoundManager();

	{// ResourceFactory Set
		this->resource_factory.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::SCENE,
			[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				tml::scene::SceneDesc desc;

				desc.SetManager(this);
				desc.Read(file_read_desc);

				if (this->GetResource<tml::scene::Scene>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);

		this->resource_factory.AddFunction(tml::ConstantUtil::SCENE::CLASS_NAME::NODE,
			[this] (const tml::INIFileReadDesc &file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::ManagerResource> res;

				tml::scene::NodeDesc desc;

				desc.SetManager(this);
				desc.Read(file_read_desc);

				if (this->GetResource<tml::scene::Node>(res, desc, dst_result) == nullptr) {
					return (res);
				}

				return (res);
			}
		);
	}

	if (this->common.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Update関数
 */
void tml::scene::Manager::Update(void)
{
	tml::Manager::Update();

	for (UINT event_i = 0U; event_i < this->GetEventCount(tml::scene::SceneEvent::EVENT_MAIN_INDEX); ++event_i) {
		auto event = reinterpret_cast<tml::scene::SceneEvent *>(this->GetEventFast(tml::scene::SceneEvent::EVENT_MAIN_INDEX, event_i));
		auto &event_dat = event->data;

		switch (event_dat.type) {
		case tml::ConstantUtil::SCENE::SCENE_EVENT_DATA_TYPE::START: {
			if (this->scene_ == event_dat.scene) {
				break;
			}

			if (this->scene_ != nullptr) {
				this->scene_->End();
				this->scene_->SetRunFlag(false);
			}

			event_dat.scene->End();
			event_dat.scene->SetRunFlag(true);

			this->scene_ = event_dat.scene;

			break;
		}
		case tml::ConstantUtil::SCENE::SCENE_EVENT_DATA_TYPE::END: {
			if (this->scene_ == nullptr) {
				return;
			}

			this->scene_->End();
			this->scene_->SetRunFlag(false);

			this->scene_.reset();

			return;
		}
		}

		event_dat.Init();
	}

	for (UINT event_i = 0U; event_i < this->GetEventCount(tml::scene::NodeEvent::EVENT_MAIN_INDEX); ++event_i) {
		auto event = reinterpret_cast<tml::scene::NodeEvent *>(this->GetEventFast(tml::scene::NodeEvent::EVENT_MAIN_INDEX, event_i));
		auto &event_dat = event->data;

		switch (event_dat.type) {
		case tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::ADD: {
			if (event_dat.parent_node != nullptr) {
				if (event_dat.child_node != nullptr) {
					event_dat.parent_node->AddChildNode(event_dat.child_node, false);
				}
			}

			break;
		}
		case tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::REMOVE: {
			if (event_dat.parent_node != nullptr) {
				if (event_dat.child_node != nullptr) {
					event_dat.parent_node->RemoveChildNode(event_dat.child_node, false);
				} else {
					event_dat.parent_node->RemoveChildNode(false);
				}
			} else {
				event_dat.child_node->RemoveChildNodeFromParentNode(false);
			}

			break;
		}
		}

		event_dat.Init();
	}

	if (this->scene_ != nullptr) {
		if (!this->scene_->IsStarted()) {
			if (this->scene_->GetStartFlag()) {
				if (this->scene_->Start() < 0) {
					this->scene_->End();
					this->scene_->SetRunFlag(false);

					this->scene_.reset();

					return;
				} else {
					this->frame_rate_.Start(this->graphic_mgr_->GetFrameRateLimit());
				}
			}
		}

		if (this->scene_->GetStartFlag()) {
			this->input_mgr_->Update();

			this->scene_->Update();

			this->graphic_mgr_->Update();

			this->sound_mgr_->Update();

			this->frame_rate_.Update();
		}

		if (!this->scene_->GetStartFlag()) {
			this->scene_->End();
			this->scene_->SetRunFlag(false);

			this->scene_.reset();

			return;
		}
	}

	return;
}


/**
 * @brief GetScene関数
 * @param dst_scene (dst_scene)
 * @param file_read_desc (file_read_desc)
 * @param dst_result (dst_result)
 * @return dst_scene (dst_scene)
 */
tml::shared_ptr<tml::scene::Scene> &tml::scene::Manager::GetScene(tml::shared_ptr<tml::scene::Scene> &dst_scene, const tml::XMLFileReadDesc &file_read_desc, INT *dst_result)
{
	dst_scene.reset();
	tml::SetResult(dst_result, 0);

	auto file_read_desc_dat = file_read_desc.GetDataByParent();

	tml::XMLFile xml_file;

	xml_file.read_desc.parent_data = file_read_desc_dat;

	if (xml_file.Read() < 0) {
		tml::SetResult(dst_result, -1);

		return (dst_scene);
	}

	if (xml_file.data.GetRootNode()->GetChildNodeContainer().empty()) {
		tml::SetResult(dst_result, -1);

		return (dst_scene);
	}

	auto &xml_file_node = xml_file.data.GetRootNode()->GetChildNodeContainer().front();

	if (xml_file_node->name != L"scene") {
		tml::SetResult(dst_result, -1);

		return (dst_scene);
	}

	INT get_result = 0;

	if (this->GetSceneGetPart(dst_scene, xml_file_node, &get_result) == nullptr) {
		tml::SetResult(dst_result, -1);

		return (dst_scene);
	}

	if (get_result == 0) {
		for (auto &xml_file_child_node : xml_file_node->GetChildNodeContainer()) {
			this->GetNodeRecursivePart(dst_scene->GetRootNode(), xml_file_child_node);
		}
	}

	tml::SetResult(dst_result, get_result);

	return (dst_scene);
}


/**
 * @brief GetSceneGetPart関数
 * @param dst_scene (dst_scene)
 * @param xml_file_node (xml_file_node)
 * @param dst_result (dst_result)
 */
tml::shared_ptr<tml::scene::Scene> &tml::scene::Manager::GetSceneGetPart(tml::shared_ptr<tml::scene::Scene> &dst_scene, const tml::shared_ptr<tml::XMLFileDataNode> &xml_file_node, INT *dst_result)
{
	auto class_name = xml_file_node->GetValue(L"class_name");
	auto ini_file_path = xml_file_node->GetValue(L"ini_file_path");
	auto xml_file_path = xml_file_node->GetValue(L"xml_file_path");
	auto res_name = xml_file_node->GetValue(L"res_name");

	if (class_name != nullptr) {
		if (xml_file_path != nullptr) {
			if ((*class_name) != ConstantUtil::SCENE::CLASS_NAME::SCENE) {
				tml::SetResult(dst_result, -1);

				return (dst_scene);
			}

			if (this->GetScene(dst_scene, tml::XMLFileReadDesc(xml_file_path->c_str()), dst_result) == nullptr) {
				return (dst_scene);
			}
		} else if (ini_file_path != nullptr) {
			if (this->resource_factory.Get(dst_scene, class_name->c_str(), tml::INIFileReadDesc(ini_file_path->c_str()), dst_result) == nullptr) {
				return (dst_scene);
			}
		} else {
			tml::INIFileReadDesc desc;

			desc.data.string = xml_file_node->string;

			if (this->resource_factory.Get(dst_scene, class_name->c_str(), desc, dst_result) == nullptr) {
				return (dst_scene);
			}
		}
	} else if (res_name != nullptr) {
		if (this->GetResource<tml::scene::Scene>(dst_scene, res_name->c_str(), dst_result) == nullptr) {
			return (dst_scene);
		}
	} else {
		tml::SetResult(dst_result, -1);

		return (dst_scene);
	}

	return (dst_scene);
}


/**
 * @brief StartScene関数
 * @param scene (scene)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Manager::StartScene(const tml::shared_ptr<tml::scene::Scene> &scene)
{
	if (scene == nullptr) {
		return (-1);
	}

	tml::scene::SceneEventDesc event_desc;

	event_desc.SetManager(this);
	event_desc.data.type = tml::ConstantUtil::SCENE::SCENE_EVENT_DATA_TYPE::START;
	event_desc.data.scene = scene;

	if (this->AddEvent<tml::scene::SceneEvent>(event_desc) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief EndScene関数
 */
void tml::scene::Manager::EndScene(void)
{
	tml::scene::SceneEventDesc event_desc;

	event_desc.SetManager(this);
	event_desc.data.type = tml::ConstantUtil::SCENE::SCENE_EVENT_DATA_TYPE::END;

	if (this->AddEvent<tml::scene::SceneEvent>(event_desc) < 0) {
		return;
	}

	return;
}


/**
 * @brief GetNode関数
 * @param dst_node (dst_node)
 * @param file_read_desc (file_read_desc)
 * @param dst_result (dst_result)
 * @return dst_node (dst_node)
 */
tml::shared_ptr<tml::scene::Node> &tml::scene::Manager::GetNode(tml::shared_ptr<tml::scene::Node> &dst_node, const tml::XMLFileReadDesc &file_read_desc, INT *dst_result)
{
	dst_node.reset();
	tml::SetResult(dst_result, 0);

	auto file_read_desc_dat = file_read_desc.GetDataByParent();

	tml::XMLFile xml_file;

	xml_file.read_desc.parent_data = file_read_desc_dat;

	if (xml_file.Read() < 0) {
		tml::SetResult(dst_result, -1);

		return (dst_node);
	}

	if (xml_file.data.GetRootNode()->GetChildNodeContainer().empty()) {
		tml::SetResult(dst_result, -1);

		return (dst_node);
	}

	auto &xml_file_node = xml_file.data.GetRootNode()->GetChildNodeContainer().front();

	if (xml_file_node->name != L"node") {
		tml::SetResult(dst_result, -1);

		return (dst_node);
	}

	INT get_result = 0;

	if (this->GetNodeGetPart(dst_node, xml_file_node, &get_result) == nullptr) {
		tml::SetResult(dst_result, -1);

		return (dst_node);
	}

	if (get_result == 0) {
		for (auto &xml_file_child_node : xml_file_node->GetChildNodeContainer()) {
			this->GetNodeRecursivePart(dst_node, xml_file_child_node);
		}
	}

	tml::SetResult(dst_result, get_result);

	return (dst_node);
}


/**
 * @brief GetNodeGetPart関数
 * @param dst_node (dst_node)
 * @param xml_file_node (xml_file_node)
 * @param dst_result (dst_result)
 */
tml::shared_ptr<tml::scene::Node> &tml::scene::Manager::GetNodeGetPart(tml::shared_ptr<tml::scene::Node> &dst_node, const tml::shared_ptr<tml::XMLFileDataNode> &xml_file_node, INT *dst_result)
{
	auto class_name = xml_file_node->GetValue(L"class_name");
	auto ini_file_path = xml_file_node->GetValue(L"ini_file_path");
	auto xml_file_path = xml_file_node->GetValue(L"xml_file_path");
	auto res_name = xml_file_node->GetValue(L"res_name");

	if (class_name != nullptr) {
		if (xml_file_path != nullptr) {
			if ((*class_name) != ConstantUtil::SCENE::CLASS_NAME::NODE) {
				tml::SetResult(dst_result, -1);

				return (dst_node);
			}

			if (this->GetNode(dst_node, tml::XMLFileReadDesc(xml_file_path->c_str()), dst_result) == nullptr) {
				return (dst_node);
			}
		} else if (ini_file_path != nullptr) {
			if (this->resource_factory.Get(dst_node, class_name->c_str(), tml::INIFileReadDesc(ini_file_path->c_str()), dst_result) == nullptr) {
				return (dst_node);
			}
		} else {
			tml::INIFileReadDesc desc;

			desc.data.string = xml_file_node->string;

			if (this->resource_factory.Get(dst_node, class_name->c_str(), desc, dst_result) == nullptr) {
				return (dst_node);
			}
		}
	} else if (res_name != nullptr) {
		if (this->GetResource<tml::scene::Node>(dst_node, res_name->c_str(), dst_result) == nullptr) {
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
void tml::scene::Manager::GetNodeRecursivePart(const tml::shared_ptr<tml::scene::Node> &parent_node, const tml::shared_ptr<tml::XMLFileDataNode> &xml_file_node)
{
	tml::shared_ptr<tml::scene::Node> child_node;

	if (xml_file_node->name != L"node") {
		if (xml_file_node->name == L"if") {
			bool result_flg = true;

			for (auto &val : xml_file_node->value_container) {
				auto factory_val = this->GetResourceFactoryValue(val.first.c_str());

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

	if (this->GetNodeGetPart(child_node, xml_file_node, &get_result) == nullptr) {
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
