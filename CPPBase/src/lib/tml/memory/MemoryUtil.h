/**
 * @file
 * @brief MemoryUtilヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "MemoryUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief MemoryUtilクラス
 *
 * ユーティリティパターン<br>
 * エンジンパターン
 */
class MemoryUtil
{
public: MemoryUtil() = delete;
public: MemoryUtil(const MemoryUtil &) = delete;
public: MemoryUtil &operator =(const MemoryUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::MemoryUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::MemoryUtilEngine> &);

	template <typename T>
	static T *Get(const size_t);
	template <typename T>
	static void Release(T **);
	static tml::MemoryUtilEngine::ALLOCATOR_INFO GetAllocatorInfo(void);
	template <typename T>
	static void Clear(T *, const size_t);
	template <typename T>
	static void Copy(T *, const T *, const size_t);
	template <typename T>
	static void CopySame(T *, const T *, const size_t);
};


/**
 * @brief Get関数
 * @param cnt (count)
 * @return p (pointer)<br>
 * NULLP=失敗
 */
template <typename T>
inline T *tml::MemoryUtil::Get(const size_t cnt)
{
	return (tml::MemoryUtil::engine_->Get<T>(cnt));
}


/**
 * @brief Release関数
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::MemoryUtil::Release(T **pp)
{
	tml::MemoryUtil::engine_->Release(pp);

	return;
}


/**
 * @brief GetAllocatorInfo関数
 * @return allocator_info (allocator_info)
 */
inline tml::MemoryUtilEngine::ALLOCATOR_INFO tml::MemoryUtil::GetAllocatorInfo(void)
{
	return (tml::MemoryUtil::engine_->GetAllocatorInfo());
}


/**
 * @brief Clear関数
 *
 * エンジン不要
 *
 * @param p (pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::MemoryUtil::Clear(T *p, const size_t cnt)
{
	if (cnt <= 0U) {
		return;
	}

	memset(p, 0, sizeof(T) * cnt);

	return;
}


/**
 * @brief Copy関数
 *
 * エンジン不要
 *
 * @param dst_p (dst_pointer)
 * @param src_p (src_pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::MemoryUtil::Copy(T *dst_p, const T *src_p, const size_t cnt)
{
	if ((dst_p == src_p)
	|| (cnt <= 0U)) {
		return;
	}

	memcpy(dst_p, src_p, sizeof(T) * cnt);

	return;
}


/**
 * @brief CopySame関数
 *
 * エンジン不要
 *
 * @param dst_p (dst_pointer)
 * @param src_p (src_pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::MemoryUtil::CopySame(T *dst_p, const T *src_p, const size_t cnt)
{
	if ((dst_p == src_p)
	|| (cnt <= 0U)) {
		return;
	}

	memmove(dst_p, src_p, sizeof(T) * cnt);

	return;
}
}
