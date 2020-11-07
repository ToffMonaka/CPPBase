/**
 * @file
 * @brief StringUtil�R�[�h�t�@�C��
 */


#include "StringUtil.h"


tml::ThreadFix tml::StringUtil::th_fix_;
std::unique_ptr<tml::StringUtilEngine> tml::StringUtil::engine_;


/**
 * @brief Init�֐�
 */
void tml::StringUtil::Init(void)
{
	if (!tml::StringUtil::th_fix_.Check()) {
		return;
	}

	tml::StringUtil::engine_.reset();

	return;
}


/**
 * @brief Create�֐�
 * @param engine (engine)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::StringUtil::Create(std::unique_ptr<tml::StringUtilEngine> &engine)
{
	if (!tml::StringUtil::th_fix_.Check()) {
		tml::StringUtil::Init();

		return (-1);
	}

	tml::StringUtil::Init();

	tml::StringUtil::engine_ = std::move(engine);

	return (0);
}
