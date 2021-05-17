/**
 * @file
 * @brief FixedThreadコードファイル
 */


#include "FixedThread.h"


/**
 * @brief コンストラクタ
 */
tml::FixedThread::FixedThread()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::FixedThread::~FixedThread()
{
	return;
}


/**
 * @brief Check関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
bool tml::FixedThread::Check(void)
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
