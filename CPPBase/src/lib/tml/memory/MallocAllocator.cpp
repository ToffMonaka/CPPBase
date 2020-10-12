/**
 * @file
 * @brief MallocAllocatorコードファイル
 */


#include "MallocAllocator.h"


/**
 * @brief コンストラクタ
 */
tml::MallocAllocator::MallocAllocator()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MallocAllocator::~MallocAllocator()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::MallocAllocator::Init(void)
{
	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::MallocAllocator::Create(void)
{
	if (tml::Allocator::Create() < 0) {
		return (-1);
	}

	return (0);
}
