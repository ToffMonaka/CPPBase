/**
 * @file
 * @brief ThreadUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief ThreadUtilEngineクラス
 *
 * インターフェースパターン
 */
class ThreadUtilEngine
{
public: ThreadUtilEngine(const ThreadUtilEngine &) = delete;
public: ThreadUtilEngine &operator =(const ThreadUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	ThreadUtilEngine();
	virtual ~ThreadUtilEngine();

	virtual void Init(void);
};
}
