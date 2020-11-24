/**
 * @file
 * @brief ThreadLockBlockヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
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
	tml::ThreadLock &th_lock_;
	INT res_;

public:
	ThreadLockBlock(tml::ThreadLock &);
	ThreadLockBlock(tml::ThreadLock &, const tml::TIME_MILLI &);
	virtual ~ThreadLockBlock();

	INT GetResult(void) const;
};
}


/**
 * @brief GetResult関数
 * @return res (result)
 */
inline INT tml::ThreadLockBlock::GetResult(void) const
{
	return (this->res_);
}
