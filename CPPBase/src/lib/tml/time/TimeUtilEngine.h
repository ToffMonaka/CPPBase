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
 * @brief TimeUtilEngineDescクラス
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
 * @brief Release関数
 */
inline void tml::TimeUtilEngineDesc::Release(void)
{
	return;
}


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
 * @brief Release関数
 */
inline void tml::TimeUtilEngine::Release(void)
{
	return;
}
