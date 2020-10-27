/**
 * @file
 * @brief MutexThreadLockヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include <mutex>
#include "ThreadLockBlock.h"


namespace tml {
/**
 * @brief MutexThreadLockクラス
 */
class MutexThreadLock : public tml::ThreadLock
{
public: MutexThreadLock(const MutexThreadLock &) = delete;
public: MutexThreadLock &operator =(const MutexThreadLock &) = delete;
protected: virtual void InterfaceDummy(void) {return;}

private:
	std::recursive_timed_mutex mtx_;

public:
	MutexThreadLock();
	virtual ~MutexThreadLock();

	virtual INT Lock(void);
	virtual INT Lock(const TIME_MILLI &);
	virtual void Unlock(void);
};
}
