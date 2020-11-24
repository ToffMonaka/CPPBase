/**
 * @file
 * @brief DefaultTimeUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "TimeUtilEngine.h"


namespace tml {
/**
 * @brief DefaultTimeUtilEngineクラス
 */
class DefaultTimeUtilEngine : public tml::TimeUtilEngine
{
public: DefaultTimeUtilEngine(const DefaultTimeUtilEngine &) = delete;
public: DefaultTimeUtilEngine &operator =(const DefaultTimeUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultTimeUtilEngine();
	virtual ~DefaultTimeUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}
