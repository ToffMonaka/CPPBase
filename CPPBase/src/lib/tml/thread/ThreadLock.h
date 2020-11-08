/**
 * @file
 * @brief ThreadLockヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief ThreadLockクラス
 *
 * インターフェースパターン
 */
class ThreadLock
{
public: ThreadLock(const ThreadLock &) = delete;
public: ThreadLock &operator =(const ThreadLock &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	ThreadLock();
	virtual ~ThreadLock();

	virtual INT Lock(void) = 0;
	virtual INT Lock(const tml::TIME_MILLI &) = 0;
	virtual void Unlock(void) = 0;
};
}
