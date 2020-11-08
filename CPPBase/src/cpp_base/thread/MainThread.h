/**
 * @file
 * @brief MainThreadヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "../../lib/tml/time/FrameRate.h"
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
	tml::FrameRate frame_rate_;

private:
	void Release(void);

public:
	MainThread();
	virtual ~MainThread();

	virtual void Init(void);
	INT Create(void);

	virtual INT Start(void);
	virtual void End(void);
	virtual void Update(void);
};
}
