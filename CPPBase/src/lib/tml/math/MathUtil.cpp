/**
 * @file
 * @brief MathUtil�R�[�h�t�@�C��
 */


#include "MathUtil.h"


tml::ThreadFix tml::MathUtil::th_fix_;
std::unique_ptr<tml::MathUtilEngine> tml::MathUtil::engine_;


/**
 * @brief Init�֐�
 */
void tml::MathUtil::Init(void)
{
	if (!tml::MathUtil::th_fix_.Check()) {
		return;
	}

	tml::MathUtil::engine_.reset();

	return;
}


/**
 * @brief Create�֐�
 * @param engine (engine)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::MathUtil::Create(std::unique_ptr<tml::MathUtilEngine> &engine)
{
	if (!tml::MathUtil::th_fix_.Check()) {
		tml::MathUtil::Init();

		return (-1);
	}

	tml::MathUtil::Init();

	tml::MathUtil::engine_ = std::move(engine);

	return (0);
}


/**
 * @brief Sleep�֐�
 *
 * �G���W���s�v
 *
 * @param time (time)
 * @return elapsed_time (elapsed_time)
 */
TIME_REAL tml::MathUtil::Sleep(const TIME_REAL &time)
{
	if (time.count() <= 0.0) {
		return (TIME_REAL(0.0));
	}

	auto start_time = std::chrono::high_resolution_clock::now();

	std::this_thread::sleep_for(time);

	return (std::chrono::duration_cast<TIME_REAL >(std::chrono::high_resolution_clock::now() - start_time));
}


/**
 * @brief Wait�֐�
 *
 * �G���W���s�v
 *
 * @param time (time)
 * @return elapsed_time (elapsed_time)
 */
TIME_REAL tml::MathUtil::Wait(const TIME_REAL &time)
{
	if (time.count() <= 0.0) {
		return (TIME_REAL(0.0));
	}

	auto start_time = std::chrono::high_resolution_clock::now();

	while ((std::chrono::duration_cast<TIME_REAL >(std::chrono::high_resolution_clock::now() - start_time)).count() < time.count()) {
	}

	return (std::chrono::duration_cast<TIME_REAL >(std::chrono::high_resolution_clock::now() - start_time));
}
