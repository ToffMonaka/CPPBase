/**
 * @file
 * @brief RandomUtilEngineコードファイル
 */


#include "RandomUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::RandomUtilEngineDesc::RandomUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::RandomUtilEngineDesc::~RandomUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::RandomUtilEngineDesc::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::RandomUtilEngine::RandomUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::RandomUtilEngine::~RandomUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::RandomUtilEngine::Init(void)
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
INT tml::RandomUtilEngine::Create(const tml::RandomUtilEngineDesc &desc)
{
	return (0);
}
