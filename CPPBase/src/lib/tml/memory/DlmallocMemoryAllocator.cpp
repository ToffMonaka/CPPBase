/**
 * @file
 * @brief DlmallocMemoryAllocatorコードファイル
 */


#include "DlmallocMemoryAllocator.h"


/**
 * @brief コンストラクタ
 */
tml::DlmallocMemoryAllocator::DlmallocMemoryAllocator() :
	ms_(nullptr),
	ms_use_cnt_(0U),
	ms_cnt_head_size_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::DlmallocMemoryAllocator::~DlmallocMemoryAllocator()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::DlmallocMemoryAllocator::Release(void)
{
	if (this->ms_ != nullptr) {
		destroy_mspace(this->ms_);

		this->ms_ = nullptr;
		this->ms_use_cnt_ = 0U;
	}

	tml::MemoryAllocator::Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::DlmallocMemoryAllocator::Init(void)
{
	this->Release();

	this->ms_cnt_head_size_ = 0U;

	tml::MemoryAllocator::Init();

	return;
}


/**
 * @brief Create関数
 * @param size (size)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::DlmallocMemoryAllocator::Create(const size_t size)
{
	if (this->ms_ != nullptr) {
		this->Init();

		return (-1);
	}

	this->Release();

	if (tml::MemoryAllocator::Create(tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::DLMALLOC) < 0) {
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
tml::MemoryAllocator::INFO tml::DlmallocMemoryAllocator::GetInfo(void)
{
	if (this->ms_ == nullptr) {
		return (tml::MemoryAllocator::INFO());
	}

	auto info = tml::MemoryAllocator::GetInfo();
	auto ms_info = mspace_mallinfo(this->ms_);

	info.size = ms_info.usmblks;
	info.use_size = ms_info.uordblks;
	info.use_cnt = this->ms_use_cnt_;

	return (info);
}
