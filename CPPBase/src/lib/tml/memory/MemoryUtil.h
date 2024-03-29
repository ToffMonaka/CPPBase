/**
 * @file
 * @brief MemoryUtilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../util/Util.h"
#include "MemoryUtilEngine.h"


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
public: MemoryUtil(const tml::MemoryUtil &) = delete;
public: tml::MemoryUtil &operator =(const tml::MemoryUtil &) = delete;

private:
	static std::unique_ptr<tml::MemoryUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::MemoryUtilEngine> &);

	static bool CheckFixedThread(void);
	template <typename T, typename... ARGS>
	static T *Get(const size_t, ARGS&&...);
	template <typename T>
	static void Release(T **);
	static tml::MemoryAllocator::INFO GetAllocatorInfo(void);
	static void SetBufferIndex(const size_t, size_t &, const size_t, INT *);
	static void AddBufferIndex(const size_t, size_t &, const INT, INT *);
	static CHAR ReadBufferChar(const BYTE *, const size_t, size_t &, INT *);
	static UCHAR ReadBufferUChar(const BYTE *, const size_t, size_t &, INT *);
	static SHORT ReadBufferShortB(const BYTE *, const size_t, size_t &, INT *);
	static SHORT ReadBufferShortL(const BYTE *, const size_t, size_t &, INT *);
	static USHORT ReadBufferUShortB(const BYTE *, const size_t, size_t &, INT *);
	static USHORT ReadBufferUShortL(const BYTE *, const size_t, size_t &, INT *);
	static INT ReadBufferIntB(const BYTE *, const size_t, size_t &, INT *);
	static INT ReadBufferIntL(const BYTE *, const size_t, size_t &, INT *);
	static UINT ReadBufferUIntB(const BYTE *, const size_t, size_t &, INT *);
	static UINT ReadBufferUIntL(const BYTE *, const size_t, size_t &, INT *);
	static LONGLONG ReadBufferLongLongB(const BYTE *, const size_t, size_t &, INT *);
	static LONGLONG ReadBufferLongLongL(const BYTE *, const size_t, size_t &, INT *);
	static ULONGLONG ReadBufferULongLongB(const BYTE *, const size_t, size_t &, INT *);
	static ULONGLONG ReadBufferULongLongL(const BYTE *, const size_t, size_t &, INT *);
	static FLOAT ReadBufferFloatB(const BYTE *, const size_t, size_t &, INT *);
	static FLOAT ReadBufferFloatL(const BYTE *, const size_t, size_t &, INT *);
	static DOUBLE ReadBufferDoubleB(const BYTE *, const size_t, size_t &, INT *);
	static DOUBLE ReadBufferDoubleL(const BYTE *, const size_t, size_t &, INT *);
	static BYTE *ReadBufferArray(BYTE *, const size_t, const BYTE *, const size_t, size_t &, const size_t, INT *);
	static CHAR *ReadBufferStringB(CHAR *, const size_t, BYTE *, const size_t, size_t &, INT *);
	static CHAR *ReadBufferStringL(CHAR *, const size_t, BYTE *, const size_t, size_t &, INT *);
	static WCHAR *ReadBufferStringB(WCHAR *, const size_t, BYTE *, const size_t, size_t &, INT *);
	static WCHAR *ReadBufferStringL(WCHAR *, const size_t, BYTE *, const size_t, size_t &, INT *);
	static void WriteBufferChar(BYTE *, const size_t, size_t &, const CHAR, INT *);
	static void WriteBufferUChar(BYTE *, const size_t, size_t &, const UCHAR, INT *);
	static void WriteBufferShortB(BYTE *, const size_t, size_t &, const SHORT, INT *);
	static void WriteBufferShortL(BYTE *, const size_t, size_t &, const SHORT, INT *);
	static void WriteBufferUShortB(BYTE *, const size_t, size_t &, const USHORT, INT *);
	static void WriteBufferUShortL(BYTE *, const size_t, size_t &, const USHORT, INT *);
	static void WriteBufferIntB(BYTE *, const size_t, size_t &, const INT, INT *);
	static void WriteBufferIntL(BYTE *, const size_t, size_t &, const INT, INT *);
	static void WriteBufferUIntB(BYTE *, const size_t, size_t &, const UINT, INT *);
	static void WriteBufferUIntL(BYTE *, const size_t, size_t &, const UINT, INT *);
	static void WriteBufferLongLongB(BYTE *, const size_t, size_t &, const LONGLONG, INT *);
	static void WriteBufferLongLongL(BYTE *, const size_t, size_t &, const LONGLONG, INT *);
	static void WriteBufferULongLongB(BYTE *, const size_t, size_t &, const ULONGLONG, INT *);
	static void WriteBufferULongLongL(BYTE *, const size_t, size_t &, const ULONGLONG, INT *);
	static void WriteBufferFloatB(BYTE *, const size_t, size_t &, const FLOAT, INT *);
	static void WriteBufferFloatL(BYTE *, const size_t, size_t &, const FLOAT, INT *);
	static void WriteBufferDoubleB(BYTE *, const size_t, size_t &, const DOUBLE, INT *);
	static void WriteBufferDoubleL(BYTE *, const size_t, size_t &, const DOUBLE, INT *);
	static void WriteBufferArray(BYTE *, const size_t, size_t &, const BYTE *, const size_t, const size_t, INT *);
	static void WriteBufferStringB(BYTE *, const size_t, size_t &, const CHAR *, INT *);
	static void WriteBufferStringL(BYTE *, const size_t, size_t &, const CHAR *, INT *);
	static void WriteBufferStringB(BYTE *, const size_t, size_t &, const WCHAR *, INT *);
	static void WriteBufferStringL(BYTE *, const size_t, size_t &, const WCHAR *, INT *);
};
}


/**
 * @brief CheckFixedThread関数
 * @return result_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::MemoryUtil::CheckFixedThread(void)
{
	return (tml::Util::CheckFixedThread());
}


/**
 * @brief Get関数
 * @param cnt (count)
 * @param args (arguments)
 * @return p (pointer)<br>
 * nullptr=失敗
 */
