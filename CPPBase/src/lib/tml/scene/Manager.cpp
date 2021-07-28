/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "Scene.h"
#include "BaseScene.h"
#include "Node.h"
#include "BaseNode.h"
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

	this->factory.Init();
	this->common.Init();

	this->DeleteResourceContainer();

	tml::Manager::Release();

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

	if (this->factory.Create(this) < 0) {
		this->Init();

		return (-1);
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
