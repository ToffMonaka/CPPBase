/**
 * @file
 * @brief ThreadLockBlock�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "ThreadLock.h"


namespace tml {
/**
 * @brief ThreadLockBlock�N���X
 */
class ThreadLockBlock
{
public: ThreadLockBlock(const ThreadLockBlock &) = delete;
public: ThreadLockBlock &operator =(const ThreadLockBlock &) = delete;

private:
	tml::ThreadLock *th_lock_;
	INT lock_res_;

public:
	ThreadLockBlock(tml::ThreadLock *);
	ThreadLockBlock(tml::ThreadLock *, const TIME_MILLI &);
	~ThreadLockBlock();

	tml::ThreadLock *thread_lock(void) const;
	INT lock_result(void) const;
};


/**
 * @brief thread_lock�֐�
 *
 * @return th_lock : thread_lock
 */
inline tml::ThreadLock *tml::ThreadLockBlock::thread_lock(void) const
{
	return (this->th_lock_);
}


/**
 * @brief lock_result�֐�
 *
 * @return lock_res : lock_result
 */
inline INT tml::ThreadLockBlock::lock_result(void) const
{
	return (this->lock_res_);
}
}
