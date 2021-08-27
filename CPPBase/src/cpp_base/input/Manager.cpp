/**
 * @file
 * @brief Manager�R�[�h�t�@�C��
 */


#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::input::ManagerDesc::ManagerDesc()

{
	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::input::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::input::ManagerDesc::Init(void)
{
	this->Release();

	tml::input::ManagerDesc::Init();

	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount�֐�
 */
void cpp_base::input::ManagerDesc::InitResourceCount(void)
{
	tml::input::ManagerDesc::InitResourceCount();

	this->resource_count_container.resize(cpp_base::ConstantUtil::INPUT::RESOURCE_TYPE_COUNT);

	return;
}


/**
 * @brief InitEventCount�֐�
 */
void cpp_base::input::ManagerDesc::InitEventCount(void)
{
	tml::input::ManagerDesc::InitEventCount();

	this->event_count_container.resize(cpp_base::ConstantUtil::INPUT::EVENT_TYPE_COUNT);

	return;
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::input::Manager::Manager()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::input::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void cpp_base::input::Manager::Release(void)
{
	this->common2.Init();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::input::Manager::Init(void)
{
	this->Release();

	tml::input::Manager::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::input::Manager::Create(const cpp_base::input::ManagerDesc &desc)
{
	this->Init();

	if (tml::input::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	{// ResourceFactory Set
	}

	if (this->common2.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
