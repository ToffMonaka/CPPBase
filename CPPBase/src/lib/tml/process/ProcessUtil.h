/**
 * @file
 * @brief ProcessUtilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
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
public: ProcessUtil(const tml::ProcessUtil &) = delete;
public: tml::ProcessUtil &operator =(const tml::ProcessUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::ProcessUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::ProcessUtilEngine> &);

	static bool CheckThreadFix(void);
	static tml::Process *Get(void);
	static INT Start(std::unique_ptr<tml::Process> &);
	static void End(const INT exit_code = 0);
	static tml::ProcessUtilEngine::STATE GetState(void);
	static INT GetExitCode(void);
};
}


/**
 * @brief CheckThreadFix関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::ProcessUtil::CheckThreadFix(void)
{
	return (tml::ProcessUtil::th_fix_.Check());
}


/**
 * @brief Get関数
 * @return proc (process)<br>
 * nullptr=失敗
 */
inline tml::Process *tml::ProcessUtil::Get(void)
{
	if (tml::ProcessUtil::engine_ == nullptr) {
		return (nullptr);
	}

	return (tml::ProcessUtil::engine_->Get());
}


/**
 * @brief Start関数
 * @param proc (process)
 * @return res (result)<br>
 * 0未満=失敗
 */
inline INT tml::ProcessUtil::Start(std::unique_ptr<tml::Process> &proc)
{
	if (tml::ProcessUtil::engine_ == nullptr) {
		return (-1);
	}

	return (tml::ProcessUtil::engine_->Start(proc));
}


/**
 * @brief End関数
 * @param exit_code (exit_code)
 */
inline void tml::ProcessUtil::End(const INT exit_code)
{
	if (tml::ProcessUtil::engine_ == nullptr) {
		return;
	}

	tml::ProcessUtil::engine_->End(exit_code);

	return;
}


/**
 * @brief GetState関数
 * @return stat (state)
 */
inline tml::ProcessUtilEngine::STATE tml::ProcessUtil::GetState(void)
{
	if (tml::ProcessUtil::engine_ == nullptr) {
		return (tml::ProcessUtilEngine::STATE());
	}

	return (tml::ProcessUtil::engine_->GetState());
}


/**
 * @brief GetExitCode関数
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
inline INT tml::ProcessUtil::GetExitCode(void)
{
	if (tml::ProcessUtil::engine_ == nullptr) {
		return (0);
	}

	return (tml::ProcessUtil::engine_->GetExitCode());
}
