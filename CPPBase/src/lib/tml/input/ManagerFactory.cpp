/**
 * @file
 * @brief ManagerFactory�R�[�h�t�@�C��
 */


#include "ManagerFactory.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::ManagerFactory::ManagerFactory() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::ManagerFactory::~ManagerFactory()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::ManagerFactory::Init(void)
{
	this->Release();

	this->mgr_ = nullptr;

	return;
}


/**
 * @brief Create�֐�
 * @param mgr (manager)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::input::ManagerFactory::Create(tml::input::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	return (0);
}
