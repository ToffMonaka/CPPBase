/**
 * @file
 * @brief DlmallocAllocatorコードファイル
 */


#include "DlmallocAllocator.h"


/**
 * @brief コンストラクタ
 */
tml::DlmallocAllocator::DlmallocAllocator() :
	ms_(nullptr),
	ms_use_cnt_(0U),
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
	if (this->ms_ != nullptr) {
		destroy_mspace(this->ms_);

		this->ms_ = nullptr;
		this->ms_use_cnt_ = 0U;
	}

	tml::Allocator::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DlmallocAllocator::Init(void)
{
	this->Release();

	this->ms_cnt_head_size_ = 0U;

	tml::Allocator::Init();

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
	if (this->ms_ != nullptr) {
		this->Init();

		return (-1);
	}

	this->Release();

	if (tml::Allocator::Create() < 0) {
		this->Init();

		return (-1);
	}

	this->ms_ = create_mspace(size, 0);
	this->ms_use_cnt_ = 0U;

	if (this->ms_ == nullptr) {
		this->Init();

		return (-1);
	}

	this->ms_cnt_head_size_ = sizeof(size_t);

	return (0);
}


/**
 * @brief GetInfo関数
 * @return info (info)
 */
tml::Allocator::INFO tml::DlmallocAllocator::GetInfo(void)
{
	auto info = tml::Allocator::GetInfo();

	if (this->ms_ == nullptr) {
		return (info);
	}

	auto ms_info = mspace_mallinfo(this->ms_);

	info.size = ms_info.usmblks;
	info.use_size = ms_info.uordblks;
	info.use_cnt = this->ms_use_cnt_;

	return (info);
}
