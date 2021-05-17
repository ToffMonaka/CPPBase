/**
 * @file
 * @brief FixedThreadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "SpinThreadLock.h"


namespace tml {
/**
 * @brief FixedThreadクラス
 */
class FixedThread
{
public: FixedThread(const tml::FixedThread &) = delete;
public: tml::FixedThread &operator =(const tml::FixedThread &) = delete;

private:
	std::thread::id th_id_;
	tml::SpinThreadLock th_lock_;

public:
	FixedThread();
	virtual ~FixedThread();

	bool Check(void);
};
}
