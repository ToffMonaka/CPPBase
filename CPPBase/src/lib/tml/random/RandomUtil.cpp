/**
 * @file
 * @brief RandomUtilコードファイル
 */


#include "RandomUtil.h"


tml::ThreadFix tml::RandomUtil::th_fix_;
std::unique_ptr<tml::RandomUtilEngine> tml::RandomUtil::engine_;
tml::RandomSeed tml::RandomUtil::seed_;
tml::SpinThreadLock tml::RandomUtil::seed_th_lock_;


/**
 * @brief Init関数
 */
void tml::RandomUtil::Init(void)
{
	if (!tml::RandomUtil::th_fix_.Check()) {
		return;
	}

	tml::RandomUtil::engine_.reset();

	return;
}


/**
 * @brief Create関数
 * @param engine (engine)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::RandomUtil::Create(std::unique_ptr<tml::RandomUtilEngine> &engine)
{
	if (!tml::RandomUtil::th_fix_.Check()) {
		tml::RandomUtil::Init();

		return (-1);
	}

	tml::RandomUtil::Init();

	tml::RandomUtil::engine_ = std::move(engine);

	return (0);
}
