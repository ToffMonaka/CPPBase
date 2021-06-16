/**
 * @file
 * @brief InitSceneコードファイル
 */


#include "InitScene.h"
#include "Manager.h"
#include "InitSceneNode.h"


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

	cpp_base::scene::BaseSceneDesc::Init();

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
	if (cpp_base::scene::BaseSceneDesc::ReadValue(ini_file) < 0) {
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
	cpp_base::scene::BaseScene::Release();

	return;
}


/**
 * @brief Init関数
 */
void cpp_base::scene::InitScene::Init(void)
{
	this->Release();

	cpp_base::scene::BaseScene::Init();

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

	if (cpp_base::scene::BaseScene::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// InitSceneNode Add
		tml::shared_ptr<tml::scene::Node> node;

		if (this->GetManager()->node_factory.Get(node, L"InitSceneNode", tml::INIFileReadDesc()) == nullptr) {
			this->Init();

			return (-1);
		}

		if (this->GetRootNode()->AddChildNode(node, false) < 0) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnStart関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT cpp_base::scene::InitScene::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd関数
 */
void cpp_base::scene::InitScene::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate関数
 */
void cpp_base::scene::InitScene::OnUpdate(void)
{
	return;
}
