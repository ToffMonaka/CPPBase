/**
 * @file
 * @brief MemoryUtil�R�[�h�t�@�C��
 */


#include "MemoryUtil.h"


tml::ThreadFix tml::MemoryUtil::th_fix;
tml::MemoryUtilEngine *tml::MemoryUtil::engine_ = NULLP;


/**
 * @brief Release�֐�
 */
void tml::MemoryUtil::Release(void)
{
	return;
}


/**
 * @brief Init�֐�
 */
void tml::MemoryUtil::Init(void)
{
	if (!tml::MemoryUtil::th_fix.Check()) {
		return;
	}

	tml::MemoryUtil::Release();

	tml::MemoryUtil::engine_ = NULLP;

	return;
}


/**
 * @brief Create�֐�
 * @param engine (engine)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::MemoryUtil::Create(tml::MemoryUtilEngine *engine)
{
	if (!tml::MemoryUtil::th_fix.Check()) {
		tml::MemoryUtil::Init();

		return (-1);
	}

	if (engine == NULLP) {
		tml::MemoryUtil::Init();

		return (-1);
	}

	tml::MemoryUtil::Release();

	tml::MemoryUtil::engine_ = engine;

	return (0);
}