template <typename T, typename... ARGS>
inline T *tml::MemoryUtil::Get(const size_t cnt, ARGS&&... args)
{
	return (tml::MemoryUtil::engine_->Get<T>(cnt, std::forward<ARGS>(args)...));
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
 *
 * Create関数不要
 *
 * @return allocator_info (allocator_info)
 */
inline tml::MemoryAllocator::INFO tml::MemoryUtil::GetAllocatorInfo(void)
{
	if (tml::MemoryUtil::engine_ == nullptr) {
		return (tml::MemoryAllocator::INFO());
	}

	return (tml::MemoryUtil::engine_->GetAllocatorInfo());
}


namespace tml {
template <class _Ty, bool R>
struct MemoryGetBase
{
	constexpr MemoryGetBase() noexcept = default;
	template <class _Ty2, std::enable_if_t<std::is_convertible_v<_Ty2 *, _Ty *>, int> = 0>
	MemoryGetBase(const MemoryGetBase<_Ty2, R> &) noexcept {};

	_NODISCARD _Ty *operator()(const size_t cnt) const
	{
		if (cnt <= 0U) {
			return (nullptr);
		}

		return (tml::MemoryUtil::Get<_Ty>(cnt));
	};
};

template <class _Ty, bool R>
struct MemoryReleaseBase
{
	constexpr MemoryReleaseBase() noexcept = default;
	template <class _Ty2, std::enable_if_t<std::is_convertible_v<_Ty2 *, _Ty *>, int> = 0>
	MemoryReleaseBase(const MemoryReleaseBase<_Ty2, R> &) noexcept {};

	void operator()(_Ty *_Ptr) const
	{
		if (_Ptr == nullptr) {
			return;
		}

		auto p = _Ptr;

		tml::MemoryUtil::Release(&p);

		return;
	};
};

template <class _Ty>
struct MemoryGetBase<_Ty, true>
{
	constexpr MemoryGetBase() noexcept = default;
	template <class _Ty2, std::enable_if_t<std::is_convertible_v<_Ty2 *, _Ty *>, int> = 0>
	MemoryGetBase(const MemoryGetBase<_Ty2, true> &) noexcept {};

	_NODISCARD _Ty *operator()(const size_t cnt) const
	{
		if (cnt <= 0U) {
			return (nullptr);
		}

		return (new _Ty[cnt]);
	};
};

template <class _Ty>
struct MemoryReleaseBase<_Ty, true>
{
	constexpr MemoryReleaseBase() noexcept = default;
	template <class _Ty2, std::enable_if_t<std::is_convertible_v<_Ty2 *, _Ty *>, int> = 0>
	MemoryReleaseBase(const MemoryReleaseBase<_Ty2, true> &) noexcept {};

	void operator()(_Ty *_Ptr) const
	{
		if (_Ptr == nullptr) {
			return;
		}

		auto p = _Ptr;

		delete [] p;

		return;
	};
};

template <class _Ty>
using MemoryGet = tml::MemoryGetBase<_Ty, false>;

template <class _Ty>
using MemoryRelease = tml::MemoryReleaseBase<_Ty, false>;

template <class _Ty>
using MemoryGetRaw = tml::MemoryGetBase<_Ty, true>;

template <class _Ty>
using MemoryReleaseRaw = tml::MemoryReleaseBase<_Ty, true>;

template <typename T>
using unique_ptr = std::unique_ptr<T, tml::MemoryRelease<T>>;

template <typename T>
_NODISCARD tml::unique_ptr<T> make_unique(void)
{
	return (tml::unique_ptr<T>(nullptr));
};

template <typename T, typename... ARGS>
_NODISCARD tml::unique_ptr<T> make_unique(const size_t cnt, ARGS&&... args)
{
	return (tml::unique_ptr<T>(tml::MemoryUtil::Get<T>(cnt, std::forward<ARGS>(args)...)));
};

template <typename T>
using shared_ptr = std::shared_ptr<T>;

template <typename T>
_NODISCARD tml::shared_ptr<T> make_shared(void)
{
	return (tml::shared_ptr<T>(nullptr, tml::MemoryRelease<T>()));
};

template <typename T, typename... ARGS>
_NODISCARD tml::shared_ptr<T> make_shared(const size_t cnt, ARGS&&... args)
{
	return (tml::shared_ptr<T>(tml::MemoryUtil::Get<T>(cnt, std::forward<ARGS>(args)...), tml::MemoryRelease<T>()));
};
}
