/**
 * @file
 * @brief MainProcessヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../../lib/tml/time/FrameRate.h"
#include "../../lib/tml/process/Process.h"


namespace cpp_base {
/**
 * @brief MainProcessクラス
 */
class MainProcess : public tml::Process
{
public: MainProcess(const MainProcess &) = delete;
public: MainProcess &operator =(const MainProcess &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
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
