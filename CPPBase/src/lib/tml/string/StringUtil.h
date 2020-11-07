/**
 * @file
 * @brief StringUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "StringUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief StringUtil�N���X
 *
 * ���[�e�B���e�B�p�^�[��<br>
 * �G���W���p�^�[��
 */
class StringUtil
{
public: StringUtil() = delete;
public: StringUtil(const StringUtil &) = delete;
public: StringUtil &operator =(const StringUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::StringUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::StringUtilEngine> &);
};
}
