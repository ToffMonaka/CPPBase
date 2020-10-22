/**
 * @file
 * @brief MemoryUtilEngineコードファイル
 */


#include "MemoryUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::MemoryUtilEngine::MemoryUtilEngine() :
	allocator_type_(tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NONE),
	new_allocator_(NULLP),
	dlmalloc_allocator_(NULLP)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MemoryUtilEngine::~MemoryUtilEngine()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::MemoryUtilEngine::Release(void)
{
	this->allocator_th_lock_.Lock();

	this->allocator_type_ = tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NONE;

	if (this->new_allocator_ != NULLP) {
		delete this->new_allocator_;

		this->new_allocator_ = NULLP;
	}

	if (this->dlmalloc_allocator_ != NULLP) {
		delete this->dlmalloc_allocator_;

		this->dlmalloc_allocator_ = NULLP;
	}

	this->allocator_th_lock_.Unlock();

	return;
}


/**
 * @brief Init関数
 */
void tml::MemoryUtilEngine::Init(void)
{
	return;
}


/**
 * @brief Create関数
 * @param allocator_type (allocator_type)
 * @param allocator_size (allocator_size)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::MemoryUtilEngine::Create(const tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE allocator_type, const size_t allocator_size)
{
	this->allocator_th_lock_.Lock();

	this->allocator_type_ = allocator_type;

	switch (this->allocator_type_) {
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NEW: {
		this->new_allocator_ = new tml::NewAllocator();

		if (this->new_allocator_->Create() < 0) {
			this->allocator_th_lock_.Unlock();

			return (-1);
		}

		break;
	}
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC: {
		this->dlmalloc_allocator_ = new tml::DlmallocAllocator();

		if (this->dlmalloc_allocator_->Create(allocator_size) < 0) {
			this->allocator_th_lock_.Unlock();

			return (-1);
		}

		break;
	}
	default: {
		this->allocator_th_lock_.Unlock();

		return (-1);
	}
	}

	this->allocator_th_lock_.Unlock();

	return (0);
}


/**
 * @brief GetAllocatorInfo関数
 * @return allocator_info (allocator_info)
 */
tml::MemoryUtilEngine::ALLOCATOR_INFO tml::MemoryUtilEngine::GetAllocatorInfo(void)
{
	tml::MemoryUtilEngine::ALLOCATOR_INFO allocator_info;
	tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE tmp_allocator_type = tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NONE;
	tml::Allocator::INFO tmp_allocator_info;

	this->allocator_th_lock_.Lock();

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

	this->allocator_th_lock_.Unlock();

	allocator_info.type = tmp_allocator_type;
	allocator_info.size = tmp_allocator_info.size;
	allocator_info.use_size = tmp_allocator_info.use_size;
	allocator_info.use_cnt = tmp_allocator_info.use_cnt;

	return (allocator_info);
}
