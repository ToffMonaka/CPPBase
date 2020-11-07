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
};
}
