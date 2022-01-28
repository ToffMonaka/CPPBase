/**
 * @file
 * @brief DefaultStringUtilEngineコードファイル
 */


#include "DefaultStringUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultStringUtilEngineDesc::DefaultStringUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultStringUtilEngineDesc::~DefaultStringUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultStringUtilEngineDesc::Init(void)
{
	this->Release();

	tml::StringUtilEngineDesc::Init();

	return;
}


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
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultStringUtilEngine::Create(const tml::DefaultStringUtilEngineDesc &desc)
{
	this->Init();

	if (tml::StringUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
