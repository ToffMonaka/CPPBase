/**
 * @file
 * @brief Sceneコードファイル
 */


#include "Scene.h"
#include "Manager.h"


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
	type_(tml::ConstantUtil::SCENE::SCENE_TYPE::NONE)
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

	return (0);
}
