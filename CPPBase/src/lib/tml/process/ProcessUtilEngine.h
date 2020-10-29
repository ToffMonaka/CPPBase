/**
 * @file
 * @brief ProcessUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "Process.h"


namespace tml {
/**
 * @brief ProcessUtilEngineクラス
 *
 * インターフェースパターン
 */
class ProcessUtilEngine
{
public: ProcessUtilEngine(const ProcessUtilEngine &) = delete;
public: ProcessUtilEngine &operator =(const ProcessUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	ProcessUtilEngine();
	virtual ~ProcessUtilEngine();

	virtual void Init(void);

	INT Start(std::unique_ptr<tml::Process> &);
	void End(void);
	INT GetExitCode(void);
};
}
