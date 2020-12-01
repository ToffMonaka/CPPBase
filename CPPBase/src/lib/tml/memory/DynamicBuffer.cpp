/**
 * @file
 * @brief DynamicBufferコードファイル
 */


#include "DynamicBuffer.h"
#include "MemoryUtil.h"


/**
 * @brief コンストラクタ
 */
tml::DynamicBuffer::DynamicBuffer() :
	ary_(nullptr),
	size_(0U),
	len_(0U)
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

	return;
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

		this->len_ = std::min(this->len_, size);
	} else {
		if (size != this->size_) {
			tml::MemoryUtil::Release(&this->ary_);

			this->ary_ = tml::MemoryUtil::Get<BYTE>(size);
			this->size_ = size;
		}

		this->len_ = 0U;
	}

	return;
}


/**
 * @brief SetLength関数
 * @param len (length)
 */
void tml::DynamicBuffer::SetLength(const size_t len)
{
	this->len_ = std::min(len, this->size_);

	return;
}
