/**
 * @file
 * @brief StringUtilEngineコードファイル
 */


#include "StringUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::StringUtilEngineDesc::StringUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::StringUtilEngineDesc::~StringUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::StringUtilEngineDesc::Init(void)
{
	this->Release();

	this->locale_name.clear();

	return;
}


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
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::StringUtilEngine::Create(const tml::StringUtilEngineDesc &desc)
{
	this->locale_name_ = desc.locale_name;

	return (0);
}
