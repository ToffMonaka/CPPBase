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
 * @return ����
 * FALSE=���s,TRUE=����
 */
BOOL tml::ThreadFix::Check(void)
{
	auto th_id = std::this_thread::get_id();

	this->th_lock_.Lock();

	if (this->th_id_ == std::thread::id()) {
		this->th_id_ = th_id;
	} else if (this->th_id_ != th_id) {
		this->th_lock_.Unlock();

		return (FALSE);
	}

	this->th_lock_.Unlock();

	return (TRUE);
}
