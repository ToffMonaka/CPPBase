/**
 * @file
 * @brief MemoryAllocator�R�[�h�t�@�C��
 */


#include "MemoryAllocator.h"


/**
 * @brief �R���X�g���N�^
 */
tml::MemoryAllocator::MemoryAllocator() :
	type_(tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NONE)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::MemoryAllocator::~MemoryAllocator()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::MemoryAllocator::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::MemoryAllocator::Init(void)
{
	this->type_ = tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NONE;

	return;
}


/**
 * @brief Create�֐�
 * @param type (type)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::MemoryAllocator::Create(const tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE type)
{
	if (type == tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE::NONE) {
		return (-1);
	}

	this->type_ = type;

	return (0);
}


/**
 * @brief GetInfo�֐�
 * @return info (info)
 */
tml::MemoryAllocator::INFO tml::MemoryAllocator::GetInfo(void)
{
	tml::MemoryAllocator::INFO info;

	info.type = this->type_;

	return (info);
}
