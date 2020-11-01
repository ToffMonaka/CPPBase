/**
 * @file
 * @brief ThreadFixヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "SpinThreadLock.h"


namespace tml {
/**
 * @brief ThreadFixクラス
 */
class ThreadFix
{
public: ThreadFix(const ThreadFix &) = delete;
public: ThreadFix &operator =(const ThreadFix &) = delete;

private:
	std::thread::id th_id_;
	tml::SpinThreadLock th_lock_;

public:
	ThreadFix();
	virtual ~ThreadFix();

	bool Check(void);
};
}
