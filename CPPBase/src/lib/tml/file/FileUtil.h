/**
 * @file
 * @brief FileUtilヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "FileUtilEngine.h"
#include "../thread/ThreadFix.h"


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
public: FileUtil(const FileUtil &) = delete;
public: FileUtil &operator =(const FileUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::FileUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::FileUtilEngine> &);

	static bool CheckThreadFix(void);
};
}


/**
 * @brief CheckThreadFix関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::FileUtil::CheckThreadFix(void)
{
	return (tml::FileUtil::th_fix_.Check());
}
