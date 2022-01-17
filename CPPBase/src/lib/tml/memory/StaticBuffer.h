/**
 * @file
 * @brief StaticBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "MemoryUtil.h"


namespace tml {
/**
 * @brief BaseStaticBufferクラス
 */
template <size_t N, bool R>
class BaseStaticBuffer
{
private:
	BYTE p_[N];
	size_t size_;
	size_t len_;
	size_t read_index_;
	INT read_result_;
	size_t write_index_;
	INT write_result_;

private:
	void Release(void);

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
template <size_t N, bool R>
inline tml::BaseStaticBuffer<N, R>::BaseStaticBuffer() :
	size_(N),
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
template <size_t N, bool R>
inline tml::BaseStaticBuffer<N, R>::BaseStaticBuffer(const size_t size) :
	size_(N),
	len_(0U),
	read_index_(0U),
	read_result_(0),
	write_index_(0U),
	write_result_(0)
{
	if (size > N) {
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
inline tml::BaseStaticBuffer<N, R>::BaseStaticBuffer(const BYTE *p, const size_t size) :
	size_(N),
	len_(0U),
	read_index_(0U),
	read_result_(0),
	write_index_(0U),
	write_result_(0)
{
	if (size > N) {
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

	this->size_ = N;
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
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::Init(const size_t size)
{
	this->Release();

	this->size_ = N;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->read_result_ = 0;
	this->write_index_ = 0U;
	this->write_result_ = 0;

	if (size > N) {
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

	this->size_ = N;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->read_result_ = 0;
	this->write_index_ = 0U;
	this->write_result_ = 0;

	if (size > N) {
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
 * @brief Get関数
 * @return p (pointer)
 */
template <size_t N, bool R>
inline BYTE *tml::BaseStaticBuffer<N, R>::Get(void)
{
	return (this->p_);
}


/**
 * @brief Get関数
 * @return p (pointer)
 */
template <size_t N, bool R>
inline const BYTE *tml::BaseStaticBuffer<N, R>::Get(void) const
{
	return (this->p_);
}


/**
 * @brief Set関数
 * @param size (size)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::Set(const size_t size)
{
	if (size > N) {
		return;
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
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::Set(const BYTE *p, const size_t size)
{
	if (size > N) {
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
 * @brief Clear関数
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::Clear(void)
{
	this->size_ = N;
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
template <size_t N, bool R>
inline size_t tml::BaseStaticBuffer<N, R>::GetSize(void) const
{
	return (this->size_);
}


/**
 * @brief SetSize関数
 * @param size (size)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::SetSize(const size_t size)
{
	this->Set(size);

	return;
}


/**
 * @brief GetLength関数
 * @return len (length)
 */
template <size_t N, bool R>
inline size_t tml::BaseStaticBuffer<N, R>::GetLength(void) const
{
	return (this->len_);
}


/**
 * @brief SetLength関数
 * @param len (length)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::SetLength(const size_t len)
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
template <size_t N, bool R>
inline size_t tml::BaseStaticBuffer<N, R>::GetReadIndex(void) const
{
	return (this->read_index_);
}


/**
 * @brief SetReadIndex関数
 * @param index (index)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::SetReadIndex(const size_t index)
{
	tml::MemoryUtil::SetBufferIndex(this->len_, this->read_index_, index, &this->read_result_);

	return;
}


/**
 * @brief AddReadIndex関数
 * @param add_index (add_index)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::AddReadIndex(const INT add_index)
{
	tml::MemoryUtil::AddBufferIndex(this->len_, this->read_index_, add_index, &this->read_result_);

	return;
}


/**
 * @brief GetReadResult関数
 * @return read_result (read_result)<br>
 * 0未満=失敗
 */
template <size_t N, bool R>
inline INT tml::BaseStaticBuffer<N, R>::GetReadResult(void) const
{
	return (this->read_result_);
}


/**
 * @brief InitReadResult関数
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::InitReadResult(void)
{
	this->read_result_ = 0;

	return;
}


/**
 * @brief GetWriteIndex関数
 * @return write_index (write_index)
 */
template <size_t N, bool R>
inline size_t tml::BaseStaticBuffer<N, R>::GetWriteIndex(void) const
{
	return (this->write_index_);
}


/**
 * @brief SetWriteIndex関数
 * @param index (index)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::SetWriteIndex(const size_t index)
{
	tml::MemoryUtil::SetBufferIndex(this->size_, this->write_index_, index, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief AddWriteIndex関数
 * @param add_index (add_index)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::AddWriteIndex(const INT add_index)
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
template <size_t N, bool R>
inline INT tml::BaseStaticBuffer<N, R>::GetWriteResult(void) const
{
	return (this->write_result_);
}


/**
 * @brief InitWriteResult関数
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::InitWriteResult(void)
{
	this->write_result_ = 0;

	return;
}


/**
 * @brief ReadChar関数
 * @return val (value)
 */
template <size_t N, bool R>
inline CHAR tml::BaseStaticBuffer<N, R>::ReadChar(void)
{
	return (tml::MemoryUtil::ReadBufferChar(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadUChar関数
 * @return val (value)
 */
template <size_t N, bool R>
inline UCHAR tml::BaseStaticBuffer<N, R>::ReadUChar(void)
{
	return (tml::MemoryUtil::ReadBufferUChar(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadShortB関数
 * @return val (value)
 */
template <size_t N, bool R>
inline SHORT tml::BaseStaticBuffer<N, R>::ReadShortB(void)
{
	return (tml::MemoryUtil::ReadBufferShortB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadShortL関数
 * @return val (value)
 */
template <size_t N, bool R>
inline SHORT tml::BaseStaticBuffer<N, R>::ReadShortL(void)
{
	return (tml::MemoryUtil::ReadBufferShortL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadUShortB関数
 * @return val (value)
 */
template <size_t N, bool R>
inline USHORT tml::BaseStaticBuffer<N, R>::ReadUShortB(void)
{
	return (tml::MemoryUtil::ReadBufferUShortB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadUShortL関数
 * @return val (value)
 */
template <size_t N, bool R>
inline USHORT tml::BaseStaticBuffer<N, R>::ReadUShortL(void)
{
	return (tml::MemoryUtil::ReadBufferUShortL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadIntB関数
 * @return val (value)
 */
template <size_t N, bool R>
inline INT tml::BaseStaticBuffer<N, R>::ReadIntB(void)
{
	return (tml::MemoryUtil::ReadBufferIntB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadIntL関数
 * @return val (value)
 */
template <size_t N, bool R>
inline INT tml::BaseStaticBuffer<N, R>::ReadIntL(void)
{
	return (tml::MemoryUtil::ReadBufferIntL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadUIntB関数
 * @return val (value)
 */
template <size_t N, bool R>
inline UINT tml::BaseStaticBuffer<N, R>::ReadUIntB(void)
{
	return (tml::MemoryUtil::ReadBufferUIntB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadUIntL関数
 * @return val (value)
 */
template <size_t N, bool R>
inline UINT tml::BaseStaticBuffer<N, R>::ReadUIntL(void)
{
	return (tml::MemoryUtil::ReadBufferUIntL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadLongLongB関数
 * @return val (value)
 */
template <size_t N, bool R>
inline LONGLONG tml::BaseStaticBuffer<N, R>::ReadLongLongB(void)
{
	return (tml::MemoryUtil::ReadBufferLongLongB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadLongLongL関数
 * @return val (value)
 */
template <size_t N, bool R>
inline LONGLONG tml::BaseStaticBuffer<N, R>::ReadLongLongL(void)
{
	return (tml::MemoryUtil::ReadBufferLongLongL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadULongLongB関数
 * @return val (value)
 */
template <size_t N, bool R>
inline ULONGLONG tml::BaseStaticBuffer<N, R>::ReadULongLongB(void)
{
	return (tml::MemoryUtil::ReadBufferULongLongB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadULongLongL関数
 * @return val (value)
 */
template <size_t N, bool R>
inline ULONGLONG tml::BaseStaticBuffer<N, R>::ReadULongLongL(void)
{
	return (tml::MemoryUtil::ReadBufferULongLongL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadFloatB関数
 * @return val (value)
 */
template <size_t N, bool R>
inline FLOAT tml::BaseStaticBuffer<N, R>::ReadFloatB(void)
{
	return (tml::MemoryUtil::ReadBufferFloatB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadFloatL関数
 * @return val (value)
 */
template <size_t N, bool R>
inline FLOAT tml::BaseStaticBuffer<N, R>::ReadFloatL(void)
{
	return (tml::MemoryUtil::ReadBufferFloatL(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadDoubleB関数
 * @return val (value)
 */
template <size_t N, bool R>
inline DOUBLE tml::BaseStaticBuffer<N, R>::ReadDoubleB(void)
{
	return (tml::MemoryUtil::ReadBufferDoubleB(this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadDoubleL関数
 * @return val (value)
 */
template <size_t N, bool R>
inline DOUBLE tml::BaseStaticBuffer<N, R>::ReadDoubleL(void)
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
template <size_t N, bool R>
inline BYTE *tml::BaseStaticBuffer<N, R>::ReadArray(BYTE *dst_ary, const size_t dst_ary_size, const size_t read_size)
{
	return (tml::MemoryUtil::ReadBufferArray(dst_ary, dst_ary_size, this->p_, this->len_, this->read_index_, read_size, &this->read_result_));
}


/**
 * @brief ReadStringB関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <size_t N, bool R>
inline CHAR *tml::BaseStaticBuffer<N, R>::ReadStringB(CHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringB(dst_str, dst_str_size, this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadStringL関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <size_t N, bool R>
inline CHAR *tml::BaseStaticBuffer<N, R>::ReadStringL(CHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringL(dst_str, dst_str_size, this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadStringB関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <size_t N, bool R>
inline WCHAR *tml::BaseStaticBuffer<N, R>::ReadStringB(WCHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringB(dst_str, dst_str_size, this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief ReadStringL関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <size_t N, bool R>
inline WCHAR *tml::BaseStaticBuffer<N, R>::ReadStringL(WCHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringL(dst_str, dst_str_size, this->p_, this->len_, this->read_index_, &this->read_result_));
}


/**
 * @brief WriteChar関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteChar(const CHAR val)
{
	tml::MemoryUtil::WriteBufferChar(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUChar関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteUChar(const UCHAR val)
{
	tml::MemoryUtil::WriteBufferUChar(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteShortB関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteShortB(const SHORT val)
{
	tml::MemoryUtil::WriteBufferShortB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteShortL関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteShortL(const SHORT val)
{
	tml::MemoryUtil::WriteBufferShortL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUShortB関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteUShortB(const USHORT val)
{
	tml::MemoryUtil::WriteBufferUShortB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUShortL関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteUShortL(const USHORT val)
{
	tml::MemoryUtil::WriteBufferUShortL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteIntB関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteIntB(const INT val)
{
	tml::MemoryUtil::WriteBufferIntB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteIntL関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteIntL(const INT val)
{
	tml::MemoryUtil::WriteBufferIntL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUIntB関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteUIntB(const UINT val)
{
	tml::MemoryUtil::WriteBufferUIntB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUIntL関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteUIntL(const UINT val)
{
	tml::MemoryUtil::WriteBufferUIntL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteLongLongB関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteLongLongB(const LONGLONG val)
{
	tml::MemoryUtil::WriteBufferLongLongB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteLongLongL関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteLongLongL(const LONGLONG val)
{
	tml::MemoryUtil::WriteBufferLongLongL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteULongLongB関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteULongLongB(const ULONGLONG val)
{
	tml::MemoryUtil::WriteBufferULongLongB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteULongLongL関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteULongLongL(const ULONGLONG val)
{
	tml::MemoryUtil::WriteBufferULongLongL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteFloatB関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteFloatB(const FLOAT val)
{
	tml::MemoryUtil::WriteBufferFloatB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteFloatL関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteFloatL(const FLOAT val)
{
	tml::MemoryUtil::WriteBufferFloatL(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteDoubleB関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteDoubleB(const DOUBLE val)
{
	tml::MemoryUtil::WriteBufferDoubleB(this->p_, this->size_, this->write_index_, val, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteDoubleL関数
 * @param val (value)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteDoubleL(const DOUBLE val)
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
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteArray(const BYTE *ary, const size_t ary_size, const size_t write_size)
{
	tml::MemoryUtil::WriteBufferArray(this->p_, this->size_, this->write_index_, ary, ary_size, write_size, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringB関数
 * @param str (string)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteStringB(const CHAR *str)
{
	tml::MemoryUtil::WriteBufferStringB(this->p_, this->size_, this->write_index_, str, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringL関数
 * @param str (string)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteStringL(const CHAR *str)
{
	tml::MemoryUtil::WriteBufferStringL(this->p_, this->size_, this->write_index_, str, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringB関数
 * @param str (string)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteStringB(const WCHAR *str)
{
	tml::MemoryUtil::WriteBufferStringB(this->p_, this->size_, this->write_index_, str, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringL関数
 * @param str (string)
 */
template <size_t N, bool R>
inline void tml::BaseStaticBuffer<N, R>::WriteStringL(const WCHAR *str)
{
	tml::MemoryUtil::WriteBufferStringL(this->p_, this->size_, this->write_index_, str, &this->write_result_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


namespace tml {
template <size_t N>
using StaticBuffer = tml::BaseStaticBuffer<N, false>;

template <size_t N>
using RawStaticBuffer = tml::BaseStaticBuffer<N, true>;
}
