/**
 * @file
 * @brief BaseSceneコードファイル
 */


#include "BaseScene.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
tml::scene::BaseSceneDesc::BaseSceneDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::BaseSceneDesc::~BaseSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::BaseSceneDesc::Init(void)
{
	this->Release();

	tml::scene::SceneDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::BaseSceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::SceneDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// BaseScene Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"BASE_SCENE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::scene::BaseScene::BaseScene()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::scene::BaseScene::~BaseScene()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::scene::BaseScene::Release(void)
{
	tml::scene::Scene::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::scene::BaseScene::Init(void)
{
	this->Release();

	tml::scene::Scene::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::BaseScene::Create(const tml::scene::BaseSceneDesc &desc)
{
	this->Init();

	if (tml::scene::Scene::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::scene::BaseScene::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd関数
 */
void tml::scene::BaseScene::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void tml::scene::BaseScene::OnUpdate(void)
{
	return;
}
