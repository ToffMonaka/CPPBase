/**
 * @file
 * @brief MathUtilEngineコードファイル
 */


#include "MathUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::MathUtilEngineDesc::MathUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MathUtilEngineDesc::~MathUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::MathUtilEngineDesc::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::MathUtilEngine::MathUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MathUtilEngine::~MathUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::MathUtilEngine::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::MathUtilEngine::Create(const tml::MathUtilEngineDesc &desc)
{
	return (0);
}
