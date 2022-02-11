/**
 * @file
 * @brief StaticBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Buffer.h"


namespace tml {
/**
 * @brief BaseStaticBufferクラス
 */
template <size_t N, bool R>
class BaseStaticBuffer : public tml::Buffer
{
protected: virtual void InterfaceDummy(void) {return;};

private:
	BYTE ary_[N];

private:
	void Release(void);

protected:
	virtual void OnSet(const size_t);
	virtual void OnSet(const BYTE *, const size_t);

public:
	BaseStaticBuffer();
	BaseStaticBuffer(const size_t);
	BaseStaticBuffer(const BYTE *, const size_t);
	BaseStaticBuffer(const tml::BaseStaticBuffer<N, R> &);
	tml::BaseStaticBuffer<N, R> &operator =(const tml::BaseStaticBuffer<N, R> &);
	BaseStaticBuffer(tml::BaseStaticBuffer<N, R> &&) noexcept;
	tml::BaseStaticBuffer<N, R> &operator =(tml::BaseStaticBuffer<N, R> &&) noexcept;
	virtual ~BaseStaticBuffer();

	virtual void Init(void);
	virtual void Init(const size_t);
	virtual void Init(const BYTE *, const size_t);
};
}


/**
 * @brief コンストラクタ
 */
template <size_t N, bool R>
inline tml::BaseStaticBuffer<N, R>::BaseStaticBuffer()
{
	this->p_ = this->ary_;
	this->capacity_ = N;

	return;
}


/**
 * @brief コンストラクタ
 * @param size (size)
 */
template <size_t N, bool R>
inline tml::BaseStaticBuffer<N, R>::BaseStaticBuffer(const size_t size)
{
	this->p_ = this->ary_;
	this->capacity_ = N;

	if (size > this->capacity_) {
		return;
	}

	this->size_ = size;

	return;
}


/**
 * @brief コンストラクタ
 * @param p (pointer)
 * @param size (size)
 */
template <size_t N, bool R>
inline tml::BaseStaticBuffer<N, R>::BaseStaticBuffer(const BYTE *p, const size_t size)
{
	this->p_ = this->ary_;
	this->capacity_ = N;

	if (size > this->capacity_) {
		return;
	}

	tml::Copy(this->p_, p, size);
	this->size_ = size;
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

	return;
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
template <size_t N, bool R>
inline tml::BaseStaticBuffer<N, R>::BaseStaticBuffer(const tml::BaseStaticBuffer<N, R> &src)
{
	this->p_ = this->ary_;
	this->capacity_ = N;

	tml::Copy(this->p_, src.p_, src.len_);
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_result_ = src.read_result_;
	this->write_index_ = src.write_index_;
	this->write_result_ = src.write_result_;

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
template <size_t N, bool R>
inline tml::BaseStaticBuffer<N, R> &tml::BaseStaticBuffer<N, R>::operator =(const tml::BaseStaticBuffer<N, R> &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	tml::Copy(this->p_, src.p_, src.len_);
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_result_ = src.read_result_;
	this->write_index_ = src.write_index_;
	this->write_result_ = src.write_result_;

	return ((*this));
}


/**
 * @brief コンストラクタ
 * @param src (src)
 */
template <size_t N, bool R>
inline tml::BaseStaticBuffer<N, R>::BaseStaticBuffer(tml::BaseStaticBuffer<N, R> &&src) noexcept
{
	this->p_ = this->ary_;
	this->capacity_ = N;

	tml::Copy(this->p_, src.p_, src.len_);
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_result_ = src.read_result_;
	this->write_index_ = src.write_index_;
	this->write_result_ = src.write_result_;

	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
template <size_t N, bool R>
inline tml::BaseStaticBuffer<N, R> &tml::BaseStaticBuffer<N, R>::operator =(tml::BaseStaticBuffer<N, R> &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	tml::Copy(this->p_, src.p_, src.len_);
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_result_ = src.read_result_;
	this->write_index_ = src.write_index_;
	this->write_result_ = src.write_result_;

	src.Init();

	return ((*this));
}


/**
 * @brief デストラクタ
 */
template <size_t N, bool R>
inline tml::BaseStaticBuffer<N, R>::~BaseStaticBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::Init(void)
{
	this->Release();

	tml::Buffer::Init();

	this->p_ = this->ary_;
	this->capacity_ = N;

	return;
}


/**
 * @brief Init関数
 * @param size (size)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::Init(const size_t size)
{
	this->Release();

	tml::Buffer::Init();

	this->p_ = this->ary_;
	this->capacity_ = N;

	if (size > this->capacity_) {
		return;
	}

	this->size_ = size;

	return;
}


/**
 * @brief Init関数
 * @param p (pointer)
 * @param size (size)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::Init(const BYTE *p, const size_t size)
{
	this->Release();

	tml::Buffer::Init();

	this->p_ = this->ary_;
	this->capacity_ = N;

	if (size > this->capacity_) {
		return;
	}

	tml::Copy(this->p_, p, size);
	this->size_ = size;
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

	return;
}


/**
 * @brief OnSet関数
 * @param size (size)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::OnSet(const size_t size)
{
	if (size > this->capacity_) {
		return;
	}

	this->size_ = size;
	this->len_ = tml::Min(this->len_, this->size_);
	this->read_index_ = tml::Min(this->read_index_, this->len_);
	this->write_index_ = tml::Min(this->write_index_, this->len_);

	return (0);
}


/**
 * @brief OnSet関数
 * @param p (pointer)
 * @param size (size)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::OnSet(const BYTE *p, const size_t size)
{
	if (size > this->capacity_) {
		return;
	}

	tml::Copy(this->p_, p, size);
	this->size_ = size;
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

	return (0);
}


namespace tml {
template <size_t N>
using StaticBuffer = tml::BaseStaticBuffer<N, false>;

template <size_t N>
using RawStaticBuffer = tml::BaseStaticBuffer<N, true>;
}
