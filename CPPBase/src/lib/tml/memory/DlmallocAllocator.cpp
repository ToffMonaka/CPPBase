/**
 * @file
 * @brief DlmallocAllocatorコードファイル
 */


#include "DlmallocAllocator.h"


/**
 * @brief コンストラクタ
 */
tml::DlmallocAllocator::DlmallocAllocator()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DlmallocAllocator::~DlmallocAllocator()
{
	return;
}


/**
 * @brief Init関数
 */
void tml::DlmallocAllocator::Init(void)
{
	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DlmallocAllocator::Create(void)
{
	if (tml::Allocator::Create() < 0) {
		return (-1);
	}

	return (0);
}
