/**
 * @file
 * @brief DynamicBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "MemoryUtil.h"


namespace tml {
/**
 * @brief BaseDynamicBufferクラス
 */
template <bool R>
class BaseDynamicBuffer
{
private:
	BYTE *p_;
	size_t size_;
	size_t len_;
	size_t read_index_;
	INT read_result_;
	size_t write_index_;
	INT write_result_;

private:
	void Release(void);

	BYTE *GetMemory(const size_t);
	void ReleaseMemory(BYTE *);

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

	BYTE *Get(void);
	const BYTE *Get(void) const;
	void Set(const size_t);
	void Set(const BYTE *, const size_t);
	void Clear(void);
	size_t GetSize(void) const;
	void SetSize(const size_t);
	size_t GetLength(void) const;
	void SetLength(const size_t);
	size_t GetReadIndex(void) const;
	void SetReadIndex(const size_t);
	void AddReadIndex(const INT);
	INT GetReadResult(void) const;
	void InitReadResult(void);
	size_t GetWriteIndex(void) const;
	void SetWriteIndex(const size_t);
	void AddWriteIndex(const INT);
	INT GetWriteResult(void) const;
	void InitWriteResult(void);
	CHAR ReadChar(void);
	UCHAR ReadUChar(void);
	SHORT ReadShortB(void);
	SHORT ReadShortL(void);
	USHORT ReadUShortB(void);
	USHORT ReadUShortL(void);
	INT ReadIntB(void);
	INT ReadIntL(void);
	UINT ReadUIntB(void);
	UINT ReadUIntL(void);
	LONGLONG ReadLongLongB(void);
	LONGLONG ReadLongLongL(void);
	ULONGLONG ReadULongLongB(void);
	ULONGLONG ReadULongLongL(void);
	FLOAT ReadFloatB(void);
	FLOAT ReadFloatL(void);
	DOUBLE ReadDoubleB(void);
	DOUBLE ReadDoubleL(void);
	BYTE *ReadArray(BYTE *, const size_t, const size_t);
	CHAR *ReadStringB(CHAR *, const size_t);
	CHAR *ReadStringL(CHAR *, const size_t);
	WCHAR *ReadStringB(WCHAR *, const size_t);
	WCHAR *ReadStringL(WCHAR *, const size_t);
	void WriteChar(const CHAR);
	void WriteUChar(const UCHAR);
	void WriteShortB(const SHORT);
	void WriteShortL(const SHORT);
	void WriteUShortB(const USHORT);
	void WriteUShortL(const USHORT);
	void WriteIntB(const INT);
	void WriteIntL(const INT);
	void WriteUIntB(const UINT);
	void WriteUIntL(const UINT);
	void WriteLongLongB(const LONGLONG);
	void WriteLongLongL(const LONGLONG);
	void WriteULongLongB(const ULONGLONG);
	void WriteULongLongL(const ULONGLONG);
	void WriteFloatB(const FLOAT);
	void WriteFloatL(const FLOAT);
	void WriteDoubleB(const DOUBLE);
	void WriteDoubleL(const DOUBLE);
	void WriteArray(const BYTE *, const size_t, const size_t);
	void WriteStringB(const CHAR *);
	void WriteStringL(const CHAR *);
	void WriteStringB(const WCHAR *);
	void WriteStringL(const WCHAR *);
};
}


/**
 * @brief コンストラクタ
 */
template <bool R>
inline tml::BaseDynamicBuffer<R>::BaseDynamicBuffer() :
	p_(nullptr),
	size_(0U),
	len_(0U),
	read_index_(0U),
	read_result_(0),
	write_index_(0U),
	write_result_(0)
{
	return;
}


/**
 * @brief コンストラクタ
 * @param size (size)
 */
template <bool R>
inline tml::BaseDynamicBuffer<R>::BaseDynamicBuffer(const size_t size) :
	p_(nullptr),
	read_result_(0),
	write_result_(0)
{
	this->p_ = this->GetMemory(size);
	this->size_ = size;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->write_index_ = 0U;

	return;
}


/**
 * @brief コンストラクタ
 * @param p (pointer)
 * @param size (size)
 */
