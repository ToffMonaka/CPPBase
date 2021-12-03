/**
 * @file
 * @brief Sceneコードファイル
 */


#include "Scene.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../graphic/Canvas2D.h"
#include "../graphic/Canvas3D.h"
#include "../graphic/Light2D.h"
#include "../graphic/Light3D.h"
#include "../graphic/Fog2D.h"
#include "../graphic/Fog3D.h"
#include "../graphic/Model2D.h"
#include "../graphic/Model3D.h"
#include "../sound/Manager.h"
#include "Manager.h"
#include "Node.h"


/**
 * @brief コンストラクタ
 */
tml::scene::SceneDesc::SceneDesc() :
	color(1.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::SceneDesc::~SceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::SceneDesc::Init(void)
{
	this->Release();

	this->name.clear();
	this->transform_2d.Init();
	this->transform_3d.Init();
	this->color = 1.0f;

	tml::scene::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::SceneDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::scene::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Scene Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"SCENE");

		if (val_name_cont != nullptr) {
			val = conf_file.data.GetValue((*val_name_cont), L"NAME");

			if (val != nullptr) {
				this->name = (*val);
			}
		}
	}

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::scene::Scene::Scene() :
	input_mgr_(nullptr),
	graphic_mgr_(nullptr),
	sound_mgr_(nullptr),
	type_(tml::ConstantUtil::SCENE::SCENE_TYPE::NONE),
	run_flg_(false),
	start_flg_(false),
	started_flg_(false),
	draw_canvas_2d_cont_(nullptr),
	draw_canvas_3d_cont_(nullptr),
	color(1.0f)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::Scene::~Scene()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::scene::Scene::Release(void)
{
	if (this->root_node_ != nullptr) {
		this->root_node_->End();
		this->root_node_->SetRunFlag(false);

		this->root_node_.reset();
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::Scene::Init(void)
{
	this->Release();

	this->input_mgr_ = nullptr;
	this->graphic_mgr_ = nullptr;
	this->sound_mgr_ = nullptr;
	this->type_ = tml::ConstantUtil::SCENE::SCENE_TYPE::NONE;
	this->run_flg_ = false;
	this->start_flg_ = false;
	this->started_flg_ = false;
	this->canvas_cont_.clear();
	this->canvas_2d_cont_.clear();
	this->canvas_3d_cont_.clear();
	this->light_cont_.clear();
	this->light_2d_cont_.clear();
	this->light_3d_cont_.clear();
	this->fog_cont_.clear();
	this->fog_2d_cont_.clear();
	this->fog_3d_cont_.clear();
	this->model_cont_.clear();
	this->model_2d_cont_.clear();
	this->model_3d_cont_.clear();
	this->draw_canvas_2d_cont_ = nullptr;
	this->draw_canvas_3d_cont_ = nullptr;

	this->name.clear();
	this->transform_2d.Init();
	this->transform_3d.Init();
	this->color = 1.0f;

	tml::scene::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Scene::Create(const tml::scene::SceneDesc &desc)
{
	this->Init();

	if (tml::scene::ManagerResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->input_mgr_ = desc.GetManager()->GetInputManager();
	this->graphic_mgr_ = desc.GetManager()->GetGraphicManager();
	this->sound_mgr_ = desc.GetManager()->GetSoundManager();
	this->type_ = static_cast<tml::ConstantUtil::SCENE::SCENE_TYPE>(this->GetResourceSubIndex());
	this->start_flg_ = true;

	this->name = desc.name;
	this->transform_2d = desc.transform_2d;
	this->transform_3d = desc.transform_3d;
	this->color = desc.color;

	this->SetRootNode();

	return (0);
}


/**
 * @brief Start関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Scene::Start(void)
{
	if ((!this->run_flg_) || (!this->start_flg_)) {
		return (-1);
	}

	if (!this->started_flg_) {
		if (this->OnStart() < 0) {
			this->OnEnd();

			return (-1);
		}

		this->started_flg_ = true;
	}

	if (this->root_node_ != nullptr) {
		this->root_node_->Start();
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Scene::OnStart(void)
{
	return (0);
}


/**
 * @brief End関数
 */
void tml::scene::Scene::End(void)
{
	if (!this->run_flg_) {
		return;
	}

	if (this->root_node_ != nullptr) {
		this->root_node_->End();
	}

	if (this->started_flg_) {
		this->OnEnd();

		this->started_flg_ = false;
	}

	return;
}


/**
 * @brief OnEnd関数
 */
void tml::scene::Scene::OnEnd(void)
{
	return;
}


/**
 * @brief Update関数
 */
void tml::scene::Scene::Update(void)
{
	if ((!this->run_flg_) || (!this->started_flg_)) {
		return;
	}

	this->OnUpdate();

	if (!this->canvas_cont_.empty()) {
		for (auto &canvas : this->canvas_cont_) {
			switch (canvas->GetDimensionType()) {
			case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D: {
				this->GetGraphicManager()->SetDrawCanvas(reinterpret_cast<tml::graphic::Canvas2D *>(canvas.get()));

				break;
			}
			case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D: {
				this->GetGraphicManager()->SetDrawCanvas(reinterpret_cast<tml::graphic::Canvas3D *>(canvas.get()));

				break;
			}
			}
		}

		this->draw_canvas_2d_cont_ = &this->canvas_2d_cont_;
		this->draw_canvas_3d_cont_ = &this->canvas_3d_cont_;
	}

	if (this->draw_canvas_2d_cont_ != nullptr) {
		for (auto draw_canvas_2d : (*this->draw_canvas_2d_cont_)) {
			for (auto light_2d : this->light_2d_cont_) {
				draw_canvas_2d->SetDrawLight(light_2d, this->transform_2d, this->color);
			}

			for (auto fog_2d : this->fog_2d_cont_) {
				draw_canvas_2d->SetDrawFog(fog_2d, this->transform_2d, this->color);
			}

			for (auto model_2d : this->model_2d_cont_) {
				draw_canvas_2d->SetDrawModel(model_2d, this->transform_2d, this->color);
			}
		}
	}

	if (this->draw_canvas_3d_cont_ != nullptr) {
		for (auto draw_canvas_3d : (*this->draw_canvas_3d_cont_)) {
			for (auto light_3d : this->light_3d_cont_) {
				draw_canvas_3d->SetDrawLight(light_3d, this->transform_3d, this->color);
			}

			for (auto fog_3d : this->fog_3d_cont_) {
				draw_canvas_3d->SetDrawFog(fog_3d, this->transform_3d, this->color);
			}

			for (auto model_3d : this->model_3d_cont_) {
				draw_canvas_3d->SetDrawModel(model_3d, this->transform_3d, this->color);
			}
		}
	}

	if (this->root_node_ != nullptr) {
		if (!this->root_node_->IsStarted()) {
			if (this->root_node_->GetStartFlag()) {
				this->root_node_->Start();
			}
		}

		if (this->root_node_->GetStartFlag()) {
			this->root_node_->SetDrawCanvas(this->draw_canvas_2d_cont_, this->draw_canvas_3d_cont_);

			this->root_node_->Update();

			this->root_node_->ClearDrawCanvas();
		}

		if (!this->root_node_->GetStartFlag()) {
			this->root_node_->End();
		}
	}

	return;
}


/**
 * @brief OnUpdate関数
 */
void tml::scene::Scene::OnUpdate(void)
{
	return;
}


/**
 * @brief SetRunFlag関数
 * @param run_flg (run_flag)
 */
void tml::scene::Scene::SetRunFlag(const bool run_flg)
{
	this->run_flg_ = run_flg;

	if (this->root_node_ != nullptr) {
		this->root_node_->SetRunFlag(run_flg);
	}

	return;
}


/**
 * @brief SetRootNode関数
 */
void tml::scene::Scene::SetRootNode(void)
{
	if (this->root_node_ != nullptr) {
		return;
	}

	tml::scene::NodeDesc node_desc;

	node_desc.SetManager(this->GetManager());

	this->GetManager()->GetResource<tml::scene::Node>(this->root_node_, node_desc);

	this->root_node_->name = L"root";

	return;
}


/**
 * @brief SetCanvas関数
 * @param index (index)
 * @param canvas (canvas)
 */
void tml::scene::Scene::SetCanvas(const UINT index, const tml::shared_ptr<tml::graphic::Canvas> &canvas)
{
	if (index >= this->canvas_cont_.size()) {
		this->canvas_cont_.resize(index + 1U);
	}

	auto &old_canvas = this->canvas_cont_[index];

	if (old_canvas != nullptr) {
		switch (old_canvas->GetDimensionType()) {
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D: {
			this->canvas_2d_cont_.remove(reinterpret_cast<tml::graphic::Canvas2D *>(old_canvas.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D: {
			this->canvas_3d_cont_.remove(reinterpret_cast<tml::graphic::Canvas3D *>(old_canvas.get()));

			break;
		}
		}
	}

	this->canvas_cont_[index] = canvas;

	if (canvas != nullptr) {
		switch (canvas->GetDimensionType()) {
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D: {
			this->canvas_2d_cont_.push_back(reinterpret_cast<tml::graphic::Canvas2D *>(canvas.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D: {
			this->canvas_3d_cont_.push_back(reinterpret_cast<tml::graphic::Canvas3D *>(canvas.get()));

			break;
		}
		}
	}

	return;
}


/**
 * @brief SetLight関数
 * @param index (index)
 * @param light (light)
 */
void tml::scene::Scene::SetLight(const UINT index, const tml::shared_ptr<tml::graphic::Light> &light)
{
	if (index >= this->light_cont_.size()) {
		this->light_cont_.resize(index + 1U);
	}

	auto &old_light = this->light_cont_[index];

	if (old_light != nullptr) {
		switch (old_light->GetDimensionType()) {
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D: {
			this->light_2d_cont_.remove(reinterpret_cast<tml::graphic::Light2D *>(old_light.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D: {
			this->light_3d_cont_.remove(reinterpret_cast<tml::graphic::Light3D *>(old_light.get()));

			break;
		}
		}
	}

	this->light_cont_[index] = light;

	if (light != nullptr) {
		switch (light->GetDimensionType()) {
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D: {
			this->light_2d_cont_.push_back(reinterpret_cast<tml::graphic::Light2D *>(light.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D: {
			this->light_3d_cont_.push_back(reinterpret_cast<tml::graphic::Light3D *>(light.get()));

			break;
		}
		}
	}

	return;
}


/**
 * @brief SetFog関数
 * @param index (index)
 * @param fog (fog)
 */
void tml::scene::Scene::SetFog(const UINT index, const tml::shared_ptr<tml::graphic::Fog> &fog)
{
	if (index >= this->fog_cont_.size()) {
		this->fog_cont_.resize(index + 1U);
	}

	auto &old_fog = this->fog_cont_[index];

	if (old_fog != nullptr) {
		switch (old_fog->GetDimensionType()) {
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D: {
			this->fog_2d_cont_.remove(reinterpret_cast<tml::graphic::Fog2D *>(old_fog.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D: {
			this->fog_3d_cont_.remove(reinterpret_cast<tml::graphic::Fog3D *>(old_fog.get()));

			break;
		}
		}
	}

	this->fog_cont_[index] = fog;

	if (fog != nullptr) {
		switch (fog->GetDimensionType()) {
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D: {
			this->fog_2d_cont_.push_back(reinterpret_cast<tml::graphic::Fog2D *>(fog.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D: {
			this->fog_3d_cont_.push_back(reinterpret_cast<tml::graphic::Fog3D *>(fog.get()));

			break;
		}
		}
	}

	return;
}


/**
 * @brief SetModel関数
 * @param index (index)
 * @param model (model)
 */
void tml::scene::Scene::SetModel(const UINT index, const tml::shared_ptr<tml::graphic::Model> &model)
{
	if (index >= this->model_cont_.size()) {
		this->model_cont_.resize(index + 1U);
	}

	auto &old_model = this->model_cont_[index];

	if (old_model != nullptr) {
		switch (old_model->GetDimensionType()) {
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D: {
			this->model_2d_cont_.remove(reinterpret_cast<tml::graphic::Model2D *>(old_model.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D: {
			this->model_3d_cont_.remove(reinterpret_cast<tml::graphic::Model3D *>(old_model.get()));

			break;
		}
		}
	}

	this->model_cont_[index] = model;

	if (model != nullptr) {
		switch (model->GetDimensionType()) {
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_2D: {
			this->model_2d_cont_.push_back(reinterpret_cast<tml::graphic::Model2D *>(model.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::DIMENSION_TYPE::_3D: {
			this->model_3d_cont_.push_back(reinterpret_cast<tml::graphic::Model3D *>(model.get()));

			break;
		}
		}
	}

	return;
}
