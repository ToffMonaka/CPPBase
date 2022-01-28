/**
 * @file
 * @brief DefaultTimeUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "TimeUtilEngine.h"


namespace tml {
/**
 * @brief DefaultTimeUtilEngineDesc�N���X
 */
class DefaultTimeUtilEngineDesc : public tml::TimeUtilEngineDesc
{
public:

private:
	void Release(void);

public:
	DefaultTimeUtilEngineDesc();
	virtual ~DefaultTimeUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::DefaultTimeUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief DefaultTimeUtilEngine�N���X
 */
class DefaultTimeUtilEngine : public tml::TimeUtilEngine
{
public: DefaultTimeUtilEngine(const tml::DefaultTimeUtilEngine &) = delete;
public: tml::DefaultTimeUtilEngine &operator =(const tml::DefaultTimeUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultTimeUtilEngine();
	virtual ~DefaultTimeUtilEngine();

	virtual void Init(void);
	INT Create(const tml::DefaultTimeUtilEngineDesc &);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::DefaultTimeUtilEngine::Release(void)
{
	return;
}
