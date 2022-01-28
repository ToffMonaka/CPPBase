/**
 * @file
 * @brief RandomUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief RandomUtilEngineDescクラス
 */
class RandomUtilEngineDesc
{
public:

private:
	void Release(void);

public:
	RandomUtilEngineDesc();
	virtual ~RandomUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::RandomUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief RandomUtilEngineクラス
 *
 * インターフェースパターン
 */
class RandomUtilEngine
{
public: RandomUtilEngine(const tml::RandomUtilEngine &) = delete;
public: tml::RandomUtilEngine &operator =(const tml::RandomUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	void Release(void);

public:
	RandomUtilEngine();
	virtual ~RandomUtilEngine();

	virtual void Init(void);
	INT Create(const tml::RandomUtilEngineDesc &);
};
}


/**
 * @brief Release関数
 */
inline void tml::RandomUtilEngine::Release(void)
{
	return;
}
