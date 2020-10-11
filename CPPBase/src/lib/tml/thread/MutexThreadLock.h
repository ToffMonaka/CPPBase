/**
 * @file
 * @brief MutexThreadLockヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include <mutex>
#include "ThreadLock.h"


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
	std::recursive_timed_mutex stat_;

public:
	MutexThreadLock();
	virtual ~MutexThreadLock();

	INT Lock(void);
	INT Lock(const TIME_MILLI &);
	void Unlock(void);
};
}
