/**
 * @file
 * @brief DynamicBufferコードファイル
 */


#include "DynamicBuffer.h"


/**
 * @brief コンストラクタ
 */
tml::DynamicBuffer::DynamicBuffer() :
	ary_(nullptr),
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
 * @brief コンストラクタ
 * @param size (size)
 */
tml::DynamicBuffer::DynamicBuffer(const size_t size) :
	ary_(nullptr),
	read_res_(0),
	write_res_(0)
{
	this->ary_ = tml::MemoryUtil::Get<BYTE>(size);
	this->size_ = size;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->write_index_ = 0U;

	return;
}


/**
 * @brief コンストラクタ
 * @param ary (array)
 * @param size (size)
 */
tml::DynamicBuffer::DynamicBuffer(const BYTE *ary, const size_t size) :
	ary_(nullptr),
	read_res_(0),
	write_res_(0)
{
	this->ary_ = tml::MemoryUtil::Get<BYTE>(size);
	this->size_ = size;
	tml::MemoryUtil::Copy(this->ary_, ary, this->size_);
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

	return;
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::DynamicBuffer::DynamicBuffer(const tml::DynamicBuffer &src)
{
	this->ary_ = tml::MemoryUtil::Get<BYTE>(src.size_);
	this->size_ = src.size_;
	tml::MemoryUtil::Copy(this->ary_, src.ary_, src.len_);
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_res_ = src.read_res_;
	this->write_index_ = src.write_index_;
	this->write_res_ = src.write_res_;

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::DynamicBuffer &tml::DynamicBuffer::operator =(const tml::DynamicBuffer &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->ary_ = tml::MemoryUtil::Get<BYTE>(src.size_);
	this->size_ = src.size_;
	tml::MemoryUtil::Copy(this->ary_, src.ary_, src.len_);
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_res_ = src.read_res_;
	this->write_index_ = src.write_index_;
	this->write_res_ = src.write_res_;

	return ((*this));
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::DynamicBuffer::DynamicBuffer(tml::DynamicBuffer &&src) noexcept
{
	this->ary_ = src.ary_;
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_res_ = src.read_res_;
	this->write_index_ = src.write_index_;
	this->write_res_ = src.write_res_;

	src.ary_ = nullptr;
	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
tml::DynamicBuffer &tml::DynamicBuffer::operator =(tml::DynamicBuffer &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->ary_ = src.ary_;
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_res_ = src.read_res_;
	this->write_index_ = src.write_index_;
	this->write_res_ = src.write_res_;

	src.ary_ = nullptr;
	src.Init();

	return ((*this));
}


/**
 * @brief デストラクタ
 */
tml::DynamicBuffer::~DynamicBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
void tml::DynamicBuffer::Release(void)
{
	tml::MemoryUtil::Release(&this->ary_);

	return;
}


/**
 * @brief Init関数
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
 * @brief Init関数
 * @param size (size)
 */
void tml::DynamicBuffer::Init(const size_t size)
{
	this->Release();

	this->read_res_ = 0;
	this->write_res_ = 0;

	this->ary_ = tml::MemoryUtil::Get<BYTE>(size);
	this->size_ = size;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->write_index_ = 0U;

	return;
}


/**
 * @brief Init関数
 * @param ary (array)
 * @param size (size)
 */
void tml::DynamicBuffer::Init(const BYTE *ary, const size_t size)
{
	this->Release();

	this->read_res_ = 0;
	this->write_res_ = 0;

	this->ary_ = tml::MemoryUtil::Get<BYTE>(size);
	this->size_ = size;
	tml::MemoryUtil::Copy(this->ary_, ary, this->size_);
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

	return;
}


/**
 * @brief Clear関数
 */
void tml::DynamicBuffer::Clear(void)
{
	this->ary_ = nullptr;
	this->size_ = 0U;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->read_res_ = 0;
	this->write_index_ = 0U;
	this->write_res_ = 0;

	return;
}
