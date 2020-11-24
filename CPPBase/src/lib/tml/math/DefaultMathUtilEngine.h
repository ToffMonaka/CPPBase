/**
 * @file
 * @brief DefaultMathUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "MathUtilEngine.h"


namespace tml {
/**
 * @brief DefaultMathUtilEngineクラス
 */
class DefaultMathUtilEngine : public tml::MathUtilEngine
{
public: DefaultMathUtilEngine(const DefaultMathUtilEngine &) = delete;
public: DefaultMathUtilEngine &operator =(const DefaultMathUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultMathUtilEngine();
	virtual ~DefaultMathUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}
