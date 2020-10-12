/**
 * @file
 * @brief MemoryUtilヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


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

public:
	static void Init(void);
	static INT Create(void);

	template <typename T>
	static T *Get(const size_t);
	template <typename T>
	static void Release(T **);
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
	return (NULLP);
}


/**
 * @brief Release関数
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::MemoryUtil::Release(T **pp)
{
	return;
}
}
