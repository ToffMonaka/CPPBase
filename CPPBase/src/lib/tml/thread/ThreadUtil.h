/**
 * @file
 * @brief ThreadUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "ThreadUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief ThreadUtil�N���X
 *
 * ���[�e�B���e�B�p�^�[��<br>
 * �G���W���p�^�[��
 */
class ThreadUtil
{
public: ThreadUtil() = delete;
public: ThreadUtil(const ThreadUtil &) = delete;
public: ThreadUtil &operator =(const ThreadUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::ThreadUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::ThreadUtilEngine> &);
};
}
