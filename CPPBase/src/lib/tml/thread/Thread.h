/**
 * @file
 * @brief Threadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "../constant/ConstantUtil_THREAD.h"
#include "MutexThreadLock.h"
#include "SpinThreadLock.h"


namespace tml {
/**
 * @brief Threadクラス
 *
 * インターフェースパターン
 */
class Thread
{
public: Thread(const tml::Thread &) = delete;
public: tml::Thread &operator =(const tml::Thread &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	std::thread::id id_;
	tml::ConstantUtil::THREAD::TYPE type_;
	std::atomic<bool> run_flg_;
	std::atomic<bool> start_flg_;
	std::atomic<bool> started_flg_;
	std::thread core_;
	std::atomic<bool> core_created_flg_;
	tml::MutexThreadLock core_th_lock_;

protected:
	void Release(void);
	INT Create(const tml::ConstantUtil::THREAD::TYPE);

public:
	Thread();
	virtual ~Thread();

	virtual void Init(void);

	INT Start(void);
	void End(void);
	void Update(void);

	virtual INT OnStart(void) = 0;
	virtual void OnEnd(void) = 0;
	virtual void OnUpdate(void) = 0;

	const std::thread::id &GetID(void) const;
	tml::ConstantUtil::THREAD::TYPE GetType(void) const;
	bool GetRunFlag(void) const;
	void SetRunFlag(const bool);
	bool GetStartFlag(void) const;
	void SetStartFlag(const bool);
	bool IsStarted(void) const;
	INT CreateCore(void);
	void DeleteCore(void);
	void RunCore(void);
};
}


/**
 * @brief GetID関数
 * @return id (id)
 */
inline const std::thread::id &tml::Thread::GetID(void) const
{
	return (this->id_);
}


/**
 * @brief GetType関数
 * @return type (type)
 */
inline tml::ConstantUtil::THREAD::TYPE tml::Thread::GetType(void) const
{
	return (this->type_);
}


/**
 * @brief GetRunFlag関数
 * @return run_flg (run_flag)
 */
inline bool tml::Thread::GetRunFlag(void) const
{
	return (this->run_flg_);
}


/**
 * @brief GetStartFlag関数
 * @return start_flg (start_flag)
 */
inline bool tml::Thread::GetStartFlag(void) const
{
	return (this->start_flg_);
}


/**
 * @brief SetStartFlag関数
 * @param start_flg (start_flag)
 */
inline void tml::Thread::SetStartFlag(const bool start_flg)
{
	this->start_flg_ = start_flg;

	return;
}


/**
 * @brief IsStarted関数
 * @return result_flg (result_flag)<br>
 * false=非開始済み,true=開始済み
 */
inline bool tml::Thread::IsStarted(void) const
{
	return (this->started_flg_);
}
