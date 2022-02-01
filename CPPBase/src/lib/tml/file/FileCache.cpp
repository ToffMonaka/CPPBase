/**
 * @file
 * @brief FileCache�R�[�h�t�@�C��
 */


#include "FileCache.h"


/**
 * @brief �R���X�g���N�^
 */
tml::FileCacheFile::FileCacheFile()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::FileCacheFile::~FileCacheFile()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::FileCacheFile::Init(void)
{
	this->Release();

	this->file_path_.clear();
	this->buf_.Init();

	return;
}


/**
 * @brief Create�֐�
 * @param file_path (file_path)
 * @param buf (buffer)
 * @return result (result)<br>
 * 0����=���s
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
 * @brief �R���X�g���N�^
 */
tml::FileCacheDesc::FileCacheDesc()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::FileCacheDesc::~FileCacheDesc()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::FileCacheDesc::Init(void)
{
	this->Release();

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::FileCache::FileCache()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::FileCache::~FileCache()
{
	this->Release();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::FileCache::Init(void)
{
	this->Release();

	this->file_cont_.clear();

	return;
}


/**
 * @brief Create�֐�
 * @param desc (desc)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::FileCache::Create(const tml::FileCacheDesc &desc)
{
	this->Init();

	return (0);
}


/**
 * @brief AddFile�֐�
 * @param file_path (file_path)
 * @param buf (buffer)
 * @return result (result)<br>
 * 0����=���s
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
 * @brief RemoveFile�֐�
 * @param file_path (file_path)
 * @return result (result)<br>
 * 0����=���s
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
