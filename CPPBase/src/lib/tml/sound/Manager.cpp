/**
 * @file
 * @brief Manager�R�[�h�t�@�C��
 */


#include "Manager.h"
#include "../memory/MemoryUtil.h"


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
	return;
}


/**
 * @brief Init�֐�
 */
void tml::sound::Manager::Init(void)
{
	this->Release();

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

	return (0);
}
