/**
 * @file
 * @brief SubThreadヘッダーファイル
 */
#pragma once


#include "../constant/ConstantUtil.h"
#include "Thread.h"


namespace tml {
/**
 * @brief SubThreadクラス
 *
 * インターフェースパターン
 */
class SubThread : public tml::Thread
{
public: SubThread(const tml::SubThread &) = delete;
public: tml::SubThread &operator =(const tml::SubThread &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

private:
	bool com_created_flg_;

private:
	void Release(void);

protected:
	virtual INT OnStart(void) = 0;
	virtual void OnEnd(void) = 0;
	virtual void OnUpdate(void) = 0;

	INT CreateCOM(void);
	void DeleteCOM(void);

public:
	SubThread();
	virtual ~SubThread();

	virtual void Init(void);
	INT Create(void);
};
}


/**
 * @brief Release関数
 */
inline void tml::SubThread::Release(void)
{
	return;
}
