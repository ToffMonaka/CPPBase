/**
 * @file
 * @brief DefaultMemoryUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "MemoryUtilEngine.h"


namespace tml {
/**
 * @brief DefaultMemoryUtilEngineクラス
 */
class DefaultMemoryUtilEngine : public tml::MemoryUtilEngine
{
public: DefaultMemoryUtilEngine(const DefaultMemoryUtilEngine &) = delete;
public: DefaultMemoryUtilEngine &operator =(const DefaultMemoryUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	DefaultMemoryUtilEngine();
	virtual ~DefaultMemoryUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}
