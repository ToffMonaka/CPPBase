/**
 * @file
 * @brief TitleScene�R�[�h�t�@�C��
 */


#include "TitleScene.h"
#include "../../lib/tml/scene/Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::TitleSceneDesc::TitleSceneDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::TitleSceneDesc::~TitleSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::TitleSceneDesc::Init(void)
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
INT cpp_base::scene::TitleSceneDesc::ReadValue(const tml::INIFile &ini_file)
{
	if (tml::scene::SceneDesc::ReadValue(ini_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// TitleScene Section Read
		val_name_cont = ini_file.data.GetValueNameContainer(L"TITLE_SCENE");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::TitleScene::TitleScene()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::TitleScene::~TitleScene()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::TitleScene::Init(void)
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
INT cpp_base::scene::TitleScene::Create(const cpp_base::scene::TitleSceneDesc &desc)
{
	this->Init();

	if (tml::scene::Scene::Create(desc, static_cast<tml::ConstantUtil::SCENE::SCENE_TYPE>(cpp_base::ConstantUtil::SCENE::SCENE_TYPE::TITLE)) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
