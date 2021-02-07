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
public: DefaultTimeUtilEngine(const tml::DefaultTimeUtilEngine &) = delete;
public: tml::DefaultTimeUtilEngine &operator =(const tml::DefaultTimeUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

protected:
	void Release(void);

public:
	DefaultTimeUtilEngine();
	virtual ~DefaultTimeUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::DefaultTimeUtilEngine::Release(void)
{
	tml::TimeUtilEngine::Release();

	return;
}
