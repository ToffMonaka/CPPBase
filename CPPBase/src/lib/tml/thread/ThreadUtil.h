/**
 * @file
 * @brief ThreadUtilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/ThreadFix.h"
#include "ThreadUtilEngine.h"


namespace tml {
/**
 * @brief ThreadUtilクラス
 *
 * ユーティリティパターン<br>
 * エンジンパターン
 */
class ThreadUtil
{
public: ThreadUtil() = delete;
public: ThreadUtil(const tml::ThreadUtil &) = delete;
public: tml::ThreadUtil &operator =(const tml::ThreadUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::ThreadUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::ThreadUtilEngine> &);

	static bool CheckThreadFix(void);
	static tml::Thread *Get(void);
	static INT Start(std::unique_ptr<tml::MainThread> &);
	static INT Start(std::unique_ptr<tml::SubThread> &);
	static INT StartAll(void);
	static void End(const bool finish_flg = false);
	static void EndAll(const bool finish_flg = false);
	static INT GetExitCode(void);
};
}


/**
 * @brief CheckThreadFix関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::ThreadUtil::CheckThreadFix(void)
{
	return (tml::ThreadUtil::th_fix_.Check());
}


/**
 * @brief Get関数
 * @return th (thread)<br>
 * nullptr=失敗
 */
inline tml::Thread *tml::ThreadUtil::Get(void)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return (nullptr);
	}

	return (tml::ThreadUtil::engine_->Get());
}


/**
 * @brief Start関数
 * @param th (thread)
 * @return res (result)<br>
 * 0未満=失敗
 */
inline INT tml::ThreadUtil::Start(std::unique_ptr<tml::MainThread> &th)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return (-1);
	}

	return (tml::ThreadUtil::engine_->Start(th));
}


/**
 * @brief Start関数
 * @param th (thread)
 * @return res (result)<br>
 * 0未満=失敗
 */
inline INT tml::ThreadUtil::Start(std::unique_ptr<tml::SubThread> &th)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return (-1);
	}

	return (tml::ThreadUtil::engine_->Start(th));
}


/**
 * @brief StartAll関数
 * @return res (result)<br>
 * 0未満=失敗
 */
inline INT tml::ThreadUtil::StartAll(void)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return (-1);
	}

	return (tml::ThreadUtil::engine_->StartAll());
}


/**
 * @brief End関数
 * @param finish_flg (finish_flag)
 */
inline void tml::ThreadUtil::End(const bool finish_flg)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return;
	}

	tml::ThreadUtil::engine_->End(finish_flg);

	return;
}


/**
 * @brief EndAll関数
 * @param finish_flg (finish_flg)
 */
inline void tml::ThreadUtil::EndAll(const bool finish_flg)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return;
	}

	tml::ThreadUtil::engine_->EndAll(finish_flg);

	return;
}


/**
 * @brief GetExitCode関数
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
inline INT tml::ThreadUtil::GetExitCode(void)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return (0);
	}

	return (tml::ThreadUtil::engine_->GetExitCode());
}
