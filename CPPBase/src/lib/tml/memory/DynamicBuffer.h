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

private:
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

	BYTE *Get(void);
	const BYTE *Get(void) const;
	void Set(const size_t, const bool keep_flg = false);
	void Set(const BYTE *, const size_t);
	void Clear(void);
	size_t GetSize(void) const;
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
 * @brief GetSize関数
 * @return size (size)
 */
inline size_t tml::DynamicBuffer::GetSize(void) const
{
	return (this->size_);
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
	this->len_ = std::min(len, this->size_);
	this->read_index_ = std::min(this->read_index_, this->len_);
	this->write_index_ = std::min(this->write_index_, this->len_);

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
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief AddWriteIndex関数
 * @param add_index (add_index)
 */
inline void tml::DynamicBuffer::AddWriteIndex(const INT add_index)
{
	tml::MemoryUtil::AddBufferIndex(this->size_, this->write_index_, add_index, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

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
 * @brief ReadCHAR関数
 * @return val (value)
 */
inline CHAR tml::DynamicBuffer::ReadCHAR(void)
{
	return (tml::MemoryUtil::ReadBufferCHAR(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUCHAR関数
 * @return val (value)
 */
inline UCHAR tml::DynamicBuffer::ReadUCHAR(void)
{
	return (tml::MemoryUtil::ReadBufferUCHAR(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadSHORT_B関数
 * @return val (value)
 */
inline SHORT tml::DynamicBuffer::ReadSHORT_B(void)
{
	return (tml::MemoryUtil::ReadBufferSHORT_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadSHORT_L関数
 * @return val (value)
 */
inline SHORT tml::DynamicBuffer::ReadSHORT_L(void)
{
	return (tml::MemoryUtil::ReadBufferSHORT_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUSHORT_B関数
 * @return val (value)
 */
inline USHORT tml::DynamicBuffer::ReadUSHORT_B(void)
{
	return (tml::MemoryUtil::ReadBufferUSHORT_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUSHORT_L関数
 * @return val (value)
 */
inline USHORT tml::DynamicBuffer::ReadUSHORT_L(void)
{
	return (tml::MemoryUtil::ReadBufferUSHORT_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadINT_B関数
 * @return val (value)
 */
inline INT tml::DynamicBuffer::ReadINT_B(void)
{
	return (tml::MemoryUtil::ReadBufferINT_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadINT_L関数
 * @return val (value)
 */
inline INT tml::DynamicBuffer::ReadINT_L(void)
{
	return (tml::MemoryUtil::ReadBufferINT_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUINT_B関数
 * @return val (value)
 */
inline UINT tml::DynamicBuffer::ReadUINT_B(void)
{
	return (tml::MemoryUtil::ReadBufferUINT_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadUINT_L関数
 * @return val (value)
 */
inline UINT tml::DynamicBuffer::ReadUINT_L(void)
{
	return (tml::MemoryUtil::ReadBufferUINT_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadLONGLONG_B関数
 * @return val (value)
 */
inline LONGLONG tml::DynamicBuffer::ReadLONGLONG_B(void)
{
	return (tml::MemoryUtil::ReadBufferLONGLONG_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadLONGLONG_L関数
 * @return val (value)
 */
inline LONGLONG tml::DynamicBuffer::ReadLONGLONG_L(void)
{
	return (tml::MemoryUtil::ReadBufferLONGLONG_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadULONGLONG_B関数
 * @return val (value)
 */
inline ULONGLONG tml::DynamicBuffer::ReadULONGLONG_B(void)
{
	return (tml::MemoryUtil::ReadBufferULONGLONG_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadULONGLONG_L関数
 * @return val (value)
 */
inline ULONGLONG tml::DynamicBuffer::ReadULONGLONG_L(void)
{
	return (tml::MemoryUtil::ReadBufferULONGLONG_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadFLOAT_B関数
 * @return val (value)
 */
inline FLOAT tml::DynamicBuffer::ReadFLOAT_B(void)
{
	return (tml::MemoryUtil::ReadBufferFLOAT_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadFLOAT_L関数
 * @return val (value)
 */
inline FLOAT tml::DynamicBuffer::ReadFLOAT_L(void)
{
	return (tml::MemoryUtil::ReadBufferFLOAT_L(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadDOUBLE_B関数
 * @return val (value)
 */
inline DOUBLE tml::DynamicBuffer::ReadDOUBLE_B(void)
{
	return (tml::MemoryUtil::ReadBufferDOUBLE_B(this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadDOUBLE_L関数
 * @return val (value)
 */
inline DOUBLE tml::DynamicBuffer::ReadDOUBLE_L(void)
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
inline BYTE *tml::DynamicBuffer::ReadArray(BYTE *dst_ary, const size_t dst_ary_size, const size_t read_size)
{
	return (tml::MemoryUtil::ReadBufferArray(dst_ary, dst_ary_size, this->ary_, this->len_, this->read_index_, read_size, &this->read_res_));
}


/**
 * @brief ReadString_B関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
inline CHAR *tml::DynamicBuffer::ReadString_B(CHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferString_B(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadString_L関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
inline CHAR *tml::DynamicBuffer::ReadString_L(CHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferString_L(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadString_B関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
inline WCHAR *tml::DynamicBuffer::ReadString_B(WCHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferString_B(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief ReadString_L関数
 * @param dst_str (dst_string)
 * @param dst_str_size (dst_string_size)
 * @return dst_str (dst_string)
 */
inline WCHAR *tml::DynamicBuffer::ReadString_L(WCHAR *dst_str, const size_t dst_str_size)
{
	return (tml::MemoryUtil::ReadBufferString_L(dst_str, dst_str_size, this->ary_, this->len_, this->read_index_, &this->read_res_));
}


/**
 * @brief WriteCHAR関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteCHAR(const CHAR val)
{
	tml::MemoryUtil::WriteBufferCHAR(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUCHAR関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteUCHAR(const UCHAR val)
{
	tml::MemoryUtil::WriteBufferUCHAR(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteSHORT_B関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteSHORT_B(const SHORT val)
{
	tml::MemoryUtil::WriteBufferSHORT_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteSHORT_L関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteSHORT_L(const SHORT val)
{
	tml::MemoryUtil::WriteBufferSHORT_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUSHORT_B関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteUSHORT_B(const USHORT val)
{
	tml::MemoryUtil::WriteBufferUSHORT_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUSHORT_L関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteUSHORT_L(const USHORT val)
{
	tml::MemoryUtil::WriteBufferUSHORT_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteINT_B関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteINT_B(const INT val)
{
	tml::MemoryUtil::WriteBufferINT_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteINT_L関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteINT_L(const INT val)
{
	tml::MemoryUtil::WriteBufferINT_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUINT_B関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteUINT_B(const UINT val)
{
	tml::MemoryUtil::WriteBufferUINT_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteUINT_L関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteUINT_L(const UINT val)
{
	tml::MemoryUtil::WriteBufferUINT_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteLONGLONG_B関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteLONGLONG_B(const LONGLONG val)
{
	tml::MemoryUtil::WriteBufferLONGLONG_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteLONGLONG_L関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteLONGLONG_L(const LONGLONG val)
{
	tml::MemoryUtil::WriteBufferLONGLONG_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteULONGLONG_B関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteULONGLONG_B(const ULONGLONG val)
{
	tml::MemoryUtil::WriteBufferULONGLONG_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteULONGLONG_L関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteULONGLONG_L(const ULONGLONG val)
{
	tml::MemoryUtil::WriteBufferULONGLONG_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteFLOAT_B関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteFLOAT_B(const FLOAT val)
{
	tml::MemoryUtil::WriteBufferFLOAT_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteFLOAT_L関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteFLOAT_L(const FLOAT val)
{
	tml::MemoryUtil::WriteBufferFLOAT_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteDOUBLE_B関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteDOUBLE_B(const DOUBLE val)
{
	tml::MemoryUtil::WriteBufferDOUBLE_B(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteDOUBLE_L関数
 * @param val (value)
 */
inline void tml::DynamicBuffer::WriteDOUBLE_L(const DOUBLE val)
{
	tml::MemoryUtil::WriteBufferDOUBLE_L(this->ary_, this->size_, this->write_index_, val, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

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
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteString_B関数
 * @param str (string)
 */
inline void tml::DynamicBuffer::WriteString_B(const CHAR *str)
{
	tml::MemoryUtil::WriteBufferString_B(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteString_L関数
 * @param str (string)
 */
inline void tml::DynamicBuffer::WriteString_L(const CHAR *str)
{
	tml::MemoryUtil::WriteBufferString_L(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteString_B関数
 * @param str (string)
 */
inline void tml::DynamicBuffer::WriteString_B(const WCHAR *str)
{
	tml::MemoryUtil::WriteBufferString_B(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}


/**
 * @brief WriteString_L関数
 * @param str (string)
 */
inline void tml::DynamicBuffer::WriteString_L(const WCHAR *str)
{
	tml::MemoryUtil::WriteBufferString_L(this->ary_, this->size_, this->write_index_, str, &this->write_res_);
	this->len_ = std::max(this->len_, this->write_index_);

	return;
}
