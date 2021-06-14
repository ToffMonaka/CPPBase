/**
 * @file
 * @brief TitleScene�R�[�h�t�@�C��
 */


#include "TitleScene.h"
#include "Manager.h"
#include "TitleSceneNode.h"


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

	cpp_base::scene::BaseSceneDesc::Init();

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
	if (cpp_base::scene::BaseSceneDesc::ReadValue(ini_file) < 0) {
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
 * @brief Release�֐�
 */
void cpp_base::scene::TitleScene::Release(void)
{
	cpp_base::scene::BaseScene::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::TitleScene::Init(void)
{
	this->Release();

	cpp_base::scene::BaseScene::Init();

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

	if (cpp_base::scene::BaseScene::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// TitleSceneNode Add
		tml::shared_ptr<tml::scene::Node> node;

		if (this->GetManager()->node_factory.Get(node, L"TitleSceneNode", tml::INIFileReadDesc()) == nullptr) {
			this->Init();

			return (-1);
		}

		if (this->GetRootrNode()->AddChildNode(node, false) < 0) {
			this->Init();

			return (-1);
		}
	}

	return (0);
}


/**
 * @brief OnStart�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::TitleScene::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd�֐�
 */
void cpp_base::scene::TitleScene::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate�֐�
 */
void cpp_base::scene::TitleScene::OnUpdate(void)
{
	return;
}
