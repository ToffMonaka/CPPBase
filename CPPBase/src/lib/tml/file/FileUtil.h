/**
 * @file
 * @brief FileUtilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../util/Util.h"
#include "FileUtilEngine.h"


namespace tml {
/**
 * @brief FileUtilクラス
 *
 * ユーティリティパターン<br>
 * エンジンパターン
 */
class FileUtil
{
public: FileUtil() = delete;
public: FileUtil(const tml::FileUtil &) = delete;
public: tml::FileUtil &operator =(const tml::FileUtil &) = delete;

private:
	static std::unique_ptr<tml::FileUtilEngine> engine_;
	static tml::MutexThreadLock file_th_lock_;
	static tml::MutexThreadLock dir_th_lock_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::FileUtilEngine> &);

	static bool CheckFixedThread(void);
	static tml::MutexThreadLock &GetFileThreadLock(void);
	static tml::MutexThreadLock &GetDirectoryThreadLock(void);
};
}


/**
 * @brief CheckFixedThread関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::FileUtil::CheckFixedThread(void)
{
	return (tml::Util::CheckFixedThread());
}


/**
 * @brief GetFileThreadLock関数
 *
 * Create関数不要
 *
 * @return file_th_lock (file_thread_lock)
 */
inline tml::MutexThreadLock &tml::FileUtil::GetFileThreadLock(void)
{
	return (tml::FileUtil::file_th_lock_);
}


/**
 * @brief GetDirectoryThreadLock関数
 *
 * Create関数不要
 *
 * @return dir_th_lock (directory_thread_lock)
 */
inline tml::MutexThreadLock &tml::FileUtil::GetDirectoryThreadLock(void)
{
	return (tml::FileUtil::dir_th_lock_);
}
