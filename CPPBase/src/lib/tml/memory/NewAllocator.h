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
	size_t ms_cnt_head_size_;

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
	BYTE *GetMemorySpacePart(const size_t);
	template <typename T>
	T *GetConstructorPart(BYTE *, const size_t);
	template <typename T>
	void Release(T **);
	template <typename T>
	BYTE *ReleaseDestructorPart(T **);
	template <typename T>
	void ReleaseMemorySpacePart(BYTE *, T **);
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
	return (this->GetConstructorPart<T>(this->GetMemorySpacePart<T>(cnt), cnt));
}


/**
 * @brief GetMemorySpacePart関数
 * @param cnt (count)
 * @return ms_p (memory_space_pointer)<br>
 * NULLP=失敗
 */
template <typename T>
inline BYTE *tml::NewAllocator::GetMemorySpacePart(const size_t cnt)
{
	if (cnt <= 0U) {
		return (NULLP);
	}

	if (this->ms_size_ <= 0U) {
		return (NULLP);
	}

	BYTE *ms_p = new BYTE[sizeof(T) * cnt + this->ms_cnt_head_size_];

	if (ms_p == NULLP) {
		return (NULLP);
	}

	++this->ms_use_size_;

	return (ms_p);
}


/**
 * @brief GetConstructorPart関数
 * @param ms_p (memory_space_pointer)
 * @param cnt (count)
 * @return p (pointer)<br>
 * NULLP=失敗
 */
template <typename T>
inline T *tml::NewAllocator::GetConstructorPart(BYTE *ms_p, const size_t cnt)
{
	if (ms_p == NULLP) {
		return (NULLP);
	}

	T *p = NULLP;

	if (std::is_class<T>::value) {
		(*(reinterpret_cast<size_t *>(ms_p))) = cnt;

		p = reinterpret_cast<T *>(ms_p + this->ms_cnt_head_size_);

		for (size_t p_i = 0U; p_i < cnt; ++p_i) {
			new(p + p_i) T();
		}
	} else {
		(*(reinterpret_cast<size_t *>(ms_p))) = 0U;

		p = reinterpret_cast<T *>(ms_p + this->ms_cnt_head_size_);
	}

	return (p);
}


/**
 * @brief Release関数
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::NewAllocator::Release(T **pp)
{
	this->ReleaseMemorySpacePart<T>(this->ReleaseDestructorPart<T>(pp), pp);

	return;
}


/**
 * @brief ReleaseDestructorPart関数
 * @param pp (pointer_pointer)
 * @return ms_p (memory_space_pointer)<br>
 * NULLP=失敗
 */
template <typename T>
inline BYTE *tml::NewAllocator::ReleaseDestructorPart(T **pp)
{
	if ((*pp) == NULLP) {
		return (NULLP);
	}

	BYTE *ms_p = reinterpret_cast<BYTE *>(*pp) - this->ms_cnt_head_size_;

	size_t cnt = (*(reinterpret_cast<size_t *>(ms_p)));

	for (size_t pp_i = cnt; pp_i > 0U;) {
		--pp_i;

		(*pp)[pp_i].~T();
	}

	return (ms_p);
}


/**
 * @brief ReleaseMemorySpacePart関数
 * @param ms_p (memory_space_pointer)
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::NewAllocator::ReleaseMemorySpacePart(BYTE *ms_p, T **pp)
{
	if (ms_p == NULLP) {
		return;
	}

	delete [] ms_p;

	(*pp) = NULLP;

	--this->ms_use_size_;

	return;
}
}
