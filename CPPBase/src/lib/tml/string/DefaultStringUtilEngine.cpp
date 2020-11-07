/**
 * @file
 * @brief DefaultStringUtilEngineコードファイル
 */


#include "DefaultStringUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultStringUtilEngine::DefaultStringUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultStringUtilEngine::~DefaultStringUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::DefaultStringUtilEngine::Release(void)
{
	tml::StringUtilEngine::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultStringUtilEngine::Init(void)
{
	this->Release();

	tml::StringUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultStringUtilEngine::Create(void)
{
	this->Release();

	if (tml::StringUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
