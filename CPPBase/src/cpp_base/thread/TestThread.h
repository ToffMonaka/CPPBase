/**
 * @file
 * @brief TestThreadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/time/FrameRate.h"
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
	tml::FrameRate frame_rate_;

protected:
	void Release(void);

public:
	TestThread();
	virtual ~TestThread();

	virtual void Init(void);
	INT Create(void);

	virtual INT Start(void);
	virtual void End(void);
	virtual void Update(void);
	const tml::FrameRate &GetFrameRate(void) const;
};
}


/**
 * @brief Release関数
 */
inline void cpp_base::TestThread::Release(void)
{
	tml::SubThread::Release();

	return;
}


/**
 * @brief GetFrameRate関数
 * @return frame_rate (frame_rate)
 */
inline const tml::FrameRate &cpp_base::TestThread::GetFrameRate(void) const
{
	return (this->frame_rate_);
}
