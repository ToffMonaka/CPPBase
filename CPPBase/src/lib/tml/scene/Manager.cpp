/**
 * @file
 * @brief Managerコードファイル
 */


#include "Manager.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "Scene.h"


/**
 * @brief コンストラクタ
 */
tml::scene::ManagerDesc::ManagerDesc() :
	input_manager(nullptr),
	graphic_manager(nullptr),
	sound_manager(nullptr)

{
	this->resource_count_container.clear();
	this->resource_count_container.resize(tml::ConstantUtil::SCENE::RESOURCE_TYPE_COUNT);
	this->resource_count_container[static_cast<UINT>(tml::ConstantUtil::SCENE::RESOURCE_TYPE::SCENE)] = tml::ConstantUtil::SCENE::SCENE_TYPE_COUNT;
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

	this->resource_count_container.clear();
	this->resource_count_container.resize(tml::ConstantUtil::SCENE::RESOURCE_TYPE_COUNT);
	this->event_count = tml::ConstantUtil::SCENE::EVENT_TYPE_COUNT;

	this->input_manager = nullptr;
	this->graphic_manager = nullptr;
	this->sound_manager = nullptr;

	tml::ManagerDesc::Init();

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

		this->scene_end_flg_ = false;

		this->ReleaseResource(this->scene_);
		this->ReleaseResource(this->next_scene_);
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
	if ((desc.input_manager == nullptr)
	|| (desc.graphic_manager == nullptr)
	|| (desc.sound_manager == nullptr)) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->input_mgr_ = desc.input_manager;
	this->graphic_mgr_ = desc.graphic_manager;
	this->sound_mgr_ = desc.sound_manager;

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

	if (this->scene_ != nullptr) {
		this->input_mgr_->Update();

		this->scene_->Update();

		this->graphic_mgr_->Update();

		this->sound_mgr_->Update();

		this->frame_rate_.Update();

		if (this->scene_end_flg_) {
			this->scene_->End();

			this->scene_end_flg_ = false;

			this->ReleaseResource(this->scene_);
			this->ReleaseResource(this->next_scene_);
		}

		if (this->next_scene_ != nullptr) {
			this->scene_->End();

			this->scene_end_flg_ = false;

			this->GetResource(this->scene_, this->next_scene_);

			if (this->scene_ == nullptr) {
				this->ReleaseResource(this->next_scene_);

				return;
			}

			this->ReleaseResource(this->next_scene_);

			if (this->scene_->Start() < 0) {
				this->ReleaseResource(this->scene_);

				return;
			}

			this->frame_rate_.Start(this->graphic_mgr_->GetFrameRateLimit());
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
	if (this->common_.Create(this) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief DeleteCommon関数
 */
void tml::scene::Manager::DeleteCommon(void)
{
	this->common_.Init();

	return;
}


/**
 * @brief Start関数
 * @param scene (scene)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Manager::Start(tml::shared_ptr<tml::scene::Scene> &scene)
{
	if (scene == nullptr) {
		return (-1);
	}

	if (this->scene_ != nullptr) {
		this->GetResource(this->next_scene_, scene);

		if (this->next_scene_ == nullptr) {
			return (-1);
		}

		return (0);
	}

	this->GetResource(this->scene_, scene);

	if (this->scene_ == nullptr) {
		this->ReleaseResource(this->next_scene_);

		return (-1);
	}

	this->ReleaseResource(this->next_scene_);

	if (this->scene_->Start() < 0) {
		this->ReleaseResource(this->scene_);

		return (-1);
	}

	this->frame_rate_.Start(this->graphic_mgr_->GetFrameRateLimit());

	return (0);
}


/**
 * @brief End関数
 */
void tml::scene::Manager::End(void)
{
	if (this->scene_ != nullptr) {
		this->scene_end_flg_ = true;
	}

	return;
}
