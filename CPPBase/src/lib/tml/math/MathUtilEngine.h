/**
 * @file
 * @brief MathUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief MathUtilEngineクラス
 *
 * インターフェースパターン
 */
class MathUtilEngine
{
public: MathUtilEngine(const MathUtilEngine &) = delete;
public: MathUtilEngine &operator =(const MathUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	MathUtilEngine();
	virtual ~MathUtilEngine();

	virtual void Init(void);
};
}
