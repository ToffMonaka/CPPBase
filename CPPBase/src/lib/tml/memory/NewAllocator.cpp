/**
 * @file
 * @brief NewAllocator�R�[�h�t�@�C��
 */


#include "NewAllocator.h"


/**
 * @brief �R���X�g���N�^
 */
tml::NewAllocator::NewAllocator()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::NewAllocator::~NewAllocator()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::NewAllocator::Init(void)
{
	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::NewAllocator::Create(void)
{
	if (tml::Allocator::Create() < 0) {
		return (-1);
	}

	return (0);
}
