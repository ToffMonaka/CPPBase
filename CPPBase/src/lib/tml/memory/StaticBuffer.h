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
public: StaticBuffer(const StaticBuffer &) = delete;
public: StaticBuffer &operator =(const StaticBuffer &) = delete;

private:
	BYTE ary_[N];
	size_t size_;
	size_t len_;

private:
	void Release(void);

public:
	StaticBuffer();
	virtual ~StaticBuffer();

	void Init(void);

	BYTE *GetArray(void);
	void SetArray(const BYTE *, const size_t);
	size_t GetSize(void) const;
	size_t GetLength(void) const;
	void SetLength(const size_t);
};
}


/**
 * @brief コンストラクタ
 */
template <size_t N>
inline tml::StaticBuffer<N>::StaticBuffer() :
	size_(N),
	len_(0U)
{
	return;
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

	return;
}


/**
 * @brief GetArray関数
 * @return ary (array)
 */
template <size_t N>
inline BYTE *tml::StaticBuffer<N>::GetArray(void)
{
	return (this->ary_);
}


/**
 * @brief SetArray関数
 * @param ary (array)
 * @param len (length)
 */
template <size_t N>
inline void tml::StaticBuffer<N>::SetArray(const BYTE *ary, const size_t len)
{
	if (len > this->size_) {
		return;
	}

	tml::MemoryUtil::Copy(this->ary_, ary, len);
	this->len_ = len;

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
void tml::StaticBuffer<N>::SetLength(const size_t len)
{
	this->len_ = std::min(len, this->size_);

	return;
}
