/**
 * @file
 * @brief DefaultMathUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "MathUtilEngine.h"


namespace tml {
/**
 * @brief DefaultMathUtilEngineDescクラス
 */
class DefaultMathUtilEngineDesc : public tml::MathUtilEngineDesc
{
public:

private:
	void Release(void);

public:
	DefaultMathUtilEngineDesc();
	virtual ~DefaultMathUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::DefaultMathUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief DefaultMathUtilEngineクラス
 */
class DefaultMathUtilEngine : public tml::MathUtilEngine
{
public: DefaultMathUtilEngine(const tml::DefaultMathUtilEngine &) = delete;
public: tml::DefaultMathUtilEngine &operator =(const tml::DefaultMathUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultMathUtilEngine();
	virtual ~DefaultMathUtilEngine();

	virtual void Init(void);
	INT Create(const tml::DefaultMathUtilEngineDesc &);
};
}


/**
 * @brief Release関数
 */
inline void tml::DefaultMathUtilEngine::Release(void)
{
	return;
}
