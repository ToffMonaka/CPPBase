/**
 * @file
 * @brief DlmallocAllocator�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "Allocator.h"


namespace tml {
/**
 * @brief DlmallocAllocator�N���X
 */
class DlmallocAllocator : public tml::Allocator
{
public: DlmallocAllocator(const DlmallocAllocator &) = delete;
public: DlmallocAllocator &operator =(const DlmallocAllocator &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

public:
	DlmallocAllocator();
	virtual ~DlmallocAllocator();

	virtual void Init(void);
	INT Create(void);
};
}
