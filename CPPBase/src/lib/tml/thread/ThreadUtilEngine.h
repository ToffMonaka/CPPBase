/**
 * @file
 * @brief ThreadUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "Thread.h"


namespace tml {
/**
 * @brief ThreadUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class ThreadUtilEngine
{
public: ThreadUtilEngine(const ThreadUtilEngine &) = delete;
public: ThreadUtilEngine &operator =(const ThreadUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	ThreadUtilEngine();
	virtual ~ThreadUtilEngine();

	virtual void Init(void);

	INT Start(std::unique_ptr<tml::Thread> &);
	void End(void);
	void EndAll(void);
};
}
