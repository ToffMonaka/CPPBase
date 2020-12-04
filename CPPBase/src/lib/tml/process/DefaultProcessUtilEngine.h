/**
 * @file
 * @brief DefaultProcessUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ProcessUtilEngine.h"


namespace tml {
/**
 * @brief DefaultProcessUtilEngineクラス
 */
class DefaultProcessUtilEngine : public tml::ProcessUtilEngine
{
public: DefaultProcessUtilEngine(const tml::DefaultProcessUtilEngine &) = delete;
public: tml::DefaultProcessUtilEngine &operator =(const tml::DefaultProcessUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultProcessUtilEngine();
	virtual ~DefaultProcessUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}
