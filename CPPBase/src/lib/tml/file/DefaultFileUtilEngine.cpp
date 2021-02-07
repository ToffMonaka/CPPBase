/**
 * @file
 * @brief DefaultFileUtilEngineコードファイル
 */


#include "DefaultFileUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultFileUtilEngine::DefaultFileUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultFileUtilEngine::~DefaultFileUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultFileUtilEngine::Init(void)
{
	this->Release();

	tml::FileUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultFileUtilEngine::Create(void)
{
	this->Init();

	if (tml::FileUtilEngine::Create() < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
