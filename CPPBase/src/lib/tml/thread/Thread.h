/**
 * @file
 * @brief Threadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include <thread>
#include <atomic>
#include "MutexThreadLock.h"


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
	std::thread::id th_id_;
	std::thread core_;
	std::atomic<bool> core_created_flg_;
	tml::MutexThreadLock core_th_lock_;
	std::atomic<bool> loop_flg_;

protected:
	void Release(void);
	INT Create(void);

public:
	Thread();
	virtual ~Thread();

	virtual void Init(void);

	virtual INT Start(void) = 0;
	virtual void End(void) = 0;
	virtual void Update(void) = 0;
	const std::thread::id &GetThreadID(void) const;
	INT CreateCore(void);
	void DeleteCore(void);
	void RunCore(void);
	bool GetLoopFlag(void) const;
	void SetLoopFlag(const bool);
};
}


/**
 * @brief GetThreadID関数
 * @return th_id (thread_id)
 */
inline const std::thread::id &tml::Thread::GetThreadID(void) const
{
	return (this->th_id_);
}


/**
 * @brief GetLoopFlag関数
 * @return loop_flg (loop_flag)
 */
inline bool tml::Thread::GetLoopFlag(void) const
{
	return (this->loop_flg_);
}


/**
 * @brief SetLoopFlag関数
 * @param loop_flg (loop_flag)
 */
inline void tml::Thread::SetLoopFlag(const bool loop_flg)
{
	this->loop_flg_ = loop_flg;

	return;
}
