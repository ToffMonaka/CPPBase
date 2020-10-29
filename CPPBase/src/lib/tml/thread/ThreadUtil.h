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

	static INT Start(std::unique_ptr<tml::Thread> &);
	void End(void);
	void EndAll(void);
};


/**
 * @brief Start関数
 * @param th (thread)
 * @return res (result)<br>
 * 0未満=失敗
 */
inline INT tml::ThreadUtil::Start(std::unique_ptr<tml::Thread> &th)
{
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
}
