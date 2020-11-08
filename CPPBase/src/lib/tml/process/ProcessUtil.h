/**
 * @file
 * @brief ProcessUtil�w�b�_�[�t�@�C��
 */
#pragma once


#include "../ConstantUtil.h"
#include "ProcessUtilEngine.h"
#include "../thread/ThreadFix.h"


namespace tml {
/**
 * @brief ProcessUtil�N���X
 *
 * ���[�e�B���e�B�p�^�[��<br>
 * �G���W���p�^�[��
 */
class ProcessUtil
{
public: ProcessUtil() = delete;
public: ProcessUtil(const ProcessUtil &) = delete;
public: ProcessUtil &operator =(const ProcessUtil &) = delete;

private:
	static tml::ThreadFix th_fix_;
	static std::unique_ptr<tml::ProcessUtilEngine> engine_;

public:
	static void Init(void);
	static INT Create(std::unique_ptr<tml::ProcessUtilEngine> &);

	static tml::Process *Get(void);
	static INT Start(std::unique_ptr<tml::Process> &);
	static void End(const INT exit_code = 0);
	static tml::ProcessUtilEngine::STATE GetState(void);
	static INT GetExitCode(void);
};
}


/**
 * @brief Get�֐�
 * @return proc (process)<br>
 * nullptr=���s
 */
inline tml::Process *tml::ProcessUtil::Get(void)
{
	return (tml::ProcessUtil::engine_->Get());
}


/**
 * @brief Start�֐�
 * @param proc (process)
 * @return res (result)<br>
 * 0����=���s
 */
inline INT tml::ProcessUtil::Start(std::unique_ptr<tml::Process> &proc)
{
	return (tml::ProcessUtil::engine_->Start(proc));
}


/**
 * @brief End�֐�
 * @param exit_code (exit_code)
 */
inline void tml::ProcessUtil::End(const INT exit_code)
{
	tml::ProcessUtil::engine_->End(exit_code);

	return;
}


/**
 * @brief GetState�֐�
 * @return stat (state)
 */
inline tml::ProcessUtilEngine::STATE tml::ProcessUtil::GetState(void)
{
	return (tml::ProcessUtil::engine_->GetState());
}


/**
 * @brief GetExitCode�֐�
 * @return exit_code (exit_code)<br>
 * 0�ȊO=���s
 */
inline INT tml::ProcessUtil::GetExitCode(void)
{
	return (tml::ProcessUtil::engine_->GetExitCode());
}
