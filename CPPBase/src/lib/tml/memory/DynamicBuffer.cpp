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
tml::DynamicBuffer::DynamicBuffer(const size_t size)
{
	this->ary_ = tml::MemoryUtil::Get<BYTE>(size);
	this->size_ = size;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->read_res_ = 0;
	this->write_index_ = 0U;
	this->write_res_ = 0;

	return;
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
tml::DynamicBuffer::DynamicBuffer(const tml::DynamicBuffer &src)
{
	this->ary_ = tml::MemoryUtil::Get<BYTE>(src.size_);
	tml::MemoryUtil::Copy(this->ary_, src.ary_, src.len_);
	this->size_ = src.size_;
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

	tml::MemoryUtil::Release(&this->ary_);

	this->ary_ = tml::MemoryUtil::Get<BYTE>(src.size_);
	tml::MemoryUtil::Copy(this->ary_, src.ary_, src.len_);
	this->size_ = src.size_;
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
	src.size_ = 0U;
	src.len_ = 0U;
	src.read_index_ = 0U;
	src.read_res_ = 0;
	src.write_index_ = 0U;
	src.write_res_ = 0;

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

	tml::MemoryUtil::Release(&this->ary_);

	this->ary_ = src.ary_;
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_res_ = src.read_res_;
	this->write_index_ = src.write_index_;
	this->write_res_ = src.write_res_;

	src.ary_ = nullptr;
	src.size_ = 0U;
	src.len_ = 0U;
	src.read_index_ = 0U;
	src.read_res_ = 0;
	src.write_index_ = 0U;
	src.write_res_ = 0;

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
 * @brief SetArray関数
 * @param ary (array)
 * @param len (length)
 */
void tml::DynamicBuffer::SetArray(const BYTE *ary, const size_t len)
{
	if (len > this->size_) {
		return;
	}

	tml::MemoryUtil::Copy(this->ary_, ary, len);
	this->len_ = len;
	this->read_index_ = 0U;
	this->read_res_ = 0;
	this->write_index_ = len;
	this->write_res_ = 0;

	return;
}


/**
 * @brief SetSize関数
 * @param size (size)
 * @param keep_flg (keep_flag)
 */
void tml::DynamicBuffer::SetSize(const size_t size, const bool keep_flg)
{
	if (keep_flg) {
		if (size != this->size_) {
			auto ary = tml::MemoryUtil::Get<BYTE>(size);

			tml::MemoryUtil::Copy(ary, this->ary_, std::min(this->size_, size));

			tml::MemoryUtil::Release(&this->ary_);

			this->ary_ = ary;
			this->size_ = size;
		}

		this->len_ = std::min(this->len_, this->size_);
		this->read_index_ = std::min(this->read_index_, this->len_);
		this->write_index_ = std::min(this->write_index_, this->len_);
	} else {
		if (size != this->size_) {
			tml::MemoryUtil::Release(&this->ary_);

			this->ary_ = tml::MemoryUtil::Get<BYTE>(size);
			this->size_ = size;
		}

		this->len_ = 0U;
		this->read_index_ = 0U;
		this->read_res_ = 0;
		this->write_index_ = 0U;
		this->write_res_ = 0;
	}

	return;
}
