/**
 * @file
 * @brief MallocAllocatorヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "Allocator.h"


namespace tml {
/**
 * @brief MallocAllocatorクラス
 */
class MallocAllocator : public tml::Allocator
{
public: MallocAllocator(const MallocAllocator &) = delete;
public: MallocAllocator &operator =(const MallocAllocator &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	MallocAllocator();
	virtual ~MallocAllocator();

	virtual void Init(void);
	INT Create(void);
};
}
