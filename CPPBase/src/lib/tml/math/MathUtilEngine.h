/**
 * @file
 * @brief MathUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief MathUtilEngineDesc�N���X
 */
class MathUtilEngineDesc
{
public:

private:
	void Release(void);

public:
	MathUtilEngineDesc();
	virtual ~MathUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::MathUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief MathUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class MathUtilEngine
{
public: MathUtilEngine(const tml::MathUtilEngine &) = delete;
public: tml::MathUtilEngine &operator =(const tml::MathUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:

private:
	void Release(void);

public:
	MathUtilEngine();
	virtual ~MathUtilEngine();

	virtual void Init(void);
	INT Create(const tml::MathUtilEngineDesc &);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::MathUtilEngine::Release(void)
{
	return;
}
