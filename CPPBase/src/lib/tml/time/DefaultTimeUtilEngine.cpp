/**
 * @file
 * @brief DefaultTimeUtilEngineコードファイル
 */


#include "DefaultTimeUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultTimeUtilEngine::DefaultTimeUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultTimeUtilEngine::~DefaultTimeUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultTimeUtilEngine::Init(void)
{
	this->Release();

	tml::TimeUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultTimeUtilEngine::Create(void)
{
	this->Init();

	if (tml::TimeUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
