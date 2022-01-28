/**
 * @file
 * @brief DefaultMemoryUtilEngineコードファイル
 */


#include "DefaultMemoryUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultMemoryUtilEngineDesc::DefaultMemoryUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultMemoryUtilEngineDesc::~DefaultMemoryUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultMemoryUtilEngineDesc::Init(void)
{
	this->Release();

	tml::MemoryUtilEngineDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::DefaultMemoryUtilEngine::DefaultMemoryUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultMemoryUtilEngine::~DefaultMemoryUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultMemoryUtilEngine::Init(void)
{
	this->Release();

	tml::MemoryUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultMemoryUtilEngine::Create(const tml::DefaultMemoryUtilEngineDesc &desc)
{
	this->Init();

	if (tml::MemoryUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
