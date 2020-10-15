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
	mspace ms;
	tml::SpinThreadLock ms_th_lock_;
	INT alignment;
	INT cnt_head_size;
	INT offset_head_size;
	INT head_size;

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

	void *ms_p = NULLP;

	this->ms_th_lock_.Lock();

	if (this->ms == NULLP) {
		this->ms_th_lock_.Unlock();

		return (NULLP);
	}

	ms_p = mspace_memalign(this->ms, this->alignment, sizeof(T) * cnt + this->cnt_head_size + this->head_size);

	this->ms_th_lock_.Unlock();

	p = new(reinterpret_cast<BYTE *>(ms_p) + this->head_size) T[cnt];

	if (reinterpret_cast<BYTE *>(p) == (reinterpret_cast<BYTE *>(ms_p) + this->head_size)) {
		(*(reinterpret_cast<size_t *>(reinterpret_cast<BYTE *>(p) - this->cnt_head_size))) = 0U;
		(*(reinterpret_cast<size_t *>(reinterpret_cast<BYTE *>(p) - this->cnt_head_size - this->offset_head_size))) = 0U;
	} else if (reinterpret_cast<BYTE *>(p) == (reinterpret_cast<BYTE *>(ms_p) + this->cnt_head_size + this->head_size)) {
		(*(reinterpret_cast<size_t *>(reinterpret_cast<BYTE *>(p) - this->cnt_head_size - this->offset_head_size))) = this->cnt_head_size;
	} else {
		return (NULLP);
	}

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

	size_t cnt = (*(reinterpret_cast<size_t *>(reinterpret_cast<BYTE *>(*pp) - this->cnt_head_size)));
	size_t offset = (*(reinterpret_cast<size_t *>(reinterpret_cast<BYTE *>(*pp) - this->cnt_head_size - this->offset_head_size)));

	for (size_t pp_i = 0U; pp_i < cnt; ++pp_i) {
		(*pp)[pp_i].~T();
	}

	void *ms_p = reinterpret_cast<BYTE *>(*pp) - offset - this->head_size;

	(*pp) = NULLP;

	this->ms_th_lock_.Lock();

	mspace_free(this->ms, ms_p);

	this->ms_th_lock_.Unlock();

	return;
}
}
