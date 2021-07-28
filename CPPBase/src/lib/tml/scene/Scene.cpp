/**
 * @file
 * @brief Sceneコードファイル
 */


#include "Scene.h"
#include "Manager.h"
#include "BaseNode.h"


/**
 * @brief コンストラクタ
 */
tml::scene::SceneDesc::SceneDesc()
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

	tml::scene::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::SceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Scene Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SCENE");

		if (val_name_cont != nullptr) {
			val = ini_file.data.GetValue((*val_name_cont), L"NAME");

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
	type_(tml::ConstantUtil::SCENE::SCENE_TYPE::NONE),
	run_flg_(false),
	start_flg_(false),
	started_flg_(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::Scene::~Scene()
{
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

	tml::scene::ManagerResource::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::Scene::Init(void)
{
	this->name_.clear();
	this->type_ = tml::ConstantUtil::SCENE::SCENE_TYPE::NONE;
	this->run_flg_ = false;
	this->start_flg_ = false;
	this->started_flg_ = false;

	tml::scene::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param type (type)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Scene::Create(const tml::scene::SceneDesc &desc, const tml::ConstantUtil::SCENE::SCENE_TYPE type)
{
	if (type == tml::ConstantUtil::SCENE::SCENE_TYPE::NONE) {
		return (-1);
	}

	if (tml::scene::ManagerResource::Create(desc, tml::ConstantUtil::SCENE::RESOURCE_TYPE::SCENE, static_cast<UINT>(type)) < 0) {
		return (-1);
	}

	this->name_ = desc.name;
	this->type_ = type;
	this->start_flg_ = true;

	this->SetRootNode();

	if (this->root_node_ == nullptr) {
		return (-1);
	}

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
 * @brief Update関数
 */
void tml::scene::Scene::Update(void)
{
	if ((!this->run_flg_) || (!this->started_flg_)) {
		return;
	}

	this->OnUpdate();

	if (this->root_node_ != nullptr) {
		if (!this->root_node_->IsStarted()) {
			if (this->root_node_->GetStartFlag()) {
				this->root_node_->Start();
			}
		}

		if (this->root_node_->GetStartFlag()) {
			this->root_node_->Update();
		}

		if (!this->root_node_->GetStartFlag()) {
			this->root_node_->End();
		}
	}

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
		this->root_node_->End();
		this->root_node_->SetRunFlag(false);

		this->root_node_.reset();
	}

	tml::scene::BaseNodeDesc desc;

	desc.SetManager(this->GetManager());
	desc.name = L"root";

	this->GetManager()->GetResource<tml::scene::BaseNode>(this->root_node_, desc);

	return;
}
