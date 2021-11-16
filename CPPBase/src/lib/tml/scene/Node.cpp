/**
 * @file
 * @brief Nodeコードファイル
 */


#include "Node.h"
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
#include "NodeEvent.h"


/**
 * @brief コンストラクタ
 */
tml::scene::NodeDesc::NodeDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::NodeDesc::~NodeDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::NodeDesc::Init(void)
{
	this->Release();

	this->name.clear();
	this->transform_2d.Init();
	this->transform_3d.Init();

	tml::scene::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::NodeDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::scene::ManagerResourceDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Node Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"NODE");

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
tml::scene::Node::Node() :
	input_mgr_(nullptr),
	graphic_mgr_(nullptr),
	sound_mgr_(nullptr),
	type_(tml::ConstantUtil::SCENE::NODE_TYPE::NONE),
	run_flg_(false),
	start_flg_(false),
	started_flg_(false),
	parent_node_(nullptr),
	draw_canvas_2d_cont_(nullptr),
	draw_canvas_3d_cont_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::Node::~Node()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::scene::Node::Release(void)
{
	for (auto &child_node : this->child_node_cont_) {
		child_node->End();
		child_node->SetRunFlag(false);
		child_node->SetParentNode(nullptr);
	}

	this->child_node_cont_.clear();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::Node::Init(void)
{
	this->Release();

	this->input_mgr_ = nullptr;
	this->graphic_mgr_ = nullptr;
	this->sound_mgr_ = nullptr;
	this->name_.clear();
	this->type_ = tml::ConstantUtil::SCENE::NODE_TYPE::NONE;
	this->run_flg_ = false;
	this->start_flg_ = false;
	this->started_flg_ = false;
	this->parent_node_ = nullptr;
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

	this->transform_2d.Init();
	this->transform_3d.Init();

	tml::scene::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Node::Create(const tml::scene::NodeDesc &desc)
{
	this->Init();

	if (tml::scene::ManagerResource::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->input_mgr_ = desc.GetManager()->GetInputManager();
	this->graphic_mgr_ = desc.GetManager()->GetGraphicManager();
	this->sound_mgr_ = desc.GetManager()->GetSoundManager();
	this->name_ = desc.name;
	this->type_ = static_cast<tml::ConstantUtil::SCENE::NODE_TYPE>(this->GetResourceSubIndex());
	this->start_flg_ = true;

	this->transform_2d = desc.transform_2d;
	this->transform_3d = desc.transform_3d;

	return (0);
}


/**
 * @brief Start関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Node::Start(void)
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

	for (auto &child_node : this->child_node_cont_) {
		child_node->Start();
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Node::OnStart(void)
{
	return (0);
}


/**
 * @brief End関数
 */
void tml::scene::Node::End(void)
{
	if (!this->run_flg_) {
		return;
	}

	for (auto &child_node : this->child_node_cont_) {
		child_node->End();
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
void tml::scene::Node::OnEnd(void)
{
	return;
}


/**
 * @brief Update関数
 */
void tml::scene::Node::Update(void)
{
	if ((!this->run_flg_) || (!this->started_flg_)) {
		return;
	}

	this->OnUpdate();

	if (!this->canvas_cont_.empty()) {
		for (auto &canvas : this->canvas_cont_) {
			switch (canvas->GetType()) {
			case tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::_2D: {
				this->GetGraphicManager()->SetDrawCanvas(reinterpret_cast<tml::graphic::Canvas2D *>(canvas.get()));

				break;
			}
			case tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::_3D: {
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
				draw_canvas_2d->SetDrawLight(light_2d, this->transform_2d);
			}

			for (auto fog_2d : this->fog_2d_cont_) {
				draw_canvas_2d->SetDrawFog(fog_2d, this->transform_2d);
			}

			for (auto model_2d : this->model_2d_cont_) {
				draw_canvas_2d->SetDrawModel(model_2d, this->transform_2d);
			}
		}
	}

	if (this->draw_canvas_3d_cont_ != nullptr) {
		for (auto draw_canvas_3d : (*this->draw_canvas_3d_cont_)) {
			for (auto light_3d : this->light_3d_cont_) {
				draw_canvas_3d->SetDrawLight(light_3d, this->transform_3d);
			}

			for (auto fog_3d : this->fog_3d_cont_) {
				draw_canvas_3d->SetDrawFog(fog_3d, this->transform_3d);
			}

			for (auto model_3d : this->model_3d_cont_) {
				draw_canvas_3d->SetDrawModel(model_3d, this->transform_3d);
			}
		}
	}

	for (auto &child_node : this->child_node_cont_) {
		if (!child_node->IsStarted()) {
			if (child_node->GetStartFlag()) {
				child_node->Start();
			}
		}

		if (child_node->GetStartFlag()) {
			child_node->SetDrawCanvas(this->draw_canvas_2d_cont_, this->draw_canvas_3d_cont_);

			child_node->Update();

			child_node->ClearDrawCanvas();
		}

		if (!child_node->GetStartFlag()) {
			child_node->End();
		}
	}

	return;
}


/**
 * @brief OnUpdate関数
 */
void tml::scene::Node::OnUpdate(void)
{
	return;
}


/**
 * @brief SetRunFlag関数
 * @param run_flg (run_flag)
 */
void tml::scene::Node::SetRunFlag(const bool run_flg)
{
	this->run_flg_ = run_flg;

	for (auto &child_node : this->child_node_cont_) {
		child_node->SetRunFlag(run_flg);
	}

	return;
}


/**
 * @brief SetParentNode関数
 * @param parent_node (parent_node)
 */
void tml::scene::Node::SetParentNode(tml::scene::Node *parent_node)
{
	if (parent_node == this) {
		return;
	}

	this->parent_node_ = parent_node;

	return;
}


/**
 * @brief GetChildNodeRecursivePart関数
 * @param child_node_cont (child_node_container)
 * @param child_node_name (child_node_name)
 * @return child_node (child_node)
 */
const tml::shared_ptr<tml::scene::Node> &tml::scene::Node::GetChildNodeRecursivePart(const std::list<tml::shared_ptr<tml::scene::Node>> &child_node_cont, const WCHAR *child_node_name)
{
	for (auto &child_node : child_node_cont) {
		if (child_node->GetName() == child_node_name) {
			return (child_node);
		}

		auto &child_child_node = this->GetChildNodeRecursivePart(child_node->GetChildNodeContainer(), child_node_name);

		if (child_child_node != nullptr) {
			return (child_child_node);
		}
	}

	return (this->empty_child_node_);
}


/**
 * @brief AddChildNode関数
 * @param child_node (child_node)
 * @param event_flg (event_flag)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Node::AddChildNode(const tml::shared_ptr<tml::scene::Node> &child_node, const bool event_flg)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return (-1);
	}

	if (event_flg) {
		tml::scene::NodeEventDesc event_desc;

		event_desc.SetManager(this->GetManager());
		event_desc.data.type = tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::ADD;
		event_desc.data.parent_node = std::reinterpret_pointer_cast<tml::scene::Node>(this->GetResourceSharedPointer());
		event_desc.data.child_node = child_node;

		if (this->GetManager()->AddEvent<tml::scene::NodeEvent>(event_desc) < 0) {
			return (-1);
		}
	} else {
		if (child_node->GetParentNode() != nullptr) {
			return (-1);
		}

		auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

		if (child_node_itr != this->child_node_cont_.end()) {
			return (-1);
		}

		child_node->End();
		child_node->SetRunFlag(this->run_flg_);
		child_node->SetParentNode(this);

		this->child_node_cont_.push_back(child_node);
	}

	return (0);
}


/**
 * @brief RemoveChildNode関数
 * @param event_flg (event_flag)
 */
void tml::scene::Node::RemoveChildNode(const bool event_flg)
{
	if (event_flg) {
		tml::scene::NodeEventDesc event_desc;

		event_desc.SetManager(this->GetManager());
		event_desc.data.type = tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::REMOVE;
		event_desc.data.parent_node = std::reinterpret_pointer_cast<tml::scene::Node>(this->GetResourceSharedPointer());

		if (this->GetManager()->AddEvent<tml::scene::NodeEvent>(event_desc) < 0) {
			return;
		}
	} else {
		std::list<tml::shared_ptr<tml::scene::Node>> child_node_cont = this->child_node_cont_;

		for (auto &child_node : child_node_cont) {
			this->RemoveChildNode(child_node, false);
		}
	}

	return;
}


/**
 * @brief RemoveChildNode関数
 * @param child_node (child_node)
 * @param event_flg (event_flag)
 */
void tml::scene::Node::RemoveChildNode(const tml::shared_ptr<tml::scene::Node> &child_node, const bool event_flg)
{
	if ((child_node == nullptr)
	|| (child_node.get() == this)) {
		return;
	}

	if (event_flg) {
		tml::scene::NodeEventDesc event_desc;

		event_desc.SetManager(this->GetManager());
		event_desc.data.type = tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::REMOVE;
		event_desc.data.parent_node = std::reinterpret_pointer_cast<tml::scene::Node>(this->GetResourceSharedPointer());
		event_desc.data.child_node = child_node;

		if (this->GetManager()->AddEvent<tml::scene::NodeEvent>(event_desc) < 0) {
			return;
		}
	} else {
		if (child_node->GetParentNode() == nullptr) {
			return;
		}

		auto child_node_itr = std::find(this->child_node_cont_.begin(), this->child_node_cont_.end(), child_node);

		if (child_node_itr == this->child_node_cont_.end()) {
			return;
		}

		child_node->End();
		child_node->SetRunFlag(false);
		child_node->SetParentNode(nullptr);

		this->child_node_cont_.erase(child_node_itr);
	}

	return;
}


/**
 * @brief RemoveChildNodeFromParentNode関数
 * @param event_flg (event_flag)
 */
void tml::scene::Node::RemoveChildNodeFromParentNode(const bool event_flg)
{
	if (event_flg) {
		tml::scene::NodeEventDesc event_desc;

		event_desc.SetManager(this->GetManager());
		event_desc.data.type = tml::ConstantUtil::SCENE::NODE_EVENT_DATA_TYPE::REMOVE;
		event_desc.data.child_node = std::reinterpret_pointer_cast<tml::scene::Node>(this->GetResourceSharedPointer());

		if (this->GetManager()->AddEvent<tml::scene::NodeEvent>(event_desc) < 0) {
			return;
		}
	} else {
		if (this->parent_node_ == nullptr) {
			return;
		}

		tml::shared_ptr<tml::scene::Node> tmp_child_node;

		for (auto &child_node : this->parent_node_->child_node_cont_) {
			if (child_node.get() == this) {
				tmp_child_node = child_node;

				break;
			}
		}

		if (tmp_child_node == nullptr) {
			return;
		}

		this->parent_node_->RemoveChildNode(tmp_child_node, false);
	}

	return;
}


/**
 * @brief SetCanvas関数
 * @param index (index)
 * @param canvas (canvas)
 */
void tml::scene::Node::SetCanvas(const UINT index, const tml::shared_ptr<tml::graphic::Canvas> &canvas)
{
	if (index >= this->canvas_cont_.size()) {
		this->canvas_cont_.resize(index + 1U);
	}

	auto &old_canvas = this->canvas_cont_[index];

	if (old_canvas != nullptr) {
		switch (old_canvas->GetType()) {
		case tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::_2D: {
			this->canvas_2d_cont_.remove(reinterpret_cast<tml::graphic::Canvas2D *>(old_canvas.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::_3D: {
			this->canvas_3d_cont_.remove(reinterpret_cast<tml::graphic::Canvas3D *>(old_canvas.get()));

			break;
		}
		}
	}

	this->canvas_cont_[index] = canvas;

	if (canvas != nullptr) {
		switch (canvas->GetType()) {
		case tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::_2D: {
			this->canvas_2d_cont_.push_back(reinterpret_cast<tml::graphic::Canvas2D *>(canvas.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::CANVAS_TYPE::_3D: {
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
void tml::scene::Node::SetLight(const UINT index, const tml::shared_ptr<tml::graphic::Light> &light)
{
	if (index >= this->light_cont_.size()) {
		this->light_cont_.resize(index + 1U);
	}

	auto &old_light = this->light_cont_[index];

	if (old_light != nullptr) {
		switch (old_light->GetType()) {
		case tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::_2D: {
			this->light_2d_cont_.remove(reinterpret_cast<tml::graphic::Light2D *>(old_light.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::_3D: {
			this->light_3d_cont_.remove(reinterpret_cast<tml::graphic::Light3D *>(old_light.get()));

			break;
		}
		}
	}

	this->light_cont_[index] = light;

	if (light != nullptr) {
		switch (light->GetType()) {
		case tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::_2D: {
			this->light_2d_cont_.push_back(reinterpret_cast<tml::graphic::Light2D *>(light.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::LIGHT_TYPE::_3D: {
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
void tml::scene::Node::SetFog(const UINT index, const tml::shared_ptr<tml::graphic::Fog> &fog)
{
	if (index >= this->fog_cont_.size()) {
		this->fog_cont_.resize(index + 1U);
	}

	auto &old_fog = this->fog_cont_[index];

	if (old_fog != nullptr) {
		switch (old_fog->GetType()) {
		case tml::ConstantUtil::GRAPHIC::FOG_TYPE::_2D: {
			this->fog_2d_cont_.remove(reinterpret_cast<tml::graphic::Fog2D *>(old_fog.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::FOG_TYPE::_3D: {
			this->fog_3d_cont_.remove(reinterpret_cast<tml::graphic::Fog3D *>(old_fog.get()));

			break;
		}
		}
	}

	this->fog_cont_[index] = fog;

	if (fog != nullptr) {
		switch (fog->GetType()) {
		case tml::ConstantUtil::GRAPHIC::FOG_TYPE::_2D: {
			this->fog_2d_cont_.push_back(reinterpret_cast<tml::graphic::Fog2D *>(fog.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::FOG_TYPE::_3D: {
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
void tml::scene::Node::SetModel(const UINT index, const tml::shared_ptr<tml::graphic::Model> &model)
{
	if (index >= this->model_cont_.size()) {
		this->model_cont_.resize(index + 1U);
	}

	auto &old_model = this->model_cont_[index];

	if (old_model != nullptr) {
		switch (old_model->GetType()) {
		case tml::ConstantUtil::GRAPHIC::MODEL_TYPE::_2D: {
			this->model_2d_cont_.remove(reinterpret_cast<tml::graphic::Model2D *>(old_model.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::MODEL_TYPE::_3D: {
			this->model_3d_cont_.remove(reinterpret_cast<tml::graphic::Model3D *>(old_model.get()));

			break;
		}
		}
	}

	this->model_cont_[index] = model;

	if (model != nullptr) {
		switch (model->GetType()) {
		case tml::ConstantUtil::GRAPHIC::MODEL_TYPE::_2D: {
			this->model_2d_cont_.push_back(reinterpret_cast<tml::graphic::Model2D *>(model.get()));

			break;
		}
		case tml::ConstantUtil::GRAPHIC::MODEL_TYPE::_3D: {
			this->model_3d_cont_.push_back(reinterpret_cast<tml::graphic::Model3D *>(model.get()));

			break;
		}
		}
	}

	return;
}
