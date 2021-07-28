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
 * @return result (result)<br>
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
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ThreadUtilEngine::Start(std::unique_ptr<tml::MainThread> &th)
{
	if (th == nullptr) {
		return (-1);
	}

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		if ((this->main_th_ != nullptr)
		|| (this->stat_.all_ended_flg)) {
			return (-1);
		}

		auto tmp_th = th.get();

		if (this->stat_.all_started_flg) {
			return (-1);
		} else {
			tmp_th->CreateCore();

			this->start_th_cont_.push_back(tmp_th);
			this->start_th_cont_by_th_id_.insert(std::make_pair(tmp_th->GetID(), tmp_th));
		}

		this->main_th_ = std::move(th);
	}

	if (this->StartAll() < 0) {
		this->EndAll(true);

		return (-1);
	}

	this->EndAll(true);

	return (0);
}


/**
 * @brief Start関数
 * @param th (thread)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ThreadUtilEngine::Start(std::unique_ptr<tml::SubThread> &th)
{
	if (th == nullptr) {
		return (-1);
	}

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		if ((this->main_th_ == nullptr)
		|| (this->stat_.all_ended_flg)) {
			return (-1);
		}

		auto tmp_th = th.get();

		if (this->stat_.all_started_flg) {
			tmp_th->CreateCore();

			this->start_th_cont_.push_back(tmp_th);
			this->start_th_cont_by_th_id_.insert(std::make_pair(tmp_th->GetID(), tmp_th));
		} else {
			this->ready_th_cont_.push_back(tmp_th);
		}

		this->sub_th_cont_.push_back(std::move(th));
	}

	return (0);
}


/**
 * @brief StartAll関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ThreadUtilEngine::StartAll(void)
{
	tml::MainThread *main_th = this->main_th_.get();
	tml::ThreadUtilEngine::STATE stat;

	if (main_th->Start() < 0) {
		this->End(true);

		return (-1);
	}

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_.all_started_flg = true;

		for (auto tmp_th : this->ready_th_cont_) {
			tmp_th->CreateCore();

			this->start_th_cont_.push_back(tmp_th);
			this->start_th_cont_by_th_id_.insert(std::make_pair(tmp_th->GetID(), tmp_th));
		}

		this->ready_th_cont_.clear();

		stat = this->stat_;
	}

	if (main_th->GetWindowHandle() != nullptr) {
		MSG msg = {};

		do {
			while (PeekMessage(&msg, nullptr, 0U, 0U, PM_REMOVE)) {
				if (msg.message == WM_QUIT) {
					{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
						this->stat_.exit_code = static_cast<INT>(msg.wParam);

						main_th->SetStartFlag(false);
					}

					break;
				}

				TranslateMessage(&msg);
				DispatchMessage(&msg);
			}

			if (main_th->GetStartFlag()) {
				main_th->Update();
			}
		} while (main_th->GetStartFlag());
	} else {
		do {
			if (main_th->GetStartFlag()) {
				main_th->Update();
			}
		} while (main_th->GetStartFlag());
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
		auto th_itr = this->start_th_cont_by_th_id_.find(th_id);

		if (th_itr == this->start_th_cont_by_th_id_.end()) {
			return;
		}

		auto th = th_itr->second;

		th->SetStartFlag(false);

		if (finish_flg) {
			this->start_th_cont_.remove(th);
			this->start_th_cont_by_th_id_.erase(th_id);
		}
	}

	return;
}


/**
 * @brief EndAll関数
 * @param finish_flg (finish_flg)
 */
void tml::ThreadUtilEngine::EndAll(const bool finish_flg)
{
	std::unique_ptr<tml::Thread> main_th;
	std::list<std::unique_ptr<tml::Thread>> sub_th_cont;
	tml::ThreadUtilEngine::STATE stat;

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		this->stat_.all_ended_flg = true;

		this->ready_th_cont_.clear();

		for (auto th : this->start_th_cont_) {
			th->SetStartFlag(false);
		}

		if (finish_flg) {
			main_th = std::move(this->main_th_);

			for (auto &sub_th : this->sub_th_cont_) {
				sub_th_cont.push_back(std::move(sub_th));
			}

			this->sub_th_cont_.clear();
		}

		stat = this->stat_;
	}

	if (!sub_th_cont.empty()) {
		sub_th_cont.clear();
	}

	if (main_th != nullptr) {
		if (stat.all_started_flg) {
			main_th->End();

			this->End(true);
		}

		main_th.reset();
	}

	return;
}


/**
 * @brief CreateCOM関数
 * @param init_flg (init_flag)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::ThreadUtilEngine::CreateCOM(const DWORD init_flg)
{
	{tml::ThreadLockBlock th_lock_block(this->com_th_lock_);
		if (FAILED(CoInitializeEx(nullptr, init_flg))) {
			return (-1);
		}
	}

	return (0);
}


/**
 * @brief DeleteCOM関数
 */
void tml::ThreadUtilEngine::DeleteCOM(void)
{
	{tml::ThreadLockBlock th_lock_block(this->com_th_lock_);
		CoUninitialize();
	}

	return;
}
