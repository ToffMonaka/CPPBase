/**
 * @file
 * @brief ProcessUtil�R�[�h�t�@�C��
 */


#include "ProcessUtil.h"


tml::ThreadFix tml::ProcessUtil::th_fix_;
std::unique_ptr<tml::ProcessUtilEngine> tml::ProcessUtil::engine_;


/**
 * @brief Init�֐�
 */
void tml::ProcessUtil::Init(void)
{
	if (!tml::ProcessUtil::th_fix_.Check()) {
		return;
	}

	tml::ProcessUtil::engine_.reset();

	return;
}


/**
 * @brief Create�֐�
 * @param engine (engine)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::ProcessUtil::Create(std::unique_ptr<tml::ProcessUtilEngine> &engine)
{
	if (!tml::ProcessUtil::th_fix_.Check()) {
		tml::ProcessUtil::Init();

		return (-1);
	}

	tml::ProcessUtil::Init();

	tml::ProcessUtil::engine_ = std::move(engine);

	return (0);
}
