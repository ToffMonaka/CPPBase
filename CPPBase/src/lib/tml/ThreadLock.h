/**
 * @file
 * @brief ThreadLockヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"


namespace tml {
/**
 * @brief ThreadLockクラス
 *
 * インターフェースパターン
 */
class ThreadLock
{
private: ThreadLock(const ThreadLock &) {return;};
private: ThreadLock &operator =(const ThreadLock &) {return ((*this));};
protected: virtual void InterfaceDummy(void) = 0;

public:
	ThreadLock();
	virtual ~ThreadLock();

	virtual INT Lock(void) = 0;
	virtual INT Lock(const TIME_MILLI &) = 0;
	virtual void Unlock(void) = 0;
};
}
