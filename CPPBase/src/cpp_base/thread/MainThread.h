/**
 * @file
 * @brief MainThreadヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "../../lib/tml/thread/Thread.h"


namespace cpp_base {
/**
 * @brief MainThreadクラス
 */
class MainThread : public tml::Thread
{
public: MainThread(const MainThread &) = delete;
public: MainThread &operator =(const MainThread &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	MainThread();
	virtual ~MainThread();

	virtual void Init(void);
	INT Create(void);
};
}
