/**
 * @file
 * @brief ManagerCommon�R�[�h�t�@�C��
 */


#include "ManagerCommon.h"
#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::ManagerCommon::ManagerCommon() :
	mgr_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::ManagerCommon::~ManagerCommon()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::input::ManagerCommon::Release(void)
{
	if (this->mgr_ != nullptr) {
	}

	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::ManagerCommon::Init(void)
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
INT tml::input::ManagerCommon::Create(tml::input::Manager *mgr)
{
	if (mgr == nullptr) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->mgr_ = mgr;

	return (0);
}
