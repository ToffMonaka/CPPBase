/**
 * @file
 * @brief DefaultThreadUtilEngineコードファイル
 */


#include "DefaultThreadUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::DefaultThreadUtilEngineDesc::DefaultThreadUtilEngineDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultThreadUtilEngineDesc::~DefaultThreadUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultThreadUtilEngineDesc::Init(void)
{
	this->Release();

	tml::ThreadUtilEngineDesc::Init();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::DefaultThreadUtilEngine::DefaultThreadUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DefaultThreadUtilEngine::~DefaultThreadUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultThreadUtilEngine::Init(void)
{
	this->Release();

	tml::ThreadUtilEngine::Init();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultThreadUtilEngine::Create(const tml::DefaultThreadUtilEngineDesc &desc)
{
	this->Init();

	if (tml::ThreadUtilEngine::Create(desc) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
