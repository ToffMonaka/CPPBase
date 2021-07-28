/**
 * @file
 * @brief ThreadLockBlock�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ThreadLock.h"


namespace tml {
/**
 * @brief ThreadLockBlock�N���X
 */
class ThreadLockBlock
{
public: ThreadLockBlock(const tml::ThreadLockBlock &) = delete;
public: tml::ThreadLockBlock &operator =(const tml::ThreadLockBlock &) = delete;

private:
	tml::ThreadLock &th_lock_;
	INT result_;

public:
	ThreadLockBlock(tml::ThreadLock &);
	ThreadLockBlock(tml::ThreadLock &, const tml::TIME_MILLI &);
	virtual ~ThreadLockBlock();

	INT GetResult(void) const;
};
}


/**
 * @brief GetResult�֐�
 * @return result (result)
 */
inline INT tml::ThreadLockBlock::GetResult(void) const
{
	return (this->result_);
}
