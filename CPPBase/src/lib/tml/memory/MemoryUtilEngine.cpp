/**
 * @file
 * @brief MemoryUtilEngineコードファイル
 */


#include "MemoryUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::MemoryUtilEngine::MemoryUtilEngine() :
	allocator_type_(tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NONE)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MemoryUtilEngine::~MemoryUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::MemoryUtilEngine::Release(void)
{
	{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
		this->allocator_type_ = tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NONE;
		this->new_allocator_.reset();
		this->dlmalloc_allocator_.reset();
	}

	return;
}


/**
 * @brief Init関数
 */
void tml::MemoryUtilEngine::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create関数
 * @param allocator_type (allocator_type)
 * @param allocator_size (allocator_size)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::MemoryUtilEngine::Create(const tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE allocator_type, const size_t allocator_size)
{
	{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
		this->allocator_type_ = allocator_type;

		switch (this->allocator_type_) {
		case tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NEW: {
			this->new_allocator_ = std::make_unique<tml::NewMemoryAllocator>();

			if (this->new_allocator_->Create() < 0) {
				return (-1);
			}

			break;
		}
		case tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::DLMALLOC: {
			this->dlmalloc_allocator_ = std::make_unique<tml::DlmallocMemoryAllocator>();

			if (this->dlmalloc_allocator_->Create(allocator_size) < 0) {
				return (-1);
			}

			break;
		}
		default: {
			return (-1);
		}
		}
	}

	return (0);
}


/**
 * @brief GetAllocatorInfo関数
 * @return allocator_info (allocator_info)
 */
tml::MemoryAllocator::INFO tml::MemoryUtilEngine::GetAllocatorInfo(void)
{
	tml::MemoryAllocator::INFO allocator_info;

	{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
		switch (this->allocator_type_) {
		case tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NEW: {
			allocator_info = this->new_allocator_->GetInfo();

			break;
		}
		case tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::DLMALLOC: {
			allocator_info = this->dlmalloc_allocator_->GetInfo();

			break;
		}
		}
	}

	return (allocator_info);
}
