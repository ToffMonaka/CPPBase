/**
 * @file
 * @brief TimeUtilEngineコードファイル
 */


#include "TimeUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::TimeUtilEngineDesc::TimeUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::TimeUtilEngineDesc::~TimeUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::TimeUtilEngineDesc::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::TimeUtilEngine::TimeUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::TimeUtilEngine::~TimeUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::TimeUtilEngine::Init(void)
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
INT tml::TimeUtilEngine::Create(const tml::TimeUtilEngineDesc &desc)
{
	return (0);
}
