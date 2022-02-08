/**
 * @file
 * @brief FileCache�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <list>
#include <map>
#include "../memory/DynamicBuffer.h"


namespace tml {
class FileCache;
}


namespace tml {
/**
 * @brief FileCacheFile�N���X
 */
class FileCacheFile
{
friend class tml::FileCache;

private:
	std::wstring file_path_;
	tml::DynamicBuffer buf_;

private:
	void Release(void);

public:
	FileCacheFile();
	virtual ~FileCacheFile();

	virtual void Init(void);
	INT Create(const WCHAR *, const tml::DynamicBuffer &);

	const std::wstring &GetFilePath(void) const;
	const tml::DynamicBuffer &GetBuffer(void) const;
};
}


/**
 * @brief Release�֐�
 */
inline void tml::FileCacheFile::Release(void)
{
	return;
}


/**
 * @brief GetFilePath�֐�
 * @return file_path (file_path)
 */
inline const std::wstring &tml::FileCacheFile::GetFilePath(void) const
{
	return (this->file_path_);
}


/**
 * @brief GetBuffer�֐�
 * @return buf (buffer)
 */
inline const tml::DynamicBuffer &tml::FileCacheFile::GetBuffer(void) const
{
	return (this->buf_);
}


namespace tml {
/**
 * @brief FileCacheDesc�N���X
 */
class FileCacheDesc
{
public:
	size_t file_limit;
	size_t file_buffer_limit;

private:
	void Release(void);

public:
	FileCacheDesc();
	virtual ~FileCacheDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::FileCacheDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief FileCache�N���X
 */
class FileCache
{
public: FileCache(const tml::FileCache &) = delete;
public: tml::FileCache &operator =(const tml::FileCache &) = delete;

private:
	size_t file_limit_;
	size_t file_buf_limit_;
	std::list<tml::unique_ptr<tml::FileCacheFile>> file_cont_;
	std::map<std::wstring, tml::FileCacheFile *> file_cont_by_file_path_;

private:
	void Release(void);

	void UpFilePart(const tml::FileCacheFile *);

public:
	FileCache();
	virtual ~FileCache();

	virtual void Init(void);
	INT Create(const tml::FileCacheDesc &);

	const tml::FileCacheFile *GetFile(const WCHAR *);
	INT AddFile(const WCHAR *, const BYTE *, const size_t);
	void RemoveFile(const WCHAR *);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::FileCache::Release(void)
{
	return;
}


/**
 * @brief GetFile�֐�
 * @param file_path (file_path)
 * @return file (file)<br>
 * nullptr=���s
 */
inline const tml::FileCacheFile *tml::FileCache::GetFile(const WCHAR *file_path)
{
	auto file_itr = this->file_cont_by_file_path_.find(file_path);

	if (file_itr == this->file_cont_by_file_path_.end()) {
		return (nullptr);
	}

	this->UpFilePart(file_itr->second);

	return (file_itr->second);
}
