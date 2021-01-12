/**
 * @file
 * @brief MainThreadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/time/FrameRate.h"
#include "../../lib/tml/thread/MainThread.h"
#include "../../lib/tml/input/Manager.h"
#include "../../lib/tml/graphic/Manager.h"
#include "../../lib/tml/sound/Manager.h"
#include "../data/SystemConfigFile.h"


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
	tml::FrameRate frame_rate_;
	cpp_base::SystemConfigFile sys_conf_file_;
	tml::input::Manager input_mgr_;
	tml::graphic::Manager graphic_mgr_;
	tml::sound::Manager sound_mgr_;

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
