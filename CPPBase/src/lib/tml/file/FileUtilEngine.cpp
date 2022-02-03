/**
 * @file
 * @brief FileUtilEngineコードファイル
 */


#include "FileUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::FileUtilEngineDesc::FileUtilEngineDesc() :
	cache_file_limit(0U),
	cache_file_buffer_limit(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::FileUtilEngineDesc::~FileUtilEngineDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::FileUtilEngineDesc::Init(void)
{
	this->Release();

	this->cache_file_limit = 0U;
	this->cache_file_buffer_limit = 0U;

	return;
}


/**
 * @brief コンストラクタ
 */
tml::FileUtilEngine::FileUtilEngine() :
	cache_file_limit_(0U),
	cache_file_buf_limit_(0U)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::FileUtilEngine::~FileUtilEngine()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::FileUtilEngine::Init(void)
{
	this->Release();

	this->cache_file_limit_ = 0U;
	this->cache_file_buf_limit_ = 0U;

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::FileUtilEngine::Create(const tml::FileUtilEngineDesc &desc)
{
	this->cache_file_limit_ = desc.cache_file_limit;
	this->cache_file_buf_limit_ = desc.cache_file_buffer_limit;

	return (0);
}
