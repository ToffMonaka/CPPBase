/**
 * @file
 * @brief MutexThreadLockヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <thread>
#include <mutex>
#include "ThreadLockBlock.h"


namespace tml {
/**
 * @brief MutexThreadLockクラス
 */
class MutexThreadLock : public tml::ThreadLock
{
public: MutexThreadLock(const tml::MutexThreadLock &) = delete;
public: tml::MutexThreadLock &operator =(const tml::MutexThreadLock &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	std::recursive_timed_mutex mtx_;

public:
	MutexThreadLock();
	virtual ~MutexThreadLock();

	virtual INT Lock(void);
	virtual INT Lock(const tml::TIME_MILLI &);
	virtual void Unlock(void);
};
}
