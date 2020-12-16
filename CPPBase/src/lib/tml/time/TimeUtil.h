/**
 * @file
 * @brief TimeUtilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/ThreadFix.h"
#include "TimeUtilEngine.h"


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
public: TimeUtil(const tml::TimeUtil &) = delete;
public: tml::TimeUtil &operator =(const tml::TimeUtil &) = delete;

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
