/**
 * @file
 * @brief DefaultFileUtilEngineコードファイル
 */


#include "DefaultFileUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultFileUtilEngineDesc::DefaultFileUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultFileUtilEngineDesc::~DefaultFileUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultFileUtilEngineDesc::Init(void)
{
	this->Release();

	tml::FileUtilEngineDesc::Init();

	return;
}


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
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultFileUtilEngine::Create(const tml::DefaultFileUtilEngineDesc &desc)
{
	this->Init();

	if (tml::FileUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
