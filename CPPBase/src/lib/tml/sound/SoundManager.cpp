/**
 * @file
 * @brief SoundManager�R�[�h�t�@�C��
 */


#include "SoundManager.h"


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
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::SoundManager::Create(void)
{
	this->Init();

	return (0);
}
