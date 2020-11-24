/**
 * @file
 * @brief ThreadUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <list>
#include <map>
#include "Thread.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief ThreadUtilEngineクラス
 *
 * インターフェースパターン
 */
class ThreadUtilEngine
{
public: ThreadUtilEngine(const ThreadUtilEngine &) = delete;
public: ThreadUtilEngine &operator =(const ThreadUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	/**
	 * @brief STATE構造体
	 */
	typedef struct STATE_
	{
		bool ended_flg;

		/**
		 * @brief コンストラクタ
		 */
		STATE_() :
			ended_flg(false)
		{
			return;
		}
	} STATE;

private:
	std::list<std::unique_ptr<tml::Thread>> th_cont_;
	std::list<tml::Thread *> ready_th_cont_;
	std::list<tml::Thread *> start_th_cont_;
	std::map<std::thread::id, tml::Thread *> start_th_cont_with_th_id_;
	tml::ThreadUtilEngine::STATE stat_;
	tml::SpinThreadLock stat_th_lock_;

protected:
	void Release(void);
	INT Create(void);

public:
	ThreadUtilEngine();
	virtual ~ThreadUtilEngine();

	virtual void Init(void);

	tml::Thread *Get(void);
	INT Start(std::unique_ptr<tml::Thread> &, const bool ready_flg = false);
	INT StartAll(void);
	void End(const bool finish_flg = false);
	void EndAll(const bool delete_flg = false);
	tml::ThreadUtilEngine::STATE GetState(void);
};
}


/**
 * @brief Get関数
 * @return th (thread)<br>
 * nullptr=失敗
 */
inline tml::Thread *tml::ThreadUtilEngine::Get(void)
{
	tml::Thread *th = nullptr;
	auto th_id = std::this_thread::get_id();

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		auto th_itr = this->start_th_cont_with_th_id_.find(th_id);

		if (th_itr != this->start_th_cont_with_th_id_.end()) {
			th = th_itr->second;
		}
	}

	return (th);
}


/**
 * @brief GetState関数
 * @return stat (state)
 */
inline tml::ThreadUtilEngine::STATE tml::ThreadUtilEngine::GetState(void)
{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
	return (this->stat_);
}
