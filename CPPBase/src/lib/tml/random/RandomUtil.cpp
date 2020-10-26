/**
 * @file
 * @brief RandomUtil�R�[�h�t�@�C��
 */


#include "RandomUtil.h"


tml::ThreadFix tml::RandomUtil::th_fix_;
std::unique_ptr<tml::RandomUtilEngine> tml::RandomUtil::engine_;


/**
 * @brief Init�֐�
 */
void tml::RandomUtil::Init(void)
{
	if (!tml::RandomUtil::th_fix_.Check()) {
		return;
	}

	tml::RandomUtil::engine_.reset();

	return;
}


/**
 * @brief Create�֐�
 * @param engine (engine)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::RandomUtil::Create(std::unique_ptr<tml::RandomUtilEngine> &engine)
{
	if (!tml::RandomUtil::th_fix_.Check()) {
		tml::RandomUtil::Init();

		return (-1);
	}

	tml::RandomUtil::Init();

	tml::RandomUtil::engine_ = std::move(engine);

	return (0);
}
