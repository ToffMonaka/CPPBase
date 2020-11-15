/**
 * @file
 * @brief RandomUtilEngineコードファイル
 */


#include "RandomUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::RandomUtilEngine::RandomUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::RandomUtilEngine::~RandomUtilEngine()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::RandomUtilEngine::Release(void)
{
	{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
		this->seed_.Init();
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::RandomUtilEngine::Init(void)
{
	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::RandomUtilEngine::Create(void)
{
	{tml::ThreadLockBlock th_lock_block(this->seed_th_lock_);
		if (this->seed_.Create() < 0) {
			return (-1);
		}
	}

	return (0);
}
