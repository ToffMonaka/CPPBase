/**
 * @file
 * @brief DlmallocAllocator�R�[�h�t�@�C��
 */


#include "DlmallocAllocator.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DlmallocAllocator::DlmallocAllocator()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DlmallocAllocator::~DlmallocAllocator()
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::DlmallocAllocator::Init(void)
{
	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::DlmallocAllocator::Create(void)
{
	if (tml::Allocator::Create() < 0) {
		return (-1);
	}

	return (0);
}