template <bool R>
inline tml::BaseDynamicBuffer<R>::BaseDynamicBuffer(const BYTE *p, const size_t size) :
	p_(nullptr),
	read_result_(0),
	write_result_(0)
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

	this->size_ = 0U;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->read_result_ = 0;
	this->write_index_ = 0U;
	this->write_result_ = 0;

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

	this->read_result_ = 0;
	this->write_result_ = 0;

	this->p_ = this->GetMemory(size);
	this->size_ = size;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->write_index_ = 0U;

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

	this->read_result_ = 0;
	this->write_result_ = 0;

	this->p_ = this->GetMemory(size);
	tml::Copy(this->p_, p, size);
	this->size_ = size;
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

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


/**
 * @brief Get関数
 * @return p (pointer)
 */
template <bool R>
inline BYTE *tml::BaseDynamicBuffer<R>::Get(void)
{
	return (this->p_);
}


/**
 * @brief Get関数
 * @return p (pointer)
 */
template <bool R>
inline const BYTE *tml::BaseDynamicBuffer<R>::Get(void) const
{
	return (this->p_);
}


/**
 * @brief Set関数
 * @param size (size)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::Set(const size_t size)
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
 * @brief Set関数
 * @param p (pointer)
 * @param size (size)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::Set(const BYTE *p, const size_t size)
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
 * @brief Clear関数
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::Clear(void)
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
 * @brief GetSize関数
 * @return size (size)
 */
template <bool R>
inline size_t tml::BaseDynamicBuffer<R>::GetSize(void) const
{
	return (this->size_);
}


/**
 * @brief SetSize関数
 * @param size (size)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::SetSize(const size_t size)
{
	this->Set(size);

	return;
}


/**
 * @brief GetLength関数
 * @return len (length)
 */
template <bool R>
inline size_t tml::BaseDynamicBuffer<R>::GetLength(void) const
{
	return (this->len_);
}


/**
 * @brief SetLength関数
 * @param len (length)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::SetLength(const size_t len)
{
	this->len_ = tml::Min(len, this->size_);
	this->read_index_ = tml::Min(this->read_index_, this->len_);
	this->write_index_ = tml::Min(this->write_index_, this->len_);

	return;
}


/**
 * @brief GetReadIndex関数
 * @return read_index (read_index)
 */
template <bool R>
inline size_t tml::BaseDynamicBuffer<R>::GetReadIndex(void) const
{
	return (this->read_index_);
}


/**
 * @brief SetReadIndex関数
 * @param index (index)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::SetReadIndex(const size_t index)
{
	tml::MemoryUtil::SetBufferIndex(this->len_, this->read_index_, index, &this->read_result_);

	return;
}


/**
 * @brief AddReadIndex関数
 * @param add_index (add_index)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::AddReadIndex(const INT add_index)
{
	tml::MemoryUtil::AddBufferIndex(this->len_, this->read_index_, add_index, &this->read_result_);

	return;
}


/**
 * @brief GetReadResult関数
 * @return read_result (read_result)<br>
 * 0未満=失敗
 */
template <bool R>
inline INT tml::BaseDynamicBuffer<R>::GetReadResult(void) const
{
	return (this->read_result_);
}


/**
 * @brief InitReadResult関数
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::InitReadResult(void)
{
	this->read_result_ = 0;

	return;
}


/**
 * @brief GetWriteIndex関数
 * @return write_index (write_index)
 */
template <bool R>
inline size_t tml::BaseDynamicBuffer<R>::GetWriteIndex(void) const
{
	return (this->write_index_);
}


/**
 * @brief SetWriteIndex関数
 * @param index (index)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::SetWriteIndex(const size_t index)
{
	tml::MemoryUtil::SetBufferIndex(this->size_, this->write_index_, index, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief AddWriteIndex関数
 * @param add_index (add_index)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::AddWriteIndex(const INT add_index)
{
	tml::MemoryUtil::AddBufferIndex(this->size_, this->write_index_, add_index, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief GetWriteResult関数
 * @return write_result (write_result)<br>
 * 0未満=失敗
 */
template <bool R>
inline INT tml::BaseDynamicBuffer<R>::GetWriteResult(void) const
{
	return (this->write_result_);
}


/**
 * @brief InitWriteResult関数
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::InitWriteResult(void)
{
	this->write_result_ = 0;

	return;
}


/**
 * @brief ReadChar関数
 * @return val (value)
 */
