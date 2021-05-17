/**
 * @file
 * @brief FixedThread�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "SpinThreadLock.h"


namespace tml {
/**
 * @brief FixedThread�N���X
 */
class FixedThread
{
public: FixedThread(const tml::FixedThread &) = delete;
public: tml::FixedThread &operator =(const tml::FixedThread &) = delete;

private:
	std::thread::id th_id_;
	tml::SpinThreadLock th_lock_;

public:
	FixedThread();
	virtual ~FixedThread();

	bool Check(void);
};
}
