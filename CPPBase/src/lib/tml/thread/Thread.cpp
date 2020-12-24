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
	loop_flg_(true),
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
	switch (this->type_) {
	case tml::ConstantUtil::THREAD::TYPE::MAIN: {
		this->id_ = std::thread::id();

		break;
	}
	}

	this->type_ = tml::ConstantUtil::THREAD::TYPE::NONE;
	this->loop_flg_ = true;

	return;
}


/**
 * @brief Create関数
 * @param type (type)
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Thread::Create(const tml::ConstantUtil::THREAD::TYPE type)
{
	switch (type) {
	case tml::ConstantUtil::THREAD::TYPE::MAIN: {
		this->id_ = std::this_thread::get_id();

		break;
	}
	}

	this->type_ = type;
	this->loop_flg_ = true;

	return (0);
}


/**
 * @brief CreateCore関数
 * @return res (result)<br>
 * 0未満=失敗
 */
INT tml::Thread::CreateCore(void)
{
	if (this->type_ != tml::ConstantUtil::THREAD::TYPE::SUB) {
		return (-1);
	}

	{tml::ThreadLockBlock th_lock_block(this->core_th_lock_);
		if (this->core_created_flg_) {
			return (0);
		}

		this->core_ = std::thread(&tml::Thread::RunCore, this);

		this->id_ = this->core_.get_id();

		this->core_created_flg_ = true;
	}

	return (0);
}


/**
 * @brief DeleteCore関数
 */
void tml::Thread::DeleteCore(void)
{
	if (this->type_ != tml::ConstantUtil::THREAD::TYPE::SUB) {
		return;
	}

	{tml::ThreadLockBlock th_lock_block(this->core_th_lock_);
		if (!this->core_created_flg_) {
			return;
		}

		if (this->core_.joinable()) {
			this->core_.join();
		}

		this->id_ = std::thread::id();

		this->core_created_flg_ = false;
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
		this->Update();
	} while (this->loop_flg_);

	this->End();

	tml::ThreadUtil::End(true);

	return;
}
