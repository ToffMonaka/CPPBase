/**
 * @file
 * @brief ThreadLockBlockヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "ThreadLock.h"


namespace tml {
/**
 * @brief ThreadLockBlockクラス
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

	tml::ThreadLock *GetThreadLock(void) const;
	INT GetLockResult(void) const;
};


/**
 * @brief GetThreadLock関数
 * @return th_lock (thread_lock)
 */
inline tml::ThreadLock *tml::ThreadLockBlock::GetThreadLock(void) const
{
	return (this->th_lock_);
}


/**
 * @brief GetLockResult関数
 * @return lock_res (lock_result)
 */
inline INT tml::ThreadLockBlock::GetLockResult(void) const
{
	return (this->lock_res_);
}
}
