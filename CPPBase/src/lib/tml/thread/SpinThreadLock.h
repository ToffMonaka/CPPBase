/**
 * @file
 * @brief SpinThreadLockヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include <atomic>
#include <thread>
#include "ThreadLock.h"


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

	INT Lock(void);
	INT Lock(const TIME_MILLI &);
	void Unlock(void);
};
}
