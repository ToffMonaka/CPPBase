/**
 * @file
 * @brief InitSceneコードファイル
 */


#include "InitScene.h"
#include "../../lib/tml/scene/Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::InitSceneDesc::InitSceneDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::InitSceneDesc::~InitSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::InitSceneDesc::Init(void)
{
	this->Release();

	tml::scene::SceneDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
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
 * @brief コンストラクタ
 */
cpp_base::scene::InitScene::InitScene()
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::InitScene::~InitScene()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::InitScene::Release(void)
{
	if (this->GetManager() != nullptr) {
	}

	tml::scene::Scene::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::InitScene::Init(void)
{
	this->Release();

	tml::scene::Scene::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
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
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::InitScene::Start(void)
{
	return (0);
}


/**
 * @brief End関数
 */
void cpp_base::scene::InitScene::End(void)
{
	return;
}


/**
 * @brief Update関数
 */
void cpp_base::scene::InitScene::Update(void)
{
	return;
}
