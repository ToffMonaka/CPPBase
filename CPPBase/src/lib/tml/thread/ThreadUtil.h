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

	static INT Start(std::unique_ptr<tml::Thread> &);
	void End(void);
	void EndAll(void);
};


/**
 * @brief Start�֐�
 * @param th (thread)
 * @return res (result)<br>
 * 0����=���s
 */
inline INT tml::ThreadUtil::Start(std::unique_ptr<tml::Thread> &th)
{
	return (tml::ThreadUtil::engine_->Start(th));
}


/**
 * @brief End�֐�
 */
inline void tml::ThreadUtil::End(void)
{
	tml::ThreadUtil::engine_->End();

	return;
}


/**
 * @brief EndAll�֐�
 */
inline void tml::ThreadUtil::EndAll(void)
{
	tml::ThreadUtil::engine_->EndAll();

	return;
}
}
