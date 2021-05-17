/**
 * @file
 * @brief TimeUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../util/Util.h"
#include "TimeUtilEngine.h"


namespace tml {
/**
 * @brief TimeUtil�N���X
 *
 * ���[�e�B���e�B�p�^�[��<br>
 * �G���W���p�^�[��
 */
class TimeUtil
{
public: TimeUtil() = delete;
public: TimeUtil(const tml::TimeUtil &) = delete;
public: tml::TimeUtil &operator =(const tml::TimeUtil &) = delete;

private:
	static std::unique_ptr<tml::TimeUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::TimeUtilEngine> &);

	static bool CheckFixedThread(void);
	static tml::TIME_REAL Sleep(const tml::TIME_REAL &);
	static tml::TIME_REAL Wait(const tml::TIME_REAL &);
};
}


/**
 * @brief CheckFixedThread�֐�
 * @return res_flg (result_flag)<br>
 * false=���s,true=����
 */
inline bool tml::TimeUtil::CheckFixedThread(void)
{
	return (tml::Util::CheckFixedThread());
}
