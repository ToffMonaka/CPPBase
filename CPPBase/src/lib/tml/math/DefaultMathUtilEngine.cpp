/**
 * @file
 * @brief DefaultMathUtilEngineコードファイル
 */


#include "DefaultMathUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultMathUtilEngineDesc::DefaultMathUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultMathUtilEngineDesc::~DefaultMathUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultMathUtilEngineDesc::Init(void)
{
	this->Release();

	tml::MathUtilEngineDesc::Init();

	return;
}


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
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultMathUtilEngine::Create(const tml::DefaultMathUtilEngineDesc &desc)
{
	this->Init();

	if (tml::MathUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
