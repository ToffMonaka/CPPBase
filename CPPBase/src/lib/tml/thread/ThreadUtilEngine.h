/**
 * @file
 * @brief ThreadUtilEngineヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <list>
#include <unordered_map>
#include <objbase.h>
#include "MutexThreadLock.h"
#include "SpinThreadLock.h"
#include "MainThread.h"
#include "SubThread.h"


namespace tml {
/**
 * @brief ThreadUtilEngineクラス
 *
 * インターフェースパターン
 */
class ThreadUtilEngine
{
public: ThreadUtilEngine(const tml::ThreadUtilEngine &) = delete;
public: tml::ThreadUtilEngine &operator =(const tml::ThreadUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	/**
	 * @brief STATE構造体
	 */
	typedef struct STATE_
	{
		bool all_started_flg;
		bool all_ended_flg;
		INT exit_code;

		/**
		 * @brief コンストラクタ
		 */
		STATE_() :
			all_started_flg(false),
			all_ended_flg(false),
			exit_code(0)
		{
			return;
		};
	} STATE;

private:
	std::unique_ptr<tml::MainThread> main_th_;
	std::list<std::unique_ptr<tml::SubThread>> sub_th_cont_;
	std::list<tml::Thread *> ready_th_cont_;
	std::list<tml::Thread *> start_th_cont_;
	std::unordered_map<std::thread::id, tml::Thread *> start_th_cont_by_th_id_;
	tml::ThreadUtilEngine::STATE stat_;
	tml::SpinThreadLock stat_th_lock_;
	tml::MutexThreadLock com_th_lock_;

private:
	void Release(void);

public:
	ThreadUtilEngine();
	virtual ~ThreadUtilEngine();

	virtual void Init(void);
	INT Create(void);

	tml::Thread *Get(void);
	INT Start(std::unique_ptr<tml::MainThread> &);
	INT Start(std::unique_ptr<tml::SubThread> &);
	INT StartAll(void);
	void End(const bool finish_flg = false);
	void EndAll(const bool finish_flg = false);
	INT CreateCOM(const DWORD);
	void DeleteCOM(void);
	INT GetExitCode(void);
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
		auto th_itr = this->start_th_cont_by_th_id_.find(th_id);

		if (th_itr != this->start_th_cont_by_th_id_.end()) {
			th = th_itr->second;
		}
	}

	return (th);
}


/**
 * @brief GetExitCode関数
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
inline INT tml::ThreadUtilEngine::GetExitCode(void)
{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
	return (this->stat_.exit_code);
}
