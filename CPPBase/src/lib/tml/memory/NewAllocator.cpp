/**
 * @file
 * @brief NewAllocatorコードファイル
 */


#include "NewAllocator.h"


/**
 * @brief コンストラクタ
 */
tml::NewAllocator::NewAllocator()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::NewAllocator::~NewAllocator()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::NewAllocator::Init(void)
{
	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::NewAllocator::Create(void)
{
	if (tml::Allocator::Create() < 0) {
		return (-1);
	}

	return (0);
}
