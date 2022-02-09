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
 * @param buf_size (buffer_size)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::FileCacheFile::Create(const WCHAR *file_path, const BYTE *buf, const size_t buf_size)
{
	if ((file_path == nullptr)
	|| (file_path[0] == 0)) {
		this->Init();

		return (-1);
	}

	this->Init();

	this->file_path_ = file_path;
	this->buf_.Set(buf, buf_size);

	return (0);
}


/**
 * @brief �R���X�g���N�^
 */
tml::FileCacheDesc::FileCacheDesc() :
	file_limit(0U),
	file_buffer_limit(0U)
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

	this->file_limit = 0U;
	this->file_buffer_limit = 0U;

	return;
}


/**
 * @brief �R���X�g���N�^
 */
tml::FileCache::FileCache() :
	file_limit_(0U),
	file_buf_limit_(0U)
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

	this->file_limit_ = 0U;
	this->file_buf_limit_ = 0U;
	this->file_cont_.clear();
	this->file_cont_by_file_path_.clear();

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

	this->file_limit_ = desc.file_limit;
	this->file_buf_limit_ = desc.file_buffer_limit;

	return (0);
}


/**
 * @brief AddFile�֐�
 * @param file_path (file_path)
 * @param buf (buffer)
 * @param buf_size (buffer_size)
 * @param append_flg (append_flag)
 * @return result (result)<br>
 * 0����=���s
 */
INT tml::FileCache::AddFile(const WCHAR *file_path, const BYTE *buf, const size_t buf_size, const bool append_flg)
{
	if ((file_path == nullptr)
	|| (file_path[0] == 0)) {
		return (-1);
	}

	if (buf_size > this->file_buf_limit_) {
		this->RemoveFile(file_path);

		return (-1);
	}

	auto file_itr = this->file_cont_by_file_path_.find(file_path);

	if (file_itr == this->file_cont_by_file_path_.end()) {
		if (this->file_limit_ <= 0U) {
			return (-1);
		}

		if (this->file_cont_.size() >= this->file_limit_) {
			auto file_itr2 = this->file_cont_.begin();

			this->file_cont_by_file_path_.erase(file_itr2->get()->file_path_);
			this->file_cont_.erase(file_itr2);
		}

		auto file = tml::make_unique<tml::FileCacheFile>(1U);
		auto file_p = file.get();

		file_p->file_path_ = file_path;
		file_p->buf_.Set(buf, buf_size);

		this->file_cont_by_file_path_.emplace(file_path, file_p);
		this->file_cont_.push_back(std::move(file));

		return (0);
	}

	auto file = file_itr->second;

	file->buf_.Set(buf, buf_size);

	this->UpFilePart(file);

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

	auto file_itr = this->file_cont_by_file_path_.find(file_path);

	if (file_itr == this->file_cont_by_file_path_.end()) {
		return;
	}

	auto file = file_itr->second;

	this->file_cont_by_file_path_.erase(file_itr);

	for (auto file_itr2 = this->file_cont_.begin(), file_end_itr2 = this->file_cont_.end(); file_itr2 != file_end_itr2; ++file_itr2) {
		if (file_itr2->get() == file) {
			this->file_cont_.erase(file_itr2);

			break;
		}
	}

	return;
}


/**
 * @brief UpFilePart�֐�
 * @param file (file)
 */
void tml::FileCache::UpFilePart(const tml::FileCacheFile *file)
{
	if (file == this->file_cont_.back().get()) {
		return;
	}

	for (auto file_itr2 = this->file_cont_.begin(), file_end_itr2 = this->file_cont_.end(); file_itr2 != file_end_itr2; ++file_itr2) {
		if (file_itr2->get() == file) {
			tml::unique_ptr<tml::FileCacheFile> tmp_file = std::move((*file_itr2));

			this->file_cont_.erase(file_itr2);
			this->file_cont_.push_back(std::move(tmp_file));

			break;
		}
	}

	return;
}
