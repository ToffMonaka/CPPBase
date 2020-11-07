/**
 * @file
 * @brief StringUtilヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "StringUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief StringUtilクラス
 *
 * ユーティリティパターン<br>
 * エンジンパターン
 */
class StringUtil
{
public: StringUtil() = delete;
public: StringUtil(const StringUtil &) = delete;
public: StringUtil &operator =(const StringUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::StringUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::StringUtilEngine> &);
};
}
