/**
 * @file
 * @brief Util�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../thread/FixedThread.h"


namespace tml {
/**
 * @brief Util�N���X
 *
 * ���[�e�B���e�B�p�^�[��
 */
class Util
{
public: Util() = delete;
public: Util(const tml::Util &) = delete;
public: tml::Util &operator =(const tml::Util &) = delete;

private:
	static tml::FixedThread fixed_th_;

public:
	static bool CheckFixedThread(void);
};
}


/**
 * @brief CheckFixedThread�֐�
 * @return res_flg (result_flag)<br>
 * false=���s,true=����
 */
inline bool tml::Util::CheckFixedThread(void)
{
	return (tml::Util::fixed_th_.Check());
}
