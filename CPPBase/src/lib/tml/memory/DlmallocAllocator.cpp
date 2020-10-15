/**
 * @file
 * @brief DlmallocAllocatorコードファイル
 */


#include "DlmallocAllocator.h"
#include <cmath>


/**
 * @brief コンストラクタ
 */
tml::DlmallocAllocator::DlmallocAllocator() :
	ms(NULLP),
	alignment(0),
	cnt_head_size(0),
	offset_head_size(0),
	head_size(0)
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

	if (this->ms != NULLP) {
		destroy_mspace(this->ms);

		this->ms = NULLP;
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

	this->alignment = 0;
	this->cnt_head_size = 0;
	this->offset_head_size = 0;
	this->head_size = 0;

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

	if (this->ms != NULLP) {
		this->ms_th_lock_.Unlock();

		return (-1);
	}

	this->Release();

	if (tml::Allocator::Create() < 0) {
		this->ms_th_lock_.Unlock();

		return (-1);
	}

	this->ms = create_mspace(size, 0);

	if (this->ms == NULLP) {
		this->ms_th_lock_.Unlock();

		return (-1);
	}

	this->alignment = 2 * sizeof(void *);
	this->cnt_head_size = sizeof(size_t);
	this->offset_head_size = sizeof(size_t);
	this->head_size = static_cast<INT>(std::ceil(static_cast<DOUBLE>(this->cnt_head_size + this->offset_head_size) / this->alignment)) * this->alignment;

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

	if (this->ms == NULLP) {
		this->ms_th_lock_.Unlock();

		return (info);
	}

	auto ms_info = mspace_mallinfo(this->ms);

	info.size = ms_info.arena;
	info.use_size = ms_info.uordblks;

	this->ms_th_lock_.Unlock();

	return (info);
}
