/**
 * @file
 * @brief SpinThreadLockコードファイル
 */


#include "SpinThreadLock.h"


/**
 * @brief コンストラクタ
 */
tml::SpinThreadLock::SpinThreadLock() :
	stat_type_(STATE_TYPE_UNLOCK),
	lock_cnt_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::SpinThreadLock::~SpinThreadLock()
{
	return;
}


/**
 * @brief Lock関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::SpinThreadLock::Lock(void)
{
	auto th_id = std::this_thread::get_id();

	while (this->stat_type_.exchange(STATE_TYPE_LOCK, std::memory_order_acquire) == STATE_TYPE_LOCK) {
		if (this->th_id_ == th_id) {
			++this->lock_cnt_;

			return (0);
		}
	}

	this->th_id_ = th_id;

	++this->lock_cnt_;

	return (0);
}


/**
 * @brief Lock関数
 * @param timeout_time (timeout_time)
 * @return result (result)<br>
 * 0未満=失敗,-2=タイムアウト
 */
INT tml::SpinThreadLock::Lock(const tml::TIME_MILLI &timeout_time)
{
	auto th_id = std::this_thread::get_id();
	auto timeout_time_point = std::chrono::steady_clock::now() + timeout_time;

	while (this->stat_type_.exchange(STATE_TYPE_LOCK, std::memory_order_acquire) == STATE_TYPE_LOCK) {
		if (this->th_id_ == th_id) {
			++this->lock_cnt_;

			return (0);
		}

		if (std::chrono::steady_clock::now() >= timeout_time_point) {
			return (-2);
		}
	}

	this->th_id_ = th_id;

	++this->lock_cnt_;

	return (0);
}


/**
 * @brief Unlock関数
 *
 * Lock関数を先に呼ぶ
 */
void tml::SpinThreadLock::Unlock(void)
{
	if (--this->lock_cnt_) {
		return;
	}

	this->th_id_ = std::thread::id();

	this->stat_type_.store(STATE_TYPE_UNLOCK, std::memory_order_release);

	return;
}
