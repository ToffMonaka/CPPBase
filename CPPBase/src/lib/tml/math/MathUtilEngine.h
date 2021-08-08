/**
 * @file
 * @brief MathUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief MathUtilEngineクラス
 *
 * インターフェースパターン
 */
class MathUtilEngine
{
public: MathUtilEngine(const tml::MathUtilEngine &) = delete;
public: tml::MathUtilEngine &operator =(const tml::MathUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	void Release(void);

public:
	MathUtilEngine();
	virtual ~MathUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::MathUtilEngine::Release(void)
{
	return;
}
