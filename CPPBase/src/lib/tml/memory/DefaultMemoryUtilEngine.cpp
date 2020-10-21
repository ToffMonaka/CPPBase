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
	this->allocator_th_lock_.Lock();

	tml::MemoryUtilEngine::Release();

	this->allocator_th_lock_.Unlock();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::DefaultMemoryUtilEngine::Init(void)
{
	this->allocator_th_lock_.Lock();

	this->Release();

	tml::MemoryUtilEngine::Init();

	this->allocator_th_lock_.Unlock();

	return;
}


/**
 * @brief Create�֐�
 * @param allocator_type (allocator_type)
 * @param allocator_size (allocator_size)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::DefaultMemoryUtilEngine::Create(const tml::MemoryUtilEngineConstantUtil::ALLOCATOR_TYPE allocator_type, const size_t allocator_size)
{
	this->allocator_th_lock_.Lock();

	this->Release();

	if (tml::MemoryUtilEngine::Create(allocator_type, allocator_size) < 0) {
		this->Init();

		this->allocator_th_lock_.Unlock();

		return (-1);
	}

	this->allocator_th_lock_.Unlock();

	return (0);
}
