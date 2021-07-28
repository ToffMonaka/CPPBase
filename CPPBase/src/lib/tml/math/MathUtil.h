/**
 * @file
 * @brief MathUtilヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_MATH.h"
#include "../util/Util.h"
#include "MathUtilEngine.h"


namespace tml {
/**
 * @brief MathUtilクラス
 *
 * ユーティリティパターン<br>
 * エンジンパターン
 */
class MathUtil
{
public: MathUtil() = delete;
public: MathUtil(const tml::MathUtil &) = delete;
public: tml::MathUtil &operator =(const tml::MathUtil &) = delete;

private:
	static std::unique_ptr<tml::MathUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::MathUtilEngine> &);

	static bool CheckFixedThread(void);
	static FLOAT GetAngleRadian(const FLOAT);
	static FLOAT GetAngleDegree(const FLOAT);
	static FLOAT GetColor1(const UINT);
	static UINT GetColor255(const FLOAT);
};
}


/**
 * @brief CheckFixedThread関数
 * @return result_flg (result_flag)<br>
 * false=失敗,true=成功
 */
inline bool tml::MathUtil::CheckFixedThread(void)
{
	return (tml::Util::CheckFixedThread());
}


/**
 * @brief GetAngleRadian関数
 *
 * Create関数不要
 *
 * @param angle (angle)
 * @return angle (angle)
 */
inline FLOAT tml::MathUtil::GetAngleRadian(const FLOAT angle)
{
	return (angle * (tml::ConstantUtil::MATH::PI / 180.0f));
}


/**
 * @brief GetAngleDegree関数
 *
 * Create関数不要
 *
 * @param angle (angle)
 * @return angle (angle)
 */
inline FLOAT tml::MathUtil::GetAngleDegree(const FLOAT angle)
{
	return (angle * (180.0f / tml::ConstantUtil::MATH::PI));
}


/**
 * @brief GetColor1関数
 *
 * Create関数不要
 *
 * @param val (value)
 * @return val (value)
 */
inline FLOAT tml::MathUtil::GetColor1(const UINT val)
{
	return (static_cast<FLOAT>(val) / 255.0f);
}


/**
 * @brief GetColor255関数
 *
 * Create関数不要
 *
 * @param val (value)
 * @return val (value)
 */
inline UINT tml::MathUtil::GetColor255(const FLOAT val)
{
	return (static_cast<UINT>(val * 255.0f));
}
