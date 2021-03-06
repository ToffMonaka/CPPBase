/**
 * @file
 * @brief SubThreadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Thread.h"


namespace tml {
/**
 * @brief SubThreadクラス
 *
 * インターフェースパターン
 */
class SubThread : public tml::Thread
{
public: SubThread(const tml::SubThread &) = delete;
public: tml::SubThread &operator =(const tml::SubThread &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	SubThread();
	virtual ~SubThread();

	virtual void Init(void);

	virtual INT Start(void) = 0;
	virtual void End(void) = 0;
	virtual void Update(void) = 0;
};
}


/**
 * @brief Release関数
 */
inline void tml::SubThread::Release(void)
{
	tml::Thread::Release();

	return;
}
