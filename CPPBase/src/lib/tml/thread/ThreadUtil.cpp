/**
 * @file
 * @brief ThreadUtilコードファイル
 */


#include "ThreadUtil.h"


tml::ThreadFix tml::ThreadUtil::th_fix_;
std::unique_ptr<tml::ThreadUtilEngine> tml::ThreadUtil::engine_;


/**
 * @brief Init関数
 */
void tml::ThreadUtil::Init(void)
{
	if (!tml::ThreadUtil::th_fix_.Check()) {
		return;
	}

	tml::ThreadUtil::engine_.reset();

	return;
}


/**
 * @brief Create関数
 * @param engine (engine)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ThreadUtil::Create(std::unique_ptr<tml::ThreadUtilEngine> &engine)
{
	if (!tml::ThreadUtil::th_fix_.Check()) {
		tml::ThreadUtil::Init();

		return (-1);
	}

	tml::ThreadUtil::Init();

	tml::ThreadUtil::engine_ = std::move(engine);

	return (0);
}
