/**
 * @file
 * @brief TimeUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"


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

protected:
	void Release(void);
	INT Create(void);

public:
	TimeUtilEngine();
	virtual ~TimeUtilEngine();

	virtual void Init(void);
};
}
