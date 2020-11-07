/**
 * @file
 * @brief MathUtilコードファイル
 */


#include "MathUtil.h"


tml::ThreadFix tml::MathUtil::th_fix_;
std::unique_ptr<tml::MathUtilEngine> tml::MathUtil::engine_;


/**
 * @brief Init関数
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
 * @brief Create関数
 * @param engine (engine)
 * @return res (result)<br>
 * 0未満=失敗
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
