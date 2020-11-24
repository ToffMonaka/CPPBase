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
public: TimeUtilEngine(const TimeUtilEngine &) = delete;
public: TimeUtilEngine &operator =(const TimeUtilEngine &) = delete;
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
