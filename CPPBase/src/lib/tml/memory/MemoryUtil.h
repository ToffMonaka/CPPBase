/**
 * @file
 * @brief MemoryUtilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
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
	static CHAR ReadCHAR(const BYTE *, const size_t, size_t &, INT *);
	static UCHAR ReadUCHAR(const BYTE *, const size_t, size_t &, INT *);
	static SHORT ReadSHORT_B(const BYTE *, const size_t, size_t &, INT *);
	static SHORT ReadSHORT_L(const BYTE *, const size_t, size_t &, INT *);
	static USHORT ReadUSHORT_B(const BYTE *, const size_t, size_t &, INT *);
	static USHORT ReadUSHORT_L(const BYTE *, const size_t, size_t &, INT *);
	static INT ReadINT_B(const BYTE *, const size_t, size_t &, INT *);
	static INT ReadINT_L(const BYTE *, const size_t, size_t &, INT *);
	static UINT ReadUINT_B(const BYTE *, const size_t, size_t &, INT *);
	static UINT ReadUINT_L(const BYTE *, const size_t, size_t &, INT *);
	static LONGLONG ReadLONGLONG_B(const BYTE *, const size_t, size_t &, INT *);
	static LONGLONG ReadLONGLONG_L(const BYTE *, const size_t, size_t &, INT *);
	static ULONGLONG ReadULONGLONG_B(const BYTE *, const size_t, size_t &, INT *);
	static ULONGLONG ReadULONGLONG_L(const BYTE *, const size_t, size_t &, INT *);
	static FLOAT ReadFLOAT_B(const BYTE *, const size_t, size_t &, INT *);
	static FLOAT ReadFLOAT_L(const BYTE *, const size_t, size_t &, INT *);
	static DOUBLE ReadDOUBLE_B(const BYTE *, const size_t, size_t &, INT *);
	static DOUBLE ReadDOUBLE_L(const BYTE *, const size_t, size_t &, INT *);
	static BYTE *ReadArray(BYTE *, const size_t, const BYTE *, const size_t, size_t &, const size_t, INT *);
	static CHAR *ReadString_B(CHAR *, const size_t, BYTE *, const size_t, size_t &, INT *);
	static CHAR *ReadString_L(CHAR *, const size_t, BYTE *, const size_t, size_t &, INT *);
	static WCHAR *ReadString_B(WCHAR *, const size_t, BYTE *, const size_t, size_t &, INT *);
	static WCHAR *ReadString_L(WCHAR *, const size_t, BYTE *, const size_t, size_t &, INT *);
	static void WriteCHAR(BYTE *, const size_t, size_t &, const CHAR, INT *);
	static void WriteUCHAR(BYTE *, const size_t, size_t &, const UCHAR, INT *);
	static void WriteSHORT_B(BYTE *, const size_t, size_t &, const SHORT, INT *);
	static void WriteSHORT_L(BYTE *, const size_t, size_t &, const SHORT, INT *);
	static void WriteUSHORT_B(BYTE *, const size_t, size_t &, const USHORT, INT *);
	static void WriteUSHORT_L(BYTE *, const size_t, size_t &, const USHORT, INT *);
	static void WriteINT_B(BYTE *, const size_t, size_t &, const INT, INT *);
	static void WriteINT_L(BYTE *, const size_t, size_t &, const INT, INT *);
	static void WriteUINT_B(BYTE *, const size_t, size_t &, const UINT, INT *);
	static void WriteUINT_L(BYTE *, const size_t, size_t &, const UINT, INT *);
	static void WriteLONGLONG_B(BYTE *, const size_t, size_t &, const LONGLONG, INT *);
	static void WriteLONGLONG_L(BYTE *, const size_t, size_t &, const LONGLONG, INT *);
	static void WriteULONGLONG_B(BYTE *, const size_t, size_t &, const ULONGLONG, INT *);
	static void WriteULONGLONG_L(BYTE *, const size_t, size_t &, const ULONGLONG, INT *);
	static void WriteFLOAT_B(BYTE *, const size_t, size_t &, const FLOAT, INT *);
	static void WriteFLOAT_L(BYTE *, const size_t, size_t &, const FLOAT, INT *);
	static void WriteDOUBLE_B(BYTE *, const size_t, size_t &, const DOUBLE, INT *);
	static void WriteDOUBLE_L(BYTE *, const size_t, size_t &, const DOUBLE, INT *);
	static void WriteArray(BYTE *, const size_t, size_t &, const BYTE *, const size_t, const size_t, INT *);
	static void WriteString_B(BYTE *, const size_t, size_t &, const CHAR *, INT *);
	static void WriteString_L(BYTE *, const size_t, size_t &, const CHAR *, INT *);
	static void WriteString_B(BYTE *, const size_t, size_t &, const WCHAR *, INT *);
	static void WriteString_L(BYTE *, const size_t, size_t &, const WCHAR *, INT *);
};
}


/**
 * @brief CheckThreadFix関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::MemoryUtil::CheckThreadFix(void)
{
	return (tml::MemoryUtil::th_fix_.Check());
}


/**
 * @brief Get関数
 * @param cnt (count)
 * @return p (pointer)<br>
 * nullptr=失敗
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
 * Create関数不要
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
 * @brief Copy関数
 *
 * Create関数不要
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
 * @brief CopySame関数
 *
 * Create関数不要
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
