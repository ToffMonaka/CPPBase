/**
 * @file
 * @brief DefaultStringUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "StringUtilEngine.h"


namespace tml {
/**
 * @brief DefaultStringUtilEngineクラス
 */
class DefaultStringUtilEngine : public tml::StringUtilEngine
{
public: DefaultStringUtilEngine(const tml::DefaultStringUtilEngine &) = delete;
public: tml::DefaultStringUtilEngine &operator =(const tml::DefaultStringUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultStringUtilEngine();
	virtual ~DefaultStringUtilEngine();

	virtual void Init(void);
	INT Create(const CHAR *);
};
}


/**
 * @brief Release関数
 */
inline void tml::DefaultStringUtilEngine::Release(void)
{
	return;
}
