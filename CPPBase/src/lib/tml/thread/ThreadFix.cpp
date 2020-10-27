/**
 * @file
 * @brief ThreadFixコードファイル
 */


#include "ThreadFix.h"


/**
 * @brief コンストラクタ
 */
tml::ThreadFix::ThreadFix()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ThreadFix::~ThreadFix()
{
	return;
}


/**
 * @brief Check関数
 * @return 判定
 * FALSE=失敗,TRUE=成功
 */
BOOL tml::ThreadFix::Check(void)
{
	auto th_id = std::this_thread::get_id();

	{tml::ThreadLockBlock th_lock_block(this->th_lock_);
		if (this->th_id_ == std::thread::id()) {
			this->th_id_ = th_id;
		} else if (this->th_id_ != th_id) {
			return (FALSE);
		}
	}

	return (TRUE);
}
