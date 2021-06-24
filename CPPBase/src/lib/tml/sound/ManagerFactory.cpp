/**
 * @file
 * @brief ManagerFactory�R�[�h�t�@�C��
 */


#include "ManagerFactory.h"
#include "Manager.h"
#include "Sound.h"
#include "BGMSound.h"
#include "SESound.h"


/**
 * @brief �R���X�g���N�^
 */
tml::sound::ManagerFactory::ManagerFactory() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::ManagerFactory::~ManagerFactory()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::ManagerFactory::Init(void)
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
INT tml::sound::ManagerFactory::Create(tml::sound::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	return (0);
}
