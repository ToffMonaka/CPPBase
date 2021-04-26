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
	std::atomic<bool> loop_flg_;
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

	virtual INT Start(void) = 0;
	virtual void End(void) = 0;
	virtual void Update(void) = 0;

	const std::thread::id &GetID(void) const;
	tml::ConstantUtil::THREAD::TYPE GetType(void) const;
	bool GetLoopFlag(void) const;
	void SetLoopFlag(const bool);
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
