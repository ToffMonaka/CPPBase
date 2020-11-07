/**
 * @file
 * @brief TimeUtilコードファイル
 */


#include "TimeUtil.h"


tml::ThreadFix tml::TimeUtil::th_fix_;
std::unique_ptr<tml::TimeUtilEngine> tml::TimeUtil::engine_;


/**
 * @brief Init関数
 */
void tml::TimeUtil::Init(void)
{
	if (!tml::TimeUtil::th_fix_.Check()) {
		return;
	}

	tml::TimeUtil::engine_.reset();

	return;
}


/**
 * @brief Create関数
 * @param engine (engine)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::TimeUtil::Create(std::unique_ptr<tml::TimeUtilEngine> &engine)
{
	if (!tml::TimeUtil::th_fix_.Check()) {
		tml::TimeUtil::Init();

		return (-1);
	}

	tml::TimeUtil::Init();

	tml::TimeUtil::engine_ = std::move(engine);

	return (0);
}


/**
 * @brief Sleep関数
 *
 * エンジン不要
 *
 * @param time (time)
 * @return elapsed_time (elapsed_time)
 */
TIME_REAL tml::TimeUtil::Sleep(const TIME_REAL &time)
{
	if (time.count() <= 0.0) {
		return (TIME_REAL(0.0));
	}

	auto start_time = std::chrono::steady_clock::now();

	std::this_thread::sleep_for(time);

	return (tml::TimeCast<TIME_REAL>(std::chrono::steady_clock::now() - start_time));
}


/**
 * @brief Wait関数
 *
 * エンジン不要
 *
 * @param time (time)
 * @return elapsed_time (elapsed_time)
 */
TIME_REAL tml::TimeUtil::Wait(const TIME_REAL &time)
{
	if (time.count() <= 0.0) {
		return (TIME_REAL(0.0));
	}

	auto start_time = std::chrono::steady_clock::now();

	while ((tml::TimeCast<TIME_REAL>(std::chrono::steady_clock::now() - start_time)).count() < time.count()) {
	}

	return (tml::TimeCast<TIME_REAL>(std::chrono::steady_clock::now() - start_time));
}
