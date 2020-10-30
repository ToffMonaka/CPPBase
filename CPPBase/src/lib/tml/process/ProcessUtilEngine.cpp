/**
 * @file
 * @brief ProcessUtilEngine�R�[�h�t�@�C��
 */


#include "ProcessUtilEngine.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ProcessUtilEngine::ProcessUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ProcessUtilEngine::~ProcessUtilEngine()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::ProcessUtilEngine::Release(void)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->proc_.reset();
		this->stat_ = tml::ProcessUtilEngine::STATE();
	}

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ProcessUtilEngine::Init(void)
{
	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::ProcessUtilEngine::Create(void)
{
	return (0);
}


/**
 * @brief Start�֐�
 * @param proc (process)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::ProcessUtilEngine::Start(std::unique_ptr<tml::Process> &proc)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		if (this->proc_ != NULLP) {
			return (-1);
		}

		this->proc_ = std::move(proc);
	}

	if (this->proc_->Start() < 0) {
		return (-1);
	}

	while (1) {
		{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
			if (this->stat_.end_flg) {
				break;
			}
		}

		this->proc_->Update();
	}

	this->proc_->End();

	return (0);
}


/**
 * @brief End�֐�
 */
void tml::ProcessUtilEngine::End(void)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_.end_flg = TRUE;
	}

	return;
}


/**
 * @brief GetExitCode�֐�
 * @return exit_code (exit_code)<br>
 * 0�ȊO=���s
 */
INT tml::ProcessUtilEngine::GetExitCode(void)
{
	MSG msg = {};

	return (static_cast<INT>(msg.wParam));
}
