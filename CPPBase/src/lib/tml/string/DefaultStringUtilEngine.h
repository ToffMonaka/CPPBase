/**
 * @file
 * @brief DefaultStringUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "StringUtilEngine.h"


namespace tml {
/**
 * @brief DefaultStringUtilEngineクラス
 */
class DefaultStringUtilEngine : public tml::StringUtilEngine
{
public: DefaultStringUtilEngine(const DefaultStringUtilEngine &) = delete;
public: DefaultStringUtilEngine &operator =(const DefaultStringUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultStringUtilEngine();
	virtual ~DefaultStringUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}
