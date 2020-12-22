/**
 * @file
 * @brief DefaultMathUtilEngineコードファイル
 */


#include "DefaultMathUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultMathUtilEngine::DefaultMathUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultMathUtilEngine::~DefaultMathUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::DefaultMathUtilEngine::Release(void)
{
	tml::MathUtilEngine::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultMathUtilEngine::Init(void)
{
	this->Release();

	tml::MathUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultMathUtilEngine::Create(void)
{
	this->Init();

	if (tml::MathUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
