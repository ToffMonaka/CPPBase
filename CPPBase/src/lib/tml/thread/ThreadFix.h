/**
 * @file
 * @brief ThreadFix�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "SpinThreadLock.h"


namespace tml {
/**
 * @brief ThreadFix�N���X
 */
class ThreadFix
{
public: ThreadFix(const tml::ThreadFix &) = delete;
public: tml::ThreadFix &operator =(const tml::ThreadFix &) = delete;

private:
	std::thread::id th_id_;
	tml::SpinThreadLock th_lock_;

public:
	ThreadFix();
	virtual ~ThreadFix();

	bool Check(void);
};
}
