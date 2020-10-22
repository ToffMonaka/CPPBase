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
	ms_use_size_(0U),
	ms_cnt_head_size_(0U)
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
	if (this->ms_size_ > 0U) {
		this->ms_size_ = 0U;
		this->ms_use_size_ = 0U;
	}

	tml::Allocator::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::NewAllocator::Init(void)
{
	this->Release();

	this->ms_cnt_head_size_ = 0U;

	tml::Allocator::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::NewAllocator::Create(void)
{
	if (this->ms_size_ > 0U) {
		this->Init();

		return (-1);
	}

	this->Release();

	if (tml::Allocator::Create() < 0) {
		this->Init();

		return (-1);
	}

	this->ms_size_ = UINT_MAX;
	this->ms_use_size_ = 0U;

	if (this->ms_size_ <= 0U) {
		this->Init();

		return (-1);
	}

	this->ms_cnt_head_size_ = sizeof(size_t);

	return (0);
}


/**
 * @brief GetInfo�֐�
 * @return info (info)
 */
tml::Allocator::INFO tml::NewAllocator::GetInfo(void)
{
	auto info = tml::Allocator::GetInfo();

	if (this->ms_size_ <= 0U) {
		return (info);
	}

	info.size = this->ms_size_;
	info.use_size = this->ms_use_size_;
	info.use_cnt = this->ms_use_size_;

	return (info);
}
