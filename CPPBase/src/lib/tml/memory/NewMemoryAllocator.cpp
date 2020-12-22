/**
 * @file
 * @brief NewMemoryAllocator�R�[�h�t�@�C��
 */


#include "NewMemoryAllocator.h"


/**
 * @brief �R���X�g���N�^
 */
tml::NewMemoryAllocator::NewMemoryAllocator() :
	ms_size_(0U),
	ms_use_size_(0U),
	ms_cnt_head_size_(0U)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::NewMemoryAllocator::~NewMemoryAllocator()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::NewMemoryAllocator::Release(void)
{
	if (this->ms_size_ > 0U) {
		this->ms_size_ = 0U;
		this->ms_use_size_ = 0U;
	}

	tml::MemoryAllocator::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::NewMemoryAllocator::Init(void)
{
	this->Release();

	this->ms_cnt_head_size_ = 0U;

	tml::MemoryAllocator::Init();

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::NewMemoryAllocator::Create(void)
{
	if (this->ms_size_ > 0U) {
		this->Init();

		return (-1);
	}

	this->Init();

	if (tml::MemoryAllocator::Create(tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NEW) < 0) {
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
tml::MemoryAllocator::INFO tml::NewMemoryAllocator::GetInfo(void)
{
	if (this->ms_size_ <= 0U) {
		return (tml::MemoryAllocator::INFO());
	}

	auto info = tml::MemoryAllocator::GetInfo();

	info.size = this->ms_size_;
	info.use_size = this->ms_use_size_;
	info.use_cnt = this->ms_use_size_;

	return (info);
}
