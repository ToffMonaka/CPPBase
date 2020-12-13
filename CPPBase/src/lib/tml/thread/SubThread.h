/**
 * @file
 * @brief SubThread�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Thread.h"


namespace tml {
/**
 * @brief SubThread�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class SubThread : public tml::Thread
{
public: SubThread(const tml::SubThread &) = delete;
public: tml::SubThread &operator =(const tml::SubThread &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	std::thread core_;
	std::atomic<bool> core_created_flg_;
	tml::MutexThreadLock core_th_lock_;

protected:
	void Release(void);
	INT Create(void);

public:
	SubThread();
	virtual ~SubThread();

	virtual void Init(void);

	virtual INT Start(void) = 0;
	virtual void End(void) = 0;
	virtual void Update(void) = 0;
};
}
