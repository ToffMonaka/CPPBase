/**
 * @file
 * @brief FileUtilEngine�R�[�h�t�@�C��
 */


#include "FileUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::FileUtilEngineDesc::FileUtilEngineDesc() :
	cache_file_limit(0U),
	cache_file_buffer_limit(0U)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::FileUtilEngineDesc::~FileUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::FileUtilEngineDesc::Init(void)
{
	this->Release();

	this->cache_file_limit = 0U;
	this->cache_file_buffer_limit = 0U;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::FileUtilEngine::FileUtilEngine() :
	cache_file_limit_(0U),
	cache_file_buf_limit_(0U)
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::FileUtilEngine::~FileUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::FileUtilEngine::Init(void)
{
	this->Release();

	this->cache_file_limit_ = 0U;
	this->cache_file_buf_limit_ = 0U;

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::FileUtilEngine::Create(const tml::FileUtilEngineDesc &desc)
{
	this->cache_file_limit_ = desc.cache_file_limit;
	this->cache_file_buf_limit_ = desc.cache_file_buffer_limit;

	return (0);
}
