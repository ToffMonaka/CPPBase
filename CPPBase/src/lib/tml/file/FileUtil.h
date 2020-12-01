/**
 * @file
 * @brief FileUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "FileUtilEngine.h"
#include "../thread/MutexThreadLock.h"
#include "../thread/ThreadFix.h"


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
public: FileUtil(const FileUtil &) = delete;
public: FileUtil &operator =(const FileUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::FileUtilEngine> engine_;
	static tml::MutexThreadLock file_th_lock_;
	static tml::MutexThreadLock dir_th_lock_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::FileUtilEngine> &);

	static bool CheckThreadFix(void);
	static tml::MutexThreadLock &GetFileThreadLock(void);
	static tml::MutexThreadLock &GetDirectoryThreadLock(void);
};
}


/**
 * @brief CheckThreadFix�֐�
 * @return res_flg (result_flag)<br>
 * false=���s,true=����
 */
inline bool tml::FileUtil::CheckThreadFix(void)
{
	return (tml::FileUtil::th_fix_.Check());
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


/**
 * @brief GetDirectoryThreadLock�֐�
 *
 * Create�֐��s�v
 *
 * @return dir_th_lock (directory_thread_lock)
 */
inline tml::MutexThreadLock &tml::FileUtil::GetDirectoryThreadLock(void)
{
	return (tml::FileUtil::dir_th_lock_);
}
