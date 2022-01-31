/**
 * @file
 * @brief DefaultFileUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "FileUtilEngine.h"


namespace tml {
/**
 * @brief DefaultFileUtilEngineDesc�N���X
 */
class DefaultFileUtilEngineDesc : public tml::FileUtilEngineDesc
{
public:

private:
	void Release(void);

public:
	DefaultFileUtilEngineDesc();
	virtual ~DefaultFileUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::DefaultFileUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief DefaultFileUtilEngine�N���X
 */
class DefaultFileUtilEngine : public tml::FileUtilEngine
{
public: DefaultFileUtilEngine(const tml::DefaultFileUtilEngine &) = delete;
public: tml::DefaultFileUtilEngine &operator =(const tml::DefaultFileUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	DefaultFileUtilEngine();
	virtual ~DefaultFileUtilEngine();

	virtual void Init(void);
	INT Create(const tml::DefaultFileUtilEngineDesc &);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::DefaultFileUtilEngine::Release(void)
{
	return;
}
