/**
 * @file
 * @brief DefaultMemoryUtilEngineコードファイル
 */


#include "DefaultMemoryUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultMemoryUtilEngine::DefaultMemoryUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultMemoryUtilEngine::~DefaultMemoryUtilEngine()
{
	this->Init();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultMemoryUtilEngine::Init(void)
{
	tml::MemoryUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultMemoryUtilEngine::Create(void)
{
	if (tml::MemoryUtilEngine::Create() < 0) {
		return (-1);
	}

	return (0);
}
