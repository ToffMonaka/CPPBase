/**
 * @file
 * @brief DefaultMemoryUtilEngineコードファイル
 */


#include "DefaultMemoryUtilEngine.h"


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
 * @brief Release関数
 */
void tml::DefaultMemoryUtilEngine::Release(void)
{
	tml::MemoryUtilEngine::Release();

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
 * @param allocator_type (allocator_type)
 * @param allocator_size (allocator_size)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultMemoryUtilEngine::Create(const tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE allocator_type, const size_t allocator_size)
{
	this->Init();

	if (tml::MemoryUtilEngine::Create(allocator_type, allocator_size) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
