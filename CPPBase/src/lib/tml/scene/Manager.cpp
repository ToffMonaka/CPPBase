/**
 * @file
 * @brief Manager�R�[�h�t�@�C��
 */


#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::scene::ManagerDesc::ManagerDesc()
{
	this->resource_count_container.clear();
	this->resource_count_container.resize(tml::ConstantUtil::SCENE::RESOURCE_TYPE_COUNT);
	this->event_count = tml::ConstantUtil::SCENE::EVENT_TYPE_COUNT;

	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::ManagerDesc::~ManagerDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::ManagerDesc::Init(void)
{
	this->Release();

	this->resource_count_container.clear();
	this->resource_count_container.resize(tml::ConstantUtil::SCENE::RESOURCE_TYPE_COUNT);
	this->event_count = tml::ConstantUtil::SCENE::EVENT_TYPE_COUNT;

	tml::ManagerDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::scene::Manager::Manager()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::scene::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::scene::Manager::Release(void)
{
	this->common_.Init();
	this->DeleteResourceContainer();

	tml::Manager::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::scene::Manager::Init(void)
{
	this->Release();

	tml::Manager::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::scene::Manager::Create(const tml::scene::ManagerDesc &desc)
{
	this->Init();

	if (tml::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (this->common_.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Update�֐�
 */
void tml::scene::Manager::Update(void)
{
	tml::Manager::Update();

	return;
}
