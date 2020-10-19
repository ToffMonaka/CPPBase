/**
 * @file
 * @brief DefaultMemoryUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "MemoryUtilEngine.h"


namespace tml {
/**
 * @brief DefaultMemoryUtilEngineクラス
 */
class DefaultMemoryUtilEngine : public tml::MemoryUtilEngine
{
public: DefaultMemoryUtilEngine(const DefaultMemoryUtilEngine &) = delete;
public: DefaultMemoryUtilEngine &operator =(const DefaultMemoryUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:
	void Release(void);

public:
	DefaultMemoryUtilEngine();
	virtual ~DefaultMemoryUtilEngine();

	void Init(void);
	INT Create(const tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE, const size_t);
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
inline T *tml::DefaultMemoryUtilEngine::Get(const size_t cnt)
{
	return (tml::MemoryUtilEngine::Get<T>(cnt));
}


/**
 * @brief Release関数
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::DefaultMemoryUtilEngine::Release(T **pp)
{
	tml::MemoryUtilEngine::Release(pp);

	return;
}
}
