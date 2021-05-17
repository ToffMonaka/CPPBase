/**
 * @file
 * @brief ThreadUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../util/Util.h"
#include "ThreadUtilEngine.h"


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
public: ThreadUtil(const tml::ThreadUtil &) = delete;
public: tml::ThreadUtil &operator =(const tml::ThreadUtil &) = delete;

private:
	static std::unique_ptr<tml::ThreadUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::ThreadUtilEngine> &);

	static bool CheckFixedThread(void);
	static tml::Thread *Get(void);
	static INT Start(std::unique_ptr<tml::MainThread> &);
	static INT Start(std::unique_ptr<tml::SubThread> &);
	static INT StartAll(void);
	static void End(const bool finish_flg = false);
	static void EndAll(const bool finish_flg = false);
	static INT GetExitCode(void);
	static INT CreateCOM(const DWORD);
	static void DeleteCOM(void);
};
}


/**
 * @brief CheckFixedThread�֐�
 * @return res_flg (result_flag)<br>
 * false=���s,true=����
 */
inline bool tml::ThreadUtil::CheckFixedThread(void)
{
	return (tml::Util::CheckFixedThread());
}


/**
 * @brief Get�֐�
 * @return th (thread)<br>
 * nullptr=���s
 */
inline tml::Thread *tml::ThreadUtil::Get(void)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return (nullptr);
	}

	return (tml::ThreadUtil::engine_->Get());
}


/**
 * @brief Start�֐�
 * @param th (thread)
 * @return res (result)<br>
 * 0����=���s
 */
inline INT tml::ThreadUtil::Start(std::unique_ptr<tml::MainThread> &th)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return (-1);
	}

	return (tml::ThreadUtil::engine_->Start(th));
}


/**
 * @brief Start�֐�
 * @param th (thread)
 * @return res (result)<br>
 * 0����=���s
 */
inline INT tml::ThreadUtil::Start(std::unique_ptr<tml::SubThread> &th)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return (-1);
	}

	return (tml::ThreadUtil::engine_->Start(th));
}


/**
 * @brief StartAll�֐�
 * @return res (result)<br>
 * 0����=���s
 */
inline INT tml::ThreadUtil::StartAll(void)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return (-1);
	}

	return (tml::ThreadUtil::engine_->StartAll());
}


/**
 * @brief End�֐�
 * @param finish_flg (finish_flag)
 */
inline void tml::ThreadUtil::End(const bool finish_flg)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return;
	}

	tml::ThreadUtil::engine_->End(finish_flg);

	return;
}


/**
 * @brief EndAll�֐�
 * @param finish_flg (finish_flg)
 */
inline void tml::ThreadUtil::EndAll(const bool finish_flg)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return;
	}

	tml::ThreadUtil::engine_->EndAll(finish_flg);

	return;
}


/**
 * @brief GetExitCode�֐�
 * @return exit_code (exit_code)<br>
 * 0�ȊO=���s
 */
inline INT tml::ThreadUtil::GetExitCode(void)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return (0);
	}

	return (tml::ThreadUtil::engine_->GetExitCode());
}


/**
 * @brief CreateCOM�֐�
 * @param init_flg (init_flag)
 * @return res (result)<br>
 * 0����=���s
 */
inline INT tml::ThreadUtil::CreateCOM(const DWORD init_flg)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return (-1);
	}

	return (tml::ThreadUtil::engine_->CreateCOM(init_flg));
}


/**
 * @brief DeleteCOM�֐�
 */
inline void tml::ThreadUtil::DeleteCOM(void)
{
	if (tml::ThreadUtil::engine_ == nullptr) {
		return;
	}

	return (tml::ThreadUtil::engine_->DeleteCOM());
}
