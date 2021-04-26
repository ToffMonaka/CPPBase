/**
 * @file
 * @brief InitScene�R�[�h�t�@�C��
 */


#include "InitScene.h"
#include "../../lib/tml/scene/Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::InitSceneDesc::InitSceneDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::InitSceneDesc::~InitSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::InitSceneDesc::Init(void)
{
	this->Release();

	tml::scene::SceneDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::InitSceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::SceneDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// InitScene Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"INIT_SCENE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::InitScene::InitScene()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::InitScene::~InitScene()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::InitScene::Release(void)
{
	if (this->GetManager() != nullptr) {
	}

	tml::scene::Scene::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::InitScene::Init(void)
{
	this->Release();

	tml::scene::Scene::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::InitScene::Create(const cpp_base::scene::InitSceneDesc &desc)
{
	this->Init();

	if (tml::scene::Scene::Create(desc, static_cast<tml::ConstantUtil::SCENE::SCENE_TYPE>(cpp_base::ConstantUtil::SCENE::SCENE_TYPE::INIT)) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Start�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::InitScene::Start(void)
{
	return (0);
}


/**
 * @brief End�֐�
 */
void cpp_base::scene::InitScene::End(void)
{
	return;
}


/**
 * @brief Update�֐�
 */
void cpp_base::scene::InitScene::Update(void)
{
	return;
}
