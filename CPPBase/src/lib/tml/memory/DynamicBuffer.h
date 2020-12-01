/**
 * @file
 * @brief DynamicBuffer�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
/**
 * @brief DynamicBuffer�N���X
 */
class DynamicBuffer
{
public: DynamicBuffer(const DynamicBuffer &) = delete;
public: DynamicBuffer &operator =(const DynamicBuffer &) = delete;

private:
	BYTE *ary_;
	size_t size_;
	size_t len_;

private:
	void Release(void);

public:
	DynamicBuffer();
	DynamicBuffer(const size_t);
	virtual ~DynamicBuffer();

	void Init(void);

	BYTE *GetArray(void);
	void SetArray(const BYTE *, const size_t);
	size_t GetSize(void) const;
	void SetSize(const size_t, const bool keep_flg = false);
	size_t GetLength(void) const;
	void SetLength(const size_t);
};
}


/**
 * @brief GetArray�֐�
 * @return ary (array)
 */
inline BYTE *tml::DynamicBuffer::GetArray(void)
{
	return (this->ary_);
}


/**
 * @brief GetSize�֐�
 * @return size (size)
 */
inline size_t tml::DynamicBuffer::GetSize(void) const
{
	return (this->size_);
}


/**
 * @brief GetLength�֐�
 * @return len (length)
 */
inline size_t tml::DynamicBuffer::GetLength(void) const
{
	return (this->len_);
}
