/**
 * @file
 * @brief DefaultFileUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "FileUtilEngine.h"


namespace tml {
/**
 * @brief DefaultFileUtilEngineクラス
 */
class DefaultFileUtilEngine : public tml::FileUtilEngine
{
public: DefaultFileUtilEngine(const tml::DefaultFileUtilEngine &) = delete;
public: tml::DefaultFileUtilEngine &operator =(const tml::DefaultFileUtilEngine &) = delete;
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


/**
 * @brief Release関数
 */
inline void tml::DefaultFileUtilEngine::Release(void)
{
	return;
}
