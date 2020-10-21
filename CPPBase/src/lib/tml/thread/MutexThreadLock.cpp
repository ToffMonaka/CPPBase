/**
 * @file
 * @brief MutexThreadLockコードファイル
 */


#include "MutexThreadLock.h"


/**
 * @brief コンストラクタ
 */
tml::MutexThreadLock::MutexThreadLock()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MutexThreadLock::~MutexThreadLock()
{
	return;
}


/**
 * @brief Lock関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::MutexThreadLock::Lock(void)
{
	this->mtx_.lock();

	return (0);
}


/**
 * @brief Lock関数
 * @param timeout_time (timeout_time)
 * @return res (result)<br>
 * 0未満=失敗,-2=タイムアウト
 */
INT tml::MutexThreadLock::Lock(const TIME_MILLI &timeout_time)
{
	auto timeout_time_point = std::chrono::steady_clock::now() + timeout_time;

	if (!this->mtx_.try_lock_until(timeout_time_point)) {
		return (-2);
	}

	return (0);
}


/**
 * @brief Unlock関数
 *
 * Lock関数を先に呼ぶ
 */
void tml::MutexThreadLock::Unlock(void)
{
	this->mtx_.unlock();

	return;
}
