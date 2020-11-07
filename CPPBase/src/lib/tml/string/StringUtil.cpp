/**
 * @file
 * @brief StringUtilコードファイル
 */


#include "StringUtil.h"


tml::ThreadFix tml::StringUtil::th_fix_;
std::unique_ptr<tml::StringUtilEngine> tml::StringUtil::engine_;


/**
 * @brief Init関数
 */
void tml::StringUtil::Init(void)
{
	if (!tml::StringUtil::th_fix_.Check()) {
		return;
	}

	tml::StringUtil::engine_.reset();

	return;
}


/**
 * @brief Create関数
 * @param engine (engine)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::StringUtil::Create(std::unique_ptr<tml::StringUtilEngine> &engine)
{
	if (!tml::StringUtil::th_fix_.Check()) {
		tml::StringUtil::Init();

		return (-1);
	}

	tml::StringUtil::Init();

	tml::StringUtil::engine_ = std::move(engine);

	return (0);
}
