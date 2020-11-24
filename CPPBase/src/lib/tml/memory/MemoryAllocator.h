/**
 * @file
 * @brief MemoryAllocator�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"


namespace tml {
/**
 * @brief MemoryAllocator�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class MemoryAllocator
{
public: MemoryAllocator(const MemoryAllocator &) = delete;
public: MemoryAllocator &operator =(const MemoryAllocator &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	/**
	 * @brief INFO�\����
	 */
	typedef struct INFO_
	{
		size_t size;
		size_t use_size;
		size_t use_cnt;

		/**
		 * @brief �R���X�g���N�^
		 */
		INFO_() :
			size(0U),
			use_size(0U),
			use_cnt(0U)
		{
			return;
		}
	} INFO;

protected:
	void Release(void);
	INT Create(void);

public:
	MemoryAllocator();
	virtual ~MemoryAllocator();

	virtual void Init(void);

	virtual tml::MemoryAllocator::INFO GetInfo(void);
};
}
