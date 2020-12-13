/**
 * @file
 * @brief MainThreadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/time/FrameRate.h"
#include "../../lib/tml/thread/MainThread.h"
#include "../file/SystemConfigFile.h"


namespace cpp_base {
/**
 * @brief MainThreadクラス
 */
class MainThread : public tml::MainThread
{
public: MainThread(const cpp_base::MainThread &) = delete;
public: cpp_base::MainThread &operator =(const cpp_base::MainThread &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	cpp_base::SystemConfigFile sys_conf_file_;
	tml::FrameRate frame_rate_;

private:
	static LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

private:
	void Release(void);

public:
	MainThread();
	virtual ~MainThread();

	virtual void Init(void);
	INT Create(const HINSTANCE, const WCHAR *, const INT);

	virtual INT Start(void);
	virtual void End(void);
	virtual void Update(void);
};
}
