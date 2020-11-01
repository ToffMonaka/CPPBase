/**
 * @file
 * @brief Processヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"
#include <thread>


namespace tml {
/**
 * @brief Processクラス
 *
 * インターフェースパターン
 */
class Process
{
public: Process(const Process &) = delete;
public: Process &operator =(const Process &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	std::thread::id th_id_;

protected:
	void Release(void);
	INT Create(void);

public:
	Process();
	virtual ~Process();

	virtual void Init(void);

	virtual INT Start(void) = 0;
	virtual void End(void) = 0;
	virtual void Update(void) = 0;
	const std::thread::id &GetThreadID(void) const;
};


/**
 * @brief GetThreadID関数
 * @return th_id (thread_id)
 */
inline const std::thread::id &tml::Process::GetThreadID(void) const
{
	return (this->th_id_);
}
}
