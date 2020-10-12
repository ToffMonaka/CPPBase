/**
 * @file
 * @brief NewAllocatorヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "Allocator.h"


namespace tml {
/**
 * @brief NewAllocatorクラス
 */
class NewAllocator : public tml::Allocator
{
public: NewAllocator(const NewAllocator &) = delete;
public: NewAllocator &operator =(const NewAllocator &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	NewAllocator();
	virtual ~NewAllocator();

	virtual void Init(void);
	INT Create(void);
};
}