template <bool R>
inline CHAR tml::BaseDynamicBuffer<R>::ReadChar(void)
{
	return (tml::MemoryUtil::ReadBufferChar(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadUChar関数
 * @return val (value)
 */
template <bool R>
inline UCHAR tml::BaseDynamicBuffer<R>::ReadUChar(void)
{
	return (tml::MemoryUtil::ReadBufferUChar(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadShortB関数
 * @return val (value)
 */
template <bool R>
inline SHORT tml::BaseDynamicBuffer<R>::ReadShortB(void)
{
	return (tml::MemoryUtil::ReadBufferShortB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadShortL関数
 * @return val (value)
 */
template <bool R>
inline SHORT tml::BaseDynamicBuffer<R>::ReadShortL(void)
{
	return (tml::MemoryUtil::ReadBufferShortL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadUShortB関数
 * @return val (value)
 */
template <bool R>
inline USHORT tml::BaseDynamicBuffer<R>::ReadUShortB(void)
{
	return (tml::MemoryUtil::ReadBufferUShortB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadUShortL関数
 * @return val (value)
 */
template <bool R>
inline USHORT tml::BaseDynamicBuffer<R>::ReadUShortL(void)
{
	return (tml::MemoryUtil::ReadBufferUShortL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadIntB関数
 * @return val (value)
 */
template <bool R>
inline INT tml::BaseDynamicBuffer<R>::ReadIntB(void)
{
	return (tml::MemoryUtil::ReadBufferIntB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadIntL関数
 * @return val (value)
 */
template <bool R>
inline INT tml::BaseDynamicBuffer<R>::ReadIntL(void)
{
	return (tml::MemoryUtil::ReadBufferIntL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadUIntB関数
 * @return val (value)
 */
template <bool R>
inline UINT tml::BaseDynamicBuffer<R>::ReadUIntB(void)
{
	return (tml::MemoryUtil::ReadBufferUIntB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadUIntL関数
 * @return val (value)
 */
template <bool R>
inline UINT tml::BaseDynamicBuffer<R>::ReadUIntL(void)
{
	return (tml::MemoryUtil::ReadBufferUIntL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadLongLongB関数
 * @return val (value)
 */
template <bool R>
inline LONGLONG tml::BaseDynamicBuffer<R>::ReadLongLongB(void)
{
	return (tml::MemoryUtil::ReadBufferLongLongB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadLongLongL関数
 * @return val (value)
 */
template <bool R>
inline LONGLONG tml::BaseDynamicBuffer<R>::ReadLongLongL(void)
{
	return (tml::MemoryUtil::ReadBufferLongLongL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadULongLongB関数
 * @return val (value)
 */
template <bool R>
inline ULONGLONG tml::BaseDynamicBuffer<R>::ReadULongLongB(void)
{
	return (tml::MemoryUtil::ReadBufferULongLongB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadULongLongL関数
 * @return val (value)
 */
template <bool R>
inline ULONGLONG tml::BaseDynamicBuffer<R>::ReadULongLongL(void)
{
	return (tml::MemoryUtil::ReadBufferULongLongL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadFloatB関数
 * @return val (value)
 */
template <bool R>
inline FLOAT tml::BaseDynamicBuffer<R>::ReadFloatB(void)
{
	return (tml::MemoryUtil::ReadBufferFloatB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadFloatL関数
 * @return val (value)
 */
template <bool R>
inline FLOAT tml::BaseDynamicBuffer<R>::ReadFloatL(void)
{
	return (tml::MemoryUtil::ReadBufferFloatL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadDoubleB関数
 * @return val (value)
 */
template <bool R>
inline DOUBLE tml::BaseDynamicBuffer<R>::ReadDoubleB(void)
{
	return (tml::MemoryUtil::ReadBufferDoubleB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadDoubleL関数
 * @return val (value)
 */
template <bool R>
inline DOUBLE tml::BaseDynamicBuffer<R>::ReadDoubleL(void)
{
	return (tml::MemoryUtil::ReadBufferDoubleL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadArray関数
 * @param dst_ary (dst_array)
 * @param dst_ary_size (dst_array_size)
 * @param read_size (read_size)
 * @return dst_ary (dst_array)
 */
template <bool R>
inline BYTE *tml::BaseDynamicBuffer<R>::ReadArray(BYTE *dst_ary, const size_t dst_ary_size, const size_t read_size)
{
	return (tml::MemoryUtil::ReadBufferArray(dst_ary, dst_ary_size, this->p_, this->len_, this->read_index_, read_size, &this->read_result_));
}


/**
 * @brief ReadStringB関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <bool R>
inline CHAR *tml::BaseDynamicBuffer<R>::ReadStringB(CHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringB(dst_str, dst_str_size, this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadStringL関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <bool R>
inline CHAR *tml::BaseDynamicBuffer<R>::ReadStringL(CHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringL(dst_str, dst_str_size, this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadStringB関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <bool R>
inline WCHAR *tml::BaseDynamicBuffer<R>::ReadStringB(WCHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringB(dst_str, dst_str_size, this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadStringL関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <bool R>
inline WCHAR *tml::BaseDynamicBuffer<R>::ReadStringL(WCHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringL(dst_str, dst_str_size, this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief WriteChar関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteChar(const CHAR val)
{
	tml::MemoryUtil::WriteBufferChar(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUChar関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteUChar(const UCHAR val)
{
	tml::MemoryUtil::WriteBufferUChar(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteShortB関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteShortB(const SHORT val)
{
	tml::MemoryUtil::WriteBufferShortB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteShortL関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteShortL(const SHORT val)
{
	tml::MemoryUtil::WriteBufferShortL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUShortB関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteUShortB(const USHORT val)
{
	tml::MemoryUtil::WriteBufferUShortB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUShortL関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteUShortL(const USHORT val)
{
	tml::MemoryUtil::WriteBufferUShortL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteIntB関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteIntB(const INT val)
{
	tml::MemoryUtil::WriteBufferIntB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteIntL関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteIntL(const INT val)
{
	tml::MemoryUtil::WriteBufferIntL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUIntB関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteUIntB(const UINT val)
{
	tml::MemoryUtil::WriteBufferUIntB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUIntL関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteUIntL(const UINT val)
{
	tml::MemoryUtil::WriteBufferUIntL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteLongLongB関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteLongLongB(const LONGLONG val)
{
	tml::MemoryUtil::WriteBufferLongLongB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteLongLongL関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteLongLongL(const LONGLONG val)
{
	tml::MemoryUtil::WriteBufferLongLongL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteULongLongB関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteULongLongB(const ULONGLONG val)
{
	tml::MemoryUtil::WriteBufferULongLongB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteULongLongL関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteULongLongL(const ULONGLONG val)
{
	tml::MemoryUtil::WriteBufferULongLongL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteFloatB関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteFloatB(const FLOAT val)
{
	tml::MemoryUtil::WriteBufferFloatB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteFloatL関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteFloatL(const FLOAT val)
{
	tml::MemoryUtil::WriteBufferFloatL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteDoubleB関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteDoubleB(const DOUBLE val)
{
	tml::MemoryUtil::WriteBufferDoubleB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteDoubleL関数
 * @param val (value)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteDoubleL(const DOUBLE val)
{
	tml::MemoryUtil::WriteBufferDoubleL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteArray関数
 * @param ary (array)
 * @param ary_size (array_size)
 * @param write_size (write_size)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteArray(const BYTE *ary, const size_t ary_size, const size_t write_size)
{
	tml::MemoryUtil::WriteBufferArray(this->p_, this->size_, this->write_index_, ary, ary_size, write_size, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringB関数
 * @param str (string)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteStringB(const CHAR *str)
{
	tml::MemoryUtil::WriteBufferStringB(this->p_, this->size_, this->write_index_, str, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringL関数
 * @param str (string)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteStringL(const CHAR *str)
{
	tml::MemoryUtil::WriteBufferStringL(this->p_, this->size_, this->write_index_, str, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringB関数
 * @param str (string)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteStringB(const WCHAR *str)
{
	tml::MemoryUtil::WriteBufferStringB(this->p_, this->size_, this->write_index_, str, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringL関数
 * @param str (string)
 */
template <bool R>
inline void tml::BaseDynamicBuffer<R>::WriteStringL(const WCHAR *str)
{
	tml::MemoryUtil::WriteBufferStringL(this->p_, this->size_, this->write_index_, str, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


namespace tml {
using DynamicBuffer = tml::BaseDynamicBuffer<false>;

using RawDynamicBuffer = tml::BaseDynamicBuffer<true>;
}
