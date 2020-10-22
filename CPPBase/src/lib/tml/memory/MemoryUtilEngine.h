/**
 * @file
 * @brief MemoryUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "NewAllocator.h"
#include "DlmallocAllocator.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
namespace MemoryUtilEngineConstantUtil {
enum class ALLOCATOR_TYPE : UINT {
	NONE = 0U,
	NEW,
	DLMALLOC
};
}

/**
 * @brief MemoryUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class MemoryUtilEngine
{
public: MemoryUtilEngine(const MemoryUtilEngine &) = delete;
public: MemoryUtilEngine &operator =(const MemoryUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	/**
	 * @brief ALLOCATOR_INFO�\����
	 */
	typedef struct ALLOCATOR_INFO_
	{
		tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE type;
		size_t size;
		size_t use_size;
		size_t use_cnt;

		/**
		 * @brief �R���X�g���N�^
		 */
		ALLOCATOR_INFO_() :
			type(tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NONE),
			size(0U),
			use_size(0U),
			use_cnt(0U)
		{
			return;
		}
	} ALLOCATOR_INFO;

private:
	tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE allocator_type_;
	tml::NewAllocator *new_allocator_;
	tml::DlmallocAllocator *dlmalloc_allocator_;
	tml::SpinThreadLock allocator_th_lock_;

protected:
	void Release(void);
	INT Create(const tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE, const size_t);

public:
	MemoryUtilEngine();
	virtual ~MemoryUtilEngine();

	virtual void Init(void);
	template <typename T>
	T *Get(const size_t);
	template <typename T>
	void Release(T **);
	template <typename T>
	void Clear(T *, const size_t);
	template <typename T>
	void Copy(T *, const T *, const size_t);
	template <typename T>
	void CopySame(T *, const T *, const size_t);
	tml::MemoryUtilEngine::ALLOCATOR_INFO GetAllocatorInfo(void);
};


/**
 * @brief Get�֐�
 * @param cnt (count)
 * @return p (pointer)<br>
 * NULLP=���s
 */
template <typename T>
inline T *tml::MemoryUtilEngine::Get(const size_t cnt)
{
	T *p = NULLP;

	switch (this->allocator_type_) {
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NEW: {
		BYTE *ms_p = NULLP;

		this->allocator_th_lock_.Lock();

		ms_p = this->new_allocator_->GetMemorySpacePart<T>(cnt);

		this->allocator_th_lock_.Unlock();

		p = this->new_allocator_->GetConstructorPart<T>(ms_p, cnt);

		break;
	}
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC: {
		BYTE *ms_p = NULLP;

		this->allocator_th_lock_.Lock();

		ms_p = this->dlmalloc_allocator_->GetMemorySpacePart<T>(cnt);

		this->allocator_th_lock_.Unlock();

		p = this->dlmalloc_allocator_->GetConstructorPart<T>(ms_p, cnt);

		break;
	}
	}

	return (p);
}


/**
 * @brief Release�֐�
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::MemoryUtilEngine::Release(T **pp)
{
	switch (this->allocator_type_) {
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NEW: {
		BYTE *ms_p = NULLP;

		ms_p = this->new_allocator_->ReleaseDestructorPart<T>(pp);

		this->allocator_th_lock_.Lock();

		this->new_allocator_->ReleaseMemorySpacePart<T>(ms_p, pp);

		this->allocator_th_lock_.Unlock();

		break;
	}
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC: {
		BYTE *ms_p = NULLP;

		ms_p = this->dlmalloc_allocator_->ReleaseDestructorPart<T>(pp);

		this->allocator_th_lock_.Lock();

		this->dlmalloc_allocator_->ReleaseMemorySpacePart<T>(ms_p, pp);

		this->allocator_th_lock_.Unlock();

		break;
	}
	}

	return;
}


/**
 * @brief Clear�֐�
 * @param p (pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::MemoryUtilEngine::Clear(T *p, const size_t cnt)
{
	if (cnt <= 0U) {
		return;
	}

	memset(p, 0, sizeof(T) * cnt);

	return;
}


/**
 * @brief Copy�֐�
 * @param dst_p (dst_pointer)
 * @param src_p (src_pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::MemoryUtilEngine::Copy(T *dst_p, const T *src_p, const size_t cnt)
{
	if ((dst_p == src_p)
	|| (cnt <= 0U)) {
		return;
	}

	memcpy(dst_p, src_p, sizeof(T) * cnt);

	return;
}


/**
 * @brief CopySame�֐�
 * @param dst_p (dst_pointer)
 * @param src_p (src_pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::MemoryUtilEngine::CopySame(T *dst_p, const T *src_p, const size_t cnt)
{
	if ((dst_p == src_p)
	|| (cnt <= 0U)) {
		return;
	}

	memmove(dst_p, src_p, sizeof(T) * cnt);

	return;
}
}
