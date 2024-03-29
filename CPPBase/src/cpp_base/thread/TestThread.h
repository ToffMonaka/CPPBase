/**
 * @file
 * @brief TestThreadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/thread/SubThread.h"


namespace cpp_base {
/**
 * @brief TestThreadクラス
 */
class TestThread : public tml::SubThread
{
public: TestThread(const cpp_base::TestThread &) = delete;
public: cpp_base::TestThread &operator =(const cpp_base::TestThread &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

protected:
	virtual INT OnStart(void);
	virtual void OnEnd(void);
	virtual void OnUpdate(void);

public:
	TestThread();
	virtual ~TestThread();

	virtual void Init(void);
	INT Create(void);
};
}
