#if 0
/**
 * @file
 * @brief MemoryUtilEngineヘッダーファイル
 */
#pragma once


#include "dlmalloc/malloc.h"
#include "ConstantUtil.h"


namespace tml {
/**
 * @brief MemoryUtilEngineクラス
 *
 * インターフェースパターン
 */
class MemoryUtilEngine
{
private: MemoryUtilEngine(const MemoryUtilEngine &) {return;};
private: MemoryUtilEngine &operator =(const MemoryUtilEngine &) {return ((*this));};
protected: virtual void InterfaceDummy(void) = 0;

public:
	MemoryUtilEngine();
	virtual ~MemoryUtilEngine();

	virtual void Init(void);
	INT Create(void);

	template <typename T>
	T *Get(const size_t);
	template <typename T>
	void Release(T **);
};


/**
 * @brief Get関数
 *
 * @param cnt : 
 * @return p : NULLP=失敗
 */
template <typename T>
inline T *tml::MemoryUtilEngine::Get(const size_t cnt)
{
	return (NULLP);
}


/**
 * @brief Release関数
 *
 * @param pp : 
 */
template <typename T>
inline void tml::MemoryUtilEngine::Release(T **pp)
{
	return;
}
}
#endif
