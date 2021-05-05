/**
 * @file
 * @brief StaticBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "MemoryUtil.h"


namespace tml {
/**
 * @brief StaticBufferクラス
 */
template <size_t N>
class StaticBuffer
{
private:
	BYTE ary_[N];
	size_t size_;
	size_t len_;
	size_t read_index_;
	INT read_res_;
	size_t write_index_;
	INT write_res_;

protected:
	void Release(void);

public:
	StaticBuffer();
	StaticBuffer(const size_t);
	StaticBuffer(const BYTE *, const size_t);
	StaticBuffer(const tml::StaticBuffer<N> &);
	tml::StaticBuffer<N> &operator =(const tml::StaticBuffer<N> &);
	StaticBuffer(tml::StaticBuffer<N> &&) noexcept;
	tml::StaticBuffer<N> &operator =(tml::StaticBuffer<N> &&) noexcept;
	virtual ~StaticBuffer();

	virtual void Init(void);
	virtual void Init(const size_t);
	virtual void Init(const BYTE *, const size_t);

	BYTE *Get(void);
	const BYTE *Get(void) const;
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
	CHAR ReadCHAR(void);
	UCHAR ReadUCHAR(void);
	SHORT ReadSHORT_B(void);
	SHORT ReadSHORT_L(void);
	USHORT ReadUSHORT_B(void);
	USHORT ReadUSHORT_L(void);
	INT ReadINT_B(void);
	INT ReadINT_L(void);
	UINT ReadUINT_B(void);
	UINT ReadUINT_L(void);
	LONGLONG ReadLONGLONG_B(void);
	LONGLONG ReadLONGLONG_L(void);
	ULONGLONG ReadULONGLONG_B(void);
	ULONGLONG ReadULONGLONG_L(void);
	FLOAT ReadFLOAT_B(void);
	FLOAT ReadFLOAT_L(void);
	DOUBLE ReadDOUBLE_B(void);
	DOUBLE ReadDOUBLE_L(void);
	BYTE *ReadArray(BYTE *, const size_t, const size_t);
	CHAR *ReadString_B(CHAR *, const size_t);
	CHAR *ReadString_L(CHAR *, const size_t);
	WCHAR *ReadString_B(WCHAR *, const size_t);
	WCHAR *ReadString_L(WCHAR *, const size_t);
	void WriteCHAR(const CHAR);
	void WriteUCHAR(const UCHAR);
	void WriteSHORT_B(const SHORT);
	void WriteSHORT_L(const SHORT);
	void WriteUSHORT_B(const USHORT);
	void WriteUSHORT_L(const USHORT);
	void WriteINT_B(const INT);
	void WriteINT_L(const INT);
	void WriteUINT_B(const UINT);
	void WriteUINT_L(const UINT);
	void WriteLONGLONG_B(const LONGLONG);
	void WriteLONGLONG_L(const LONGLONG);
	void WriteULONGLONG_B(const ULONGLONG);
	void WriteULONGLONG_L(const ULONGLONG);
	void WriteFLOAT_B(const FLOAT);
	void WriteFLOAT_L(const FLOAT);
	void WriteDOUBLE_B(const DOUBLE);
	void WriteDOUBLE_L(const DOUBLE);
	void WriteArray(const BYTE *, const size_t, const size_t);
	void WriteString_B(const CHAR *);
	void WriteString_L(const CHAR *);
	void WriteString_B(const WCHAR *);
	void WriteString_L(const WCHAR *);
};
}


/**
 * @brief コンストラクタ
 */
template <size_t N>
inline tml::StaticBuffer<N>::StaticBuffer() :
	size_(N),
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
template <size_t N>
inline tml::StaticBuffer<N>::StaticBuffer(const size_t size) :
	size_(N),
	len_(0U),
	read_index_(0U),
	read_res_(0),
	write_index_(0U),
	write_res_(0)
{
	if (size > N) {
		return;
	}

	this->size_ = size;

	return;
}


