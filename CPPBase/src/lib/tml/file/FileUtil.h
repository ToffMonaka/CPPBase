/**
 * @file
 * @brief FileUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../util/Util.h"
#include "FileUtilEngine.h"
#include "FileCache.h"


namespace tml {
/**
 * @brief FileUtil�N���X
 *
 * ���[�e�B���e�B�p�^�[��<br>
 * �G���W���p�^�[��
 */
class FileUtil
{
public: FileUtil() = delete;
public: FileUtil(const tml::FileUtil &) = delete;
public: tml::FileUtil &operator =(const tml::FileUtil &) = delete;

private:
	static std::unique_ptr<tml::FileUtilEngine> engine_;
	static BYTE *read_buf_;
	static size_t read_buf_size_;
	static BYTE *write_buf_;
	static size_t write_buf_size_;
	static tml::FileCache cache_;
	static tml::MutexThreadLock file_th_lock_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::FileUtilEngine> &);

	static bool CheckFixedThread(void);
	static BYTE *&GetReadBuffer(BYTE *&, size_t &);
	static BYTE *&GetWriteBuffer(BYTE *&, size_t &);
	static tml::FileCache &GetCache(void);
	static tml::MutexThreadLock &GetFileThreadLock(void);
};
}


/**
 * @brief CheckFixedThread�֐�
 * @return result_flg (result_flag)<br>
 * false=���s,true=����
 */
inline bool tml::FileUtil::CheckFixedThread(void)
{
	return (tml::Util::CheckFixedThread());
}


/**
 * @brief GetCache�֐�
 *
 * Create�֐��s�v
 *
 * @return cache (cache)
 */
inline tml::FileCache &tml::FileUtil::GetCache(void)
{
	return (tml::FileUtil::cache_);
}


/**
 * @brief GetFileThreadLock�֐�
 *
 * Create�֐��s�v
 *
 * @return file_th_lock (file_thread_lock)
 */
inline tml::MutexThreadLock &tml::FileUtil::GetFileThreadLock(void)
{
	return (tml::FileUtil::file_th_lock_);
}
