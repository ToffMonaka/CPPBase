/**
 * @file
 * @brief MemoryUtilEngine�R�[�h�t�@�C��
 */


#include "MemoryUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::MemoryUtilEngine::MemoryUtilEngine() :
	allocator_type_(tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NONE),
	new_allocator_(nullptr),
	dlmalloc_allocator_(nullptr)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::MemoryUtilEngine::~MemoryUtilEngine()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::MemoryUtilEngine::Release(void)
{
	{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
		this->allocator_type_ = tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NONE;

		if (this->new_allocator_ != nullptr) {
			delete this->new_allocator_;

			this->new_allocator_ = nullptr;
		}

		if (this->dlmalloc_allocator_ != nullptr) {
			delete this->dlmalloc_allocator_;

			this->dlmalloc_allocator_ = nullptr;
		}
	}

	return;
}


/**
 * @brief Init�֐�
 */
void tml::MemoryUtilEngine::Init(void)
{
	return;
}


/**
 * @brief Create�֐�
 * @param allocator_type (allocator_type)
 * @param allocator_size (allocator_size)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::MemoryUtilEngine::Create(const tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE allocator_type, const size_t allocator_size)
{
	{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
		this->allocator_type_ = allocator_type;

		switch (this->allocator_type_) {
		case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NEW: {
			this->new_allocator_ = new tml::NewAllocator();

			if (this->new_allocator_->Create() < 0) {
				return (-1);
			}

			break;
		}
		case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC: {
			this->dlmalloc_allocator_ = new tml::DlmallocAllocator();

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
tml::MemoryUtilEngine::ALLOCATOR_INFO tml::MemoryUtilEngine::GetAllocatorInfo(void)
{
	tml::MemoryUtilEngine::ALLOCATOR_INFO allocator_info;
	tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE tmp_allocator_type = tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NONE;
	tml::Allocator::INFO tmp_allocator_info;

	{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
		tmp_allocator_type = this->allocator_type_;

		switch (this->allocator_type_) {
		case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NEW: {
			tmp_allocator_info = this->new_allocator_->GetInfo();

			break;
		}
		case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC: {
			tmp_allocator_info = this->dlmalloc_allocator_->GetInfo();

			break;
		}
		}
	}

	allocator_info.type = tmp_allocator_type;
	allocator_info.size = tmp_allocator_info.size;
	allocator_info.use_size = tmp_allocator_info.use_size;
	allocator_info.use_cnt = tmp_allocator_info.use_cnt;

	return (allocator_info);
}
