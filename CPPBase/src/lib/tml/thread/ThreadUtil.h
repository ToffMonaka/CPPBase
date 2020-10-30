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

	static tml::Thread *Get(void);
	static INT Start(std::unique_ptr<tml::Thread> &);
	static void End(void);
	static void EndAll(void);
	static tml::ThreadUtilEngine::STATE GetState(void);
};


/**
 * @brief Get関数
 * @return th (thread)<br>
 * NULLP=失敗
 */
inline tml::Thread *tml::ThreadUtil::Get(void)
{
	return (tml::ThreadUtil::engine_->Get());
}


/**
 * @brief Start関数
 * @param th (thread)
 * @return res (result)<br>
 * 0未満=失敗
 */
inline INT tml::ThreadUtil::Start(std::unique_ptr<tml::Thread> &th)
{
	if (!tml::ThreadUtil::th_fix_.Check()) {
		return (-1);
	}

	return (tml::ThreadUtil::engine_->Start(th));
}


/**
 * @brief End関数
 */
inline void tml::ThreadUtil::End(void)
{
	tml::ThreadUtil::engine_->End();

	return;
}


/**
 * @brief EndAll関数
 */
inline void tml::ThreadUtil::EndAll(void)
{
	tml::ThreadUtil::engine_->EndAll();

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
}
