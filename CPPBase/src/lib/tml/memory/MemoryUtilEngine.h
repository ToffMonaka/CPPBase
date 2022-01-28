/**
 * @file
 * @brief MemoryUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/SpinThreadLock.h"
#include "NewMemoryAllocator.h"
#include "DlmallocMemoryAllocator.h"


namespace tml {
/**
 * @brief MemoryUtilEngineDescクラス
 */
class MemoryUtilEngineDesc
{
public:
	tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE allocator_type;
	size_t allocator_size;

private:
	void Release(void);

public:
	MemoryUtilEngineDesc();
	virtual ~MemoryUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::MemoryUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief MemoryUtilEngineクラス
 *
 * インターフェースパターン
 */
class MemoryUtilEngine
{
public: MemoryUtilEngine(const tml::MemoryUtilEngine &) = delete;
public: tml::MemoryUtilEngine &operator =(const tml::MemoryUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE allocator_type_;
	std::unique_ptr<tml::NewMemoryAllocator> new_allocator_;
	std::unique_ptr<tml::DlmallocMemoryAllocator> dlmalloc_allocator_;
	tml::SpinThreadLock allocator_th_lock_;

private:
	void Release(void);

public:
	MemoryUtilEngine();
	virtual ~MemoryUtilEngine();

	virtual void Init(void);
	INT Create(const tml::MemoryUtilEngineDesc &);

	template <typename T, typename... ARGS>
	T *Get(const size_t, ARGS&&...);
	template <typename T>
	void Release(T **);
	tml::MemoryAllocator::INFO GetAllocatorInfo(void);
};
}


/**
 * @brief Get関数
 * @param cnt (count)
 * @param args (arguments)
 * @return p (pointer)<br>
 * nullptr=失敗
 */
template <typename T, typename... ARGS>
inline T *tml::MemoryUtilEngine::Get(const size_t cnt, ARGS&&... args)
{
	T *p = nullptr;

	switch (this->allocator_type_) {
	case tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NEW: {
		BYTE *ms_p = nullptr;

		{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
			ms_p = this->new_allocator_->GetMemorySpacePart<T>(cnt);
		}

		p = this->new_allocator_->GetConstructorPart<T>(ms_p, cnt, std::forward<ARGS>(args)...);

		break;
	}
	case tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::DLMALLOC: {
		BYTE *ms_p = nullptr;

		{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
			ms_p = this->dlmalloc_allocator_->GetMemorySpacePart<T>(cnt);
		}

		p = this->dlmalloc_allocator_->GetConstructorPart<T>(ms_p, cnt, std::forward<ARGS>(args)...);

		break;
	}
	}

	return (p);
}


/**
 * @brief Release関数
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::MemoryUtilEngine::Release(T **pp)
{
	switch (this->allocator_type_) {
	case tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NEW: {
		BYTE *ms_p = nullptr;

		ms_p = this->new_allocator_->ReleaseDestructorPart<T>(pp);

		{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
			this->new_allocator_->ReleaseMemorySpacePart<T>(ms_p, pp);
		}

		break;
	}
	case tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::DLMALLOC: {
		BYTE *ms_p = nullptr;

		ms_p = this->dlmalloc_allocator_->ReleaseDestructorPart<T>(pp);

		{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
			this->dlmalloc_allocator_->ReleaseMemorySpacePart<T>(ms_p, pp);
		}

		break;
	}
	}

	return;
}
