/**
 * @file
 * @brief MallocAllocatorヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "Allocator.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief MallocAllocatorクラス
 */
class MallocAllocator : public tml::Allocator
{
public: MallocAllocator(const MallocAllocator &) = delete;
public: MallocAllocator &operator =(const MallocAllocator &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	size_t ms_size_;
	size_t ms_use_size_;
	tml::SpinThreadLock ms_th_lock_;

private:
	void Release(void);

public:
	MallocAllocator();
	virtual ~MallocAllocator();

	void Init(void);
	INT Create(void);
	template <typename T>
	T *Get(const size_t);
	template <typename T>
	void Release(T **);
	tml::Allocator::INFO GetInfo(void);
};


/**
 * @brief Get関数
 * @param cnt (count)
 * @return p (pointer)<br>
 * NULLP=失敗
 */
template <typename T>
inline T *tml::MallocAllocator::Get(const size_t cnt)
{
	if (cnt <= 0U) {
		return (NULLP);
	}

	T *p = NULLP;

	this->ms_th_lock_.Lock();

	if (this->ms_size_ <= 0U) {
		this->ms_th_lock_.Unlock();

		return (NULLP);
	}

	p = static_cast<T *>(std::malloc(sizeof(T) * cnt));

	if (p == NULLP) {
		this->ms_th_lock_.Unlock();

		return (NULLP);
	}

	++this->ms_use_size_;

	this->ms_th_lock_.Unlock();

	return (p);
}


/**
 * @brief Release関数
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::MallocAllocator::Release(T **pp)
{
	if ((*pp) == NULLP) {
		return;
	}

	this->ms_th_lock_.Lock();

	std::free((*pp));

	(*pp) = NULLP;

	--this->ms_use_size_;

	this->ms_th_lock_.Unlock();

	return;
}
}
