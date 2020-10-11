/**
 * @file
 * @brief SpinThreadLockコードファイル
 */


#include "SpinThreadLock.h"


/**
 * @brief コンストラクタ
 */
tml::SpinThreadLock::SpinThreadLock() :
	stat_(tml::SpinThreadLock::STATE::UNLOCK),
	lock_cnt_(0UL)
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
 *
 * @return res : result<br>0未満=失敗
 */
INT tml::SpinThreadLock::Lock(void)
{
	auto th_id = std::this_thread::get_id();

	while (this->stat_.exchange(tml::SpinThreadLock::STATE::LOCK, std::memory_order_acquire) == tml::SpinThreadLock::STATE::LOCK) {
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
 *
 * @param timeout_time : timeout_time
 * @return res : result<br>0未満=失敗,-2=タイムアウト
 */
INT tml::SpinThreadLock::Lock(const TIME_MILLI &timeout_time)
{
	auto th_id = std::this_thread::get_id();
	auto timeout_time_point = std::chrono::steady_clock::now() + timeout_time;

	while (this->stat_.exchange(tml::SpinThreadLock::STATE::LOCK, std::memory_order_acquire) == tml::SpinThreadLock::STATE::LOCK) {
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

	this->stat_.store(tml::SpinThreadLock::STATE::UNLOCK, std::memory_order_release);

	return;
}
