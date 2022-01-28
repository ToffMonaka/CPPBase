/**
 * @file
 * @brief FileUtilEngineコードファイル
 */


#include "FileUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::FileUtilEngineDesc::FileUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::FileUtilEngineDesc::~FileUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::FileUtilEngineDesc::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::FileUtilEngine::FileUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::FileUtilEngine::~FileUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::FileUtilEngine::Init(void)
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
INT tml::FileUtilEngine::Create(const tml::FileUtilEngineDesc &desc)
{
	return (0);
}
