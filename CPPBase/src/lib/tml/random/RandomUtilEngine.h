/**
 * @file
 * @brief RandomUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief RandomUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class RandomUtilEngine
{
public: RandomUtilEngine(const tml::RandomUtilEngine &) = delete;
public: tml::RandomUtilEngine &operator =(const tml::RandomUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	RandomUtilEngine();
	virtual ~RandomUtilEngine();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::RandomUtilEngine::Release(void)
{
	return;
}
