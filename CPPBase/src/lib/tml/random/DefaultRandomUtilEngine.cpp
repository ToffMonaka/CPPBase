/**
 * @file
 * @brief DefaultRandomUtilEngineコードファイル
 */


#include "DefaultRandomUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultRandomUtilEngine::DefaultRandomUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultRandomUtilEngine::~DefaultRandomUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultRandomUtilEngine::Init(void)
{
	this->Release();

	tml::RandomUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultRandomUtilEngine::Create(void)
{
	this->Init();

	if (tml::RandomUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
