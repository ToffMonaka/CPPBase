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

	static INT Start(std::unique_ptr<tml::Process> &);
	void End(void);
	static INT GetExitCode(void);
};


/**
 * @brief Start�֐�
 * @param proc (process)
 * @return res (result)<br>
 * 0����=���s,-2=���d�N��
 */
inline INT tml::ProcessUtil::Start(std::unique_ptr<tml::Process> &proc)
{
	return (tml::ProcessUtil::engine_->Start(proc));
}


/**
 * @brief End�֐�
 */
inline void tml::ProcessUtil::End(void)
{
	tml::ProcessUtil::engine_->End();

	return;
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
}
