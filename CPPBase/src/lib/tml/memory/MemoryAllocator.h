/**
 * @file
 * @brief MemoryAllocator�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_MEMORY.h"


namespace tml {
/**
 * @brief MemoryAllocator�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class MemoryAllocator
{
public: MemoryAllocator(const tml::MemoryAllocator &) = delete;
public: tml::MemoryAllocator &operator =(const tml::MemoryAllocator &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	/**
	 * @brief INFO�\����
	 */
	typedef struct INFO_
	{
		tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE type;
		size_t size;
		size_t use_size;
		size_t use_count;

		/**
		 * @brief �R���X�g���N�^
		 */
		INFO_() :
			type(tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NONE),
			size(0U),
			use_size(0U),
			use_count(0U)
		{
			return;
		};
	} INFO;

private:
	tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE type_;

private:
	void Release(void);

public:
	MemoryAllocator();
	virtual ~MemoryAllocator();

	virtual void Init(void);
	INT Create(const tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE);

	tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE GetType(void) const;
	virtual tml::MemoryAllocator::INFO GetInfo(void) const;
};
}


/**
 * @brief Release�֐�
 */
inline void tml::MemoryAllocator::Release(void)
{
	return;
}


/**
 * @brief GetType�֐�
 * @return type (type)
 */
inline tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE tml::MemoryAllocator::GetType(void) const
{
	return (this->type_);
}
