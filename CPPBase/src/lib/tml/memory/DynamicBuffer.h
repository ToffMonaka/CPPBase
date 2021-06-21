/**
 * @file
 * @brief DynamicBufferヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "MemoryUtil.h"


namespace tml {
/**
 * @brief DynamicBufferクラス
 */
class DynamicBuffer
{
private:
	BYTE *ary_;
	size_t size_;
	size_t len_;
	size_t read_index_;
	INT read_res_;
	size_t write_index_;
	INT write_res_;

protected:
	void Release(void);

public:
	DynamicBuffer();
	DynamicBuffer(const size_t);
	DynamicBuffer(const BYTE *, const size_t);
	DynamicBuffer(const tml::DynamicBuffer &);
	tml::DynamicBuffer &operator =(const tml::DynamicBuffer &);
	DynamicBuffer(tml::DynamicBuffer &&) noexcept;
	tml::DynamicBuffer &operator =(tml::DynamicBuffer &&) noexcept;
	virtual ~DynamicBuffer();

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
 * @brief Get関数
 * @return ary (array)
 */
inline BYTE *tml::DynamicBuffer::Get(void)
{
	return (this->ary_);
}


/**
 * @brief Get関数
 * @return ary (array)
 */
inline const BYTE *tml::DynamicBuffer::Get(void) const
{
	return (this->ary_);
}


/**
 * @brief Set関数
 * @param ary (array)
 * @param size (size)
 */
inline void tml::DynamicBuffer::Set(const BYTE *ary, const size_t size)
{
	if (size > this->size_) {
		auto ary = tml::MemoryUtil::Get<BYTE>(size);

		tml::MemoryUtil::Release(&this->ary_);

		this->ary_ = ary;
	}

	tml::Copy(this->ary_, ary, size);
	this->size_ = size;
	this->len_ = this->size_;
	this->read_index_ = 0U;
	this->write_index_ = this->size_;

	return;
}


/**
 * @brief GetSize関数
 * @return size (size)
 */
inline size_t tml::DynamicBuffer::GetSize(void) const
{
	return (this->size_);
}


/**
 * @brief SetSize関数
 * @param size (size)
 */
inline void tml::DynamicBuffer::SetSize(const size_t size)
{
	if (size > this->size_) {
		auto ary = tml::MemoryUtil::Get<BYTE>(size);

		tml::Copy(ary, this->ary_, this->size_);

		tml::MemoryUtil::Release(&this->ary_);

		this->ary_ = ary;
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
inline size_t tml::DynamicBuffer::GetLength(void) const
{
	return (this->len_);
}


/**
 * @brief SetLength関数
 * @param len (length)
 */
inline void tml::DynamicBuffer::SetLength(const size_t len)
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
inline size_t tml::DynamicBuffer::GetReadIndex(void) const
{
	return (this->read_index_);
}


/**
 * @brief SetReadIndex関数
 * @param index (index)
 */
inline void tml::DynamicBuffer::SetReadIndex(const size_t index)
{
	tml::MemoryUtil::SetBufferIndex(this->len_, this->read_index_, index, &this->read_res_);

	return;
}


/**
 * @brief AddReadIndex関数
 * @param add_index (add_index)
 */
inline void tml::DynamicBuffer::AddReadIndex(const INT add_index)
{
	tml::MemoryUtil::AddBufferIndex(this->len_, this->read_index_, add_index, &this->read_res_);

	return;
}


/**
 * @brief GetReadResult関数
 * @return read_res (read_result)<br>
 * 0未満=失敗
 */
inline INT tml::DynamicBuffer::GetReadResult(void) const
{
	return (this->read_res_);
}


/**
 * @brief InitReadResult関数
 */
inline void tml::DynamicBuffer::InitReadResult(void)
{
	this->read_res_ = 0;

	return;
}


/**
 * @brief GetWriteIndex関数
 * @return write_index (write_index)
 */
inline size_t tml::DynamicBuffer::GetWriteIndex(void) const
{
	return (this->write_index_);
}


/**
 * @brief SetWriteIndex関数
 * @param index (index)
 */
inline void tml::DynamicBuffer::SetWriteIndex(const size_t index)
{
	tml::MemoryUtil::SetBufferIndex(this->size_, this->write_index_, index, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief AddWriteIndex関数
 * @param add_index (add_index)
 */
inline void tml::DynamicBuffer::AddWriteIndex(const INT add_index)
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
inline INT tml::DynamicBuffer::GetWriteResult(void) const
{
	return (this->write_res_);
}


/**
 * @brief InitWriteResult関数
 */
inline void tml::DynamicBuffer::InitWriteResult(void)
{
	this->write_res_ = 0;

	return;
}


/**
 * @brief ReadChar関数
 * @return val (value)
 */
inline CHAR tml::DynamicBuffer::ReadChar(void)
{
	return (tml::MemoryUtil::ReadBufferChar(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUChar関数
 * @return val (value)
 */
inline UCHAR tml::DynamicBuffer::ReadUChar(void)
{
	return (tml::MemoryUtil::ReadBufferUChar(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadShortB関数
 * @return val (value)
 */
inline SHORT tml::DynamicBuffer::ReadShortB(void)
{
	return (tml::MemoryUtil::ReadBufferShortB(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadShortL関数
 * @return val (value)
 */
inline SHORT tml::DynamicBuffer::ReadShortL(void)
{
	return (tml::MemoryUtil::ReadBufferShortL(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUShortB関数
 * @return val (value)
 */
inline USHORT tml::DynamicBuffer::ReadUShortB(void)
{
	return (tml::MemoryUtil::ReadBufferUShortB(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUShortL関数
 * @return val (value)
 */
inline USHORT tml::DynamicBuffer::ReadUShortL(void)
{
	return (tml::MemoryUtil::ReadBufferUShortL(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadIntB関数
 * @return val (value)
 */
inline INT tml::DynamicBuffer::ReadIntB(void)
{
	return (tml::MemoryUtil::ReadBufferIntB(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadIntL関数
 * @return val (value)
 */
inline INT tml::DynamicBuffer::ReadIntL(void)
{
	return (tml::MemoryUtil::ReadBufferIntL(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUIntB関数
 * @return val (value)
 */
inline UINT tml::DynamicBuffer::ReadUIntB(void)
{
	return (tml::MemoryUtil::ReadBufferUIntB(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUIntL関数
 * @return val (value)
 */
inline UINT tml::DynamicBuffer::ReadUIntL(void)
{
	return (tml::MemoryUtil::ReadBufferUIntL(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadLongLongB関数
 * @return val (value)
 */
inline LONGLONG tml::DynamicBuffer::ReadLongLongB(void)
{
	return (tml::MemoryUtil::ReadBufferLongLongB(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadLongLongL関数
 * @return val (value)
 */
inline LONGLONG tml::DynamicBuffer::ReadLongLongL(void)
{
	return (tml::MemoryUtil::ReadBufferLongLongL(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadULongLongB関数
 * @return val (value)
 */
inline ULONGLONG tml::DynamicBuffer::ReadULongLongB(void)
{
	return (tml::MemoryUtil::ReadBufferULongLongB(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadULongLongL関数
 * @return val (value)
 */
inline ULONGLONG tml::DynamicBuffer::ReadULongLongL(void)
{
	return (tml::MemoryUtil::ReadBufferULongLongL(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadFloatB関数
 * @return val (value)
 */
inline FLOAT tml::DynamicBuffer::ReadFloatB(void)
{
	return (tml::MemoryUtil::ReadBufferFloatB(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadFloatL関数
 * @return val (value)
 */
inline FLOAT tml::DynamicBuffer::ReadFloatL(void)
{
	return (tml::MemoryUtil::ReadBufferFloatL(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadDoubleB関数
 * @return val (value)
 */
inline DOUBLE tml::DynamicBuffer::ReadDoubleB(void)
{
	return (tml::MemoryUtil::ReadBufferDoubleB(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadDoubleL関数
 * @return val (value)
 */
inline DOUBLE tml::DynamicBuffer::ReadDoubleL(void)
{
	return (tml::MemoryUtil::ReadBufferDoubleL(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadArray関数
 * @param dst_ary (dst_array)
 * @param dst_ary_size (dst_array_size)
 * @param read_size (read_size)
 * @return dst_ary (dst_array)
 */
inline BYTE *tml::DynamicBuffer::ReadArray(BYTE *dst_ary, const size_t dst_ary_size, const size_t read_size)
{
	return (tml::MemoryUtil::ReadBufferArray(dst_ary, dst_ary_size, this->ary_, this->len_, this->read_index_, read_size, &this->read_res_));
}


/**
 * @brief ReadStringB関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
inline CHAR *tml::DynamicBuffer::ReadStringB(CHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringB(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadStringL関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
inline CHAR *tml::DynamicBuffer::ReadStringL(CHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringL(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadStringB関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
inline WCHAR *tml::DynamicBuffer::ReadStringB(WCHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringB(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadStringL関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
inline WCHAR *tml::DynamicBuffer::ReadStringL(WCHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferStringL(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief WriteChar関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteChar(const CHAR val)
{
	tml::MemoryUtil::WriteBufferChar(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUChar関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteUChar(const UCHAR val)
{
	tml::MemoryUtil::WriteBufferUChar(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteShortB関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteShortB(const SHORT val)
{
	tml::MemoryUtil::WriteBufferShortB(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteShortL関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteShortL(const SHORT val)
{
	tml::MemoryUtil::WriteBufferShortL(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUShortB関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteUShortB(const USHORT val)
{
	tml::MemoryUtil::WriteBufferUShortB(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUShortL関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteUShortL(const USHORT val)
{
	tml::MemoryUtil::WriteBufferUShortL(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteIntB関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteIntB(const INT val)
{
	tml::MemoryUtil::WriteBufferIntB(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteIntL関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteIntL(const INT val)
{
	tml::MemoryUtil::WriteBufferIntL(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUIntB関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteUIntB(const UINT val)
{
	tml::MemoryUtil::WriteBufferUIntB(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUIntL関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteUIntL(const UINT val)
{
	tml::MemoryUtil::WriteBufferUIntL(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteLongLongB関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteLongLongB(const LONGLONG val)
{
	tml::MemoryUtil::WriteBufferLongLongB(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteLongLongL関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteLongLongL(const LONGLONG val)
{
	tml::MemoryUtil::WriteBufferLongLongL(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteULongLongB関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteULongLongB(const ULONGLONG val)
{
	tml::MemoryUtil::WriteBufferULongLongB(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteULongLongL関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteULongLongL(const ULONGLONG val)
{
	tml::MemoryUtil::WriteBufferULongLongL(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteFloatB関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteFloatB(const FLOAT val)
{
	tml::MemoryUtil::WriteBufferFloatB(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteFloatL関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteFloatL(const FLOAT val)
{
	tml::MemoryUtil::WriteBufferFloatL(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteDoubleB関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteDoubleB(const DOUBLE val)
{
	tml::MemoryUtil::WriteBufferDoubleB(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteDoubleL関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteDoubleL(const DOUBLE val)
{
	tml::MemoryUtil::WriteBufferDoubleL(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteArray関数
 * @param ary (array)
 * @param ary_size (array_size)
 * @param write_size (write_size)
 */
inline void tml::DynamicBuffer::WriteArray(const BYTE *ary, const size_t ary_size, const size_t write_size)
{
	tml::MemoryUtil::WriteBufferArray(this->ary_, this->size_, this->write_index_, ary, ary_size, write_size, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringB関数
 * @param str (string)
 */
inline void tml::DynamicBuffer::WriteStringB(const CHAR *str)
{
	tml::MemoryUtil::WriteBufferStringB(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringL関数
 * @param str (string)
 */
inline void tml::DynamicBuffer::WriteStringL(const CHAR *str)
{
	tml::MemoryUtil::WriteBufferStringL(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringB関数
 * @param str (string)
 */
inline void tml::DynamicBuffer::WriteStringB(const WCHAR *str)
{
	tml::MemoryUtil::WriteBufferStringB(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteStringL関数
 * @param str (string)
 */
inline void tml::DynamicBuffer::WriteStringL(const WCHAR *str)
{
	tml::MemoryUtil::WriteBufferStringL(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = tml::Max(this->len_, this->write_index_);

	return;
}
