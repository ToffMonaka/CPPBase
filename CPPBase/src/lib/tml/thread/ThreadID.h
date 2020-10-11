/**
 * @file
 * @brief ThreadIDヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief THREAD_ID構造体
 */
typedef struct THREAD_ID_
{
	UINT id;
	UDLONG count;

	/**
	 * @brief コンストラクタ
	 */
	THREAD_ID_() :
		id(0U),
		count(0ULL)
	{
		return;
	}

	/**
	 * @brief コンストラクタ
	 *
	 * @param id : id
	 * @param cnt : count
	 */
	THREAD_ID_(const UINT id, const UDLONG cnt) :
		id(id),
		count(cnt)
	{
		return;
	}
} THREAD_ID;
}
