/**
 * @file
 * @brief NewAllocator�R�[�h�t�@�C��
 */


#include "NewAllocator.h"


/**
 * @brief �R���X�g���N�^
 */
tml::NewAllocator::NewAllocator() :
	ms_size_(0U),
	ms_use_size_(0U)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::NewAllocator::~NewAllocator()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::NewAllocator::Release(void)
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
 * @brief Init�֐�
 */
void tml::NewAllocator::Init(void)
{
	this->ms_th_lock_.Lock();

	this->Release();

	tml::Allocator::Init();

	this->ms_th_lock_.Unlock();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::NewAllocator::Create(void)
{
	this->ms_th_lock_.Lock();

	if (this->ms_size_ > 0U) {
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

	this->ms_size_ = UINT_MAX;
	this->ms_use_size_ = 0U;

	this->ms_th_lock_.Unlock();

	return (0);
}


/**
 * @brief GetInfo�֐�
 * @return info (info)
 */
tml::Allocator::INFO tml::NewAllocator::GetInfo(void)
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
