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
	UINT master_id;
	ULONGLONG count;

	/**
	 * @brief コンストラクタ
	 */
	THREAD_ID_() :
		master_id(0U),
		count(0ULL)
	{
		return;
	}

	/**
	 * @brief コンストラクタ
	 * @param mst_id (master_id)
	 * @param cnt (count)
	 */
	THREAD_ID_(const UINT mst_id, const ULONGLONG cnt) :
		master_id(mst_id),
		count(cnt)
	{
		return;
	}
} THREAD_ID;
}
