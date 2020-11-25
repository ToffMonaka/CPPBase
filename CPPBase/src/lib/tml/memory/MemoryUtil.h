/**
 * @file
 * @brief MemoryUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "MemoryUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief MemoryUtil�N���X
 *
 * ���[�e�B���e�B�p�^�[��<br>
 * �G���W���p�^�[��
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

	static bool CheckThreadFix(void);
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
}


/**
 * @brief CheckThreadFix�֐�
 * @return res_flg (result_flag)<br>
 * false=���s,true=����
 */
inline bool tml::MemoryUtil::CheckThreadFix(void)
{
	return (tml::MemoryUtil::th_fix_.Check());
}


/**
 * @brief Get�֐�
 * @param cnt (count)
 * @return p (pointer)<br>
 * nullptr=���s
 */
template <typename T>
inline T *tml::MemoryUtil::Get(const size_t cnt)
{
	return (tml::MemoryUtil::engine_->Get<T>(cnt));
}


/**
 * @brief Release�֐�
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::MemoryUtil::Release(T **pp)
{
	tml::MemoryUtil::engine_->Release(pp);

	return;
}


/**
 * @brief GetAllocatorInfo�֐�
 * @return allocator_info (allocator_info)
 */
inline tml::MemoryUtilEngine::ALLOCATOR_INFO tml::MemoryUtil::GetAllocatorInfo(void)
{
	return (tml::MemoryUtil::engine_->GetAllocatorInfo());
}


/**
 * @brief Clear�֐�
 *
 * Create�֐��s�v
 *
 * @param p (pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::MemoryUtil::Clear(T *p, const size_t cnt)
{
	if ((p == nullptr)
	|| (cnt <= 0U)) {
		return;
	}

	memset(p, 0, sizeof(T) * cnt);

	return;
}


/**
 * @brief Copy�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_p (dst_pointer)
 * @param src_p (src_pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::MemoryUtil::Copy(T *dst_p, const T *src_p, const size_t cnt)
{
	if ((dst_p == nullptr) || (src_p == nullptr) || (dst_p == src_p)
	|| (cnt <= 0U)) {
		return;
	}

	memcpy(dst_p, src_p, sizeof(T) * cnt);

	return;
}


/**
 * @brief CopySame�֐�
 *
 * Create�֐��s�v
 *
 * @param dst_p (dst_pointer)
 * @param src_p (src_pointer)
 * @param cnt (count)
 */
template <typename T>
inline void tml::MemoryUtil::CopySame(T *dst_p, const T *src_p, const size_t cnt)
{
	if ((dst_p == nullptr) || (src_p == nullptr) || (dst_p == src_p)
	|| (cnt <= 0U)) {
		return;
	}

	memmove(dst_p, src_p, sizeof(T) * cnt);

	return;
}


namespace tml {
template <class _Ty>
struct default_delete
{
	constexpr default_delete() noexcept = default;

	template <class _Ty2, std::enable_if_t<std::is_convertible_v<_Ty2 *, _Ty *>, int> = 0>
	default_delete(const default_delete<_Ty2> &) noexcept {};

	void operator()(_Ty *_Ptr) const noexcept {
		auto p = _Ptr;

		tml::MemoryUtil::Release(&p);

		return;
	};
};

template <class _Ty>
struct default_delete<_Ty[]>
{
	constexpr default_delete() noexcept = default;

	template <class _Uty, std::enable_if_t<std::is_convertible_v<_Uty (*)[], _Ty (*)[]>, int> = 0>
	default_delete(const default_delete<_Uty[]> &) noexcept {};

	template <class _Uty, std::enable_if_t<std::is_convertible_v<_Uty (*)[], _Ty (*)[]>, int> = 0>
	void operator()(_Uty *_Ptr) const noexcept {
		auto p = _Ptr;

		tml::MemoryUtil::Release(&p);

		return;
	};
};

template <typename T>
using unique_ptr = std::unique_ptr<T, tml::default_delete<T>>;

template <class _Ty, class... _Types, std::enable_if_t<!std::is_array_v<_Ty>, int> = 0>
_NODISCARD tml::unique_ptr<_Ty> make_unique(_Types&&... _Args) {
	return (tml::unique_ptr<_Ty>(tml::MemoryUtil::Get<_Ty>(1U)));
};

template <class _Ty, std::enable_if_t<std::is_array_v<_Ty> && std::extent_v<_Ty> == 0, int> = 0>
_NODISCARD tml::unique_ptr<_Ty> make_unique(size_t _Size) {
    using _Elem = std::remove_extent_t<_Ty>;

	return (tml::unique_ptr<_Ty>(tml::MemoryUtil::Get<_Elem>(_Size)));
};

template <class _Ty, class... _Types, std::enable_if_t<std::extent_v<_Ty> != 0, int> = 0>
void make_unique(_Types&&...) = delete;
}
