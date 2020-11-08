/**
 * @file
 * @brief ThreadLock�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief ThreadLock�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ThreadLock
{
public: ThreadLock(const ThreadLock &) = delete;
public: ThreadLock &operator =(const ThreadLock &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	ThreadLock();
	virtual ~ThreadLock();

	virtual INT Lock(void) = 0;
	virtual INT Lock(const tml::TIME_MILLI &) = 0;
	virtual void Unlock(void) = 0;
};
}
