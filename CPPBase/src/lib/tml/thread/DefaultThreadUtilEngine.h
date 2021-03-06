/**
 * @file
 * @brief DefaultThreadUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "ThreadUtilEngine.h"


namespace tml {
/**
 * @brief DefaultThreadUtilEngineクラス
 */
class DefaultThreadUtilEngine : public tml::ThreadUtilEngine
{
public: DefaultThreadUtilEngine(const tml::DefaultThreadUtilEngine &) = delete;
public: tml::DefaultThreadUtilEngine &operator =(const tml::DefaultThreadUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

protected:
	void Release(void);

public:
	DefaultThreadUtilEngine();
	virtual ~DefaultThreadUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::DefaultThreadUtilEngine::Release(void)
{
	tml::ThreadUtilEngine::Release();

	return;
}
