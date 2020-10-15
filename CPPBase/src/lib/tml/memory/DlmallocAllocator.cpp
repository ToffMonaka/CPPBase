/**
 * @file
 * @brief DlmallocAllocator�R�[�h�t�@�C��
 */


#include "DlmallocAllocator.h"
#include <cmath>


/**
 * @brief �R���X�g���N�^
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

	if (this->ms != NULLP) {
		destroy_mspace(this->ms);

		this->ms = NULLP;
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

	this->alignment = 0;
	this->cnt_head_size = 0;
	this->offset_head_size = 0;
	this->head_size = 0;

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
 * @brief GetInfo�֐�
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
