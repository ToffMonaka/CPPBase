/**
 * @file
 * @brief ThreadID�w�b�_�[�t�@�C��
 */
#pragma once


#include "ConstantUtil.h"


namespace tml {
/**
 * @brief THREAD_ID�\����
 */
typedef struct THREAD_ID_
{
	UINT master_id;
	UDLONG count;

	/**
	 * @brief �R���X�g���N�^
	 */
	THREAD_ID_() :
		master_id(0U),
		count(0ULL)
	{
		return;
	}

	/**
	 * @brief �R���X�g���N�^
	 *
	 * @param mst_id : 
	 * @param cnt : 
	 */
	THREAD_ID_(const UINT mst_id, const UDLONG cnt) :
		master_id(mst_id),
		count(cnt)
	{
		return;
	}
} THREAD_ID;
}
