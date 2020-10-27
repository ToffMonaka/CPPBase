/**
 * @file
 * @brief ProcessUtilヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "ProcessUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief ProcessUtilクラス
 *
 * ユーティリティパターン<br>
 * エンジンパターン
 */
class ProcessUtil
{
public: ProcessUtil() = delete;
public: ProcessUtil(const ProcessUtil &) = delete;
public: ProcessUtil &operator =(const ProcessUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::ProcessUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::ProcessUtilEngine> &);
};
}
