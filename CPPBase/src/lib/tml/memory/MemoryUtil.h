#if 0
/**
 * @file
 * @brief MemoryUtilヘッダーファイル
 */
#pragma once


#include "ConstantUtil.h"
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
private: MemoryUtil() {return;};
private: MemoryUtil(const MemoryUtil &) {return;};
private: MemoryUtil &operator =(const MemoryUtil &) {return ((*this));};

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
 *
 * @param cnt : 
 * @return p : NULLP=失敗
 */
template <typename T>
inline T *tml::MemoryUtil::Get(const size_t cnt)
{
	return (NULLP);
}


/**
 * @brief Release関数
 *
 * @param pp : 
 */
template <typename T>
inline void tml::MemoryUtil::Release(T **pp)
{
	return;
}
}
#endif
