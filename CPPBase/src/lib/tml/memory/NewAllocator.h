/**
 * @file
 * @brief NewAllocatorヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "Allocator.h"


namespace tml {
/**
 * @brief NewAllocatorクラス
 */
class NewAllocator : public tml::Allocator
{
public: NewAllocator(const NewAllocator &) = delete;
public: NewAllocator &operator =(const NewAllocator &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	size_t ms_size_;
	size_t ms_use_size_;

private:
	void Release(void);

public:
	NewAllocator();
	virtual ~NewAllocator();

	virtual void Init(void);
	INT Create(void);
	template <typename T>
	T *Get(const size_t);
	template <typename T>
	void Release(T **);
	virtual tml::Allocator::INFO GetInfo(void);
};


/**
 * @brief Get関数
 * @param cnt (count)
 * @return p (pointer)<br>
 * NULLP=失敗
 */
template <typename T>
inline T *tml::NewAllocator::Get(const size_t cnt)
{
	if (cnt <= 0U) {
		return (NULLP);
	}

	T *p = NULLP;

	if (this->ms_size_ <= 0U) {
		return (NULLP);
	}

	p = new T[cnt];

	if (p == NULLP) {
		return (NULLP);
	}

	++this->ms_use_size_;

	return (p);
}


/**
 * @brief Release関数
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::NewAllocator::Release(T **pp)
{
	if ((*pp) == NULLP) {
		return;
	}

	delete [] ((*pp));

	(*pp) = NULLP;

	--this->ms_use_size_;

	return;
}
}
