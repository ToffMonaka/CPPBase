/**
 * @file
 * @brief MemoryUtilコードファイル
 */


#include "MemoryUtil.h"


tml::ThreadFix tml::MemoryUtil::th_fix_;
std::unique_ptr<tml::MemoryUtilEngine> tml::MemoryUtil::engine_;


/**
 * @brief Release関数
 */
void tml::MemoryUtil::Release(void)
{
	tml::MemoryUtil::engine_.reset();

	return;
}


/**
 * @brief Init関数
 */
void tml::MemoryUtil::Init(void)
{
	if (!tml::MemoryUtil::th_fix_.Check()) {
		return;
	}

	tml::MemoryUtil::Release();

	return;
}


/**
 * @brief Create関数
 * @param engine (engine)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::MemoryUtil::Create(std::unique_ptr<tml::MemoryUtilEngine> &engine)
{
	if (!tml::MemoryUtil::th_fix_.Check()) {
		tml::MemoryUtil::Init();

		return (-1);
	}

	tml::MemoryUtil::Release();

	tml::MemoryUtil::engine_ = std::move(engine);

	return (0);
}
