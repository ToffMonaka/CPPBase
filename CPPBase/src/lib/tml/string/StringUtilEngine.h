/**
 * @file
 * @brief StringUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief StringUtilEngineクラス
 *
 * インターフェースパターン
 */
class StringUtilEngine
{
public: StringUtilEngine(const StringUtilEngine &) = delete;
public: StringUtilEngine &operator =(const StringUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	StringUtilEngine();
	virtual ~StringUtilEngine();

	virtual void Init(void);
};
}
