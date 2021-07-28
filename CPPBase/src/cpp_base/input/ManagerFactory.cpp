/**
 * @file
 * @brief ManagerFactory�R�[�h�t�@�C��
 */


#include "ManagerFactory.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
cpp_base::input::ManagerFactory::ManagerFactory() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
cpp_base::input::ManagerFactory::~ManagerFactory()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void cpp_base::input::ManagerFactory::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create�֐�
 * @param mgr (manager)
 * @return result (result)<br>
 * 0����=���s
 */
INT cpp_base::input::ManagerFactory::Create(cpp_base::input::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	return (0);
}
