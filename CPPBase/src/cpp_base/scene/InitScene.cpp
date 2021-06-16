/**
 * @file
 * @brief InitScene�R�[�h�t�@�C��
 */


#include "InitScene.h"
#include "Manager.h"
#include "InitSceneNode.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::scene::InitSceneDesc::InitSceneDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::InitSceneDesc::~InitSceneDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::InitSceneDesc::Init(void)
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
 * @brief �R���X�g���N�^
 */
cpp_base::scene::InitScene::InitScene()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::scene::InitScene::~InitScene()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::scene::InitScene::Release(void)
{
	cpp_base::scene::BaseScene::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::scene::InitScene::Init(void)
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
 * @brief OnStart�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::scene::InitScene::OnStart(void)
{
	return (0);
}


/**
 * @brief OnEnd�֐�
 */
void cpp_base::scene::InitScene::OnEnd(void)
{
	return;
}


/**
 * @brief OnUpdate�֐�
 */
void cpp_base::scene::InitScene::OnUpdate(void)
{
	return;
}
