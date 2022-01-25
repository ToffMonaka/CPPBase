/**
 * @file
 * @brief DynamicBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Buffer.h"


namespace tml {
/**
 * @brief BaseDynamicBufferクラス
 */
template <bool R>
class BaseDynamicBuffer : public tml::Buffer
{
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

	BYTE *GetMemory(const size_t);
	void ReleaseMemory(BYTE *);

protected:
	virtual void OnSet(const size_t);
	virtual void OnSet(const BYTE *, const size_t);
	virtual void OnClear(void);

public:
	BaseDynamicBuffer();
	BaseDynamicBuffer(const size_t);
	BaseDynamicBuffer(const BYTE *, const size_t);
	BaseDynamicBuffer(const tml::BaseDynamicBuffer<R> &);
	tml::BaseDynamicBuffer<R> &operator =(const tml::BaseDynamicBuffer<R> &);
	BaseDynamicBuffer(tml::BaseDynamicBuffer<R> &&) noexcept;
	tml::BaseDynamicBuffer<R> &operator =(tml::BaseDynamicBuffer<R> &&) noexcept;
	virtual ~BaseDynamicBuffer();

	virtual void Init(void);
	virtual void Init(const size_t);
	virtual void Init(const BYTE *, const size_t);
};
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseDynamicBuffer<R>::BaseDynamicBuffer()
{
	return;
}


/**
 * @brief コンストラクタ
 * @param size (size)
 */
template <bool R>
inline tml::BaseDynamicBuffer<R>::BaseDynamicBuffer(const size_t size) 
{
	this->p_ = this->GetMemory(size);
	this->size_ = size;

	return;
}


/**
 * @brief コンストラクタ
 * @param p (pointer)
 * @param size (size)
 */
template <bool R>
inline tml::BaseDynamicBuffer<R>::BaseDynamicBuffer(const BYTE *p, const size_t size)
{
	this->p_ = this->GetMemory(size);
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
template <bool R>
inline tml::BaseDynamicBuffer<R>::BaseDynamicBuffer(const tml::BaseDynamicBuffer<R> &src)
{
	this->p_ = this->GetMemory(src.size_);
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
template <bool R>
inline tml::BaseDynamicBuffer<R> &tml::BaseDynamicBuffer<R>::operator =(const tml::BaseDynamicBuffer<R> &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->p_ = this->GetMemory(src.size_);
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
template <bool R>
inline tml::BaseDynamicBuffer<R>::BaseDynamicBuffer(tml::BaseDynamicBuffer<R> &&src) noexcept
{
	this->p_ = src.p_;
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_result_ = src.read_result_;
	this->write_index_ = src.write_index_;
	this->write_result_ = src.write_result_;

	src.p_ = nullptr;
	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
template <bool R>
inline tml::BaseDynamicBuffer<R> &tml::BaseDynamicBuffer<R>::operator =(tml::BaseDynamicBuffer<R> &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	this->p_ = src.p_;
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_result_ = src.read_result_;
	this->write_index_ = src.write_index_;
	this->write_result_ = src.write_result_;

	src.p_ = nullptr;
	src.Init();

	return ((*this));
}


/**
 * @brief デストラクタ
 */
template <bool R>
inline tml::BaseDynamicBuffer<R>::~BaseDynamicBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::Release(void)
{
	this->ReleaseMemory(this->p_);

	this->p_ = nullptr;

	return;
}


/**
 * @brief Init関数
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::Init(void)
{
	this->Release();

	tml::Buffer::Init();

	return;
}


/**
 * @brief Init関数
 * @param size (size)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::Init(const size_t size)
{
	this->Release();

	tml::Buffer::Init();

	this->p_ = this->GetMemory(size);
	this->size_ = size;

	return;
}


/**
 * @brief Init関数
 * @param p (pointer)
 * @param size (size)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::Init(const BYTE *p, const size_t size)
{
	this->Release();

	tml::Buffer::Init();

	this->p_ = this->GetMemory(size);
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
template <bool R>
inline void tml::BaseDynamicBuffer<R>::OnSet(const size_t size)
{
	if (size > this->size_) {
		auto new_p = this->GetMemory(size);

		tml::Copy(new_p, this->p_, this->size_);

		this->ReleaseMemory(this->p_);

		this->p_ = new_p;
	}

	this->size_ = size;
	this->len_ = tml::Min(this->len_, this->size_);
	this->read_index_ = tml::Min(this->read_index_, this->len_);
	this->write_index_ = tml::Min(this->write_index_, this->len_);

	return;
}


/**
 * @brief OnSet関数
 * @param p (pointer)
 * @param size (size)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::OnSet(const BYTE *p, const size_t size)
{
	if (size > this->size_) {
		auto new_p = this->GetMemory(size);

		this->ReleaseMemory(this->p_);

		this->p_ = new_p;
	}

	tml::Copy(this->p_, p, size);
	this->size_ = size;
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

	return;
}


/**
 * @brief OnClear関数
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::OnClear(void)
{
	this->p_ = nullptr;
	this->size_ = 0U;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->read_result_ = 0;
	this->write_index_ = 0U;
	this->write_result_ = 0;

	return;
}


/**
 * @brief GetMemory関数
 * @param size (size)
 * @return p (pointer)
 */
template <bool R>
inline BYTE *tml::BaseDynamicBuffer<R>::GetMemory(const size_t size)
{
	tml::MemoryGetBase<BYTE, R> mem_get;

	return (mem_get(size));
}


/**
 * @brief ReleaseMemory関数
 * @param p (pointer)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::ReleaseMemory(BYTE *p)
{
	tml::MemoryReleaseBase<BYTE, R> mem_release;

	mem_release(p);

	return;
}


namespace tml {
using DynamicBuffer = tml::BaseDynamicBuffer<false>;

using RawDynamicBuffer = tml::BaseDynamicBuffer<true>;
}
