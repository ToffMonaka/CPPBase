/**
 * @file
 * @brief MallocAllocatorコードファイル
 */


#include "MallocAllocator.h"


/**
 * @brief コンストラクタ
 */
tml::MallocAllocator::MallocAllocator() :
	ms_size_(0U),
	ms_use_size_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::MallocAllocator::~MallocAllocator()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::MallocAllocator::Release(void)
{
	this->ms_th_lock_.Lock();

	if (this->ms_size_ > 0U) {
		this->ms_size_ = 0U;
		this->ms_use_size_ = 0U;
	}

	tml::Allocator::Release();

	this->ms_th_lock_.Unlock();

	return;
}


/**
 * @brief Init関数
 */
void tml::MallocAllocator::Init(void)
{
	this->ms_th_lock_.Lock();

	this->Release();

	tml::Allocator::Init();

	this->ms_th_lock_.Unlock();

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::MallocAllocator::Create(void)
{
	this->ms_th_lock_.Lock();

	if (this->ms_size_ > 0U) {
		this->ms_th_lock_.Unlock();

		return (-1);
	}

	this->Release();

	if (tml::Allocator::Create() < 0) {
		this->ms_th_lock_.Unlock();

		return (-1);
	}

	this->ms_size_ = UINT_MAX;
	this->ms_use_size_ = 0U;

	this->ms_th_lock_.Unlock();

	return (0);
}


/**
 * @brief GetInfo関数
 * @return info (info)
 */
tml::Allocator::INFO tml::MallocAllocator::GetInfo(void)
{
	this->ms_th_lock_.Lock();

	auto info = tml::Allocator::GetInfo();

	if (this->ms_size_ <= 0U) {
		this->ms_th_lock_.Unlock();

		return (info);
	}

	info.size = this->ms_size_;
	info.use_size = this->ms_use_size_;

	this->ms_th_lock_.Unlock();

	return (info);
}
