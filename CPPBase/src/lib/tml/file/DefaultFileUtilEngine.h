/**
 * @file
 * @brief DefaultFileUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "FileUtilEngine.h"


namespace tml {
/**
 * @brief DefaultFileUtilEngineクラス
 */
class DefaultFileUtilEngine : public tml::FileUtilEngine
{
public: DefaultFileUtilEngine(const DefaultFileUtilEngine &) = delete;
public: DefaultFileUtilEngine &operator =(const DefaultFileUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultFileUtilEngine();
	virtual ~DefaultFileUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}
