/**
 * @file
 * @brief DefaultMemoryUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "MemoryUtilEngine.h"


namespace tml {
/**
 * @brief DefaultMemoryUtilEngineDescクラス
 */
class DefaultMemoryUtilEngineDesc : public tml::MemoryUtilEngineDesc
{
public:

private:
	void Release(void);

public:
	DefaultMemoryUtilEngineDesc();
	virtual ~DefaultMemoryUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::DefaultMemoryUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief DefaultMemoryUtilEngineクラス
 */
class DefaultMemoryUtilEngine : public tml::MemoryUtilEngine
{
public: DefaultMemoryUtilEngine(const tml::DefaultMemoryUtilEngine &) = delete;
public: tml::DefaultMemoryUtilEngine &operator =(const tml::DefaultMemoryUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

private:

private:
	void Release(void);

public:
	DefaultMemoryUtilEngine();
	virtual ~DefaultMemoryUtilEngine();

	virtual void Init(void);
	INT Create(const tml::DefaultMemoryUtilEngineDesc &);

	template <typename T>
	T *Get(const size_t);
	template <typename T>
	void Release(T **);
};
}


/**
 * @brief Release関数
 */
inline void tml::DefaultMemoryUtilEngine::Release(void)
{
	return;
}


/**
 * @brief Get関数
 * @param cnt (count)
 * @return p (pointer)<br>
 * nullptr=失敗
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
