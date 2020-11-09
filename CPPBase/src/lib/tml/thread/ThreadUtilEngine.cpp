/**
 * @file
 * @brief ThreadUtilEngine�R�[�h�t�@�C��
 */


#include "ThreadUtilEngine.h"
#include "../process/ProcessUtil.h"


/**
 * @brief �R���X�g���N�^
 */
tml::ThreadUtilEngine::ThreadUtilEngine()
{
	return;
}


/**
 * @brief �f�X�g���N�^
 */
tml::ThreadUtilEngine::~ThreadUtilEngine()
{
	return;
}


/**
 * @brief Release�֐�
 */
void tml::ThreadUtilEngine::Release(void)
{
	std::list<std::unique_ptr<tml::Thread>> th_cont;

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_.ended_flg = true;

		this->ready_th_cont_.clear();

		for (auto th : this->start_th_cont_) {
			th->SetLoopFlag(false);
		}

		for (auto &th : this->th_cont_) {
			th_cont.push_back(std::move(th));
		}

		this->th_cont_.clear();
	}

	th_cont.clear();

	return;
}


/**
 * @brief Init�֐�
 */
void tml::ThreadUtilEngine::Init(void)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_ = tml::ThreadUtilEngine::STATE();
	}

	return;
}


/**
 * @brief Create�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::ThreadUtilEngine::Create(void)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_ = tml::ThreadUtilEngine::STATE();
	}

	return (0);
}


/**
 * @brief Start�֐�
 * @param th (thread)
 * @param ready_flg (ready_flag)
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::ThreadUtilEngine::Start(std::unique_ptr<tml::Thread> &th, const bool ready_flg)
{
	if (tml::ProcessUtil::Get() == nullptr) {
		return (-1);
	}

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		if (this->stat_.ended_flg) {
			return (-1);
		}

		auto tmp_th = th.get();

		if (!ready_flg) {
			tmp_th->CreateCore();

			this->start_th_cont_.push_back(tmp_th);
			this->start_th_cont_with_th_id_.insert(std::make_pair(tmp_th->GetThreadID(), tmp_th));
		} else {
			this->ready_th_cont_.push_back(tmp_th);
		}

		this->th_cont_.push_back(std::move(th));
	}

	return (0);
}


/**
 * @brief StartAll�֐�
 * @return res (result)<br>
 * 0����=���s
 */
INT tml::ThreadUtilEngine::StartAll(void)
{
	if (tml::ProcessUtil::Get() == nullptr) {
		return (-1);
	}

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		if (this->stat_.ended_flg) {
			return (-1);
		}

		for (auto tmp_th : this->ready_th_cont_) {
			tmp_th->CreateCore();

			this->start_th_cont_.push_back(tmp_th);
			this->start_th_cont_with_th_id_.insert(std::make_pair(tmp_th->GetThreadID(), tmp_th));
		}

		this->ready_th_cont_.clear();
	}

	return (0);
}


/**
 * @brief End�֐�
 * @param finish_flg (finish_flag)
 */
void tml::ThreadUtilEngine::End(const bool finish_flg)
{
	if (tml::ProcessUtil::Get() == nullptr) {
		return;
	}

	auto th_id = std::this_thread::get_id();

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		auto th_itr = this->start_th_cont_with_th_id_.find(th_id);

		if (th_itr == this->start_th_cont_with_th_id_.end()) {
			return;
		}

		auto th = th_itr->second;

		th->SetLoopFlag(false);

		if (finish_flg) {
			this->start_th_cont_.remove(th);
			this->start_th_cont_with_th_id_.erase(th_id);
		}
	}

	return;
}


/**
 * @brief EndAll�֐�
 * @param delete_flg (delete_flag)
 */
void tml::ThreadUtilEngine::EndAll(const bool delete_flg)
{
	if (tml::ProcessUtil::Get() == nullptr) {
		return;
	}

	std::list<std::unique_ptr<tml::Thread>> th_cont;

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_.ended_flg = true;

		this->ready_th_cont_.clear();

		for (auto th : this->start_th_cont_) {
			th->SetLoopFlag(false);
		}

		if (delete_flg) {
			for (auto &th : this->th_cont_) {
				th_cont.push_back(std::move(th));
			}

			this->th_cont_.clear();
		}
	}

	th_cont.clear();

	return;
}
