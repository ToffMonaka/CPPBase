/**
 * @file
 * @brief MemoryUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "NewAllocator.h"
#include "DlmallocAllocator.h"


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

private:
	tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE allocator_type_;
	tml::NewAllocator *new_allocator_;
	tml::DlmallocAllocator *dlmalloc_allocator_;

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
	tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE GetAllocatorType(void) const;
	tml::Allocator::INFO GetAllocatorInfo(void);
};


/**
 * @brief Get関数
 * @param cnt (count)
 * @return p (pointer)<br>
 * NULLP=失敗
 */
template <typename T>
inline T *tml::MemoryUtilEngine::Get(const size_t cnt)
{
	switch (this->allocator_type_) {
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NEW: {
		return (this->new_allocator_->Get<T>(cnt));
	}
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC: {
		return (this->dlmalloc_allocator_->Get<T>(cnt));
	}
	}

	return (NULLP);
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
		return (this->new_allocator_->Release(pp));
	}
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC: {
		return (this->dlmalloc_allocator_->Release(pp));
	}
	}

	return;
}


/**
 * @brief GetAllocatorType関数
 * @return allocator_type (allocator_type)
 */
inline tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE tml::MemoryUtilEngine::GetAllocatorType(void) const
{
	return (this->allocator_type_);
}


/**
 * @brief GetAllocatorInfo関数
 * @return allocator_info (allocator_info)
 */
inline tml::Allocator::INFO tml::MemoryUtilEngine::GetAllocatorInfo(void)
{
	tml::Allocator::INFO allocator_info;

	switch (this->allocator_type_) {
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::NEW: {
		allocator_info = this->new_allocator_->GetInfo();
	}
	case tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE::DLMALLOC: {
		allocator_info = this->dlmalloc_allocator_->GetInfo();
	}
	}

	return (allocator_info);
}
}
