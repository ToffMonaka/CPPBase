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

	static bool CheckThreadFix(void);
	static tml::TIME_REAL Sleep(const tml::TIME_REAL &);
	static tml::TIME_REAL Wait(const tml::TIME_REAL &);
};
}


/**
 * @brief CheckThreadFix関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::TimeUtil::CheckThreadFix(void)
{
	return (tml::TimeUtil::th_fix_.Check());
}
