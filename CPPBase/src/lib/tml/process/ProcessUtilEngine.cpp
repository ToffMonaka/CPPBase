/**
 * @file
 * @brief ProcessUtilEngineコードファイル
 */


#include "ProcessUtilEngine.h"
#include "../thread/ThreadUtil.h"


/**
 * @brief コンストラクタ
 */
tml::ProcessUtilEngine::ProcessUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ProcessUtilEngine::~ProcessUtilEngine()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::ProcessUtilEngine::Release(void)
{
	std::unique_ptr<tml::Process> proc;

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_.end_flg = true;

		proc = std::move(this->proc_);
	}

	proc.reset();

	return;
}


/**
 * @brief Init関数
 */
void tml::ProcessUtilEngine::Init(void)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_ = tml::ProcessUtilEngine::STATE();
	}

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ProcessUtilEngine::Create(void)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_ = tml::ProcessUtilEngine::STATE();
	}

	return (0);
}


/**
 * @brief Start関数
 * @param proc (process)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ProcessUtilEngine::Start(std::unique_ptr<tml::Process> &proc)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		if (this->stat_.end_flg) {
			return (-1);
		}

		if (this->proc_ != NULLP) {
			return (-1);
		}

		this->proc_ = std::move(proc);
	}

	if (this->proc_->Start() < 0) {
		return (-1);
	}

	tml::ThreadUtil::StartAll();

	do {
		this->proc_->Update();

		{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
			if (this->stat_.end_flg) {
				break;
			}
		}
	} while (1);

	tml::ThreadUtil::EndAll(true);

	this->proc_->End();

	return (0);
}


/**
 * @brief End関数
 */
void tml::ProcessUtilEngine::End(void)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_.end_flg = true;
	}

	return;
}


/**
 * @brief GetExitCode関数
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
INT tml::ProcessUtilEngine::GetExitCode(void)
{
	MSG msg = {};

	return (static_cast<INT>(msg.wParam));
}
