/**
 * @file
 * @brief MallocAllocator�R�[�h�t�@�C��
 */


#include "MallocAllocator.h"


/**
 * @brief �R���X�g���N�^
 */
tml::MallocAllocator::MallocAllocator()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::MallocAllocator::~MallocAllocator()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::MallocAllocator::Init(void)
{
	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::MallocAllocator::Create(void)
{
	if (tml::Allocator::Create() < 0) {
		return (-1);
	}

	return (0);
}
