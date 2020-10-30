/**
 * @file
 * @brief MainProcessヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
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
	void Release(void);

public:
	MainProcess();
	virtual ~MainProcess();

	virtual void Init(void);
	INT Create(void);

	virtual INT Start(void);
	virtual void End(void);
	virtual void Update(void);
};
}
