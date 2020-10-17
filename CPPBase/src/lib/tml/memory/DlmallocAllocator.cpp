/**
 * @file
 * @brief DlmallocAllocator�R�[�h�t�@�C��
 */


#include "DlmallocAllocator.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DlmallocAllocator::DlmallocAllocator() :
	ms_(NULLP),
	ms_cnt_head_size_(0U)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DlmallocAllocator::~DlmallocAllocator()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
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
 * @brief Init�֐�
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
 * @brief Create�֐�
 * @param size (size)
 * @return res (result)<br>
 * 0����=���s
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
 * @brief GetInfo�֐�
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
