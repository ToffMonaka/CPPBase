/**
 * @file
 * @brief MemoryAllocatorヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_MEMORY.h"


namespace tml {
/**
 * @brief MemoryAllocatorクラス
 *
 * インターフェースパターン
 */
class MemoryAllocator
{
public: MemoryAllocator(const tml::MemoryAllocator &) = delete;
public: tml::MemoryAllocator &operator =(const tml::MemoryAllocator &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	/**
	 * @brief INFO構造体
	 */
	typedef struct INFO_
	{
		tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE type;
		size_t size;
		size_t use_size;
		size_t use_cnt;

		/**
		 * @brief コンストラクタ
		 */
		INFO_() :
			type(tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NONE),
			size(0U),
			use_size(0U),
			use_cnt(0U)
		{
			return;
		}
	} INFO;

private:
	tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE type_;

protected:
	void Release(void);
	INT Create(const tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE);

public:
	MemoryAllocator();
	virtual ~MemoryAllocator();

	virtual void Init(void);

	tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE GetType(void) const;
	virtual tml::MemoryAllocator::INFO GetInfo(void);
};
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE tml::MemoryAllocator::GetType(void) const
{
	return (this->type_);
}
