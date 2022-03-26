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
#include "SceneTask.h"
#include "NodeTask.h"


/**
 * @brief コンストラクタ
 */
tml::scene::ManagerDesc::ManagerDesc() :
	input_mgr_(nullptr),
	graphic_mgr_(nullptr),
	sound_mgr_(nullptr),
	frame_rate_limit(60U)
{
	this->resource_count = tml::ConstantUtil::SCENE::RESOURCE_TYPE_COUNT;
	this->task_count = tml::ConstantUtil::SCENE::TASK_TYPE_COUNT;
	this->event_count = tml::ConstantUtil::SCENE::EVENT_TYPE_COUNT;

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
	this->frame_rate_limit = 60U;

	tml::ManagerDesc::Init();

	this->resource_count = tml::ConstantUtil::SCENE::RESOURCE_TYPE_COUNT;
	this->task_count = tml::ConstantUtil::SCENE::TASK_TYPE_COUNT;
	this->event_count = tml::ConstantUtil::SCENE::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief OnSetInputManager関数
 * @param input_mgr (input_manager)
 */
void tml::scene::ManagerDesc::OnSetInputManager(tml::input::Manager *input_mgr)
{
	this->input_mgr_ = input_mgr;

	return;
}


/**
 * @brief OnSetGraphicManager関数
 * @param graphic_mgr (graphic_manager)
 */
void tml::scene::ManagerDesc::OnSetGraphicManager(tml::graphic::Manager *graphic_mgr)
{
	this->graphic_mgr_ = graphic_mgr;

	return;
}


/**
 * @brief OnSetSoundManager関数
 * @param sound_mgr (sound_manager)
 */
void tml::scene::ManagerDesc::OnSetSoundManager(tml::sound::Manager *sound_mgr)
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
	sound_mgr_(nullptr),
	frame_rate_limit_(60U),
	elapsed_time_(0.0),
	cpu_elapsed_time_(0.0),
	gpu_elapsed_time_(0.0)
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
	this->DeleteTaskContainer();
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
	this->frame_rate_limit_ = 60U;
	this->elapsed_time_ = tml::TIME_REAL(0.0);
	this->cpu_start_time_ = std::chrono::steady_clock::time_point();
	this->cpu_elapsed_time_ = tml::TIME_REAL(0.0);
	this->gpu_start_time_ = std::chrono::steady_clock::time_point();
	this->gpu_elapsed_time_ = tml::TIME_REAL(0.0);

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
	this->frame_rate_limit_ = desc.frame_rate_limit;

	{// ResourceFactory Set
		this->factory->AddResourceFunction(tml::ConstantUtil::SCENE::CLASS_NAME::SCENE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::scene::Scene> scene;
				tml::scene::SceneDesc scene_desc;

				scene_desc.SetManager(this);
				scene_desc.Read(conf_file_read_desc);

				if (this->GetResource<tml::scene::Scene>(scene, scene_desc, dst_result) == nullptr) {
					return (scene);
				}

				return (scene);
			}
		);

		this->factory->AddResourceFunction(tml::ConstantUtil::SCENE::CLASS_NAME::NODE,
			[this] (const tml::INIFileReadDesc &conf_file_read_desc, INT *dst_result) -> tml::shared_ptr<tml::ManagerResource> {
				tml::shared_ptr<tml::scene::Node> node;
				tml::scene::NodeDesc node_desc;

				node_desc.SetManager(this);
				node_desc.Read(conf_file_read_desc);

				if (this->GetResource<tml::scene::Node>(node, node_desc, dst_result) == nullptr) {
					return (node);
				}

				return (node);
			}
		);
	}

	{// EventFactory Set
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

	if (this->scene_ != nullptr) {
		if (!this->scene_->IsStarted()) {
			if (this->scene_->GetStartFlag()) {
				if (this->scene_->Start() < 0) {
					this->scene_->End();
					this->scene_->SetRunFlag(false);

					this->scene_.reset();

					return;
				} else {
					this->frame_rate_.Start(this->frame_rate_limit_);
				}
			}
		}

		if (this->scene_->GetStartFlag()) {
			this->cpu_start_time_ = std::chrono::steady_clock::now();

			this->input_mgr_->Update();

			this->scene_->Update();

			this->graphic_mgr_->Update();

			this->sound_mgr_->Update();

			this->cpu_elapsed_time_ = tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - this->cpu_start_time_);

			this->gpu_start_time_ = std::chrono::steady_clock::now();

			this->graphic_mgr_->UpdateSwapChain();

			this->gpu_elapsed_time_ = tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - this->gpu_start_time_);

			this->frame_rate_.Update();

			this->elapsed_time_ = this->frame_rate_.GetElapsedTime();
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
 * @brief OnSetInputManager関数
 * @param input_mgr (input_manager)
 */
void tml::scene::Manager::OnSetInputManager(tml::input::Manager *input_mgr)
{
	this->input_mgr_ = input_mgr;

	return;
}


/**
 * @brief OnSetGraphicManager関数
 * @param graphic_mgr (graphic_manager)
 */
void tml::scene::Manager::OnSetGraphicManager(tml::graphic::Manager *graphic_mgr)
{
	this->graphic_mgr_ = graphic_mgr;

	return;
}


/**
 * @brief OnSetSoundManager関数
 * @param sound_mgr (sound_manager)
 */
void tml::scene::Manager::OnSetSoundManager(tml::sound::Manager *sound_mgr)
{
	this->sound_mgr_ = sound_mgr;

	return;
}


/**
 * @brief GetScene関数
 * @param dst_scene (dst_scene)
 * @param prefab_file_read_desc (prefab_file_read_desc)
 * @param dst_result (dst_result)
 * @return dst_scene (dst_scene)
 */
tml::shared_ptr<tml::scene::Scene> &tml::scene::Manager::GetScene(tml::shared_ptr<tml::scene::Scene> &dst_scene, const tml::XMLFileReadDesc &prefab_file_read_desc, INT *dst_result)
{
	dst_scene.reset();
	tml::SetResult(dst_result, 0);

	auto prefab_file_read_desc_dat = prefab_file_read_desc.GetDataByParent();

	tml::XMLFile prefab_file;

	prefab_file.read_desc.parent_data = prefab_file_read_desc_dat;

	if (prefab_file.Read() < 0) {
		tml::SetResult(dst_result, -1);

		return (dst_scene);
	}

	auto &prefab_file_root_node = prefab_file.data.GetRootNode();

	if (prefab_file_root_node->GetChildNodeContainer().empty()) {
		tml::SetResult(dst_result, -1);

		return (dst_scene);
	}

	auto &prefab_file_node = prefab_file_root_node->GetChildNodeContainer().front();

	if (prefab_file_node->name != L"scene") {
		tml::SetResult(dst_result, -1);

		return (dst_scene);
	}

	INT get_result = 0;

	if (this->GetSceneGetPart(dst_scene, prefab_file_node, &get_result) == nullptr) {
		tml::SetResult(dst_result, -1);

		return (dst_scene);
	}

	if (get_result == 0) {
		for (auto &prefab_file_child_node : prefab_file_node->GetChildNodeContainer()) {
			this->GetNodeRecursivePart(dst_scene->GetRootNode(), prefab_file_child_node);
		}
	}

	tml::SetResult(dst_result, get_result);

	return (dst_scene);
}


/**
 * @brief GetSceneGetPart関数
 * @param dst_scene (dst_scene)
 * @param prefab_file_node (prefab_file_node)
 * @param dst_result (dst_result)
 */
tml::shared_ptr<tml::scene::Scene> &tml::scene::Manager::GetSceneGetPart(tml::shared_ptr<tml::scene::Scene> &dst_scene, const tml::shared_ptr<tml::XMLFileNode> &prefab_file_node, INT *dst_result)
{
	auto class_name = prefab_file_node->GetValue(L"class_name");
	auto conf_file_path = prefab_file_node->GetValue(L"conf_file_path");
	auto res_name = prefab_file_node->GetValue(L"res_name");
	auto prefab_file_path = prefab_file_node->GetValue(L"prefab_file_path");

	if (class_name != nullptr) {
		if (conf_file_path != nullptr) {
			if (this->factory->GetResource(dst_scene, class_name->c_str(), tml::INIFileReadDesc(conf_file_path->c_str()), dst_result) == nullptr) {
				return (dst_scene);
			}
		} else {
			tml::INIFileReadDesc conf_file_read_desc;

			conf_file_read_desc.data.string = prefab_file_node->string;

			if (this->factory->GetResource(dst_scene, class_name->c_str(), conf_file_read_desc, dst_result) == nullptr) {
				return (dst_scene);
			}
		}
	} else if (res_name != nullptr) {
		if (this->GetResource<tml::scene::Scene>(dst_scene, res_name->c_str(), dst_result) == nullptr) {
			return (dst_scene);
		}
	} else if (prefab_file_path != nullptr) {
		if (this->GetScene(dst_scene, tml::XMLFileReadDesc(prefab_file_path->c_str()), dst_result) == nullptr) {
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
 * @param deferred_flg (deferred_flag)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Manager::StartScene(const tml::shared_ptr<tml::scene::Scene> &scene, const bool deferred_flg)
{
	if (scene == nullptr) {
		return (-1);
	}

	if (deferred_flg) {
		tml::shared_ptr<tml::scene::SceneTask> task;
		tml::scene::SceneTaskDesc task_desc;

		task_desc.SetManager(this);
		task_desc.run_type = tml::ConstantUtil::SCENE::SCENE_TASK_RUN_TYPE::START_SCENE;
		task_desc.scene = scene;

		if (this->GetTask<tml::scene::SceneTask>(task, task_desc) == nullptr) {
			return (-1);
		}
	} else {
		if (this->scene_ == scene) {
			return (-1);
		}

		if (this->scene_ != nullptr) {
			this->scene_->End();
			this->scene_->SetRunFlag(false);
		}

		scene->End();
		scene->SetRunFlag(true);

		this->scene_ = scene;
	}

	return (0);
}


/**
 * @brief EndScene関数
 * @param deferred_flg (deferred_flag)
 */
void tml::scene::Manager::EndScene(const bool deferred_flg)
{
	if (deferred_flg) {
		tml::shared_ptr<tml::scene::SceneTask> task;
		tml::scene::SceneTaskDesc task_desc;

		task_desc.SetManager(this);
		task_desc.run_type = tml::ConstantUtil::SCENE::SCENE_TASK_RUN_TYPE::END_SCENE;

		if (this->GetTask<tml::scene::SceneTask>(task, task_desc) == nullptr) {
			return;
		}
	} else {
		if (this->scene_ == nullptr) {
			return;
		}

		this->scene_->End();
		this->scene_->SetRunFlag(false);

		this->scene_.reset();
	}

	return;
}


/**
 * @brief GetNode関数
 * @param dst_node (dst_node)
 * @param prefab_file_read_desc (prefab_file_read_desc)
 * @param dst_result (dst_result)
 * @return dst_node (dst_node)
 */
tml::shared_ptr<tml::scene::Node> &tml::scene::Manager::GetNode(tml::shared_ptr<tml::scene::Node> &dst_node, const tml::XMLFileReadDesc &prefab_file_read_desc, INT *dst_result)
{
	dst_node.reset();
	tml::SetResult(dst_result, 0);

	auto prefab_file_read_desc_dat = prefab_file_read_desc.GetDataByParent();

	tml::XMLFile prefab_file;

	prefab_file.read_desc.parent_data = prefab_file_read_desc_dat;

	if (prefab_file.Read() < 0) {
		tml::SetResult(dst_result, -1);

		return (dst_node);
	}

	auto &prefab_file_root_node = prefab_file.data.GetRootNode();

	if (prefab_file_root_node->GetChildNodeContainer().empty()) {
		tml::SetResult(dst_result, -1);

		return (dst_node);
	}

	auto &prefab_file_node = prefab_file_root_node->GetChildNodeContainer().front();

	if (prefab_file_node->name != L"node") {
		tml::SetResult(dst_result, -1);

		return (dst_node);
	}

	INT get_result = 0;

	if (this->GetNodeGetPart(dst_node, prefab_file_node, &get_result) == nullptr) {
		tml::SetResult(dst_result, -1);

		return (dst_node);
	}

	if (get_result == 0) {
		for (auto &prefab_file_child_node : prefab_file_node->GetChildNodeContainer()) {
			this->GetNodeRecursivePart(dst_node, prefab_file_child_node);
		}
	}

	tml::SetResult(dst_result, get_result);

	return (dst_node);
}


/**
 * @brief GetNodeGetPart関数
 * @param dst_node (dst_node)
 * @param prefab_file_node (prefab_file_node)
 * @param dst_result (dst_result)
 */
tml::shared_ptr<tml::scene::Node> &tml::scene::Manager::GetNodeGetPart(tml::shared_ptr<tml::scene::Node> &dst_node, const tml::shared_ptr<tml::XMLFileNode> &prefab_file_node, INT *dst_result)
{
	auto class_name = prefab_file_node->GetValue(L"class_name");
	auto conf_file_path = prefab_file_node->GetValue(L"conf_file_path");
	auto res_name = prefab_file_node->GetValue(L"res_name");
	auto prefab_file_path = prefab_file_node->GetValue(L"prefab_file_path");

	if (class_name != nullptr) {
		if (conf_file_path != nullptr) {
			if (this->factory->GetResource(dst_node, class_name->c_str(), tml::INIFileReadDesc(conf_file_path->c_str()), dst_result) == nullptr) {
				return (dst_node);
			}
		} else {
			tml::INIFileReadDesc conf_file_read_desc;

			conf_file_read_desc.data.string = prefab_file_node->string;

			if (this->factory->GetResource(dst_node, class_name->c_str(), conf_file_read_desc, dst_result) == nullptr) {
				return (dst_node);
			}
		}
	} else if (res_name != nullptr) {
		if (this->GetResource<tml::scene::Node>(dst_node, res_name->c_str(), dst_result) == nullptr) {
			return (dst_node);
		}
	} else if (prefab_file_path != nullptr) {
		if (this->GetNode(dst_node, tml::XMLFileReadDesc(prefab_file_path->c_str()), dst_result) == nullptr) {
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
 * @param prefab_file_node (prefab_file_node)
 */
void tml::scene::Manager::GetNodeRecursivePart(const tml::shared_ptr<tml::scene::Node> &parent_node, const tml::shared_ptr<tml::XMLFileNode> &prefab_file_node)
{
	tml::shared_ptr<tml::scene::Node> child_node;

	if (prefab_file_node->name != L"node") {
		if (prefab_file_node->name == L"if") {
			bool result_flg = true;

			for (auto &val : prefab_file_node->value_container) {
				auto factory_val = this->factory->GetValue(val.first.c_str());

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
				for (auto &prefab_file_child_node : prefab_file_node->GetChildNodeContainer()) {
					this->GetNodeRecursivePart(parent_node, prefab_file_child_node);
				}
			}
		}

		return;
	}

	INT get_result = 0;

	if (this->GetNodeGetPart(child_node, prefab_file_node, &get_result) == nullptr) {
		return;
	}

	child_node->RemoveChildNodeFromParentNode();

	parent_node->AddChildNode(child_node);

	if (get_result == 0) {
		for (auto &prefab_file_child_node : prefab_file_node->GetChildNodeContainer()) {
			this->GetNodeRecursivePart(child_node, prefab_file_child_node);
		}
	}

	return;
}
