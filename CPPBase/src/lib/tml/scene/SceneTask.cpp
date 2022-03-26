/**
 * @file
 * @brief SceneTask�R�[�h�t�@�C��
 */


#include "SceneTask.h"
#include "Manager.h"
#include "Scene.h"


/**
 * @brief �R���X�g���N�^
 */
tml::scene::SceneTaskDesc::SceneTaskDesc() :
	run_type(tml::ConstantUtil::SCENE::SCENE_TASK_RUN_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::SceneTaskDesc::~SceneTaskDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::SceneTaskDesc::Init(void)
{
	this->Release();

	this->run_type = tml::ConstantUtil::SCENE::SCENE_TASK_RUN_TYPE::NONE;
	this->scene.reset();

	tml::scene::ManagerTaskDesc::Init();

	return;
}


/**
 * @brief ReadValue�֐�
 * @param conf_file (config_file)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::scene::SceneTaskDesc::ReadValue(const tml::INIFile &conf_file)
{
	if (tml::scene::ManagerTaskDesc::ReadValue(conf_file) < 0) {
		return (-1);
	}

	/*
	const std::map<std::wstring, std::wstring> *val_name_cont = nullptr;
	const std::wstring *val = nullptr;

	{// SceneTask Section Read
		val_name_cont = conf_file.data.GetValueNameContainer(L"SCENE_TASK");

		if (val_name_cont != nullptr) {
		}
	}
	*/

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::scene::SceneTask::SceneTask() :
	run_type_(tml::ConstantUtil::SCENE::SCENE_TASK_RUN_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::SceneTask::~SceneTask()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::SceneTask::Init(void)
{
	this->Release();

	this->run_type_ = tml::ConstantUtil::SCENE::SCENE_TASK_RUN_TYPE::NONE;
	this->scene_.reset();

	tml::scene::ManagerTask::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::scene::SceneTask::Create(const tml::scene::SceneTaskDesc &desc)
{
	this->Init();

	if (tml::scene::ManagerTask::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	this->run_type_ = desc.run_type;
	this->scene_ = desc.scene;

	return (0);
}


/**
 * @brief OnRun�֐�
 */
void tml::scene::SceneTask::OnRun(void)
{
	switch (this->run_type_) {
	case tml::ConstantUtil::SCENE::SCENE_TASK_RUN_TYPE::START_SCENE: {
		this->GetManager()->StartScene(this->scene_, false);

		break;
	}
	case tml::ConstantUtil::SCENE::SCENE_TASK_RUN_TYPE::END_SCENE: {
		this->GetManager()->EndScene(false);

		return;
	}
	}

	this->SetRunFlag(false);

	return;
}
