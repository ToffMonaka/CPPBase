/**
 * @file
 * @brief Threadコードファイル
 */


#include "Thread.h"
#include "ThreadUtil.h"
#include "../memory/MemoryUtil.h"


/**
 * @brief コンストラクタ
 */
tml::Thread::Thread() :
	core_flg_(false),
	loop_flg_(true)
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
	this->loop_flg_ = true;

	return;
}


/**
 * @brief Create関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Thread::Create(void)
{
	this->loop_flg_ = true;

	return (0);
}


/**
 * @brief CreateCore関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Thread::CreateCore(void)
{tml::ThreadLockBlock th_lock_block(this->core_th_lock_);
	if (this->core_flg_) {
		return (0);
	}

	this->core_ = std::thread(&tml::Thread::RunCore, this);

	this->th_id_ = this->core_.get_id();

	this->core_flg_ = true;

	return (0);
}


/**
 * @brief DeleteCore関数
 */
void tml::Thread::DeleteCore(void)
{tml::ThreadLockBlock th_lock_block(this->core_th_lock_);
	if (!this->core_flg_) {
		return;
	}

	if (this->core_.joinable()) {
		this->core_.join();
	}

	this->th_id_ = std::thread::id();

	this->core_flg_ = false;

	return;
}


/**
 * @brief RunCore関数
 */
void tml::Thread::RunCore(void)
{
	while (!this->core_flg_) {
	}

	if (this->Start() < 0) {
		tml::ThreadUtil::End(true);

		return;
	}

	do {
		this->Update();
	} while (this->loop_flg_);

	this->End();

	tml::ThreadUtil::End(true);

	return;
}
