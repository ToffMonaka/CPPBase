/**
 * @file
 * @brief ThreadID�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief THREAD_ID�\����
 */
typedef struct THREAD_ID_
{
	UINT id;
	UDLONG count;

	/**
	 * @brief �R���X�g���N�^
	 */
	THREAD_ID_() :
		id(0U),
		count(0ULL)
	{
		return;
	}

	/**
	 * @brief �R���X�g���N�^
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
