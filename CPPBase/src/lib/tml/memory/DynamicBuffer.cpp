/**
 * @file
 * @brief DynamicBuffer�R�[�h�t�@�C��
 */


#include "DynamicBuffer.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DynamicBuffer::DynamicBuffer() :
	p_(nullptr),
	size_(0U),
	len_(0U),
	read_index_(0U),
	read_res_(0),
	write_index_(0U),
	write_res_(0)
{
	return;
}


/**
 * @brief �R���X�g���N�^
 * @param size (size)
 */
tml::DynamicBuffer::DynamicBuffer(const size_t size) :
	p_(nullptr),
	read_res_(0),
	write_res_(0)
{
	this->p_ = tml::MemoryUtil::Get<BYTE>(size);
	this->size_ = size;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->write_index_ = 0U;

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param p (pointer)
 * @param size (size)
 */
tml::DynamicBuffer::DynamicBuffer(const BYTE *p, const size_t size) :
	p_(nullptr),
	read_res_(0),
	write_res_(0)
{
	this->p_ = tml::MemoryUtil::Get<BYTE>(size);
	tml::Copy(this->p_, p, size);
	this->size_ = size;
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

	return;
}


/**
 * @brief �R���X�g���N�^
 * @param src (src)
 */
tml::DynamicBuffer::DynamicBuffer(const tml::DynamicBuffer &src)
{
	this->p_ = tml::MemoryUtil::Get<BYTE>(src.size_);
	tml::Copy(this->p_, src.p_, src.len_);
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_res_ = src.read_res_;
	this->write_index_ = src.write_index_;
	this->write_res_ = src.write_res_;

	return;
}


/**
 * @brief operator =�֐�
 * @param src (src)
 * @return this (this)
 */
tml::DynamicBuffer &tml::DynamicBuffer::operator =(const tml::DynamicBuffer &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->p_ = tml::MemoryUtil::Get<BYTE>(src.size_);
	tml::Copy(this->p_, src.p_, src.len_);
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_res_ = src.read_res_;
	this->write_index_ = src.write_index_;
	this->write_res_ = src.write_res_;

	return ((*this));
}


/**
 * @brief �R���X�g���N�^
 * @param src (src)
 */
tml::DynamicBuffer::DynamicBuffer(tml::DynamicBuffer &&src) noexcept
{
	this->p_ = src.p_;
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_res_ = src.read_res_;
	this->write_index_ = src.write_index_;
	this->write_res_ = src.write_res_;

	src.p_ = nullptr;
	src.Init();

	return;
}


/**
 * @brief operator =�֐�
 * @param src (src)
 * @return this (this)
 */
tml::DynamicBuffer &tml::DynamicBuffer::operator =(tml::DynamicBuffer &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->p_ = src.p_;
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_res_ = src.read_res_;
	this->write_index_ = src.write_index_;
	this->write_res_ = src.write_res_;

	src.p_ = nullptr;
	src.Init();

	return ((*this));
}


/**
 * @brief �f�X�g���N�^
 */
tml::DynamicBuffer::~DynamicBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::DynamicBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->p_);

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DynamicBuffer::Init(void)
{
	this->Release();

	this->size_ = 0U;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->read_res_ = 0;
	this->write_index_ = 0U;
	this->write_res_ = 0;

	return;
}


/**
 * @brief Init�֐�
 * @param size (size)
 */
void tml::DynamicBuffer::Init(const size_t size)
{
	this->Release();

	this->read_res_ = 0;
	this->write_res_ = 0;

	this->p_ = tml::MemoryUtil::Get<BYTE>(size);
	this->size_ = size;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->write_index_ = 0U;

	return;
}


/**
 * @brief Init�֐�
 * @param p (pointer)
 * @param size (size)
 */
void tml::DynamicBuffer::Init(const BYTE *p, const size_t size)
{
	this->Release();

	this->read_res_ = 0;
	this->write_res_ = 0;

	this->p_ = tml::MemoryUtil::Get<BYTE>(size);
	tml::Copy(this->p_, p, size);
	this->size_ = size;
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

	return;
}
