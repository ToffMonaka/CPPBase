/**
 * @file
 * @brief SoundManager�R�[�h�t�@�C��
 */


#include "SoundManager.h"
#include "../memory/MemoryUtil.h"


/**
 * @brief �R���X�g���N�^
 */
tml::SoundManagerDesc::SoundManagerDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::SoundManagerDesc::~SoundManagerDesc()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::SoundManagerDesc::Init(void)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::SoundManager::SoundManager()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::SoundManager::~SoundManager()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::SoundManager::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::SoundManager::Init(void)
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
INT tml::SoundManager::Create(const tml::SoundManagerDesc &desc)
{
	this->Init();

	return (0);
}
