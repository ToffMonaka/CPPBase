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

	tml::scene::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::SceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::ManagerResourceDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Scene Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"SCENE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::scene::Scene::Scene() :
	type_(tml::ConstantUtil::SCENE::SCENE_TYPE::NONE),
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
 * @brief Init関数
 */
void tml::scene::Scene::Init(void)
{
	this->type_ = tml::ConstantUtil::SCENE::SCENE_TYPE::NONE;
	this->header_node_.reset();
	this->started_flg_ = false;

	tml::scene::ManagerResource::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
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

	this->type_ = type;

	{// HeaderNode Create
		tml::scene::BaseNodeDesc desc;

		desc.SetManager(this->GetManager());

		if (this->GetManager()->GetResource<tml::scene::BaseNode>(this->header_node_, desc) == nullptr) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::scene::Scene::Start(void)
{
	if (this->started_flg_) {
		return (0);
	}

	if (this->OnStart() < 0) {
		return (-1);
	}

	if (this->header_node_->Start() < 0) {
		return (-1);
	}

	this->started_flg_ = true;

	return (0);
}


/**
 * @brief End関数
 */
void tml::scene::Scene::End(void)
{
	if (!this->started_flg_) {
		return;
	}

	this->OnEnd();

	this->header_node_->End();

	this->started_flg_ = false;

	return;
}


/**
 * @brief Update関数
 */
void tml::scene::Scene::Update(void)
{
	if (!this->started_flg_) {
		return;
	}

	this->OnUpdate();

	this->header_node_->Update();

	return;
}
