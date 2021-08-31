/**
 * @file
 * @brief Sceneコードファイル
 */


#include "Scene.h"
#include "../input/Manager.h"
#include "../graphic/Manager.h"
#include "../sound/Manager.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::SceneDesc::SceneDesc() :
	mgr_(nullptr)
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

	this->mgr_ = nullptr;

	tml::scene::SceneDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::SceneDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::scene::SceneDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// Scene Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"SCENE");

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
	this->mgr_ = mgr;

	tml::scene::SceneDesc::SetManager(mgr);

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::Scene::Scene() :
	mgr_(nullptr),
	input_mgr_(nullptr),
	graphic_mgr_(nullptr),
	sound_mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::Scene::~Scene()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::Scene::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::Scene::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;
	this->input_mgr_ = nullptr;
	this->graphic_mgr_ = nullptr;
	this->sound_mgr_ = nullptr;

	tml::scene::Scene::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Scene::Create(const cpp_base::scene::SceneDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::scene::Scene::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->mgr_ = desc.GetManager();
	this->input_mgr_ = desc.GetManager()->GetInputManager();
	this->graphic_mgr_ = desc.GetManager()->GetGraphicManager();
	this->sound_mgr_ = desc.GetManager()->GetSoundManager();

	return (0);
}


/**
 * @brief OnStart関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::Scene::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::Scene::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::Scene::OnUpdate(void)
{
	return;
}
