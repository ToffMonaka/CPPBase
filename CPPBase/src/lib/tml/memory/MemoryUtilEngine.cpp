/**
 * @file
 * @brief MemoryUtilEngine�R�[�h�t�@�C��
 */


#include "MemoryUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::MemoryUtilEngine::MemoryUtilEngine() :
	allocator_type_(tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::MemoryUtilEngine::~MemoryUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
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
 * @brief Init�֐�
 */
void tml::MemoryUtilEngine::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief Create�֐�
 * @param allocator_type (allocator_type)
 * @param allocator_size (allocator_size)
 * @return result (result)<br>
 * 0����=���s
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
 * @brief GetAllocatorInfo�֐�
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
