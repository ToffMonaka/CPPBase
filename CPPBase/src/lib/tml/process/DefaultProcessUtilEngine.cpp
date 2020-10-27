/**
 * @file
 * @brief DefaultProcessUtilEngineコードファイル
 */


#include "DefaultProcessUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultProcessUtilEngine::DefaultProcessUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultProcessUtilEngine::~DefaultProcessUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::DefaultProcessUtilEngine::Release(void)
{
	tml::ProcessUtilEngine::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultProcessUtilEngine::Init(void)
{
	this->Release();

	tml::ProcessUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultProcessUtilEngine::Create(void)
{
	this->Release();

	if (tml::ProcessUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
