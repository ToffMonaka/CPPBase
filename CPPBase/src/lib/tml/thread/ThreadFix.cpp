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
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
bool tml::ThreadFix::Check(void)
{
	auto th_id = std::this_thread::get_id();

	{tml::ThreadLockBlock th_lock_block(this->th_lock_);
		if (this->th_id_ == std::thread::id()) {
			this->th_id_ = th_id;
		} else if (this->th_id_ != th_id) {
			return (false);
		}
	}

	return (true);
}
