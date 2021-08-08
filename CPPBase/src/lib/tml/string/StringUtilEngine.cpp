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
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::StringUtilEngine::Init(void)
{
	this->Release();

	this->locale_name_.clear();

	return;
}


/**
 * @brief Create関数
 * @param locale_name (locale_name)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::StringUtilEngine::Create(const CHAR *locale_name)
{
	this->locale_name_ = locale_name;

	return (0);
}
