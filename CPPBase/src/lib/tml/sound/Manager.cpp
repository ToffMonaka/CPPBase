/**
 * @file
 * @brief Manager�R�[�h�t�@�C��
 */


#include "Manager.h"


/**
 * @brief �R���X�g���N�^
 */
tml::sound::ManagerDesc::ManagerDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::ManagerDesc::~ManagerDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::ManagerDesc::Init(void)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::sound::Manager::Manager()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::sound::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::sound::Manager::Release(void)
{
	for (auto &res_cont : this->res_cont_ary_) {
		for (auto &res : res_cont) {
			res->Init();
		}

		res_cont.clear();
	}

	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::Manager::Init(void)
{
	this->Release();

	this->common.Init();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::sound::Manager::Create(tml::sound::ManagerDesc &desc)
{
	this->Init();

	if (this->common.Create(this) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}


/**
 * @brief Update�֐�
 */
void tml::sound::Manager::Update(void)
{
	return;
}
