/**
 * @file
 * @brief MathUtil�R�[�h�t�@�C��
 */


#include "MathUtil.h"


std::unique_ptr<tml::MathUtilEngine> tml::MathUtil::engine_;


/**
 * @brief Init�֐�
 */
void tml::MathUtil::Init(void)
{
	if (!tml::MathUtil::CheckFixedThread()) {
		return;
	}

	tml::MathUtil::engine_.reset();

	return;
}


/**
 * @brief Create�֐�
 * @param engine (engine)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::MathUtil::Create(std::unique_ptr<tml::MathUtilEngine> &engine)
{
	if (!tml::MathUtil::CheckFixedThread()) {
		tml::MathUtil::Init();

		return (-1);
	}

	tml::MathUtil::Init();

	tml::MathUtil::engine_ = std::move(engine);

	return (0);
}
