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

	static bool CheckThreadFix(void);
	static tml::Thread *Get(void);
	static INT Start(std::unique_ptr<tml::Thread> &, const bool ready_flg = false);
	static INT StartAll(void);
	static void End(const bool finish_flg = false);
	static void EndAll(const bool delete_flg = false);
	static tml::ThreadUtilEngine::STATE GetState(void);
};
}


/**
 * @brief CheckThreadFix�֐�
 * @return res_flg (result_flag)<br>
 * false=���s,true=����
 */
inline bool tml::ThreadUtil::CheckThreadFix(void)
{
	return (tml::ThreadUtil::th_fix_.Check());
}


/**
 * @brief Get�֐�
 * @return th (thread)<br>
 * nullptr=���s
 */
inline tml::Thread *tml::ThreadUtil::Get(void)
{
	return (tml::ThreadUtil::engine_->Get());
}


/**
 * @brief Start�֐�
 * @param th (thread)
 * @param ready_flg (ready_flag)
 * @return res (result)<br>
 * 0����=���s
 */
inline INT tml::ThreadUtil::Start(std::unique_ptr<tml::Thread> &th, const bool ready_flg)
{
	return (tml::ThreadUtil::engine_->Start(th, ready_flg));
}


/**
 * @brief StartAll�֐�
 * @return res (result)<br>
 * 0����=���s
 */
inline INT tml::ThreadUtil::StartAll(void)
{
	return (tml::ThreadUtil::engine_->StartAll());
}


/**
 * @brief End�֐�
 * @param finish_flg (finish_flag)
 */
inline void tml::ThreadUtil::End(const bool finish_flg)
{
	tml::ThreadUtil::engine_->End(finish_flg);

	return;
}


/**
 * @brief EndAll�֐�
 * @param delete_flg (delete_flag)
 */
inline void tml::ThreadUtil::EndAll(const bool delete_flg)
{
	tml::ThreadUtil::engine_->EndAll(delete_flg);

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
