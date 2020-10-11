#if 0
/**
 * @file
 * @brief MemoryUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "ConstantUtil.h"
#include "MemoryUtilEngine.h"


namespace tml {
/**
 * @brief MemoryUtil�N���X
 *
 * ���[�e�B���e�B�p�^�[��<br>
 * �G���W���p�^�[��
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
 * @brief Get�֐�
 *
 * @param cnt : 
 * @return p : NULLP=���s
 */
template <typename T>
inline T *tml::MemoryUtil::Get(const size_t cnt)
{
	return (NULLP);
}


/**
 * @brief Release�֐�
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
