/**
 * @file
 * @brief ThreadUtilEngineコードファイル
 */


#include "ThreadUtilEngine.h"


/**
 * @brief コンストラクタ
 */
tml::ThreadUtilEngine::ThreadUtilEngine()
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::ThreadUtilEngine::~ThreadUtilEngine()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::ThreadUtilEngine::Release(void)
{
	this->EndAll(true);

	return;
}


/**
 * @brief Init関数
 */
void tml::ThreadUtilEngine::Init(void)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_ = tml::ThreadUtilEngine::STATE();
	}

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ThreadUtilEngine::Create(void)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_ = tml::ThreadUtilEngine::STATE();
	}

	return (0);
}


/**
 * @brief Start関数
 * @param th (thread)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ThreadUtilEngine::Start(std::unique_ptr<tml::MainThread> &th)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		if (this->stat_.all_ended_flg) {
			return (-1);
		}

		auto tmp_th = th.get();

		if (this->stat_.all_started_flg) {
			return (-1);
		} else {
			this->start_th_cont_.push_back(tmp_th);
			this->start_th_cont_with_th_id_.insert(std::make_pair(tmp_th->GetThreadID(), tmp_th));
		}

		this->main_th_ = std::move(th);
	}

	if (this->StartAll() < 0) {
		return (-1);
	}

	this->EndAll(true);

	return (0);
}


/**
 * @brief Start関数
 * @param th (thread)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ThreadUtilEngine::Start(std::unique_ptr<tml::SubThread> &th)
{
	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		if (this->stat_.all_ended_flg) {
			return (-1);
		}

		auto tmp_th = th.get();

		if (this->stat_.all_started_flg) {
			tmp_th->CreateCore();

			this->start_th_cont_.push_back(tmp_th);
			this->start_th_cont_with_th_id_.insert(std::make_pair(tmp_th->GetThreadID(), tmp_th));
		} else {
			this->ready_th_cont_.push_back(tmp_th);
		}

		this->sub_th_cont_.push_back(std::move(th));
	}

	return (0);
}


/**
 * @brief StartAll関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::ThreadUtilEngine::StartAll(void)
{
	if (this->main_th_->Start() < 0) {
		this->End(true);

		return (-1);
	}

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		if (this->stat_.all_ended_flg) {
			return (-1);
		}

		this->stat_.all_started_flg = true;

		for (auto tmp_th : this->ready_th_cont_) {
			tmp_th->CreateCore();

			this->start_th_cont_.push_back(tmp_th);
			this->start_th_cont_with_th_id_.insert(std::make_pair(tmp_th->GetThreadID(), tmp_th));
		}

		this->ready_th_cont_.clear();
	}

	if (this->main_th_->GetWindowHandle() != nullptr) {
		MSG msg = {};

		do {
			while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
						this->stat_.exit_code = static_cast<INT>(msg.wParam);

						this->main_th_->SetLoopFlag(false);
					}

					break;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (this->main_th_->GetLoopFlag()) {
				this->main_th_->Update();
			}
		} while (this->main_th_->GetLoopFlag());
	} else {
		do {
			this->main_th_->Update();
		} while (this->main_th_->GetLoopFlag());
	}

	return (0);
}


/**
 * @brief End関数
 * @param finish_flg (finish_flag)
 */
void tml::ThreadUtilEngine::End(const bool finish_flg)
{
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
 * @brief EndAll関数
 * @param delete_flg (delete_flag)
 */
void tml::ThreadUtilEngine::EndAll(const bool delete_flg)
{
	std::unique_ptr<tml::Thread> main_th;
	std::list<std::unique_ptr<tml::Thread>> sub_th_cont;

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_.all_ended_flg = true;

		this->ready_th_cont_.clear();

		for (auto th : this->start_th_cont_) {
			th->SetLoopFlag(false);
		}

		if (delete_flg) {
			main_th = std::move(this->main_th_);

			for (auto &sub_th : this->sub_th_cont_) {
				sub_th_cont.push_back(std::move(sub_th));
			}

			this->sub_th_cont_.clear();
		}
	}

	if (!sub_th_cont.empty()) {
		sub_th_cont.clear();
	}

	if (main_th != nullptr) {
		main_th->End();

		this->End(true);

		main_th.reset();
	}

	return;
}
