/**
 * @file
 * @brief Thread�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief Thread�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class Thread
{
public: Thread(const Thread &) = delete;
public: Thread &operator =(const Thread &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	Thread();
	virtual ~Thread();

	virtual void Init(void);
};
}
