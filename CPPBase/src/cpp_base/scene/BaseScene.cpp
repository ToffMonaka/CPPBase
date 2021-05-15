/**
 * @file
 * @brief BaseSceneコードファイル
 */


#include "BaseScene.h"
#include "Manager.h"


/**
 * @brief コンストラクタ
 */
cpp_base::scene::BaseSceneDesc::BaseSceneDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::BaseSceneDesc::~BaseSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::BaseSceneDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::BaseSceneDesc::Init();

	return;
}


/**
 * @brief ReadValue関数
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::BaseSceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::BaseSceneDesc::ReadValue(ini_file) < 0) {
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
 * @brief SetManager関数
 * @param mgr (manager)
 */
void cpp_base::scene::BaseSceneDesc::SetManager(cpp_base::scene::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::scene::BaseSceneDesc::SetManager(mgr);

	return;
}


/**
 * @brief コンストラクタ
 */
cpp_base::scene::BaseScene::BaseScene() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief デストラクタ
 */
cpp_base::scene::BaseScene::~BaseScene()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void cpp_base::scene::BaseScene::Release(void)
{
	tml::scene::BaseScene::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::BaseScene::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::BaseScene::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::BaseScene::Create(const cpp_base::scene::BaseSceneDesc &desc)
{
	if (desc.GetManager() == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::scene::BaseScene::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->mgr_ = desc.GetManager();

	return (0);
}


/**
 * @brief Start関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::BaseScene::Start(void)
{
	return (0);
}


/**
 * @brief End関数
 */
void cpp_base::scene::BaseScene::End(void)
{
	return;
}


/**
 * @brief Update関数
 */
void cpp_base::scene::BaseScene::Update(void)
{
	return;
}
