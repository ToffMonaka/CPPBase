/**
 * @file
 * @brief FileCacheコードファイル
 */


#include "FileCache.h"


/**
 * @brief コンストラクタ
 */
tml::FileCacheFile::FileCacheFile()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::FileCacheFile::~FileCacheFile()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::FileCacheFile::Init(void)
{
	this->Release();

	this->file_path_.clear();
	this->buf_.Init();

	return;
}


/**
 * @brief Create関数
 * @param file_path (file_path)
 * @param buf (buffer)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::FileCacheFile::Create(const WCHAR *file_path, const tml::DynamicBuffer &buf)
{
	if ((file_path == nullptr)
	|| (file_path[0] == 0)) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->file_path_ = file_path;
	this->buf_ = buf;

	return (0);
}


/**
 * @brief コンストラクタ
 */
tml::FileCacheDesc::FileCacheDesc()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::FileCacheDesc::~FileCacheDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::FileCacheDesc::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief コンストラクタ
 */
tml::FileCache::FileCache()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::FileCache::~FileCache()
{
	this->Release();

	return;
}


/**
 * @brief Init関数
 */
void tml::FileCache::Init(void)
{
	this->Release();

	this->file_cont_.clear();

	return;
}


/**
 * @brief Create関数
 * @param desc (desc)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::FileCache::Create(const tml::FileCacheDesc &desc)
{
	this->Init();

	return (0);
}


/**
 * @brief AddFile関数
 * @param file_path (file_path)
 * @param buf (buffer)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::FileCache::AddFile(const WCHAR *file_path, const tml::DynamicBuffer &buf)
{
	if ((file_path == nullptr)
	|| (file_path[0] == 0)) {
		return (-1);
	}

	tml::FileCacheFile file;

	auto insert_result = this->file_cont_.emplace(file_path, file);

	if (insert_result.second) {
		insert_result.first->second.file_path_ = file_path;
		insert_result.first->second.buf_ = buf;
	} else {
		insert_result.first->second.buf_ = buf;
	}

	return (0);
}


/**
 * @brief RemoveFile関数
 * @param file_path (file_path)
 * @return result (result)<br>
 * 0未満=失敗
 */
void tml::FileCache::RemoveFile(const WCHAR *file_path)
{
	if ((file_path == nullptr)
	|| (file_path[0] == 0)) {
		return;
	}

	this->file_cont_.erase(file_path);

	return;
}
