/**
 * @file
 * @brief DlmallocAllocatorヘッダーファイル
 */
#pragma once


#include "../dlmalloc/malloc.h"
#include "../ConstantUtil.h"
#include "Allocator.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief DlmallocAllocatorクラス
 */
class DlmallocAllocator : public tml::Allocator
{
public: DlmallocAllocator(const DlmallocAllocator &) = delete;
public: DlmallocAllocator &operator =(const DlmallocAllocator &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	mspace ms_;
	size_t ms_cnt_head_size_;
	tml::SpinThreadLock ms_th_lock_;

private:
	void Release(void);

public:
	DlmallocAllocator();
	virtual ~DlmallocAllocator();

	virtual void Init(void);
	INT Create(const size_t);
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
inline T *tml::DlmallocAllocator::Get(const size_t cnt)
{
	if (cnt <= 0U) {
		return (NULLP);
	}

	T *p = NULLP;

	this->ms_th_lock_.Lock();

	if (this->ms_ == NULLP) {
		this->ms_th_lock_.Unlock();

		return (NULLP);
	}

	void *ms_p = mspace_malloc(this->ms_, sizeof(T) * cnt + this->ms_cnt_head_size_);

	if (std::is_class<T>::value) {
		(*(reinterpret_cast<size_t *>(reinterpret_cast<BYTE *>(ms_p)))) = cnt;

		p = reinterpret_cast<T *>(reinterpret_cast<BYTE *>(ms_p) + this->ms_cnt_head_size_);

		for (size_t p_i = 0U; p_i < cnt; ++p_i) {
			new(p + p_i) T();
		}
	} else {
		(*(reinterpret_cast<size_t *>(reinterpret_cast<BYTE *>(ms_p)))) = 0U;

		p = reinterpret_cast<T *>(reinterpret_cast<BYTE *>(ms_p) + this->ms_cnt_head_size_);
	}

	this->ms_th_lock_.Unlock();

	return (p);
}


/**
 * @brief Release関数
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::DlmallocAllocator::Release(T **pp)
{
	if ((*pp) == NULLP) {
		return;
	}

	this->ms_th_lock_.Lock();

	size_t cnt = (*(reinterpret_cast<size_t *>(reinterpret_cast<BYTE *>(*pp) - this->ms_cnt_head_size_)));

	for (size_t pp_i = 0U; pp_i < cnt; ++pp_i) {
		(*pp)[pp_i].~T();
	}

	void *ms_p = reinterpret_cast<BYTE *>(*pp) - this->ms_cnt_head_size_;

	mspace_free(this->ms_, ms_p);

	(*pp) = NULLP;

	this->ms_th_lock_.Unlock();

	return;
}
}
