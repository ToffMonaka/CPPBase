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

	static tml::Thread *Get(void);
	static INT Start(std::unique_ptr<tml::Thread> &);
	static void End(void);
	static void EndAll(void);
	static tml::ThreadUtilEngine::STATE GetState(void);
};


/**
 * @brief Get�֐�
 * @return th (thread)<br>
 * NULLP=���s
 */
inline tml::Thread *tml::ThreadUtil::Get(void)
{
	return (tml::ThreadUtil::engine_->Get());
}


/**
 * @brief Start�֐�
 * @param th (thread)
 * @return res (result)<br>
 * 0����=���s
 */
inline INT tml::ThreadUtil::Start(std::unique_ptr<tml::Thread> &th)
{
	if (!tml::ThreadUtil::th_fix_.Check()) {
		return (-1);
	}

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


/**
 * @brief GetState�֐�
 * @return stat (state)
 */
inline tml::ThreadUtilEngine::STATE tml::ThreadUtil::GetState(void)
{
	return (tml::ThreadUtil::engine_->GetState());
}
}
