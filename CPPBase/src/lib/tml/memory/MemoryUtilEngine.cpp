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
	new_allocator_(NULLP),
	dlmalloc_allocator_(NULLP)
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
	if (this->new_allocator_ != NULLP) {
		delete this->new_allocator_;

		this->new_allocator_ = NULLP;
	}

	if (this->dlmalloc_allocator_ != NULLP) {
		delete this->dlmalloc_allocator_;

		this->dlmalloc_allocator_ = NULLP;
	}

	return;
}


/**
 * @brief Init�֐�
 */
void tml::MemoryUtilEngine::Init(void)
{
	this->allocator_type_ = tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NONE;

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

	return (0);
}
