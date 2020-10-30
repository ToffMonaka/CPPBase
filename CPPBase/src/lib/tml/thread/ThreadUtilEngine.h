/**
 * @file
 * @brief ThreadUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
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
		BOOL end_all_flg;

		/**
		 * @brief コンストラクタ
		 */
		STATE_() :
			end_all_flg(FALSE)
		{
			return;
		}
	} STATE;

private:
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
	INT Start(std::unique_ptr<tml::Thread> &);
	void End(void);
	void EndAll(void);
	tml::ThreadUtilEngine::STATE GetState(void);
};


/**
 * @brief Get関数
 * @return th (thread)<br>
 * NULLP=失敗
 */
inline tml::Thread *tml::ThreadUtilEngine::Get(void)
{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
	return (NULLP);
}


/**
 * @brief GetState関数
 * @return stat (state)
 */
inline tml::ThreadUtilEngine::STATE tml::ThreadUtilEngine::GetState(void)
{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
	return (this->stat_);
}
}
