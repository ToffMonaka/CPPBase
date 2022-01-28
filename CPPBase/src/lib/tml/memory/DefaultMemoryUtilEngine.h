/**
 * @file
 * @brief DefaultMemoryUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "MemoryUtilEngine.h"


namespace tml {
/**
 * @brief DefaultMemoryUtilEngineDesc�N���X
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
 * @brief Release�֐�
 */
inline void tml::DefaultMemoryUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief DefaultMemoryUtilEngine�N���X
 */
class DefaultMemoryUtilEngine : public tml::MemoryUtilEngine
{
public: DefaultMemoryUtilEngine(const tml::DefaultMemoryUtilEngine &) = delete;
public: tml::DefaultMemoryUtilEngine &operator =(const tml::DefaultMemoryUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) {return;};

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
 * @brief Release�֐�
 */
inline void tml::DefaultMemoryUtilEngine::Release(void)
{
	return;
}


/**
 * @brief Get�֐�
 * @param cnt (count)
 * @return p (pointer)<br>
 * nullptr=���s
 */
template <typename T>
inline T *tml::DefaultMemoryUtilEngine::Get(const size_t cnt)
{
	return (tml::MemoryUtilEngine::Get<T>(cnt));
}


/**
 * @brief Release�֐�
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::DefaultMemoryUtilEngine::Release(T **pp)
{
	tml::MemoryUtilEngine::Release(pp);

	return;
}
