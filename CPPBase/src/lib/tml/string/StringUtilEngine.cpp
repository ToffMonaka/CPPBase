/**
 * @file
 * @brief StringUtilEngineコードファイル
 */


#include "StringUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::StringUtilEngine::StringUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::StringUtilEngine::~StringUtilEngine()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::StringUtilEngine::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::StringUtilEngine::Init(void)
{
	this->local_name_.clear();

	return;
}


/**
 * @brief Create関数
 * @param local_name (local_name)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::StringUtilEngine::Create(const CHAR *local_name)
{
	this->local_name_ = local_name;

	return (0);
}
