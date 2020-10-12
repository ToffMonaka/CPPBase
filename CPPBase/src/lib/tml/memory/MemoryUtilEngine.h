/**
 * @file
 * @brief MemoryUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief MemoryUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class MemoryUtilEngine
{
public: MemoryUtilEngine(const MemoryUtilEngine &) = delete;
public: MemoryUtilEngine &operator =(const MemoryUtilEngine &) = delete;
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
 * @brief Get�֐�
 * @param cnt (count)
 * @return p (pointer)<br>
 * NULLP=���s
 */
template <typename T>
inline T *tml::MemoryUtilEngine::Get(const size_t cnt)
{
	return (NULLP);
}


/**
 * @brief Release�֐�
 * @param pp (pointer_pointer)
 */
template <typename T>
inline void tml::MemoryUtilEngine::Release(T **pp)
{
	return;
}
}