/**
 * @brief コンストラクタ
 * @param ary (array)
 * @param size (size)
 */
template <size_t N>
inline tml::StaticBuffer<N>::StaticBuffer(const BYTE *ary, const size_t size) :
	size_(N),
	len_(0U),
	read_index_(0U),
	read_res_(0),
	write_index_(0U),
	write_res_(0)
{
	if (size > N) {
		return;
	}

	tml::Copy(this->ary_, ary, size);
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
template <size_t N>
inline tml::StaticBuffer<N>::StaticBuffer(const tml::StaticBuffer<N> &src)
{
	tml::Copy(this->ary_, src.ary_, src.len_);
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
template <size_t N>
inline tml::StaticBuffer<N> &tml::StaticBuffer<N>::operator =(const tml::StaticBuffer<N> &src)
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	tml::Copy(this->ary_, src.ary_, src.len_);
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
template <size_t N>
inline tml::StaticBuffer<N>::StaticBuffer(tml::StaticBuffer<N> &&src) noexcept
{
	tml::Copy(this->ary_, src.ary_, src.len_);
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_res_ = src.read_res_;
	this->write_index_ = src.write_index_;
	this->write_res_ = src.write_res_;

	src.Init();

	return;
}


/**
 * @brief operator =関数
 * @param src (src)
 * @return this (this)
 */
template <size_t N>
inline tml::StaticBuffer<N> &tml::StaticBuffer<N>::operator =(tml::StaticBuffer<N> &&src) noexcept
{
	if (this == &src) {
		return ((*this));
	}

	this->Release();

	tml::Copy(this->ary_, src.ary_, src.len_);
	this->size_ = src.size_;
	this->len_ = src.len_;
	this->read_index_ = src.read_index_;
	this->read_res_ = src.read_res_;
	this->write_index_ = src.write_index_;
	this->write_res_ = src.write_res_;

	src.Init();

	return ((*this));
}


/**
 * @brief デストラクタ
 */
template <size_t N>
inline tml::StaticBuffer<N>::~StaticBuffer()
{
	this->Release();

	return;
}


/**
 * @brief Release関数
 */
template <size_t N>
inline void tml::StaticBuffer<N>::Release(void)
{
	return;
}


/**
 * @brief Init関数
 */
template <size_t N>
inline void tml::StaticBuffer<N>::Init(void)
{
	this->Release();

	this->size_ = N;
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
template <size_t N>
inline void tml::StaticBuffer<N>::Init(const size_t size)
{
	this->Release();

	this->size_ = N;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->read_res_ = 0;
	this->write_index_ = 0U;
	this->write_res_ = 0;

	if (size > N) {
		return;
	}

	this->size_ = size;

	return;
}


/**
 * @brief Init関数
 * @param ary (array)
 * @param size (size)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::Init(const BYTE *ary, const size_t size)
{
	this->Release();

	this->size_ = N;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->read_res_ = 0;
	this->write_index_ = 0U;
	this->write_res_ = 0;

	if (size > N) {
		return;
	}

	tml::Copy(this->ary_, ary, size);
	this->size_ = size;
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

	return;
}


/**
 * @brief Get関数
 * @return ary (array)
 */
template <size_t N>
inline BYTE *tml::StaticBuffer<N>::Get(void)
{
	return (this->ary_);
}


/**
 * @brief Get関数
 * @return ary (array)
 */
template <size_t N>
inline const BYTE *tml::StaticBuffer<N>::Get(void) const
{
	return (this->ary_);
}


/**
 * @brief Set関数
 * @param ary (array)
 * @param size (size)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::Set(const BYTE *ary, const size_t size)
{
	if (size > N) {
		return;
	}

	tml::Copy(this->ary_, ary, size);
	this->size_ = size;
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

	return;
}


/**
 * @brief Clear関数
 */
template <size_t N>
inline void tml::StaticBuffer<N>::Clear(void)
{
	this->size_ = N;
	this->len_ = 0U;
	this->read_index_ = 0U;
	this->read_res_ = 0;
	this->write_index_ = 0U;
	this->write_res_ = 0;

	return;
}


/**
 * @brief GetSize関数
 * @return size (size)
 */
template <size_t N>
inline size_t tml::StaticBuffer<N>::GetSize(void) const
{
	return (this->size_);
}


/**
 * @brief SetSize関数
 * @param size (size)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::SetSize(const size_t size)
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
 * @brief GetLength関数
 * @return len (length)
 */
template <size_t N>
inline size_t tml::StaticBuffer<N>::GetLength(void) const
{
	return (this->len_);
}


/**
 * @brief SetLength関数
 * @param len (length)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::SetLength(const size_t len)
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
template <size_t N>
inline size_t tml::StaticBuffer<N>::GetReadIndex(void) const
{
	return (this->read_index_);
}


/**
 * @brief SetReadIndex関数
 * @param index (index)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::SetReadIndex(const size_t index)
{
	tml::MemoryUtil::SetBufferIndex(this->len_, this->read_index_, index, &this->read_res_);

	return;
}


/**
 * @brief AddReadIndex関数
 * @param add_index (add_index)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::AddReadIndex(const INT add_index)
{
	tml::MemoryUtil::AddBufferIndex(this->len_, this->read_index_, add_index, &this->read_res_);

	return;
}


/**
 * @brief GetReadResult関数
 * @return read_res (read_result)<br>
 * 0未満=失敗
 */
template <size_t N>
inline INT tml::StaticBuffer<N>::GetReadResult(void) const
{
	return (this->read_res_);
}


/**
 * @brief InitReadResult関数
 */
template <size_t N>
inline void tml::StaticBuffer<N>::InitReadResult(void)
{
	this->read_res_ = 0;

	return;
}


/**
 * @brief GetWriteIndex関数
 * @return write_index (write_index)
 */
template <size_t N>
inline size_t tml::StaticBuffer<N>::GetWriteIndex(void) const
{
	return (this->write_index_);
}


/**
 * @brief SetWriteIndex関数
 * @param index (index)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::SetWriteIndex(const size_t index)
{
	tml::MemoryUtil::SetBufferIndex(this->size_, this->write_index_, index, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief AddWriteIndex関数
 * @param add_index (add_index)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::AddWriteIndex(const INT add_index)
{
	tml::MemoryUtil::AddBufferIndex(this->size_, this->write_index_, add_index, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief GetWriteResult関数
 * @return write_res (write_result)<br>
 * 0未満=失敗
 */
template <size_t N>
inline INT tml::StaticBuffer<N>::GetWriteResult(void) const
{
	return (this->write_res_);
}


/**
 * @brief InitWriteResult関数
 */
template <size_t N>
inline void tml::StaticBuffer<N>::InitWriteResult(void)
{
	this->write_res_ = 0;

	return;
}


/**
 * @brief ReadCHAR関数
 * @return val (value)
 */
template <size_t N>
inline CHAR tml::StaticBuffer<N>::ReadCHAR(void)
{
	return (tml::MemoryUtil::ReadBufferCHAR(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUCHAR関数
 * @return val (value)
 */
template <size_t N>
inline UCHAR tml::StaticBuffer<N>::ReadUCHAR(void)
{
	return (tml::MemoryUtil::ReadBufferUCHAR(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadSHORT_B関数
 * @return val (value)
 */
template <size_t N>
inline SHORT tml::StaticBuffer<N>::ReadSHORT_B(void)
{
	return (tml::MemoryUtil::ReadBufferSHORT_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadSHORT_L関数
 * @return val (value)
 */
template <size_t N>
inline SHORT tml::StaticBuffer<N>::ReadSHORT_L(void)
{
	return (tml::MemoryUtil::ReadBufferSHORT_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUSHORT_B関数
 * @return val (value)
 */
template <size_t N>
inline USHORT tml::StaticBuffer<N>::ReadUSHORT_B(void)
{
	return (tml::MemoryUtil::ReadBufferUSHORT_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUSHORT_L関数
 * @return val (value)
 */
template <size_t N>
inline USHORT tml::StaticBuffer<N>::ReadUSHORT_L(void)
{
	return (tml::MemoryUtil::ReadBufferUSHORT_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadINT_B関数
 * @return val (value)
 */
template <size_t N>
inline INT tml::StaticBuffer<N>::ReadINT_B(void)
{
	return (tml::MemoryUtil::ReadBufferINT_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadINT_L関数
 * @return val (value)
 */
template <size_t N>
inline INT tml::StaticBuffer<N>::ReadINT_L(void)
{
	return (tml::MemoryUtil::ReadBufferINT_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUINT_B関数
 * @return val (value)
 */
template <size_t N>
inline UINT tml::StaticBuffer<N>::ReadUINT_B(void)
{
	return (tml::MemoryUtil::ReadBufferUINT_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUINT_L関数
 * @return val (value)
 */
template <size_t N>
inline UINT tml::StaticBuffer<N>::ReadUINT_L(void)
{
	return (tml::MemoryUtil::ReadBufferUINT_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadLONGLONG_B関数
 * @return val (value)
 */
template <size_t N>
inline LONGLONG tml::StaticBuffer<N>::ReadLONGLONG_B(void)
{
	return (tml::MemoryUtil::ReadBufferLONGLONG_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadLONGLONG_L関数
 * @return val (value)
 */
template <size_t N>
inline LONGLONG tml::StaticBuffer<N>::ReadLONGLONG_L(void)
{
	return (tml::MemoryUtil::ReadBufferLONGLONG_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadULONGLONG_B関数
 * @return val (value)
 */
template <size_t N>
inline ULONGLONG tml::StaticBuffer<N>::ReadULONGLONG_B(void)
{
	return (tml::MemoryUtil::ReadBufferULONGLONG_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadULONGLONG_L関数
 * @return val (value)
 */
template <size_t N>
inline ULONGLONG tml::StaticBuffer<N>::ReadULONGLONG_L(void)
{
	return (tml::MemoryUtil::ReadBufferULONGLONG_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadFLOAT_B関数
 * @return val (value)
 */
template <size_t N>
inline FLOAT tml::StaticBuffer<N>::ReadFLOAT_B(void)
{
	return (tml::MemoryUtil::ReadBufferFLOAT_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadFLOAT_L関数
 * @return val (value)
 */
template <size_t N>
inline FLOAT tml::StaticBuffer<N>::ReadFLOAT_L(void)
{
	return (tml::MemoryUtil::ReadBufferFLOAT_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadDOUBLE_B関数
 * @return val (value)
 */
template <size_t N>
inline DOUBLE tml::StaticBuffer<N>::ReadDOUBLE_B(void)
{
	return (tml::MemoryUtil::ReadBufferDOUBLE_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadDOUBLE_L関数
 * @return val (value)
 */
template <size_t N>
inline DOUBLE tml::StaticBuffer<N>::ReadDOUBLE_L(void)
{
	return (tml::MemoryUtil::ReadBufferDOUBLE_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadArray関数
 * @param dst_ary (dst_array)
 * @param dst_ary_size (dst_array_size)
 * @param read_size (read_size)
 * @return dst_ary (dst_array)
 */
template <size_t N>
inline BYTE *tml::StaticBuffer<N>::ReadArray(BYTE *dst_ary, const size_t dst_ary_size, const size_t read_size)
{
	return (tml::MemoryUtil::ReadBufferArray(dst_ary, dst_ary_size, this->ary_, this->len_, this->read_index_, read_size, &this->read_res_));
}


/**
 * @brief ReadString_B関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <size_t N>
inline CHAR *tml::StaticBuffer<N>::ReadString_B(CHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferString_B(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadString_L関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <size_t N>
inline CHAR *tml::StaticBuffer<N>::ReadString_L(CHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferString_L(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadString_B関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <size_t N>
inline WCHAR *tml::StaticBuffer<N>::ReadString_B(WCHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferString_B(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadString_L関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
template <size_t N>
inline WCHAR *tml::StaticBuffer<N>::ReadString_L(WCHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferString_L(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief WriteCHAR関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteCHAR(const CHAR val)
{
	tml::MemoryUtil::WriteBufferCHAR(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUCHAR関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteUCHAR(const UCHAR val)
{
	tml::MemoryUtil::WriteBufferUCHAR(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteSHORT_B関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteSHORT_B(const SHORT val)
{
	tml::MemoryUtil::WriteBufferSHORT_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteSHORT_L関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteSHORT_L(const SHORT val)
{
	tml::MemoryUtil::WriteBufferSHORT_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUSHORT_B関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteUSHORT_B(const USHORT val)
{
	tml::MemoryUtil::WriteBufferUSHORT_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUSHORT_L関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteUSHORT_L(const USHORT val)
{
	tml::MemoryUtil::WriteBufferUSHORT_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteINT_B関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteINT_B(const INT val)
{
	tml::MemoryUtil::WriteBufferINT_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteINT_L関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteINT_L(const INT val)
{
	tml::MemoryUtil::WriteBufferINT_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUINT_B関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteUINT_B(const UINT val)
{
	tml::MemoryUtil::WriteBufferUINT_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUINT_L関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteUINT_L(const UINT val)
{
	tml::MemoryUtil::WriteBufferUINT_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteLONGLONG_B関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteLONGLONG_B(const LONGLONG val)
{
	tml::MemoryUtil::WriteBufferLONGLONG_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteLONGLONG_L関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteLONGLONG_L(const LONGLONG val)
{
	tml::MemoryUtil::WriteBufferLONGLONG_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteULONGLONG_B関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteULONGLONG_B(const ULONGLONG val)
{
	tml::MemoryUtil::WriteBufferULONGLONG_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteULONGLONG_L関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteULONGLONG_L(const ULONGLONG val)
{
	tml::MemoryUtil::WriteBufferULONGLONG_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteFLOAT_B関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteFLOAT_B(const FLOAT val)
{
	tml::MemoryUtil::WriteBufferFLOAT_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteFLOAT_L関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteFLOAT_L(const FLOAT val)
{
	tml::MemoryUtil::WriteBufferFLOAT_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteDOUBLE_B関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteDOUBLE_B(const DOUBLE val)
{
	tml::MemoryUtil::WriteBufferDOUBLE_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteDOUBLE_L関数
 * @param val (value)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteDOUBLE_L(const DOUBLE val)
{
	tml::MemoryUtil::WriteBufferDOUBLE_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteArray関数
 * @param ary (array)
 * @param ary_size (array_size)
 * @param write_size (write_size)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteArray(const BYTE *ary, const size_t ary_size, const size_t write_size)
{
	tml::MemoryUtil::WriteBufferArray(this->ary_, this->size_, this->write_index_, ary, ary_size, write_size, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteString_B関数
 * @param str (string)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteString_B(const CHAR *str)
{
	tml::MemoryUtil::WriteBufferString_B(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteString_L関数
 * @param str (string)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteString_L(const CHAR *str)
{
	tml::MemoryUtil::WriteBufferString_L(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteString_B関数
 * @param str (string)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteString_B(const WCHAR *str)
{
	tml::MemoryUtil::WriteBufferString_B(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteString_L関数
 * @param str (string)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::WriteString_L(const WCHAR *str)
{
	tml::MemoryUtil::WriteBufferString_L(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}
