/**
 * @file
 * @brief Manager�R�[�h�t�@�C��
 */


#include "Manager.h"
#include "../memory/MemoryUtil.h"


/**
 * @brief �R���X�g���N�^
 */
tml::input::ManagerDesc::ManagerDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::ManagerDesc::~ManagerDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::ManagerDesc::Init(void)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::input::Manager::Manager()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::input::Manager::~Manager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::input::Manager::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::input::Manager::Init(void)
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
INT tml::input::Manager::Create(tml::input::ManagerDesc &desc)
{
	this->Init();

	return (0);
}
