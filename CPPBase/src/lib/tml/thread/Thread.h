/**
 * @file
 * @brief Threadヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


namespace tml {
/**
 * @brief Threadクラス
 *
 * インターフェースパターン
 */
class Thread
{
public: Thread(const Thread &) = delete;
public: Thread &operator =(const Thread &) = delete;
protected: virtual void InterfaceDummy(void) = 0;

protected:
	void Release(void);
	INT Create(void);

public:
	Thread();
	virtual ~Thread();

	virtual void Init(void);
};
}
