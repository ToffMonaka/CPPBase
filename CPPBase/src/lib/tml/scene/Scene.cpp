/**
 * @file
 * @brief Scene�R�[�h�t�@�C��
 */


#include "Scene.h"
#include "Manager.h"
#include "BaseNode.h"


/**
 * @brief �R���X�g���N�^
 */
tml::scene::SceneDesc::SceneDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::SceneDesc::~SceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::SceneDesc::Init(void)
{
	this->Release();

	tml::scene::ManagerResourceDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
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
 * @brief �R���X�g���N�^
 */
tml::scene::Scene::Scene() :
	type_(tml::ConstantUtil::SCENE::SCENE_TYPE::NONE),
	start_flg_(false),
	started_flg_(false)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::Scene::~Scene()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::scene::Scene::Release(void)
{
	if (this->header_node_ != nullptr) {
		this->header_node_->End();

		this->header_node_.reset();
	}

	tml::scene::ManagerResource::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::Scene::Init(void)
{
	this->type_ = tml::ConstantUtil::SCENE::SCENE_TYPE::NONE;
	this->start_flg_ = false;
	this->started_flg_ = false;

	tml::scene::ManagerResource::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0����=���s
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
	this->start_flg_ = true;

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
 * @brief Start�֐�
 * @return res (result)<br>
 * 0����=���s,1=�J�n�ς�
 */
INT tml::scene::Scene::Start(void)
{
	if (this->started_flg_) {
		return (1);
	}

	if (this->OnStart() < 0) {
		return (-1);
	}

	this->started_flg_ = true;

	this->header_node_->Start();

	return (0);
}


/**
 * @brief End�֐�
 */
void tml::scene::Scene::End(void)
{
	if (!this->started_flg_) {
		return;
	}

	this->header_node_->End();

	this->OnEnd();

	this->started_flg_ = false;

	return;
}


/**
 * @brief Update�֐�
 */
void tml::scene::Scene::Update(void)
{
	if (!this->started_flg_) {
		return;
	}

	this->OnUpdate();

	if (!this->header_node_->IsStarted()) {
		if (this->header_node_->GetStartFlag()) {
			if (this->header_node_->Start() < 0) {
			} else {
			}
		}
	}

	if (this->header_node_->GetStartFlag()) {
		this->header_node_->Update();
	}

	if (!this->header_node_->GetStartFlag()) {
		this->header_node_->End();
	}

	return;
}
