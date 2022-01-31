/**
 * @file
 * @brief DefaultRandomUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "RandomUtilEngine.h"


namespace tml {
/**
 * @brief DefaultRandomUtilEngineDesc�N���X
 */
class DefaultRandomUtilEngineDesc : public tml::RandomUtilEngineDesc
{
public:

private:
	void Release(void);

public:
	DefaultRandomUtilEngineDesc();
	virtual ~DefaultRandomUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::DefaultRandomUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief DefaultRandomUtilEngine�N���X
 */
class DefaultRandomUtilEngine : public tml::RandomUtilEngine
{
public: DefaultRandomUtilEngine(const tml::DefaultRandomUtilEngine &) = delete;
public: tml::DefaultRandomUtilEngine &operator =(const tml::DefaultRandomUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	DefaultRandomUtilEngine();
	virtual ~DefaultRandomUtilEngine();

	virtual void Init(void);
	INT Create(const tml::DefaultRandomUtilEngineDesc &);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::DefaultRandomUtilEngine::Release(void)
{
	return;
}
