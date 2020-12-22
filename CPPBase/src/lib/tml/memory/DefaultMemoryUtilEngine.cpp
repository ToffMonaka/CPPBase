/**
 * @file
 * @brief DefaultMemoryUtilEngine�R�[�h�t�@�C��
 */


#include "DefaultMemoryUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::DefaultMemoryUtilEngine::DefaultMemoryUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::DefaultMemoryUtilEngine::~DefaultMemoryUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Release�֐�
 */
void tml::DefaultMemoryUtilEngine::Release(void)
{
	tml::MemoryUtilEngine::Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultMemoryUtilEngine::Init(void)
{
	this->Release();

	tml::MemoryUtilEngine::Init();

	return;
}


/**
 * @brief Create�֐�
 * @param allocator_type (allocator_type)
 * @param allocator_size (allocator_size)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::DefaultMemoryUtilEngine::Create(const tml::ConstantUtil::MEMORY::ALLOCATOR_TYPE allocator_type, const size_t allocator_size)
{
	this->Init();

	if (tml::MemoryUtilEngine::Create(allocator_type, allocator_size) < 0) {
		this->Init();

		return (-1);
	}

	return (0);
}
