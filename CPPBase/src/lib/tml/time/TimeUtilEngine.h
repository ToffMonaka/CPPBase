/**
 * @file
 * @brief TimeUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief TimeUtilEngineDesc�N���X
 */
class TimeUtilEngineDesc
{
public:

private:
	void Release(void);

public:
	TimeUtilEngineDesc();
	virtual ~TimeUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::TimeUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief TimeUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class TimeUtilEngine
{
public: TimeUtilEngine(const tml::TimeUtilEngine &) = delete;
public: tml::TimeUtilEngine &operator =(const tml::TimeUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:

private:
	void Release(void);

public:
	TimeUtilEngine();
	virtual ~TimeUtilEngine();

	virtual void Init(void);
	INT Create(const tml::TimeUtilEngineDesc &);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::TimeUtilEngine::Release(void)
{
	return;
}
