/**
 * @file
 * @brief TimeUtilヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "TimeUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief TimeUtilクラス
 *
 * ユーティリティパターン<br>
 * エンジンパターン
 */
class TimeUtil
{
public: TimeUtil() = delete;
public: TimeUtil(const TimeUtil &) = delete;
public: TimeUtil &operator =(const TimeUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::TimeUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::TimeUtilEngine> &);

	static TIME_REAL Sleep(const TIME_REAL &);
	static TIME_REAL Wait(const TIME_REAL &);
};
}
