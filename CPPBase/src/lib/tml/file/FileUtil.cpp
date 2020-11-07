/**
 * @file
 * @brief FileUtil�R�[�h�t�@�C��
 */


#include "FileUtil.h"


tml::ThreadFix tml::FileUtil::th_fix_;
std::unique_ptr<tml::FileUtilEngine> tml::FileUtil::engine_;


/**
 * @brief Init�֐�
 */
void tml::FileUtil::Init(void)
{
	if (!tml::FileUtil::th_fix_.Check()) {
		return;
	}

	tml::FileUtil::engine_.reset();

	return;
}


/**
 * @brief Create�֐�
 * @param engine (engine)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::FileUtil::Create(std::unique_ptr<tml::FileUtilEngine> &engine)
{
	if (!tml::FileUtil::th_fix_.Check()) {
		tml::FileUtil::Init();

		return (-1);
	}

	tml::FileUtil::Init();

	tml::FileUtil::engine_ = std::move(engine);

	return (0);
}
