/**
 * @file
 * @brief Utilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/FixedThread.h"


namespace tml {
/**
 * @brief Utilクラス
 *
 * ユーティリティパターン
 */
class Util
{
public: Util() = delete;
public: Util(const tml::Util &) = delete;
public: tml::Util &operator =(const tml::Util &) = delete;

private:
	static tml::FixedThread fixed_th_;

public:
	static bool CheckFixedThread(void);
};
}


/**
 * @brief CheckFixedThread関数
 * @return res_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::Util::CheckFixedThread(void)
{
	return (tml::Util::fixed_th_.Check());
}
