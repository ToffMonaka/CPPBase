/**
 * @file
 * @brief ManagerFactory�R�[�h�t�@�C��
 */


#include "ManagerFactory.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::ManagerFactoryDesc::ManagerFactoryDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::ManagerFactoryDesc::~ManagerFactoryDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::ManagerFactoryDesc::Init(void)
{
	this->Release();

	tml::ManagerFactoryDesc::Init();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
cpp_base::ManagerFactory::ManagerFactory()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::ManagerFactory::~ManagerFactory()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::ManagerFactory::Init(void)
{
	this->Release();

	tml::ManagerFactory::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::ManagerFactory::Create(const cpp_base::ManagerFactoryDesc &desc)
{
	this->Init();

	if (tml::ManagerFactory::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
