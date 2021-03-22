/**
 * @file
 * @brief DlmallocMemoryAllocatorÉwÉbÉ_Å[ÉtÉ@ÉCÉã
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantInclude_DlmallocBase.h"
#include "MemoryAllocator.h"


namespace tml {
/**
 * @brief DlmallocMemoryAllocatorÉNÉâÉX
 */
class DlmallocMemoryAllocator : public tml::MemoryAllocator
{
public: DlmallocMemoryAllocator(const tml::DlmallocMemoryAllocator &) = delete;
public: tml::DlmallocMemoryAllocator &operator =(const tml::DlmallocMemoryAllocator &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	mspace ms_;
	size_t ms_use_cnt_;
	size_t ms_cnt_head_size_;

protected:
	void Release(void);

public:
	DlmallocMemoryAllocator();
	virtual ~DlmallocMemoryAllocator();

	virtual void Init(void);
	INT Create(const size_t);

	template <typename T>
	T *Get(const size_t);
	template <typename T>
	BYTE *GetMemorySpacePart(const size_t);
	template <typename T, typename... ARGS>
	T *GetConstructorPart(BYTE *, const size_t, ARGS&&...);
	template <typename T>
	void Release(T **);
	template <typename T>
	BYTE *ReleaseDestructorPart(T **);
	template <typename T>
	void ReleaseMemorySpacePart(BYTE *, T **);
	virtual tml::MemoryAllocator::INFO GetInfo(void);
};
}


/**
 * @brief Getä÷êî
 * @param cnt (count)
 * @return p (pointer)<br>
 * nullptr=é∏îs
 */
template <typename T>
inline T *tml::DlmallocMemoryAllocator::Get(const size_t cnt)
{
	return (this->GetConstructorPart<T>(this->GetMemorySpacePart<T>(cnt), cnt));
}


/**
 * @brief GetMemorySpacePartä÷êî
 * @param cnt (count)
 * @return ms_p (memory_space_pointer)<br>
 * nullptr=é∏îs
 */
template <typename T>
inline BYTE *tml::DlmallocMemoryAllocator::GetMemorySpacePart(const size_t cnt)
{
	if (cnt <= 0U) {
		return (nullptr);
	}

	if (this->ms_ == nullptr) {
		return (nullptr);
	}

	BYTE *ms_p = static_cast<BYTE *>(mspace_malloc(this->ms_, sizeof(T) * cnt + this->ms_cnt_head_size_));

	if (ms_p == nullptr) {
		return (nullptr);
	}

	++this->ms_use_cnt_;

	return (ms_p);
}


/**
 * @brief GetConstructorPartä÷êî
 * @param ms_p (memory_space_pointer)
 * @param cnt (count)
 * @param args (arguments)
 * @return p (pointer)<br>
 * nullptr=é∏îs
 */
template <typename T, typename... ARGS>
inline T *tml::DlmallocMemoryAllocator::GetConstructorPart(BYTE *ms_p, const size_t cnt, ARGS&&... args)
{
	if (ms_p == nullptr) {
		return (nullptr);
	}

	T *p = nullptr;

	if (std::is_class<T>::value) {
		(*(reinterpret_cast<size_t *>(ms_p))) = cnt;

		p = reinterpret_cast<T *>(ms_p + this->ms_cnt_head_size_);

		for (size_t p_i = 0U; p_i < cnt; ++p_i) {
			new(p + p_i) T(args...);
		}
	} else {
		(*(reinterpret_cast<size_t *>(ms_p))) = 0U;

		p = reinterpret_cast<T *>(ms_p + this->ms_cnt_head_size_);
	}

	return (p);
}


/**
 * @brief Releaseä÷êî
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::DlmallocMemoryAllocator::Release(T **pp)
{
	this->ReleaseMemorySpacePart<T>(this->ReleaseDestructorPart<T>(pp), pp);

	return;
}


/**
 * @brief ReleaseDestructorPartä÷êî
 * @param pp (pointer_pointer)
 * @return ms_p (memory_space_pointer)<br>
 * nullptr=é∏îs
 */
template <typename T>
inline BYTE *tml::DlmallocMemoryAllocator::ReleaseDestructorPart(T **pp)
{
	if ((*pp) == nullptr) {
		return (nullptr);
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
 * @brief ReleaseMemorySpacePartä÷êî
 * @param ms_p (memory_space_pointer)
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::DlmallocMemoryAllocator::ReleaseMemorySpacePart(BYTE *ms_p, T **pp)
{
	if (ms_p == nullptr) {
		return;
	}

	mspace_free(this->ms_, ms_p);

	(*pp) = nullptr;

	--this->ms_use_cnt_;

	return;
}
