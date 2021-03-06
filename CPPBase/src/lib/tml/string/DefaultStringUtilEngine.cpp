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
 * @param locale_name (locale_name)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultStringUtilEngine::Create(const CHAR *locale_name)
{
	this->Init();

	if (tml::StringUtilEngine::Create(locale_name) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
