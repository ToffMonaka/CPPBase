/**
 * @file
 * @brief TimeUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief TimeUtilEngineクラス
 *
 * インターフェースパターン
 */
class TimeUtilEngine
{
public: TimeUtilEngine(const tml::TimeUtilEngine &) = delete;
public: tml::TimeUtilEngine &operator =(const tml::TimeUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	void Release(void);

public:
	TimeUtilEngine();
	virtual ~TimeUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::TimeUtilEngine::Release(void)
{
	return;
}
