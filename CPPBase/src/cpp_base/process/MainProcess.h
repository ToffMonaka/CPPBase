/**
 * @file
 * @brief MainProcessヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/time/FrameRate.h"
#include "../../lib/tml/process/Process.h"
#include "../file/SystemConfigFile.h"


namespace cpp_base {
/**
 * @brief MainProcessクラス
 */
class MainProcess : public tml::Process
{
public: MainProcess(const cpp_base::MainProcess &) = delete;
public: cpp_base::MainProcess &operator =(const cpp_base::MainProcess &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	cpp_base::SystemConfigFile sys_conf_file_;
	tml::FrameRate frame_rate_;

private:
	static LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

private:
	void Release(void);

public:
	MainProcess();
	virtual ~MainProcess();

	virtual void Init(void);
	INT Create(const HINSTANCE, const WCHAR *, const INT);

	virtual INT Start(void);
	virtual void End(void);
	virtual void Update(void);
};
}
