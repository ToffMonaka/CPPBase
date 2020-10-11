/**
 * @file
 * @brief ThreadLockBlock�R�[�h�t�@�C��
 */


#include "ThreadLockBlock.h"


/**
 * @brief �R���X�g���N�^
 *
 * @param th_lock : thread_lock
 */
tml::ThreadLockBlock::ThreadLockBlock(tml::ThreadLock *th_lock) :
	th_lock_(th_lock),
	lock_res_(0)
{
	if (this->th_lock_ != NULLP) {
		this->lock_res_ = this->th_lock_->Lock();
	}

	return;
}


/**
 * @brief �R���X�g���N�^
 *
 * @param th_lock : thread_lock
 * @param timeout_time : timeout_time
 */
tml::ThreadLockBlock::ThreadLockBlock(tml::ThreadLock *th_lock, const TIME_MILLI &timeout_time) :
	th_lock_(th_lock),
	lock_res_(0)
{
	if (this->th_lock_ != NULLP) {
		this->lock_res_ = this->th_lock_->Lock(timeout_time);
	}

	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ThreadLockBlock::~ThreadLockBlock()
{
	if (this->th_lock_ != NULLP) {
		if (this->lock_res_ >= 0) {
			this->th_lock_->Unlock();
		}

		this->th_lock_ = NULLP;
		this->lock_res_ = 0;
	}

	return;
}
