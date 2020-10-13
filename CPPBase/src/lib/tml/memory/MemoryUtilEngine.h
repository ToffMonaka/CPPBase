/**
 * @file
 * @brief MemoryUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "NewAllocator.h"
#include "MallocAllocator.h"
#include "DlmallocAllocator.h"


namespace tml {
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

protected:
	void Release(void);
	INT Create(void);

public:
	MemoryUtilEngine();
	virtual ~MemoryUtilEngine();

	virtual void Init(void);
	template <typename T>
	T *Get(const size_t);
	template <typename T>
	void Release(T **);
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
	return (NULLP);
}


/**
 * @brief Release関数
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::MemoryUtilEngine::Release(T **pp)
{
	return;
}
}
