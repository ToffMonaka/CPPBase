/**
 * @file
 * @brief ProcessUtilEngineヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include "Process.h"
#include "../thread/SpinThreadLock.h"


namespace tml {
/**
 * @brief ProcessUtilEngineクラス
 *
 * インターフェースパターン
 */
class ProcessUtilEngine
{
public: ProcessUtilEngine(const ProcessUtilEngine &) = delete;
public: ProcessUtilEngine &operator =(const ProcessUtilEngine &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

public:
	/**
	 * @brief STATE構造体
	 */
	typedef struct STATE_
	{
		bool end_flg;
		INT exit_code;

		/**
		 * @brief コンストラクタ
		 */
		STATE_() :
			end_flg(false),
			exit_code(0)
		{
			return;
		}
	} STATE;

private:
	std::unique_ptr<tml::Process> proc_;
	tml::ProcessUtilEngine::STATE stat_;
	tml::SpinThreadLock stat_th_lock_;

protected:
	void Release(void);
	INT Create(void);

public:
	ProcessUtilEngine();
	virtual ~ProcessUtilEngine();

	virtual void Init(void);

	tml::Process *Get(void);
	INT Start(std::unique_ptr<tml::Process> &);
	void End(const INT exit_code = 0);
	tml::ProcessUtilEngine::STATE GetState(void);
	INT GetExitCode(void);
};


/**
 * @brief Get関数
 * @return proc (process)<br>
 * NULLP=失敗
 */
inline tml::Process *tml::ProcessUtilEngine::Get(void)
{
	tml::Process *proc = NULLP;

	{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
		proc = this->proc_.get();
	}

	return (proc);
}


/**
 * @brief GetState関数
 * @return stat (state)
 */
inline tml::ProcessUtilEngine::STATE tml::ProcessUtilEngine::GetState(void)
{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
	return (this->stat_);
}


/**
 * @brief GetExitCode関数
 * @return exit_code (exit_code)<br>
 * 0以外=失敗
 */
inline INT tml::ProcessUtilEngine::GetExitCode(void)
{tml::ThreadLockBlock th_lock_block(this->stat_th_lock_);
	return (this->stat_.exit_code);
}
}
