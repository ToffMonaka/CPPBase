/**
 * @file
 * @brief DefaultTimeUtilEngineコードファイル
 */


#include "DefaultTimeUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultTimeUtilEngineDesc::DefaultTimeUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultTimeUtilEngineDesc::~DefaultTimeUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultTimeUtilEngineDesc::Init(void)
{
	this->Release();

	tml::TimeUtilEngineDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::DefaultTimeUtilEngine::DefaultTimeUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultTimeUtilEngine::~DefaultTimeUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultTimeUtilEngine::Init(void)
{
	this->Release();

	tml::TimeUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultTimeUtilEngine::Create(const tml::DefaultTimeUtilEngineDesc &desc)
{
	this->Init();

	if (tml::TimeUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
