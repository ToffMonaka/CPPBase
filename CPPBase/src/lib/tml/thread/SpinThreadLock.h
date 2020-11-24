/**
 * @file
 * @brief SpinThreadLockヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <thread>
#include <atomic>
#include "ThreadLockBlock.h"


namespace tml {
/**
 * @brief SpinThreadLockクラス
 */
class SpinThreadLock : public tml::ThreadLock
{
public: SpinThreadLock(const SpinThreadLock &) = delete;
public: SpinThreadLock &operator =(const SpinThreadLock &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	typedef enum {
		STATE_TYPE_LOCK = 0,
		STATE_TYPE_UNLOCK
	} STATE_TYPE;

private:
	std::atomic<STATE_TYPE> stat_type_;
	std::thread::id th_id_;
	UINT lock_cnt_;

public:
	SpinThreadLock();
	virtual ~SpinThreadLock();

	virtual INT Lock(void);
	virtual INT Lock(const tml::TIME_MILLI &);
	virtual void Unlock(void);
};
}
