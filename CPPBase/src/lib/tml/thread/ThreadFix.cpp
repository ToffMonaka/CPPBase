/**
 * @file
 * @brief ThreadFix�R�[�h�t�@�C��
 */


#include "ThreadFix.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ThreadFix::ThreadFix()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ThreadFix::~ThreadFix()
{
	return;
}


/**
 * @brief Check�֐�
 * @return res_flg (result_flag)<br>
 * false=���s,true=����
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
