/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "BaseScene.h"
#include "BaseNode.h"
#include "Base2DNode.h"


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

	this->event_count = tml::ConstantUtil::SCENE::EVENT_TYPE_COUNT;

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
	sound_mgr_(nullptr),
	scene_end_flg_(false)
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

		this->scene_.reset();
		this->scene_end_flg_ = false;
	}

	this->DeleteCommon();
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
	this->scene_.reset();
	this->scene_end_flg_ = false;
	this->next_scene_.reset();

	tml::Manager::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
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

	{// SceneFactory Set
		this->scene_factory.AddFunction(L"BaseScene",
			[this] (const tml::INIFileReadDesc &desc_read_desc) -> tml::shared_ptr<tml::scene::Scene> {
				tml::shared_ptr<tml::scene::Scene> scene;

				tml::scene::BaseSceneDesc desc;

				desc.SetManager(this);
				desc.Read(desc_read_desc);

				if (this->GetResource<tml::scene::BaseScene>(scene, desc) == nullptr) {
					return (scene);
				}

				return (scene);
			}
		);
	}

	{// NodeFactory Set
		this->node_factory.AddFunction(L"BaseNode",
			[this] (const tml::INIFileReadDesc &desc_read_desc) -> tml::shared_ptr<tml::scene::Node> {
				tml::shared_ptr<tml::scene::Node> node;

				tml::scene::BaseNodeDesc desc;

				desc.SetManager(this);
				desc.Read(desc_read_desc);

				if (this->GetResource<tml::scene::BaseNode>(node, desc) == nullptr) {
					return (node);
				}

				return (node);
			}
		);

		this->node_factory.AddFunction(L"Base2DNode",
			[this] (const tml::INIFileReadDesc &desc_read_desc) -> tml::shared_ptr<tml::scene::Node> {
				tml::shared_ptr<tml::scene::Node> node;

				tml::scene::Base2DNodeDesc desc;

				desc.SetManager(this);
				desc.Read(desc_read_desc);

				if (this->GetResource<tml::scene::Base2DNode>(node, desc) == nullptr) {
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
 * @brief Update関数
 */
void tml::scene::Manager::Update(void)
{
	tml::Manager::Update();

	if (this->next_scene_ != nullptr) {
		if (this->scene_ != nullptr) {
			this->scene_->End();

			this->scene_.reset();
			this->scene_end_flg_ = false;
		}

		this->scene_ = std::move(this->next_scene_);

		if (this->scene_->Start() < 0) {
			this->scene_.reset();
			this->scene_end_flg_ = false;

			return;
		}

		this->frame_rate_.Start(this->graphic_mgr_->GetFrameRateLimit());
	}

	if (this->scene_ != nullptr) {
		this->input_mgr_->Update();

		this->scene_->Update();

		this->graphic_mgr_->Update();

		this->sound_mgr_->Update();

		this->frame_rate_.Update();

		if (this->scene_end_flg_) {
			this->scene_->End();

			this->scene_.reset();
			this->scene_end_flg_ = false;
		}
	}

	return;
}


/**
 * @brief CreateCommon関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Manager::CreateCommon(void)
{
	if (this->common.Create(this) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief DeleteCommon関数
 */
void tml::scene::Manager::DeleteCommon(void)
{
	this->common.Init();

	return;
}


/**
 * @brief StartScene関数
 * @param scene (scene)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Manager::StartScene(tml::shared_ptr<tml::scene::Scene> &scene)
{
	if (scene == nullptr) {
		return (-1);
	}

	this->next_scene_ = scene;

	return (0);
}


/**
 * @brief EndScene関数
 */
void tml::scene::Manager::EndScene(void)
{
	if (this->scene_ == nullptr) {
		return;
	}

	this->scene_end_flg_ = true;

	return;
}
