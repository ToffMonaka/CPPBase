/**
 * @file
 * @brief Threadコードファイル
 */


#include "Thread.h"
#include "ThreadUtil.h"


/**
 * @brief コンストラクタ
 */
tml::Thread::Thread() :
	type_(tml::ConstantUtil::THREAD::TYPE::NONE),
	run_flg_(false),
	start_flg_(false),
	started_flg_(false),
	core_created_flg_(false)
{
	return;
}


/**
 * @brief デストラクタ
 */
tml::Thread::~Thread()
{
	return;
}


/**
 * @brief Release関数
 */
void tml::Thread::Release(void)
{
	this->DeleteCore();

	return;
}


/**
 * @brief Init関数
 */
void tml::Thread::Init(void)
{
	this->type_ = tml::ConstantUtil::THREAD::TYPE::NONE;
	this->run_flg_ = false;
	this->start_flg_ = false;
	this->started_flg_ = false;

	return;
}


/**
 * @brief Create関数
 * @param type (type)
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::Thread::Create(const tml::ConstantUtil::THREAD::TYPE type)
{
	if (type == tml::ConstantUtil::THREAD::TYPE::NONE) {
		return (-1);
	}

	this->type_ = type;
	this->start_flg_ = true;

	return (0);
}


/**
 * @brief Start関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::Thread::Start(void)
{
	if ((!this->run_flg_) || (!this->start_flg_)) {
		return (-1);
	}

	if (!this->started_flg_) {
		if (this->OnStart() < 0) {
			return (-1);
		}

		this->started_flg_ = true;
	}

	return (0);
}


/**
 * @brief End関数
 */
void tml::Thread::End(void)
{
	if (!this->run_flg_) {
		return;
	}

	if (this->started_flg_) {
		this->OnEnd();

		this->started_flg_ = false;
	}

	return;
}


/**
 * @brief Update関数
 */
void tml::Thread::Update(void)
{
	if ((!this->run_flg_) || (!this->started_flg_)) {
		return;
	}

	this->OnUpdate();

	return;
}


/**
 * @brief SetRunFlag関数
 * @param run_flg (run_flag)
 */
void tml::Thread::SetRunFlag(const bool run_flg)
{
	this->run_flg_ = run_flg;

	return;
}


/**
 * @brief CreateCore関数
 * @return result (result)<br>
 * 0未満=失敗
 */
INT tml::Thread::CreateCore(void)
{
	if (this->type_ == tml::ConstantUtil::THREAD::TYPE::MAIN) {
		this->id_ = std::this_thread::get_id();
		this->run_flg_ = true;
	} else if (this->type_ == tml::ConstantUtil::THREAD::TYPE::SUB) {
		{tml::ThreadLockBlock th_lock_block(this->core_th_lock_);
			if (this->core_created_flg_) {
				return (0);
			}

			this->core_ = std::thread(&tml::Thread::RunCore, this);

			this->id_ = this->core_.get_id();
			this->run_flg_ = true;

			this->core_created_flg_ = true;
		}
	} else {
		return (-1);
	}

	return (0);
}


/**
 * @brief DeleteCore関数
 */
void tml::Thread::DeleteCore(void)
{
	if (this->type_ == tml::ConstantUtil::THREAD::TYPE::MAIN) {
		this->id_ = std::thread::id();
		this->run_flg_ = false;
	} else if (this->type_ == tml::ConstantUtil::THREAD::TYPE::SUB) {
		{tml::ThreadLockBlock th_lock_block(this->core_th_lock_);
			if (!this->core_created_flg_) {
				return;
			}

			if (this->core_.joinable()) {
				this->core_.join();
			}

			this->id_ = std::thread::id();
			this->run_flg_ = false;

			this->core_created_flg_ = false;
		}
	} else {
		return;
	}

	return;
}


/**
 * @brief RunCore関数
 */
void tml::Thread::RunCore(void)
{
	while (!this->core_created_flg_) {
	}

	if (this->Start() < 0) {
		tml::ThreadUtil::End(true);

		return;
	}

	do {
		if (this->start_flg_) {
			this->Update();
		}
	} while (this->start_flg_);

	this->End();

	tml::ThreadUtil::End(true);

	return;
}
