/**
 * @file
 * @brief ProcessUtilヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "ProcessUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief ProcessUtilクラス
 *
 * ユーティリティパターン<br>
 * エンジンパターン
 */
class ProcessUtil
{
public: ProcessUtil() = delete;
public: ProcessUtil(const ProcessUtil &) = delete;
public: ProcessUtil &operator =(const ProcessUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::ProcessUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::ProcessUtilEngine> &);

	static INT Start(std::unique_ptr<tml::Process> &);
	void End(void);
	static INT GetExitCode(void);
};


/**
 * @brief Start関数
 * @param proc (process)
 * @return res (result)<br>
 * 0未満=失敗,-2=多重起動
 */
inline INT tml::ProcessUtil::Start(std::unique_ptr<tml::Process> &proc)
{
	return (tml::ProcessUtil::engine_->Start(proc));
}


/**
 * @brief End関数
 */
inline void tml::ProcessUtil::End(void)
{
	tml::ProcessUtil::engine_->End();

	return;
}


/**
 * @brief GetExitCode関数
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
inline INT tml::ProcessUtil::GetExitCode(void)
{
	return (tml::ProcessUtil::engine_->GetExitCode());
}
}
