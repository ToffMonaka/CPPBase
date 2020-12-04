/**
 * @file
 * @brief ThreadLockヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
/**
 * @brief ThreadLockクラス
 *
 * インターフェースパターン
 */
class ThreadLock
{
public: ThreadLock(const tml::ThreadLock &) = delete;
public: tml::ThreadLock &operator =(const tml::ThreadLock &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	ThreadLock();
	virtual ~ThreadLock();

	virtual INT Lock(void) = 0;
	virtual INT Lock(const tml::TIME_MILLI &) = 0;
	virtual void Unlock(void) = 0;
};
}
