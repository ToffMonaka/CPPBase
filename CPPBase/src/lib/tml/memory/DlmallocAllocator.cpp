/**
 * @file
 * @brief DlmallocAllocatorコードファイル
 */


#include "DlmallocAllocator.h"


/**
 * @brief コンストラクタ
 */
tml::DlmallocAllocator::DlmallocAllocator() :
	ms_(NULLP),
	ms_cnt_head_size_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DlmallocAllocator::~DlmallocAllocator()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::DlmallocAllocator::Release(void)
{
	this->ms_th_lock_.Lock();

	if (this->ms_ != NULLP) {
		destroy_mspace(this->ms_);

		this->ms_ = NULLP;
	}

	tml::Allocator::Release();

	this->ms_th_lock_.Unlock();

	return;
}


/**
 * @brief Init関数
 */
void tml::DlmallocAllocator::Init(void)
{
	this->ms_th_lock_.Lock();

	this->Release();

	this->ms_cnt_head_size_ = 0U;

	tml::Allocator::Init();

	this->ms_th_lock_.Unlock();

	return;
}


/**
 * @brief Create関数
 * @param size (size)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DlmallocAllocator::Create(const size_t size)
{
	this->ms_th_lock_.Lock();

	if (this->ms_ != NULLP) {
		this->Init();

		this->ms_th_lock_.Unlock();

		return (-1);
	}

	this->Release();

	if (tml::Allocator::Create() < 0) {
		this->Init();

		this->ms_th_lock_.Unlock();

		return (-1);
	}

	this->ms_ = create_mspace(size, 0);

	if (this->ms_ == NULLP) {
		this->Init();

		this->ms_th_lock_.Unlock();

		return (-1);
	}

	this->ms_cnt_head_size_ = sizeof(size_t);

	this->ms_th_lock_.Unlock();

	return (0);
}


/**
 * @brief GetInfo関数
 * @return info (info)
 */
tml::Allocator::INFO tml::DlmallocAllocator::GetInfo(void)
{
	this->ms_th_lock_.Lock();

	auto info = tml::Allocator::GetInfo();

	if (this->ms_ == NULLP) {
		this->ms_th_lock_.Unlock();

		return (info);
	}

	auto ms_info = mspace_mallinfo(this->ms_);

	info.size = ms_info.arena;
	info.use_size = ms_info.uordblks;

	this->ms_th_lock_.Unlock();

	return (info);
}
