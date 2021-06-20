/**
 * @file
 * @brief Manager�R�[�h�t�@�C��
 */


#include "Manager.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "BaseScene.h"
#include "BaseNode.h"
#include "SceneEvent.h"
#include "NodeEvent.h"


/**
 * @brief �R���X�g���N�^
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
 * @brief �f�X�g���N�^
 */
tml::scene::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
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
 * @brief InitResourceCount�֐�
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
 * @brief InitEventCount�֐�
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
 * @brief SetInputManager�֐�
 * @param input_mgr (input_manager)
 */
void tml::scene::ManagerDesc::SetInputManager(tml::input::Manager *input_mgr)
{
	this->input_mgr_ = input_mgr;

	return;
}


/**
 * @brief SetGraphicManager�֐�
 * @param graphic_mgr (graphic_manager)
 */
void tml::scene::ManagerDesc::SetGraphicManager(tml::graphic::Manager *graphic_mgr)
{
	this->graphic_mgr_ = graphic_mgr;

	return;
}


/**
 * @brief SetSoundManager�֐�
 * @param sound_mgr (sound_manager)
 */
void tml::scene::ManagerDesc::SetSoundManager(tml::sound::Manager *sound_mgr)
{
	this->sound_mgr_ = sound_mgr;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::scene::Manager::Manager() :
	input_mgr_(nullptr),
	graphic_mgr_(nullptr),
	sound_mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::scene::Manager::Release(void)
{
	if (this->scene_ != nullptr) {
		this->scene_->End();
		this->scene_->SetRunFlag(false);

		this->scene_.reset();
	}

	this->DeleteCommon();
	this->DeleteResourceContainer();

	tml::Manager::Release();

	return;
}


/**
 * @brief Init�֐�
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
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
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

	{// Factory Set
		this->scene_factory_by_ini_file.AddFunction(L"BaseScene",
			[this] (const tml::INIFileReadDesc &read_desc) -> tml::shared_ptr<tml::scene::Scene> {
				tml::shared_ptr<tml::scene::Scene> scene;

				tml::scene::BaseSceneDesc desc;

				desc.SetManager(this);
				desc.Read(read_desc);

				if (this->GetResource<tml::scene::BaseScene>(scene, desc) == nullptr) {
					return (scene);
				}

				return (scene);
			}
		);

		this->scene_factory_by_xml_file.AddFunction(L"Scene",
			[this] (const tml::XMLFileReadDesc &read_desc) -> tml::shared_ptr<tml::scene::Scene> {
				tml::shared_ptr<tml::scene::Scene> scene;

				auto read_desc_dat = read_desc.GetDataByParent();

				tml::XMLFile xml_file;

				xml_file.read_desc.parent_data = read_desc_dat;

				if (xml_file.Read() < 0) {
					return (scene);
				}

				if (xml_file.data.GetRootNode()->GetChildNodeContainer().empty()) {
					return (scene);
				}

				auto scene_node = xml_file.data.GetRootNode()->GetChildNodeContainer().front().get();

				if (scene_node->name != L"scene") {
					return (scene);
				}

				auto scene_class_name = scene_node->GetValue(L"class_name");

				if (scene_class_name == nullptr) {
					return (scene);
				}

				if (this->scene_factory_by_ini_file.Get(scene, scene_class_name->c_str(), tml::INIFileReadDesc()) == nullptr) {
					return (scene);
				}

				return (scene);
			}
		);

		this->node_factory_by_ini_file.AddFunction(L"BaseNode",
			[this] (const tml::INIFileReadDesc &read_desc) -> tml::shared_ptr<tml::scene::Node> {
				tml::shared_ptr<tml::scene::Node> node;

				tml::scene::BaseNodeDesc desc;

				desc.SetManager(this);
				desc.Read(read_desc);

				if (this->GetResource<tml::scene::BaseNode>(node, desc) == nullptr) {
					return (node);
				}

				return (node);
			}
		);

		this->node_factory_by_xml_file.AddFunction(L"Node",
			[this] (const tml::XMLFileReadDesc &read_desc) -> tml::shared_ptr<tml::scene::Node> {
				tml::shared_ptr<tml::scene::Node> node;

				auto read_desc_dat = read_desc.GetDataByParent();

				tml::XMLFile xml_file;

				xml_file.read_desc.parent_data = read_desc_dat;

				if (xml_file.Read() < 0) {
					return (node);
				}

				if (xml_file.data.GetRootNode()->GetChildNodeContainer().empty()) {
					return (node);
				}

				auto node_node = xml_file.data.GetRootNode()->GetChildNodeContainer().front().get();

				if (node_node->name != L"node") {
					return (node);
				}

				auto node_class_name = node_node->GetValue(L"class_name");

				if (node_class_name == nullptr) {
					return (node);
				}

				if (this->node_factory_by_ini_file.Get(node, node_class_name->c_str(), tml::INIFileReadDesc()) == nullptr) {
					return (node);
				}

				return (node);
			}
		);
	}

	if (this->CreateCommon() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Update�֐�
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
			event_dat.parent_node->AddChildNode(event_dat.child_node, false);

			break;
		}
		case tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::REMOVE: {
			event_dat.parent_node->RemoveChildNode(event_dat.child_node, false);

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
 * @brief CreateCommon�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::scene::Manager::CreateCommon(void)
{
	if (this->common.Create(this) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief DeleteCommon�֐�
 */
void tml::scene::Manager::DeleteCommon(void)
{
	this->common.Init();

	return;
}


/**
 * @brief StartScene�֐�
 * @param scene (scene)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::scene::Manager::StartScene(tml::shared_ptr<tml::scene::Scene> &scene)
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
 * @brief EndScene�֐�
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
 * @brief AddNode�֐�
 * @param parent_node (parent_node)
 * @param child_node (child_node)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::scene::Manager::AddNode(tml::shared_ptr<tml::scene::Node> &parent_node, tml::shared_ptr<tml::scene::Node> &child_node)
{
	if ((parent_node == nullptr)
	|| (child_node == nullptr)
	|| (child_node == parent_node)) {
		return (-1);
	}

	tml::scene::NodeEventDesc event_desc;

	event_desc.SetManager(this);
	event_desc.data.type = tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::ADD;
	event_desc.data.parent_node = parent_node;
	event_desc.data.child_node = child_node;

	if (this->AddEvent<tml::scene::NodeEvent>(event_desc) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief RemoveNode�֐�
 * @param parent_node (parent_node)
 * @param child_node (child_node)
 */
void tml::scene::Manager::RemoveNode(tml::shared_ptr<tml::scene::Node> &parent_node, tml::shared_ptr<tml::scene::Node> &child_node)
{
	if ((parent_node == nullptr)
	|| (child_node == nullptr)
	|| (child_node == parent_node)) {
		return;
	}

	tml::scene::NodeEventDesc event_desc;

	event_desc.SetManager(this);
	event_desc.data.type = tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::REMOVE;
	event_desc.data.parent_node = parent_node;
	event_desc.data.child_node = child_node;

	if (this->AddEvent<tml::scene::NodeEvent>(event_desc) < 0) {
		return;
	}

	return;
}
