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
	this->InitResourceCount();
	this->InitEventCount();

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

	this->InitResourceCount();
	this->InitEventCount();

	return;
}


/**
 * @brief InitResourceCount�֐�
 */
void cpp_base::sound::ManagerDesc::InitResourceCount(void)
{
	tml::sound::ManagerDesc::InitResourceCount();

	return;
}


/**
 * @brief InitEventCount�֐�
 */
void cpp_base::sound::ManagerDesc::InitEventCount(void)
{
	tml::sound::ManagerDesc::InitEventCount();

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
	this->DeleteCommon2();

	tml::sound::Manager::Release();

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
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::sound::Manager::Create(const cpp_base::sound::ManagerDesc &desc)
{
	this->Init();

	if (tml::sound::Manager::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	if (this->CreateCommon2() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief CreateCommon2�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT cpp_base::sound::Manager::CreateCommon2(void)
{
	if (this->common2.Create(this) < 0) {
		return (-1);
	}

	return (0);
}


/**
 * @brief DeleteCommon2�֐�
 */
void cpp_base::sound::Manager::DeleteCommon2(void)
{
	this->common2.Init();

	return;
}
