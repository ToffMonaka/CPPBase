/**
 * @file
 * @brief DefaultRandomUtilEngineコードファイル
 */


#include "DefaultRandomUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultRandomUtilEngineDesc::DefaultRandomUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultRandomUtilEngineDesc::~DefaultRandomUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultRandomUtilEngineDesc::Init(void)
{
	this->Release();

	tml::RandomUtilEngineDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::DefaultRandomUtilEngine::DefaultRandomUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultRandomUtilEngine::~DefaultRandomUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultRandomUtilEngine::Init(void)
{
	this->Release();

	tml::RandomUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultRandomUtilEngine::Create(const tml::DefaultRandomUtilEngineDesc &desc)
{
	this->Init();

	if (tml::RandomUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
