/**
 * @file
 * @brief ProcessID�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief PROCESS_ID�\����
 */
typedef struct PROCESS_ID_
{
	UINT master_id;
	UDLONG count;

	/**
	 * @brief �R���X�g���N�^
	 */
	PROCESS_ID_() :
		master_id(0U),
		count(0ULL)
	{
		return;
	}

	/**
	 * @brief �R���X�g���N�^
	 * @param mst_id (master_id)
	 * @param cnt (count)
	 */
	PROCESS_ID_(const UINT mst_id, const UDLONG cnt) :
		master_id(mst_id),
		count(cnt)
	{
		return;
	}
} PROCESS_ID;
}
