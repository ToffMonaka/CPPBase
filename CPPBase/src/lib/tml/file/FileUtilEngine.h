/**
 * @file
 * @brief FileUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief FileUtilEngineクラス
 *
 * インターフェースパターン
 */
class FileUtilEngine
{
public: FileUtilEngine(const tml::FileUtilEngine &) = delete;
public: tml::FileUtilEngine &operator =(const tml::FileUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	void Release(void);

public:
	FileUtilEngine();
	virtual ~FileUtilEngine();

	virtual void Init(void);
	INT Create(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::FileUtilEngine::Release(void)
{
	return;
}
