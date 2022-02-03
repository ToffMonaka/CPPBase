/**
 * @file
 * @brief FileUtilEngine�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief FileUtilEngineDesc�N���X
 */
class FileUtilEngineDesc
{
public:
	size_t cache_file_limit;
	size_t cache_file_buffer_limit;

private:
	void Release(void);

public:
	FileUtilEngineDesc();
	virtual ~FileUtilEngineDesc();

	virtual void Init(void);
};
}


/**
 * @brief Release�֐�
 */
inline void tml::FileUtilEngineDesc::Release(void)
{
	return;
}


namespace tml {
/**
 * @brief FileUtilEngine�N���X
 *
 * �C���^�[�t�F�[�X�p�^�[��
 */
class FileUtilEngine
{
public: FileUtilEngine(const tml::FileUtilEngine &) = delete;
public: tml::FileUtilEngine &operator =(const tml::FileUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	size_t cache_file_limit_;
	size_t cache_file_buf_limit_;

private:
	void Release(void);

public:
	FileUtilEngine();
	virtual ~FileUtilEngine();

	virtual void Init(void);
	INT Create(const tml::FileUtilEngineDesc &);

	size_t GetCacheFileLimit(void) const;
	size_t GetCacheFileBufferLimit(void) const;
};
}


/**
 * @brief Release�֐�
 */
inline void tml::FileUtilEngine::Release(void)
{
	return;
}


/**
 * @brief GetCacheFileLimit�֐�
 * @return cache_file_limit (cache_file_limit)
 */
inline size_t tml::FileUtilEngine::GetCacheFileLimit(void) const
{
	return (this->cache_file_limit_);
}


/**
 * @brief GetCacheFileBufferLimit�֐�
 * @return cache_file_buf_limit (cache_file_buffer_limit)
 */
inline size_t tml::FileUtilEngine::GetCacheFileBufferLimit(void) const
{
	return (this->cache_file_buf_limit_);
}
