/**
 * @file
 * @brief ThreadUtilヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "ThreadUtilEngine.h"
#include "../thread/ThreadFix.h"


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
public: ThreadUtil(const ThreadUtil &) = delete;
public: ThreadUtil &operator =(const ThreadUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::ThreadUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::ThreadUtilEngine> &);

	static bool CheckThreadFix(void);
	static tml::Thread *Get(void);
	static INT Start(std::unique_ptr<tml::Thread> &, const bool ready_flg = false);
	static INT StartAll(void);
	static void End(const bool finish_flg = false);
	static void EndAll(const bool delete_flg = false);
	static tml::ThreadUtilEngine::STATE GetState(void);
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
	return (tml::ThreadUtil::engine_->Get());
}


/**
 * @brief Start関数
 * @param th (thread)
 * @param ready_flg (ready_flag)
 * @return res (result)<br>
 * 0未満=失敗
 */
inline INT tml::ThreadUtil::Start(std::unique_ptr<tml::Thread> &th, const bool ready_flg)
{
	return (tml::ThreadUtil::engine_->Start(th, ready_flg));
}


/**
 * @brief StartAll関数
 * @return res (result)<br>
 * 0未満=失敗
 */
inline INT tml::ThreadUtil::StartAll(void)
{
	return (tml::ThreadUtil::engine_->StartAll());
}


/**
 * @brief End関数
 * @param finish_flg (finish_flag)
 */
inline void tml::ThreadUtil::End(const bool finish_flg)
{
	tml::ThreadUtil::engine_->End(finish_flg);

	return;
}


/**
 * @brief EndAll関数
 * @param delete_flg (delete_flag)
 */
inline void tml::ThreadUtil::EndAll(const bool delete_flg)
{
	tml::ThreadUtil::engine_->EndAll(delete_flg);

	return;
}


/**
 * @brief GetState関数
 * @return stat (state)
 */
inline tml::ThreadUtilEngine::STATE tml::ThreadUtil::GetState(void)
{
	return (tml::ThreadUtil::engine_->GetState());
}
