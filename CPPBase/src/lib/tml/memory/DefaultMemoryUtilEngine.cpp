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
	this->allocator_th_lock_.Lock();

	tml::MemoryUtilEngine::Release();

	this->allocator_th_lock_.Unlock();

	return;
}


/**
 * @brief Init関数
 */
void tml::DefaultMemoryUtilEngine::Init(void)
{
	this->allocator_th_lock_.Lock();

	this->Release();

	tml::MemoryUtilEngine::Init();

	this->allocator_th_lock_.Unlock();

	return;
}


/**
 * @brief Create関数
 * @param allocator_type (allocator_type)
 * @param allocator_size (allocator_size)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DefaultMemoryUtilEngine::Create(const tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE allocator_type, const size_t allocator_size)
{
	this->allocator_th_lock_.Lock();

	this->Release();

	if (tml::MemoryUtilEngine::Create(allocator_type, allocator_size) < 0) {
		this->Init();

		this->allocator_th_lock_.Unlock();

		return (-1);
	}

	this->allocator_th_lock_.Unlock();

	return (0);
}
