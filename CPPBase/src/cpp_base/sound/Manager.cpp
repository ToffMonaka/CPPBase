/**
 * @file
 * @brief Manager�R�[�h�t�@�C��
 */


#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::sound::ManagerDesc::ManagerDesc()
{
	this->resource_count = cpp_base::ConstantUtil::SOUND::RESOURCE_TYPE_COUNT;
	this->task_count = cpp_base::ConstantUtil::SOUND::TASK_TYPE_COUNT;
	this->event_count = cpp_base::ConstantUtil::SOUND::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::sound::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::sound::ManagerDesc::Init(void)
{
	this->Release();

	tml::sound::ManagerDesc::Init();

	this->resource_count = cpp_base::ConstantUtil::SOUND::RESOURCE_TYPE_COUNT;
	this->task_count = cpp_base::ConstantUtil::SOUND::TASK_TYPE_COUNT;
	this->event_count = cpp_base::ConstantUtil::SOUND::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::sound::Manager::Manager()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::sound::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::sound::Manager::Release(void)
{
	this->common2.Init();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::sound::Manager::Init(void)
{
	this->Release();

	tml::sound::Manager::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::sound::Manager::Create(const cpp_base::sound::ManagerDesc &desc)
{
	this->Init();

	if (tml::sound::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// ResourceFactory Set
	}

	{// EventFactory Set
	}

	if (this->common2.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
