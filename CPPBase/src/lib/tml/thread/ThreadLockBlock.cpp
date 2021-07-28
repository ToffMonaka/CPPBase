/**
 * @file
 * @brief ThreadLockBlock�R�[�h�t�@�C��
 */


#include "ThreadLockBlock.h"


/**
 * @brief �R���X�g���N�^
 * @param th_lock (thread_lock)
 */
tml::ThreadLockBlock::ThreadLockBlock(tml::ThreadLock &th_lock) :
	th_lock_(th_lock),
	result_(0)
{
	this->result_ = this->th_lock_.Lock();

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param th_lock (thread_lock)
 * @param timeout_time (timeout_time)
 */
tml::ThreadLockBlock::ThreadLockBlock(tml::ThreadLock &th_lock, const tml::TIME_MILLI &timeout_time) :
	th_lock_(th_lock),
	result_(0)
{
	this->result_ = this->th_lock_.Lock(timeout_time);

	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ThreadLockBlock::~ThreadLockBlock()
{
	if (this->result_ >= 0) {
		this->th_lock_.Unlock();
	}

	this->result_ = 0;

	return;
}
