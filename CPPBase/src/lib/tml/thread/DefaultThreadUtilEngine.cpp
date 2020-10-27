/**
 * @file
 * @brief DefaultThreadUtilEngineコードファイル
 */


#include "DefaultThreadUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultThreadUtilEngine::DefaultThreadUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultThreadUtilEngine::~DefaultThreadUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::DefaultThreadUtilEngine::Release(void)
{
	tml::ThreadUtilEngine::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultThreadUtilEngine::Init(void)
{
	this->Release();

	tml::ThreadUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultThreadUtilEngine::Create(void)
{
	this->Release();

	if (tml::ThreadUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
