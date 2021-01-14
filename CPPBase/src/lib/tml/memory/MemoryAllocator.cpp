/**
 * @file
 * @brief MemoryAllocatorコードファイル
 */


#include "MemoryAllocator.h"


/**
 * @brief コンストラクタ
 */
tml::MemoryAllocator::MemoryAllocator() :
	type_(tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MemoryAllocator::~MemoryAllocator()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::MemoryAllocator::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
void tml::MemoryAllocator::Init(void)
{
	this->type_ = tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NONE;

	return;
}


/**
 * @brief Create関数
 * @param type (type)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::MemoryAllocator::Create(const tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE type)
{
	if (type == tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NONE) {
		return (-1);
	}

	this->type_ = type;

	return (0);
}


/**
 * @brief GetInfo関数
 * @return info (info)
 */
tml::MemoryAllocator::INFO tml::MemoryAllocator::GetInfo(void)
{
	tml::MemoryAllocator::INFO info;

	info.type = this->type_;

	return (info);
}
