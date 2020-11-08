/**
 * @file
 * @brief MemoryUtilEngineヘッダーファイル
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
 * @brief MemoryUtilEngineクラス
 *
 * インターフェースパターン
 */
class MemoryUtilEngine
{
public: MemoryUtilEngine(const MemoryUtilEngine &) = delete;
public: MemoryUtilEngine &operator =(const MemoryUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	/**
	 * @brief ALLOCATOR_INFO構造体
	 */
	typedef struct ALLOCATOR_INFO_
	{
		tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE type;
		size_t size;
		size_t use_size;
		size_t use_cnt;

		/**
		 * @brief コンストラクタ
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
	tml::MemoryUtilEngine::ALLOCATOR_INFO GetAllocatorInfo(void);
};
}


/**
 * @brief Get関数
 * @param cnt (count)
 * @return p (pointer)<br>
 * nullptr=失敗
 */
template <typename T>
inline T *tml::MemoryUtilEngine::Get(const size_t cnt)
{
	T *p = nullptr;

	switch (this->allocator_type_) {
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NEW: {
		BYTE *ms_p = nullptr;

		{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
			ms_p = this->new_allocator_->GetMemorySpacePart<T>(cnt);
		}

		p = this->new_allocator_->GetConstructorPart<T>(ms_p, cnt);

		break;
	}
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC: {
		BYTE *ms_p = nullptr;

		{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
			ms_p = this->dlmalloc_allocator_->GetMemorySpacePart<T>(cnt);
		}

		p = this->dlmalloc_allocator_->GetConstructorPart<T>(ms_p, cnt);

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
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NEW: {
		BYTE *ms_p = nullptr;

		ms_p = this->new_allocator_->ReleaseDestructorPart<T>(pp);

		{tml::ThreadLockBlock th_lock_block(this->allocator_th_lock_);
			this->new_allocator_->ReleaseMemorySpacePart<T>(ms_p, pp);
		}

		break;
	}
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC: {
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
