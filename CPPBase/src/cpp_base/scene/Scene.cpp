/**
 * @file
 * @brief Sceneコードファイル
 */


#include "Scene.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::SceneDesc::SceneDesc() :
	manager2(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::SceneDesc::~SceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::SceneDesc::Init(void)
{
	this->Release();

	this->manager2 = nullptr;

	tml::scene::SceneDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::SceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::SceneDesc::ReadValue(ini_file) < 0) {
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
 * @brief SetManager関数
 * @param mgr (manager)
 */
void cpp_base::scene::SceneDesc::SetManager(cpp_base::scene::Manager *mgr)
{
	this->manager = mgr;
	this->manager2 = mgr;

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Scene::Scene() :
	mgr2_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Scene::~Scene()
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Scene::Init(void)
{
	this->mgr2_ = nullptr;

	tml::scene::Scene::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @param type (type)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Scene::Create(const cpp_base::scene::SceneDesc &desc, const cpp_base::ConstantUtil::SCENE::SCENE_TYPE type)
{
	if (desc.manager2 != desc.manager) {
		return (-1);
	}

	if (tml::scene::Scene::Create(desc, static_cast<tml::ConstantUtil::SCENE::SCENE_TYPE>(type)) < 0) {
		return (-1);
	}

	this->mgr2_ = desc.manager2;

	return (0);
}
