/**
 * @file
 * @brief FileUtilコードファイル
 */


#include "FileUtil.h"


std::unique_ptr<tml::FileUtilEngine> tml::FileUtil::engine_;
tml::MutexThreadLock tml::FileUtil::file_th_lock_;
tml::MutexThreadLock tml::FileUtil::dir_th_lock_;


/**
 * @brief Init関数
 */
void tml::FileUtil::Init(void)
{
	if (!tml::FileUtil::CheckFixedThread()) {
		return;
	}

	tml::FileUtil::engine_.reset();

	return;
}


/**
 * @brief Create関数
 * @param engine (engine)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::FileUtil::Create(std::unique_ptr<tml::FileUtilEngine> &engine)
{
	if (!tml::FileUtil::CheckFixedThread()) {
		tml::FileUtil::Init();

		return (-1);
	}

	tml::FileUtil::Init();

	tml::FileUtil::engine_ = std::move(engine);

	return (0);
}
