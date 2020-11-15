/**
 * @file
 * @brief RandomUtilEngine�R�[�h�t�@�C��
 */


#include "RandomUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::RandomUtilEngine::RandomUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::RandomUtilEngine::~RandomUtilEngine()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::RandomUtilEngine::Release(void)
{
	{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
		this->seed_.Init();
	}

	return;
}


/**
 * @brief Init�֐�
 */
void tml::RandomUtilEngine::Init(void)
{
	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::RandomUtilEngine::Create(void)
{
	{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
		if (this->seed_.Create() < 0) {
			return (-1);
		}
	}

	return (0);
}
