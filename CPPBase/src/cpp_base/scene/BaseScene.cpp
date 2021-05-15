/**
 * @file
 * @brief BaseScene�R�[�h�t�@�C��
 */


#include "BaseScene.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::BaseSceneDesc::BaseSceneDesc() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::BaseSceneDesc::~BaseSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::BaseSceneDesc::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::BaseSceneDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param ini_file (ini_file)
 * @return res (result)<br>
 * 0����=���s
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
 * @brief SetManager�֐�
 * @param mgr (manager)
 */
void cpp_base::scene::BaseSceneDesc::SetManager(cpp_base::scene::Manager *mgr)
{
	this->mgr_ = mgr;

	tml::scene::BaseSceneDesc::SetManager(mgr);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::BaseScene::BaseScene() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::BaseScene::~BaseScene()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::BaseScene::Release(void)
{
	tml::scene::BaseScene::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::BaseScene::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	tml::scene::BaseScene::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
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
 * @brief Start�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::BaseScene::Start(void)
{
	return (0);
}


/**
 * @brief End�֐�
 */
void cpp_base::scene::BaseScene::End(void)
{
	return;
}


/**
 * @brief Update�֐�
 */
void cpp_base::scene::BaseScene::Update(void)
{
	return;
}
