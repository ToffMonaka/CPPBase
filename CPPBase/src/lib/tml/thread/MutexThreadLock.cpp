/**
 * @file
 * @brief MutexThreadLock�R�[�h�t�@�C��
 */


#include "MutexThreadLock.h"


/**
 * @brief �R���X�g���N�^
 */
tml::MutexThreadLock::MutexThreadLock()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::MutexThreadLock::~MutexThreadLock()
{
	return;
}


/**
 * @brief Lock�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::MutexThreadLock::Lock(void)
{
	this->mtx_.lock();

	return (0);
}


/**
 * @brief Lock�֐�
 * @param timeout_time (timeout_time)
 * @return res (result)<br>
 * 0����=���s,-2=�^�C���A�E�g
 */
INT tml::MutexThreadLock::Lock(const TIME_MILLI &timeout_time)
{
	auto timeout_time_point = std::chrono::steady_clock::now() + timeout_time;

	if (!this->mtx_.try_lock_until(timeout_time_point)) {
		return (-2);
	}

	return (0);
}


/**
 * @brief Unlock�֐�
 *
 * Lock�֐����ɌĂ�
 */
void tml::MutexThreadLock::Unlock(void)
{
	this->mtx_.unlock();

	return;
}
