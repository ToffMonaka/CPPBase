/**
 * @file
 * @brief Processヘッダーファイル
 */
#pragma once


#include "../ConstantUtil.h"


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

protected:
	void Release(void);
	INT Create(void);

public:
	Process();
	virtual ~Process();

	virtual void Init(void);
};
}
