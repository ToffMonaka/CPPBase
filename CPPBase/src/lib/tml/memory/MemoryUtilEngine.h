#if 0
/**
 * @file
 * @brief MemoryUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "dlmalloc/malloc.h"
#include "ConstantUtil.h"


namespace tml {
/**
 * @brief MemoryUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
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
 * @brief Get�֐�
 *
 * @param cnt : 
 * @return p : NULLP=���s
 */
template <typename T>
inline T *tml::MemoryUtilEngine::Get(const size_t cnt)
{
	return (NULLP);
}


/**
 * @brief Release�֐�
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
