/**
 * @file
 * @brief TimeUtilコードファイル
 */


#include "TimeUtil.h"


std::unique_ptr<tml::TimeUtilEngine> tml::TimeUtil::engine_;


/**
 * @brief Init関数
 */
void tml::TimeUtil::Init(void)
{
	if (!tml::TimeUtil::CheckFixedThread()) {
		return;
	}

	tml::TimeUtil::engine_.reset();

	return;
}


/**
 * @brief Create関数
 * @param engine (engine)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::TimeUtil::Create(std::unique_ptr<tml::TimeUtilEngine> &engine)
{
	if (!tml::TimeUtil::CheckFixedThread()) {
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
 * Create関数不要
 *
 * @param time (time)
 * @return elapsed_time (elapsed_time)
 */
tml::TIME_REAL tml::TimeUtil::Sleep(const tml::TIME_REAL &time)
{
	if (time.count() <= 0.0) {
		return (tml::TIME_REAL(0.0));
	}

	auto start_time = std::chrono::steady_clock::now();

	std::this_thread::sleep_for(time);

	return (tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - start_time));
}


/**
 * @brief Wait関数
 *
 * Create関数不要
 *
 * @param time (time)
 * @return elapsed_time (elapsed_time)
 */
tml::TIME_REAL tml::TimeUtil::Wait(const tml::TIME_REAL &time)
{
	if (time.count() <= 0.0) {
		return (tml::TIME_REAL(0.0));
	}

	auto start_time = std::chrono::steady_clock::now();

	while ((tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - start_time)).count() < time.count()) {
	}

	return (tml::CastTime<tml::TIME_REAL>(std::chrono::steady_clock::now() - start_time));
}
